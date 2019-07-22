#include <iostream>		
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include "TStyle.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraph2D.h"
#include "TCanvas.h"
#include "TGaxis.h"
#include "TROOT.h"
#include "TSpectrum.h"
#include "TPolyMarker.h"

//void ReverseXAxis (TH1 *h);
//void ReverseYAxis (TH1 *h);
bool StrString(const char *s1,const char *s2);

void data_analysis_pre1(){

  cout<<"Please Select number"<<endl;
  cout<<"1. See_all_channel_statement"<<endl;
  cout<<"2. See_one_channel_statement"<<endl;
  cout<<"3. Making_a_liner_function"<<endl;
  cout<<"4. Rewrite_DAC_number(all)"<<endl;
  cout<<"5. Rewrite_DAC_number(one)"<<endl;

  Int_t value;//選択する番号を読み込ませる
  cin>>value;
  cout<<value<<endl;


  gStyle->SetOptFit(0001);
  const Int_t n=64;//チャンネルの数。どの検出器でも対応できるようにここで個数を決める。                                                                
  Int_t place[n];//位置番号                                                                       
  Int_t esrch[n];//EASIROCモジュールが認識している位置番号                                                                                             
  for(Int_t i=0;i<n;i++)
    {
      place[i]=0;
      esrch[i]=0;
    }




  std::ifstream config("config.txt");
  for(Int_t i=0;i<n;i++)
    {
      config >>esrch[i]>>place[i];//config.txtから読み込む                                                                                            
    }
  config.close();
  
  if (value==1 || value==2)
   {
     
     
     
     
     TH1F *hist[n];//64個のMPPCのそれぞれの波高データのヒストグラム
     //  TH1F *coinhist[n];//thresholdで削った後の波高データの取得
     
     for(int i=0;i<n;i++)
       {
	 std::ostringstream _name;
	 _name <<"ch"<<i;//文字列と変数を連結
	 //             cout<<_name.str()<<endl;
	 std::string hist_name = _name.str();
	 
	 hist[i]=new TH1F(hist_name.c_str(),hist_name.c_str(),4096,0,4096);
	 
	 //  std::ostringstream _cname;
	 // _cname <<"cch"<<i;
	 // std::string chhist_name =_cname.str();
	 // coinhist[i]=new TH1F(chhist_name.c_str(),chhist_name.c_str(),4096,0,4096);
	 
       }
     //n個分のヒストグラムを一気に定義している
     
     
     
     
  
     stringstream ss1;
     
     
     const char* path="./";//文字列型
     DIR *dp;//ファイル一覧を取得
     dirent* entry;//direntとは実行が成功したら0,失敗したら-1を返す
     string filename[4096];
     int filenum=0;
     dp = opendir(path);//path以下のやつを全部開く
     
     
     while((entry=readdir(dp))!=NULL){
       string tmp;
       tmp=entry -> d_name;//読み込んだものの名前を記憶(おそらく拡張子以外のところ)
       cout<<tmp<<endl;
    if(StrString(tmp.c_str(),".dat"))
      {
	filename[filenum]=tmp;
	
        cout<<tmp<<" "<<filenum<<" "<<filename[filenum]<<endl;
	filenum++;
      }
     }
    
     for(int iiii=0;iiii<filenum;iiii++)
       {
	 ss1.str("");
	 
	 ss1<<filename[iiii];
	 std::ifstream hoge(ss1.str().c_str(),std::ios::binary);
	 if(!hoge.is_open())
	   {
	     cout<<"no file"<<endl;
	     return;
	   }
	 else
	   {
	     // cout<<"2:"<<ss1.str()<<"loading"<<endl;
	     cout<<iiii<<": "<<ss1.str()<<" loading "<<endl;  
	   }
	 
	 
	 
	 
	 int buffermem[65];//他のループ内でも使いたいから
	 while(!hoge.eof())
	   {
	     UInt_t val;//datファイル内の情報を格納
	     hoge.read((char*)&val,sizeof(int));//一個目のヘッダーを読み込む
	     //   cout<<val<<endl;
	     // int buffermem[65];
	     if(val==0xffffea0c)//この形式が0xffff0xea0cの場合
	       {
		 hoge.read((char*)&val,sizeof(int));//次の行を読み込む
		 for(int i=0;i<65;++i)
		   {
		     hoge.read((char*)&val,sizeof(int));//65回読み込む意味はヘッダー一行読んだ後MPPC64個分のデータを読み込む
		     if(i>0)//
		       {
			 int buffer=val & 0xffff;//語尾についているのは何?=後ろの2byteを読み込む
			 // cout<<buffer<<endl;
			 buffermem[place[i-1]]=buffer;	    
			 hist[place[i-1]]->Fill(buffer);
			 
		       }
		   }
	       }
	     
	   }
       }
     
     //データ読み込み部
     

     
     
     if(value==1)
       {
	 //ここはGetMaximumの機能とMinimumの機能を用いることで最大値最小値のチャンネルを見つける
	 //そして最大値=ペデスタルの位置を書き出す
	 
	 Int_t pedestal[n];//他のループ内でも使いたいから
	 for(Int_t i=0;i<n;i++)
	   {
	     pedestal[i]=0;
	   }
	 std::ofstream pedestal_posi;
	 pedestal_posi.open("pedestal_position.txt");
	 // pedestal_posi<<"ch"<<" "<<"pedestal_position"<<endl;
	 for(Int_t i=0;i<n;i++)
	   {
	     // Int_t pedestal[i],min;
	     Int_t min;
	     pedestal[i]= hist[i]->GetMaximumBin();//それぞれのポジションの最大値(ペデスタル)位置を取得
	     min=hist[i]->GetMinimumBin();//それぞれのポジションの最小値位置を取得
	     //  hist[i]->Fit("gaus","","",1500,2500);
	     //     cout<<pedestal<<" "<<min<<endl;
	     pedestal_posi<<i<<" "<<pedestal[i]<<endl;//それぞれのチャンネルの最大値を出力
	   }//全てのヒストグラムのペデスタルを抽出
	 // hist[30]->Draw("");
	 
	 
	 
	 
	 

 //ノイズピークを見つける。
 //そして、その位置にマーカーをつけたものをpdfに保存
 //ピーク位置はファイルに書き出す
	 TCanvas *cvs1=new TCanvas("cvs1","My Canvas");
	 cvs1->cd();
	 cvs1->SetLogy();
	 Double_t peak_posi[n];
	 Double_t pe_edge[n]; 
	 Int_t rough_pe=7;//ノイズの下限値としたいp.eの位置
	 std::ofstream four_peak;
	 four_peak.open("four_peak.txt");//1～3p.eを見つける
	 
	 
	 for(Int_t ci=0;ci<n;ci++)//1つ1つのMPPCのピークを見つける
	   {
	     TSpectrum *s1 =new TSpectrum(4);//4つピークを見つける
	     Double_t *xpeaks=s1->GetPositionX();//座標取得
	     // Search<<i<<"\t"<<*xpeaks<<endl;
	     Int_t the_number_of_peak,bin;
	     Double_t source_hist[4096],dest_hist[4096];
	     Float_t fPositionX[100],fPositionY[100];
	     Float_t pede_sear[n];
	     Float_t pe_1_sear[n];
	     Float_t pe_2_sear[n];
	     Float_t pe_3_sear[n];
	     // Float_t pe_4_sear[n];
	     hist[ci]->Draw("");
	     for(Int_t i=0;i<4096;i++)
	       {
		 source_hist[i]=hist[ci]->GetBinContent(i+1);//それぞれのヒストグラムですべてのビン情報を取得
	       }
	     
	     the_number_of_peak=s1->SearchHighRes(source_hist,dest_hist,1000,4,0.0001,kFALSE,3,kFALSE,5);//元のヒストのビン情報、スムージングした後のビン情報、見たいとこまでのビンの数、シグマ、閾値、スムージングのパラメータ
	     
	     for(int i=0;i<the_number_of_peak;i++)
	       {
		 peak_posi[ci]=xpeaks[i];
		 bin=1+Int_t(peak_posi[ci]+0.5);
		 
		 fPositionX[i] = hist[ci]->GetBinCenter(bin);
		 fPositionY[i] = hist[ci]->GetBinContent(bin);//ピーク位置の高さを取得
		 
	       }
	     pede_sear[ci]=xpeaks[0];
	     pe_1_sear[ci]=xpeaks[1];
	     pe_2_sear[ci]=xpeaks[2];
	     pe_3_sear[ci]=xpeaks[3];
	     pe_edge[ci]=pede_sear[ci]+(pe_3_sear[ci]-pe_1_sear[ci])/2.*(rough_pe);
	     
	     four_peak<<pede_sear[ci]<<" "<<pe_1_sear[ci]<<" "<<pe_2_sear[ci]<<" "<<pe_3_sear[ci]<<" "<<pe_edge[ci]<<endl;//ファイルに書き出す
    
	     TPolyMarker * pm = (TPolyMarker*)hist[ci]->GetListOfFunctions()->FindObject("TPolyMarker");//マーカーをつけるやーつ 
	     
	     if (pm) {
	       
	       hist[ci]->GetListOfFunctions()->Remove(pm);
	       
	       delete pm;
	     }
	     
	     pm = new TPolyMarker(the_number_of_peak, fPositionX, fPositionY);
	     hist[ci]->GetListOfFunctions()->Add(pm);
	     pm->SetMarkerStyle(23);
	     pm->SetMarkerColor(kRed);
	     pm->SetMarkerSize(1.3);
   
    

     
     
     
	     if(ci==0)
	       {
		 cvs1->Print("peak_search_1.pdf(");
	       }
	     else if(ci!=63)
       {
         cvs1->Print("peak_search_1.pdf");
       }
	     else
	       {
		 cvs1->Print("peak_search_1.pdf)");//63個のヒストグラムを一気に同じpdfに保存する方法              
	       }
	     
	   }
	 //終わり





	 //ここからcchの検討を開始
	 
	 
	 /*
	   for(int iiii=0;iiii<filenum;iiii++)
	   {
	   ss1.str("");
	   
     ss1<<filename[iiii];
     std::ifstream hoge(ss1.str().c_str(),std::ios::binary);
     if(!hoge.is_open())
       {
	 cout<<"no file"<<endl;
	 return;
       }
     else
       {
	 // cout<<"2:"<<ss1.str()<<"loading"<<endl;
	 cout<<iiii<<": "<<ss1.str()<<" loading "<<endl;  
       }
     
     int buffermem[65];//他のループ内でも使いたいから
     while(!hoge.eof())
       {
	 UInt_t val;//datファイル内の情報を格納
	 hoge.read((char*)&val,sizeof(int));//一個目のヘッダーを読み込む
	 //   cout<<val<<endl;
	 // int buffermem[65];
	 if(val==0xffffea0c)//この形式が0xffff0xea0cの場合
	   {
	     hoge.read((char*)&val,sizeof(int));//次の行を読み込む
	     for(int i=0;i<65;++i)
	       {
		 hoge.read((char*)&val,sizeof(int));//65回読み込む意味はヘッダー一行読んだ後MPPC64個分のデータを読み込む
		 if(i>0)//
		   {
		     int buffer=val & 0xffff;//語尾についているのは何?=後ろの2byteを読み込む
		     // cout<<buffer<<endl;
		     buffermem[esrch[i-1]]=buffer;	    
		     //  hist[esrch[i-1]]->Fill(buffer);
		     
		   }
	       }
	     bool flag1=false;
	     bool flag2=false;
	     bool flag3=false;
	     bool flag4=false;
	     Int_t layer1[16];
	     Int_t layer2[16];
	     Int_t layer3[16];
	     Int_t layer4[16];
	     for(int j=0;j<16;j++)
	       {
		 layer1[j]=0;
		 layer2[j]=0;
		 layer3[j]=0;
		 layer4[j]=0;
	       }



	     for(int j=0;j<16;j++)
	       {
		 if(buffermem[j]>threshold1[j])
		   {
		     layer1[j]=buffermem[j];
		     flag1=true;
		   }
	       }

	     for(int j=16;j<32;i++)
	       {
		 if(buffermem[j]>threshold1[j])
		   {
		     layer2[j]=buffermem[j];
		     flag2=true;
		   }
	       }

	     for(int j=32;j<48;j++)
	       {
		 if(buffermem[j]>threshold[j])
		   {
		     layer3[j]=buffermem[j];
		     flag3=true;
		   }
	       }
	     for(int j=48;j<64;j++)
	       {
		 if(buffermem[j]>threshold[j])
		   {
		     layer4[j]=buffermem[j];
		     flag4=true;
		   }
	       }

	     if(flag1 && flag2 && flag3 && flag4)
	       {
		 for(int j=0;j<16;j++)
		   {	
		     if(layer1[j]>0)
		       {
		     coinhist[j]->Fill(layer1[j])
		       }		      
		   }

		 for(int j=16;j<32;j++)
		   {
		     if(layer[j]>0)
		       {
			 coinhist[j]->Fill(layer[j])
			   }
		   }

		 for(int j=32;j<48;j++)
		   {
		     if(layer[j]>0)
		       {
			 coinhist[j]->Fill(layer[j])
			   }
		   }


		 for(int j=48;j<64;j++)
		   {
		     if(layer[j]>0)
		       {
			 coinhist[j]->Fill(layer[j])
			   }
		   }
 
	       }
	      

	   }


	   }
	 
       }
     
   }
 */





 
//ここからノイズ幅のn倍をすることで簡単に閾値を決めてガウスフィッティング


	 TCanvas *cvs2=new TCanvas("cvs2","My Canvas");//このヒストグラムはp.eピークを見つけるのが目的                                                       
	 cvs2->cd();
	 cvs2->SetLogy();
	 std::ofstream Fitting_element1;
	 Fitting_element1.open("fitting_element_1.txt");//パラメータを保存するためのファイル
	 Fitting_element1<<"Constant"<<"     "<<"Mean"<<"     "<<"Sigma"<<endl;
	 Double_t p0[n],p1[n],p2[n];//関数の3つのパラメータ
 Double_t p1error[n];//p1のエラーバー
 
 for(int i=0;i<n;i++)
   {    
     
     TF1 *f1=new TF1("f1","gaus",1000,3200);
     hist[i]->Draw("");
     hist[i]->Fit("f1","","",1000,3200);
     f1->Draw("same");
     
     if(i==0)
       {
	 cvs2->Print("fit_ch_hist.pdf(");
       }
     else if(i!=63)
       {
	 cvs2->Print("fit_ch_hist.pdf");
       }
     else
       {
	 cvs2->Print("fit_ch_hist.pdf)");//63個のヒストグラムを一気に同じpdfに保存する方法
       }
     p0[i]=f1->GetParameter(0);
     p1[i]=f1->GetParameter(1);
     p1error[i]=f1->GetParError(1);
     p2[i]=f1->GetParameter(2);
     // cout<<p0[i]<<" "<<p1[i]<<" "<<p2[i]<<endl;
     Fitting_element1<<p0[i]<<" "<<p1[i]<<" "<<p2[i]<<endl;
     
     
   }
 //ここではフィッテングすることによってミュオンイベントのピークを見つけた段階
 
 
 

 //cvs3は全チャンネルのペデスタルの位置を書き出す
 //cvs4はフィッティングによって求めた全チャンネルのミュオンピークの位置を書き出す
 
 
 Int_t index=64;//グラフのプロット数
 Int_t x[n];//チャンネルナンバー
 Double_t xd[n];//チャンネルナンバー
 Double_t zero[n];
 for(int i=0;i<64;i++)
   {
     xd[i]=i;
     x[i]=i;
     zero[i]=0;
   }
 
 TCanvas *cvs3=new TCanvas("cvs3","Pedestal_Position");
 TGraph *gr1=new TGraph(index,x,pedestal);//int型じゃないとだめ
 
 gr1->Draw("AP");
 gr1->SetTitle("Pedestal_Position");
 gr1->GetYaxis()->SetTitle("Pedestal_Position");
 gr1->GetXaxis()->SetTitle("MPPC Channel Number");
 gr1->SetMarkerSize(1);
 gr1->SetMarkerStyle(20);
 gr1->GetYaxis()->CenterTitle();
 gr1->GetXaxis()->CenterTitle();
 
 
 
 TCanvas *cvs4=new TCanvas("cvs4","Peak_Position");
 TGraphErrors *gr2=new TGraphErrors(index,xd,p1,zero,p1error);//このグラ\フの目的はちゃんえねるごとのペデスタル位置を表したもの.最初の3つはint型、エラーバーはdouble型
 
 gr2->Draw("AP");
 gr2->SetTitle("Peak_search");
 gr2->GetYaxis()->SetTitle("Peak Channel");
 gr2->GetXaxis()->SetTitle("MPPC Channel Number");
 gr2->SetMarkerSize(1);
 gr2->SetMarkerStyle(4);
 gr2->GetYaxis()->CenterTitle();
 gr2->GetXaxis()->CenterTitle();
 gr2->GetYaxis()->SetRangeUser(0,2500);
 
 cvs3->Print("gain_adjustment.pdf(");
 
 cvs4->Print("gain_adjustment.pdf)");
 


    }
 
  if(value==2)//ここは個別でゲイン調整を行いたい場合
    {
      Int_t place_num,esr_num;
      cout<<"please select MPPC position"<<endl;
      cin>>place_num;

     
      TCanvas *cvs1=new TCanvas("cvs1","My Canvas");
      cvs1->cd();
      cvs1->SetLogy();
      TSpectrum *s1=new TSpectrum(4);
      Double_t *xpeaks=s1->GetPositionX();
      Int_t the_number_of_peak,bin;
      Double_t source_hist[4096],dest_hist[4096];
      Int_t rough_pe=7;
      Double_t peak_posi;
      Double_t pede_sear,pe_1_sear,pe_2_sear,pe_3_sear,pe_edge;
      Float_t fPositionX[100],fPositionY[100];
      Double_t p0,p1,p2;//関数の3つのパラメータ                                                                                         
      Double_t p1error;//p1のエラーバー  
      hist[place_num]->Draw("");
      for(int i=0;i<4096;i++)
	{
	  source_hist[i]=hist[place_num]->GetBinContent(i+1);

	}
      the_number_of_peak=s1->SearchHighRes(source_hist,dest_hist,1000,4,0.0001,kFALSE,3,kFALSE,5);
      for(int i=0;i<the_number_of_peak;i++)
	{
	  peak_posi=xpeaks[i];
	  bin=1+Int_t(peak_posi+0.5);
	  fPositionX[i] = hist[place_num]->GetBinCenter(bin);
	  fPositionY[i] = hist[place_num]->GetBinContent(bin);//ピーク位置の高さを取得        
	}
      pede_sear=xpeaks[0];
      pe_1_sear=xpeaks[1];
      pe_2_sear=xpeaks[2];
      pe_3_sear=xpeaks[3];
      pe_edge=pede_sear+(pe_3_sear-pe_1_sear)/2.*(rough_pe);
      TPolyMarker * pm = (TPolyMarker*)hist[place_num]->GetListOfFunctions()->FindObject("TPolyMarker");//マーカーをつけるやーつ
      if (pm) {
	
	hist[place_num]->GetListOfFunctions()->Remove(pm);
	
	delete pm;
      }
      
      pm = new TPolyMarker(the_number_of_peak, fPositionX, fPositionY);
      hist[place_num]->GetListOfFunctions()->Add(pm);
      pm->SetMarkerStyle(23);
      pm->SetMarkerColor(kRed);
      pm->SetMarkerSize(1.3);

      TCanvas *cvs2=new TCanvas("cvs2","My Canvas");

      cvs2->cd();
      cvs2->SetLogy();
      TF1 *f1=new TF1("f1","gaus",pe_edge,3000);
      hist[place_num]->Draw("");
      hist[place_num]->Fit("f1","","",pe_edge,3000);


      p0=f1->GetParameter(0);
      p1=f1->GetParameter(1);
      p1error=f1->GetParError(1);
      p2=f1->GetParameter(2);
      cout<<"Heigh:"<<p0<<endl;
      cout<<"Center_position:"<<p1<<endl;
      cout<<"Sigma:"<<p2<<endl;                   

    }





   }


  /*

 if(value==3)//最小二乗法することで電圧とピークチャンネルの一次関数を出す。
   {
     Double_t first_V,second_V;
     cout<<"What is first measurement bias Voltage"<<endl;
     cin>>first_V;
     cout<<"What is second measurement bias Voltage"<<endl;
     cin>>second_V;

 
     //一回目の計測時DAC
     std::ifstream DAC1_1("Input8bitDAC1_180506.txt");//0～31のチャンネルのDACを保存(EASIROCの)
     std::ifstream DAC2_1("Input8bitDAC2_180506.txt");//32～63のチャンネルのDACを保存 
     string buf1_1[9],buf2_1[9];
     //2回目の計測時DAC
     std::ifstream DAC1_2("Input8bitDAC1_180507.txt");
     std::ifstream DAC2_2("Input8bitDAC2_180507.txt");
     string buf1_2[9],buf2_2[9];

     std::ifstream Fitting_element1;                       
     Fitting_element1.open("fitting_element_1.txt");//一回目の計測時のピーク
     std::ifstream Fitting_element2;    
     Fitting_element2.open("fitting_element_2.txt");//二回目の計測時のピーク
     std::ofstream liner_function;
     liner_function.open("liner_function_parameter.txt");//一次関数のaとbを保存
     Double_t x[n][2],y[n][2];//xが電圧、yがピーク
     Double_t a[n],b[n];//y=ax+b
     int ch_u1[50],ch_u2[50],ch_d1[50],ch_d2[50];
     Double_t sum_x[n],sum_y[n],sum_xy[n],sum_xx[n];
     for(int i=0;i<n;i++)
       {
	 a[i]=0;//初期化
	 b[i]=0;//初期化
	 sum_x[i]=0;//初期化
         sum_y[i]=0;//初期化
         sum_xx[i]=0;//初期化
         sum_xy[i]=0;//初期化

       for(int j=0;j<2;j++)
	 {
	   x[i][j]=0;//初期化
	   y[i][j]=0;//初期化
	 }
       }


     for(int i=0;i<9;i++)
       {
         getline(DAC1_1,buf1_1[i]);//                                                                 
         getline(DAC2_1,buf2_1[i]);//それぞれのファイルを一列ずつ読み込む               
	 getline(DAC1_2,buf1_2[i]);//                                       
         getline(DAC2_2,buf2_2[i]);//それぞれのファイルを一列ずつ読み込む
	 //	 cout<<buf2_2[i]<<endl;                                                                                                                                        
       }
     istringstream iss1_1(buf1_1[8]);//これで最後の文字列を分割     
     istringstream iss2_1(buf2_1[8]);//istringstreamは文字列を切り出す機能 
     istringstream iss1_2(buf1_2[8]);
     istringstream iss2_2(buf2_2[8]);                                             
     Int_t s1_1,s2_1,s1_2,s2_2;//                                                                                                      
     Int_t i=0;
     Int_t j=0;
     Int_t k=0;
     Int_t l=0;
     while(iss1_1>>s1_1)
       { 
         ch_u1[i]=s1_1;
	 // cout<<ch_u1[i]<<endl;  
         i++;
       }
    
     while(iss2_1>>s2_1)
       {
	 ch_d1[j]=s2_1;
	 j++;
       }

     while(iss1_2>>s1_2)
       { 
         ch_u2[k]=s1_2;        
         k++;
       }

     while(iss2_2>>s2_2)
       {
         ch_d2[l]=s2_2;       
	 l++;
       }

     for(int i=0;i<32;i++)
       {
	 x[place[i]][0]=(ch_u1[i+3]-256)*0.02+first_V;//位置番号に変換+DAC値の最初の3つのデータは無視
	 x[place[i+32]][0]=(ch_d1[i+3]-256)*0.02+first_V;
	 x[place[i]][1]=(ch_u2[i+3]-256)*0.02+second_V;
	 x[place[i+32]][1]=(ch_d2[i+3]-256)*0.02+second_V;
       }

         for(int i=0;i<32;i++)
	 {
	 cout<<x[i][0]<<" "<<x[i+32][0]<<endl;
	 cout<<x[i][1]<<" "<<x[i+32][1]<<endl;
	 
       }

    

     for(int i=0;i<n;i++)
       {
	 Double_t dummy1,dummy2,dummy3,dummy4;
	 Fitting_element1>>dummy1>>y[i][0]>>dummy2;//データ格納
	 Fitting_element2>>dummy3>>y[i][1]>>dummy4;//データ格納
	 	 cout<<y[i][0]<<" "<<y[i][1]<<endl;
       }




     for(int i=0;i<n;i++)
       {
        
	 for(int j=0;j<2;j++)
	   {
	     sum_x[i]=sum_x[i]+x[i][j];//最小二乗法のための1つ1つのパラメータを計算
	     sum_y[i]=sum_y[i]+y[i][j];
	     sum_xx[i]=sum_xx[i]+(x[i][j]*x[i][j]);
	     sum_xy[i]=sum_xy[i]+(x[i][j]*y[i][j]);    
                                      
	   }
       }

     for(int i=0;i<n;i++)
       {
	 a[i]=(2*sum_xy[i]-(sum_x[i]*sum_y[i]))/(2*sum_xx[i]-sum_x[i]*sum_x[i]);
	 b[i]=(sum_xx[i]*sum_y[i]-sum_xy[i]*sum_x[i])/(2*sum_xx[i]-sum_x[i]*sum_x[i]);
      
	 if(finite(a[i])==0 || finite(b[i])==0 )
	   {
	     liner_function<<finite(a[i])<<"   "<<finite(b[i])<<endl;   
	   }
	 else if(a[i]>0)
	   {
	     liner_function<<a[i]<<"   "<<b[i]<<endl;
	   }
	 else
	   {
	     a[i]=0;
	     b[i]=0;
	     liner_function<<a[i]<<"   "<<b[i]<<endl; 
	   }
       }

   }

  





  
 if(value==4)
   {
    

     Double_t biasV;
     cout<<"what is bias Voltage ?"<<endl;
     cin >>biasV; 
     std::ifstream DAC1("Input8bitDAC1.txt");//0～31のチャンネルのDACを保存(EASIROCの)  
     std::ifstream DAC2("Input8bitDAC2.txt");//32～63のチャンネルのDACを保存
     string buf1[9],buf2[9];

     for(int i=0;i<9;i++)
       {
	 getline(DAC1,buf1[i]);//
	 getline(DAC2,buf2[i]);//それぞれのファイルを一列ずつ読み込む
	 // cout<<buf1[i]<<endl;                                             
	 // cout<<buf2[i]<<endl;                                             
       }
     DAC1.close();
     DAC2.close();

     istringstream iss1(buf1[8]);//これで最後の文字列を分割                                                                    
     istringstream iss2(buf2[8]);//istringstreamは文字列を切り出す機能       
     int s1,s2;//
     int ch_u[40],ch_d[40];//40に意味はない。余裕をもって40
     int i=0;
     int j=0;
     Double_t a[n],b[n];
  while(iss1>>s1)
       {
	 //       cout<<s<<endl;                                             
	 ch_u[i]=s1;
	 //   cout<<ch_u[i]<<endl;                                          
	 i++;
       }
  //     cout<<i<<endl;
     
 while(iss2>>s2)
   {
     ch_d[j]=s2;
     //  cout<<ch_d[j]<<endl;
     j++;
   }
 // cout<<j<<endl;





 std::ifstream moving_parameter;
 moving_parameter.open("moving_channel.txt");
 std::ifstream liner_function;
 liner_function.open("liner_function_parameter.txt");
 Double_t new_DAC[n];

 for(int i=0;i<n;i++)
   {
     new_DAC[i]=0;
   }

 for(int i=0;i<n;i++)
   {
     liner_function>>a[i]>>b[i];
     // cout<<a[i]<<" "<<b[i]<<endl;
     new_DAC[i]=(((2000-b[i])/a[i])-biasV)/0.02+256;
     if(finite(new_DAC[i])==0 || new_DAC[i]>510 ||new_DAC[i]<255)
       {
	 new_DAC[i]=400;
	 cout<<"channel"<<i<<" is failed "<<endl;
       }
     //  cout<<new_DAC[i]<<endl;
   }

 


 std::ofstream DAC11("Input8bitDAC1.txt");
 for(int i=0;i<8;i++)
   {
     DAC11<<buf1[i]<<endl;

   }
 
 DAC11<<ch_u[0]<<"       "<<ch_u[1]<<"        "<<ch_u[2]<<"        ";
 
 for(int i=0;i<32;i++)
   {
     //     cout<<place[i]<<endl;
     //  cout<<new_DAC[place[i]]<<endl;
     // int k;
     // k=new_DAC[place[i]];
     DAC11<<round(new_DAC[place[i]])<<"  ";
   }




  for(int i=0;i<32;i++)
   {
                                                                          
      DAC11<<ch_u[i+3]<<"  ";
    }
 
 std::ofstream DAC22("Input8bitDAC2.txt");
 for(int j=0;j<8;j++)
   {
     DAC22<<buf2[j]<<endl;
   }

 DAC22<<ch_d[0]<<"       "<<ch_d[1]<<"        "<<ch_d[2]<<"        ";
 

 for(int i=32;i<64;i++)
   {
     int l;
     DAC22<<round(new_DAC[place[i]])<<"  ";

   }
 
for(int j=0;j<32;j++)
   {
     DAC22<<ch_d[j+3]<<"  ";
   }
 




   }


 if(value==5)//個別にDACを入力
   {

     Int_t mppc_number,DAC_value;
     cout<<"What is MPPC number?"<<endl;
     cin>>mppc_number;//変えたいMPPCの位置番号を選択
     // cout<<"Please input DAC"<<endl;
     //  cin>>DAC_value;//DACを入力

       if(mppc_number>=0 & mppc_number<=31)
	 {
	   std::ifstream DAC1("Input8bitDAC1.txt");//0～31のチャンネルのDACを保存(EASIROCの) 
	   string buf1[9];

	   for(int i=0;i<9;i++)
	     {
	       getline(DAC1,buf1[i]);//9列分読み込む
	     }
	   DAC1.close();
	   istringstream iss1(buf1[8]);//これで最後の文字列を分割 
	   Int_t s1;
	   Int_t ch_u[40];
	   Int_t i=0;

	   while(iss1>>s1)
	     {
	       ch_u[i]=s1;
	       i++;
	     }


	   for(int i=0;i<32;i++)
	     {
	       if(mppc_number==place[i])
		 {
		   cout<<ch_u[i+3]<<endl;
		   cout<<"Please input DAC"<<endl;
		   cin>>DAC_value;
		   ch_u[i+3]=DAC_value;
		 }
	     }
	   
	   
	   std::ofstream DAC11("Input8bitDAC1.txt");
	   for(int i=0;i<8;i++)
	     {
	       DAC11<<buf1[i]<<endl;
	     }
	   DAC11<<ch_u[0]<<"       "<<ch_u[1]<<"        "<<ch_u[2]<<"        ";

	   for(int i=0;i<32;i++)
	     {           
	       DAC11<<ch_u[i+3]<<"  ";
	     }
	 }



       if(mppc_number>=32 & mppc_number<=63)
	 {
	   std::ifstream DAC2("Input8bitDAC2.txt");//32～63のチャンネルのDACを保存               
	   string buf2[9]; 
	   for(int i=0;i<9;i++)
	     {
	       getline(DAC2,buf2[i]);//それぞれのファイルを一列ずつ読み込む                                                                             
	     }
	   DAC2.close();
	   
	   
	   istringstream iss2(buf2[8]);//istringstreamは文字列を切り出す機能 
	   Int_t s2;//
	   Int_t ch_d[40];//40に意味はない。余裕をもって40                                                                                       
	   Int_t j=0;
	   
     
	   while(iss2>>s2)
	     {
	       ch_d[j]=s2;
		 j++;
	     }

	   for(int i=32;i<64;i++)
             {
               if(mppc_number==place[i])
                 {
		   cout<<ch_d[i-29]<<endl;
		   cout<<"Please input DAC"<<endl;
                   cin>>DAC_value;
                   ch_d[i-29]=DAC_value;
                 }
             }
	   

	   
	   std::ofstream DAC22("Input8bitDAC2.txt");
	   for(int j=0;j<8;j++)
	     {
	       DAC22<<buf2[j]<<endl;
	     }
	   DAC22<<ch_d[0]<<"       "<<ch_d[1]<<"        "<<ch_d[2]<<"        ";
	   
	   
	   for(int i=0;i<32;i++)
	     {
	       DAC22<<ch_d[i+3]<<"  ";
	     }
	   
	   
	   
	   
	 }
       
       
   }
 
*/


}



bool StrString(const char*s1,const char *s2)//サブルーチンみたいなもの
{
  int n;
  n=strlen(s2);//strlenは文字列の長さを返す

  while(1){
    s1=strchr(s1,s2[0]);//s1の最初からs2[0]の文字を探す。その文字がなければNULLを返す

    if(s1==NULL)
      
	return false;
      
    if(strncmp(s1,s2,n)==0)//s1とs2を前からn文字分比べる、s1=s2の場合0を返す
      
	return true;
	s1++;      

  }


}
