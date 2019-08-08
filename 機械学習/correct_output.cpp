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

voids correct_output(){
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPalette(1);
  Double_t x_bin=300;
  Double_t x_min=0;
  Double_t x_max=300;

  Double_t y_bin=300;
  Double_t y_min=0;
  Double_t y_max=300;
  TCanvas *cvs1=new TCanvas("cvs1","cvs1",900,900);//TCanvasを用いることでいくつものグラフを一斉に表示できる 
  std::ifstream file1("correct_output.csv");//バックグラウンドのデータ                                                                                                                                              
  TH2D *hist1 =new TH2D("hist1","hist1",x_bin,x_min,x_max,y_bin,y_min,y_max);//バックグラウンドデータをプロット  
  hist1->SetStats(0);//統計ボックス
  hist1->SetTitle("hist");
  hist1->GetXaxis()->SetTitle("correct [MeV]");
  hist1->GetXaxis()->CenterTitle();
  hist1->GetYaxis()->SetTitle("output [MeV]");
  hist1->GetYaxis()->CenterTitle(); 
  while(!file1.eof())
    {
      float j,k,l;
      file1  >>j>>k ; 
      hist1->Fill(j,k,l);      
    }
  hist1->SetContour(99);//グラデーションを99分割
  hist1->Draw("colz");

  Double_t ivent_num[300];
  Double_t average[300];
  Double_t difference[300];

for(Int_t i=0;i<300;i++)
    {
      ivent_num[i]=0;
      average[i]=0;
      difference[i]=0;
    }
  
  for(Int_t i=1;i<301;i++)
    {
      for(Int_t j=1:j<301;j++)
	{
	  Double_t output;
	  output=hist1->GetBinContent(i,j)
	    ivent_num[i-1]=output;
	    average[i-1]=average[i-1]+j*output;
	    difference[i-1]=(i-output)*(i-output);
	    
	    }

    }

	  
 

   
   return;



 
 
 

}

