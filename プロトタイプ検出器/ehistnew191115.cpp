#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <bitset>
#include "TStyle.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TGaxis.h"
#include "TROOT.h"
void ReverseXAxis (TH1 *h);
void ReverseYAxis (TH1 *h);
bool StrString(const char *s1,const char *s2);

void ehistnew190711(){
  /* cout<<"Please Select number"<<endl;
  cout<<"1.See coincidence event"<<endl;
  cout<<"2.Output_vector_event"<<endl;
  cout<<"3.Make_attenuation_map"<<endl;
  cout<<"4.Make_attenuation_map(cross_section)"<<endl;
  cout<<"5.Compare_two_data"<<endl; */
  // Int_t value;
  // cin>>value;
  // cout<<value<<endl;


  gStyle->SetPalette(1);  

    gStyle->SetOptFit(0001);
    const int n=64;//チャンネルの数。どの検出器でも対応できるようにここで個数を決める。                                                              
    Int_t place[n];//位置番号                                                 
    Int_t esrch[n];//EASIROCモジュールが認識している位置番号                  
    Int_t count_ij[31][31];
    Int_t x_vec=0;
    Int_t y_vec=0;    
    for(Int_t i=0;i<n;i++)
      {
	place[i]=0;
	esrch[i]=0;
      }


    for(Int_t i=0;i<31;i++)
      {
	for(Int_t j=0;j<31;j++)
	  {
	    count_ij[i][j] = 0;
	  }
      }

    std::ifstream config("config.txt");//config.txtから読み込み
    for(Int_t i=0;i<n;i++)
      {
	config >>esrch[i]>>place[i];//config.txtから読み込む    
      }
    config.close();
    
    
    Double_t ped[n],pe1[n],pe2[n],pe3[n],thresh_ch[n],dummy;
    for(Int_t i=0;i<n;i++)
      {
	ped[i]=0;
	thresh_ch[i]=0;
      }
    
    // Double_t ped[64];
    std::ifstream pedestal("pedestal_position.txt");
    for(Int_t i=0;i<n;i++)
      {
	Double_t dummy;
	pedestal>>dummy>>ped[i];
	thresh_ch[i]=1000;
      }//今はここでthresholdを一括に決めている
    //    thresh_ch[5]=1400;
    TH2D *test2d1 = new TH2D("test2d1","",16,15.5,31.5,16,-0.5,15.5);       
    TH2D *test2d2 = new TH2D("test2d2","",16,47.5,63.5,16,31.5,47.5);

    TH1F *coinhist[n];//64個のMPPCのコインシデンスを取った波高データのヒストグラム
    for(Int_t i=0;i<n;i++)
      {
	std::ostringstream _cname;
	_cname<<"cch"<<i;
	std::string chhist_name = _cname.str();
	coinhist[i]=new TH1F(chhist_name.c_str(),chhist_name.c_str(),512,0,4096);
      }


    stringstream ss1;
    
    const char* path="./";//文字列型                                        
    DIR *dp;//ファイル一覧を取得                                            
    dirent* entry;//direntとは実行が成功したら0,失敗したら-1を返す          
    string filename[4096];
    int filenum=0;
    dp = opendir(path);//path以下のやつを全部開く



    while((entry=readdir(dp))!=NULL)
      {
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





    for(Int_t iiii=0;iiii<filenum;iiii++)
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

int countertwelve=0;
	Int_t buffermem[65];//他のループ内でも使いたいから                         
		while(!hoge.eof())
	//for(int crrr=0;crrr<10;crrr++)
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
		    if(i==0)
                      {int buffero=val & 0b11111111111100000000000000000000;
			int EvNUM=buffero >>20;
			int time_lag_int=val & 0b00000000000011111111111111111111;
			// cout << static_cast<std::bitset<32> >(val) << std::endl;
			//								    cout<<static_cast<std::bitset<32> >(buffero)<<endl;
			cout<<countertwelve<<" "<<EvNUM<<endl;
			cout<<time_lag_int<<endl;
if(buffero==4095){countertwelve++;}}                              
		    if(i>0)//                                                      
		      {
			int buffer=val;//語尾についているのは何?=後ろの2byteを読み込む
			//	std::cout << static_cast<std::bitset<8> >(val) << std::endl;                                 
			//cout<<buffer<<endl;                                     
			buffermem[place[i-1]]=buffer;
			//			hist[place[i-1]]->Fill(buffer);
		      }
		  }

		Int_t maxADCch1=0;//1シート目に一番波高の高いMPPCのADC-pedestal値
		Int_t maxADCch1_2nd=0;//1シート目に2番波高の高いMPPCのADC-pedestal値
		Int_t maxch1=0;	//1シート目の一番波高の高い位置番号
		Int_t maxch1_2nd=0;//1シート目の2番目に波高の高い位置番号
		bool flag1=false;

		for(Int_t j=0;j<16;j++)
		  {
		    if(buffermem[j]-ped[j]>maxADCch1)
		      {
			maxADCch1_2nd=maxADCch1;
			maxch1_2nd=maxch1;
			maxADCch1=buffermem[j]-ped[j];
			maxch1=j;
		      }//1シートのなかで一番波高の高いMPPCのADC-Pedestalの値を探す
		  }
		maxADCch1+=ped[maxch1];//引いていたペデスタル値を直してADC値に
	       
		//		    cout<<maxADCch1<<endl;
		if(maxADCch1>thresh_ch[maxch1])
		  {
		    // cout<<maxch1<<" "<<maxch1_2nd<<endl;
		    if(maxADCch1_2nd>thresh_ch[maxch1_2nd] && abs(maxch1 - maxch1_2nd) > 1)
		      {
			flag1=false;
		      }
		    else
		      {
			flag1=true;
		      }
		    
		  }	
	  
		Int_t maxADCch2=0;//2シート目の一番波高の高いMPPCのADC-pedestal値
		Int_t maxADCch2_2nd=0;//2シート目の2番目に波高の高いMPPCのADC-pedestal値
		Int_t maxch2=0;//2シート目の一番波高の高い位置番号
		Int_t maxch2_2nd=0;//2シート目の2番目に波高の高い位置番号
		bool flag2=false;//
		for(Int_t j=16;j<32;j++)
		  {
		    if(buffermem[j]-ped[j]>maxADCch2)
                      {
                        maxADCch2_2nd=maxADCch2;
                        maxch2_2nd=maxch2;
			maxADCch2=buffermem[j]-ped[j];
                        maxch2=j;
		      }
		  }

		maxADCch2+=ped[maxch2];

		if(maxADCch2>thresh_ch[maxch2])
                  {
		    if(maxADCch2_2nd>thresh_ch[maxch2_2nd] && abs(maxch2-maxch2_2nd)>1)
		      {
			// cout<<maxADCch2<<endl;                            
			flag2=false;
		      }
		    else
		      {
			flag2=true;
		      }
		  }
	      


		Int_t maxADCch3=0;
                Int_t maxADCch3_2nd=0;
                Int_t maxch3=0;
                Int_t maxch3_2nd=0;
                bool flag3=false;
		for(Int_t j=32;j<48;j++)
                  {
                    if(buffermem[j]-ped[j]>maxADCch3)
                      {
			maxADCch3_2nd=maxADCch3;
			maxch3_2nd=maxch3;
			maxADCch3=buffermem[j]-ped[j];
			maxch3=j;
                      }
                  }
		
		maxADCch3+=ped[maxch3];
                if(maxADCch3>thresh_ch[maxch3])
                  {
		    //     cout<<maxADCch3<<endl;
		    if(maxADCch3_2nd>thresh_ch[maxch3_2nd] && abs(maxch3 - maxch3_2nd)>1)
		      {
			flag3=false;
		      }
		    else
		      {
			flag3=true;
		      }
		  }
		Int_t maxADCch4=0;
		Int_t maxADCch4_2nd=0;
		Int_t maxch4=0;
		Int_t maxch4_2nd=0;
                bool flag4=false;
		

		for(Int_t j=48;j<64;j++)
                  {
                    if(buffermem[j]-ped[j]>maxADCch4)
                      {
                        maxADCch4_2nd=maxADCch4;
                        maxch4_2nd=maxch4;
                        maxADCch4=buffermem[j]-ped[j];
                        maxch4=j;
                      }
                  }
		
		maxADCch4+=ped[maxch4];
		if(maxADCch4>thresh_ch[maxch4])
		  {
		    // cout<<maxADCch4<<endl;
		    if(maxADCch4_2nd>thresh_ch[maxch4_2nd] && abs(maxch4 - maxch4_2nd)>1)
		      {
			flag4=false;
		      }
		    else
		      {
			flag4=true;
		      }
		  }
		


		if(flag1 && flag2 && flag3 && flag4)//全部でフラグが立つ、つまり全部の層を通過したと判断した場合にプロット
		  {
		    x_vec = (63-maxch4) - (31-maxch2) + 15;
		    y_vec = (maxch3-32) - maxch1 + 15;
		    coinhist[maxch1]->Fill(maxADCch1);
		    coinhist[maxch2]->Fill(maxADCch2);
		    coinhist[maxch3]->Fill(maxADCch3);
		    coinhist[maxch4]->Fill(maxADCch4);
		    count_ij[x_vec][y_vec]++;
	// if(x_vec==15 && y_vec==15)
	//	     {
		    test2d1 -> Fill(47-maxch2,15-maxch1);
		    test2d2 -> Fill(111-maxch4,79-maxch3);
		    // }
		    /*		     if(maxch1==4 ||maxch1==6)
		     {
				cout<<maxADCch1<<" "<<buffermem[7]<<" "<<buffermem[5]<<endl;
				}*/

		  
		    /* if(maxch1==5)

		      {
			//	std::ofstream a("a.txt");

			//	cout<<maxch2<<endl;
			a<<maxADCch1<<" "<<maxch3<<" "<<maxch4<<" "<<maxch2<<endl;
			}*/

		  }	
	      }



	  }
      
	    
      }

    TCanvas *cvs1=new TCanvas("cvs1","My Canvas");
      cvs1->cd();
      Double_t Entries[n];//それぞれのエントリー数
      Double_t EntryErrors[n];
      for(Int_t i=0;i<n;i++)
	{
	  Entries[i]=0;
	  EntryErrors[i]=0;
	}
std::ofstream each("each_entries.txt");
      for(Int_t i=0;i<n;i++)
	{
	  coinhist[i]->GetYaxis()->SetRangeUser(0,100);
	  coinhist[i]->Draw("");
	  if(i==0)
	  {
	    cvs1->Print("coincident_hist64.pdf(");
	  }
	  else if(i!=63)
	    {
	      cvs1->Print("coincident_hist64.pdf");
	  }
	  else
	    {
	      cvs1->Print("coincident_hist64.pdf)");
	      
	    }//64個のヒストを1個のPDFに表示する方法
	  Entries[i]=coinhist[i]->GetEntries();
	  EntryErrors[i]=sqrt(Entries[i]);
	  cout<<Entries[i]<<endl;
each<<Entries[i]<<endl;
	}


      TCanvas *cvs2=new TCanvas("cvs2","My Canvas");
      cvs2->cd();
      //  cvs2->SetLogy();
      Double_t CONSTANT[n],MEANS[n],SIGMA[n];
      Double_t MEANS_error[n];
      std::ofstream coin_para("fitting_parameter_coin.txt");
      for(Int_t i=0;i<n;i++ )
	{
	  TF1 *f1=new TF1("f1","gaus",1000,3200);
	  coinhist[i]->Draw("");
	  coinhist[i]->Fit("f1"," ","",1000,3000);//lは最尤法を使う
	  coinhist[i]->GetYaxis()->SetRangeUser(0,600);
	  f1->Draw("same");
	  if(i==0)
	    {
	      cvs2->Print("fit_coinhist.pdf(");
	    }
	  else if(i!=63)
	    {
	      cvs2->Print("fit_coinhist.pdf");
	    }
	  else
	    {
	      cvs2->Print("fit_coinhist.pdf)");
	    }
	  CONSTANT[i]=f1->GetParameter(0);
	  MEANS[i]=f1->GetParameter(1);
	  MEANS_error[i]=f1->GetParError(1);
	  SIGMA[i]=f1->GetParameter(2);
	  coin_para<<CONSTANT[i]<<" "<<MEANS[i]<<" "<<SIGMA[i]<<" "<<MEANS_error[i]<<endl;
	}

      Int_t index=64;
      Double_t x[n];
      Double_t ex[n];
      for(Int_t i=0;i<n;i++)
	{
	  x[i]=i;
	  ex[i]=0;
	}

      TCanvas *cvs3=new TCanvas("cvs3","Entry number");
      TGraphErrors *gr1=new TGraphErrors(index,x,Entries,ex,EntryErrors);//それぞれのMPPC位置番号をX、エントリー数をY軸に取ったもの
      gr1->Draw("APL");
      gr1->SetTitle("Each_Channel_entries(coincidence)");
      gr1->GetYaxis()->SetTitle("");
      gr1->GetXaxis()->SetTitle("MPPC_Channel_Number");
      gr1->SetMarkerSize(1);
      gr1->SetMarkerStyle(20);
      gr1->GetYaxis()->CenterTitle();
      gr1->GetXaxis()->CenterTitle();
      cvs3->Print("Each_MPPC_Entries.pdf");


      TCanvas *cvs4 = new TCanvas("cvs4","My Canvas");
     
      TH2D *image_ij = new TH2D("image_ij","",31,-15.5,15.5,31,-15.5,15.5);


      for(Int_t i=0; i<31;i++)
	{
	  for(Int_t j=0;j<31;j++)
	    {
	      image_ij ->Fill(i-15,j-15,count_ij[i][j]);
	    }
	}
      image_ij->Draw("colz");
     
      TCanvas *cvs5=new TCanvas("cvs5","Upper");
      cvs5->cd();     
      test2d1->Draw("colz");
       ReverseXAxis(test2d1);
       ReverseYAxis(test2d1);

      TCanvas *cvs6=new TCanvas("cvs6","Lower");
      cvs6->cd();     
      test2d2->Draw("colz");
       ReverseXAxis(test2d2);
       ReverseYAxis(test2d2);
     

      std::ofstream output("output.txt");
      for(Int_t i=0;i<31;i++)
	{
	  for(Int_t j=0;j<31;j++)
	    {
	      output<<i-15<<" "<<j-15<<" "<<count_ij[i][j]<<endl;
	    }
	}


      
      
      

      

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

void ReverseXAxis (TH1 *h)
{
  // Remove the current axis
  h->GetXaxis()->SetLabelOffset(999);
  h->GetXaxis()->SetTickLength(0);

  // Redraw the new axis 
  gPad->Update();
  TGaxis *newaxis = new TGaxis(gPad->GetUxmax(), 
			       gPad->GetUymin(),
			       gPad->GetUxmin(),
			       gPad->GetUymin(),
			       h->GetXaxis()->GetXmin(),
			       h->GetXaxis()->GetXmax(),
			       510,"-");
  newaxis->SetLabelOffset(-0.03);
  newaxis->Draw();
}

void ReverseYAxis (TH1 *h)
{
  // Remove the current axis
  h->GetYaxis()->SetLabelOffset(999);
  h->GetYaxis()->SetTickLength(0);

  // Redraw the new axis 
  gPad->Update();
  TGaxis *newaxis = new TGaxis(gPad->GetUxmin(), 
			       gPad->GetUymax(),
			       gPad->GetUxmin()-0.001,
			       gPad->GetUymin(),
			       h->GetYaxis()->GetXmin(),
			       h->GetYaxis()->GetXmax(),
			       510,"+");
  newaxis->SetLabelOffset(-0.04);
  newaxis->Draw();
}

