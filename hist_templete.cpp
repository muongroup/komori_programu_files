
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

void hist_templete(){
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPalette(1);
  Double_t x_bin=300;
  Double_t x_min=0;
  Double_t x_max=30;

  TCanvas *cvs1=new TCanvas("cvs1","cvs1",900,900);//TCanvasを用いることでいくつものグラフを一斉に表示できる 
  std::ifstream file1("deposit.txt");//バックグラウンドのデータ                                                                                                                                              
  TH1D *hist1 =new TH1D("hist1","hist1",x_bin,x_min,x_max);//バックグラウンドデータをプロット  
  hist1->SetStats(0);//統計ボックス
  hist1->SetTitle("hist");
  hist1->GetXaxis()->SetTitle("correct [MeV]");
  hist1->GetXaxis()->CenterTitle();
  hist1->GetYaxis()->SetTitle("output [MeV]");
  hist1->GetYaxis()->CenterTitle(); 
  while(!file1.eof())
    {
      Double_t j,k;
      file1  >>j>>k ; 
      hist1->Fill(j,k);      
    }
  hist1->SetContour(99);//グラデーションを99分割
  hist1->Draw("hist");

 
	  
 

   
   return;



 
 
 

}

