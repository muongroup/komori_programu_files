



#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<math.h>
#include "TStyle.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph2D.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TMath.h"

void comparehist(){
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPalette(1);

  
  std::ifstream file1("back_compress.txt");//バックグラウンドのデータ
  std::ifstream file2("compressno.txt");//対象物のデータ
  std::ifstream file3("compress.txt");//対象物のデータ
  
  TCanvas *cvs1=new TCanvas("background","background",900,900);//TCanvasを用いることでいくつものグラフを一斉に表示できる 

  TH2D *hist1 =new TH2D("background measurement","",31,-15.5,15.5,31,-15.5,15.5);//バックグラウンドデータをプロット  
  hist1->SetStats(0);//統計ボックス
  hist1->SetTitle("Background_measurement");
  hist1->GetXaxis()->SetTitle("deltaX");
  hist1->GetXaxis()->CenterTitle();
  hist1->GetYaxis()->SetTitle("deltaY");
  hist1->GetYaxis()->CenterTitle(); 
  while(!file1.eof())
    {
      float j,k,l;
      file1  >>j>>k>>l ; 
      hist1->Fill(j,k,l);      
    }
  hist1->SetContour(99);
  hist1->Draw("colz");


    
 
  TCanvas *cvs2=new TCanvas("object","object",900,900);

  TH2D *hist2 =new TH2D("object measument","",31,-15.5,15.5,31,-15.5,15.5);//                                                                                                        
  hist2->SetTitle("Object_measurement");
  hist2->GetXaxis()->SetTitle("deltaX");
  hist2->GetXaxis()->CenterTitle();
  hist2->GetYaxis()->SetTitle("deltaY");
  hist2->GetYaxis()->CenterTitle();
 
  hist2->SetStats(0);
  
  while(!file2.eof())
    {
      float p,q,r;
      file2 >>p>>q>>r;
      hist2->Fill(p,q,r);
    }
  hist2->SetContour(99);
  hist2->Draw("COLZ");

  TCanvas *cvs3=new TCanvas("object2","object2",900,900);

  TH2D *hist3 =new TH2D("object measument2","",31,-15.5,15.5,31,-15.5,15.5);//                                                                                                        
  hist3->SetTitle("Object_measurement2");
  hist3->GetXaxis()->SetTitle("deltaX");
  hist3->GetXaxis()->CenterTitle();
  hist3->GetYaxis()->SetTitle("deltaY");
  hist3->GetYaxis()->CenterTitle();
 
  hist3->SetStats(0);
  
  while(!file3.eof())
    {
      float p,q,r;
      file3 >>p>>q>>r;
      hist3->Fill(p,q,r);
    }
  hist3->SetContour(99);
  hist3->Draw("COLZ");





  
  
  
  TCanvas *cvs4=new TCanvas("substraction","substraction",900,900);
  TH2D *hist4 =new TH2D("substraction ","",31,-15.5,15.5,31,-15.5,15.5);//両データの差を計算
  hist4-> SetTitle("substraction");
  hist4->Add(hist3,hist2,1,-1);//両データを計測時間で割る
  hist4->GetXaxis()->SetTitle("deltaX");
  hist4->GetXaxis()->CenterTitle();
  hist4->GetYaxis()->SetTitle("deltaY");
  hist4->GetYaxis()->CenterTitle(); 
  hist4->SetContour(99);
  hist4->Draw("COLZ");



  TCanvas *cvs5=new TCanvas("divide","divide",900,900);
  TH2D *hist5 =new TH2D("divide ","",31,-15.5,15.5,31,-15.5,15.5);//二つのデータの割り算
  hist5-> SetTitle("divide");
  hist5->Divide(hist3,hist2,1,1);//両データを計測時間で割る
  hist5->GetXaxis()->SetTitle("deltaX");
  hist5->GetXaxis()->CenterTitle();
  hist5->GetYaxis()->SetTitle("deltaY");
  hist5->GetYaxis()->CenterTitle(); 
  hist5->SetContour(99);
  hist5->Draw("COLZ");
 

  

 
  TCanvas *cvs6=new TCanvas("atte1","atte1",900,900);
  TH2D *hist6 =new TH2D("atte1 ","",31,-15.5,15.5,31,-15.5,15.5);//減衰率1
  hist6-> SetTitle("atte1");
  hist6->Divide(hist2,hist1,1,1);
  hist6->GetXaxis()->SetTitle("deltaX");
  hist6->GetXaxis()->CenterTitle();
  hist6->GetYaxis()->SetTitle("deltaY");
  hist6->GetYaxis()->CenterTitle(); 
hist6->SetContour(99);
  hist6->Draw("COLZ");
 
  TCanvas *cvs7=new TCanvas("atte2","atte2",900,900);
  TH2D *hist7 =new TH2D("atte2","",31,-15.5,15.5,31,-15.5,15.5);
  hist7-> SetTitle("atte2");
  hist7->Divide(hist3,hist1,1,1);
  hist7->GetXaxis()->SetTitle("deltaX");
  hist7->GetXaxis()->CenterTitle();
  hist7->GetYaxis()->SetTitle("deltaY");
  hist7->GetYaxis()->CenterTitle(); 
  hist7->SetContour(99);
  hist7->Draw("COLZ");

  TCanvas *cvs8=new TCanvas("atte_sub","atte_sub",900,900);
  TH2D *hist8 =new TH2D("atte_sub","",31,-15.5,15.5,31,-15.5,15.5);//減衰率同士の引き算
  hist8-> SetTitle("atte_sub");
  hist8->Add(hist6,hist7,1,-1);
  hist8->GetXaxis()->SetTitle("deltaX");
  hist8->GetXaxis()->CenterTitle();
  hist8->GetYaxis()->SetTitle("deltaY");
  hist8->GetYaxis()->CenterTitle(); 
  hist8->SetContour(99);
  hist8->Draw("COLZ");
 
  TCanvas *cvs9=new TCanvas("atte_sub2","atte_sub2",900,900);
  TH2D *hist9 =new TH2D("atte_sub2","",31,-15.5,15.5,31,-15.5,15.5);//減衰率同士の引き算
  hist9-> SetTitle("atte_sub2");
  hist9->GetXaxis()->SetTitle("deltaX");
  hist9->GetXaxis()->CenterTitle();
  hist9->GetYaxis()->SetTitle("deltaY");
  hist9->GetYaxis()->CenterTitle(); 
  hist9->SetContour(99);
  hist9->Draw("COLZ");
  Double_t atte1;
  Double_t atte2;

  for(int i=0;i<32;i++)
    {
      for(int j=0;j<32;j++)
	{

	  atte1 = hist6->GetBinContent(i,j);
	  atte2 = hist7->GetBinContent(i,j);
	  if((atte1-atte2)==0)
	    {
	      hist9->Fill(i-16,j-16,0.00001);
	    }
	  else{
	  hist9->Fill(i-16,j-16,abs(atte1-atte2));
	  }
	    }
	}


   return;



 
 
 

}

