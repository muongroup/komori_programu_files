//#include<iostream>
//#include<string>
//#include<sstream>
//#include<fstream>
//#include<math.h>
#include "TStyle.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph2D.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TMath.h"

void graph_templete(){
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadBottomMargin(0.15);
   gStyle->SetPalette(1);
   gStyle->SetFrameLineWidth(4);
 
  string input_file_name="eachaccuracy.txt";
  Double_t x_min=0;
  Double_t x_max=300;
  Double_t y_min=0;
  Double_t y_max=1;
  

  

  TCanvas *cvs1=new TCanvas("cvs1","cvs1",1200,1000);//TCanvasを用いることでいくつものグラフを一斉に表示できる 
  ///  cvs1->SetLineWidth(3);
  std::ifstream file1(input_file_name);

  const Int_t n=30;
  Double_t Loss[n],accuracy[n],x[n];
  for(Int_t i=0;i<n;i++)
    {
      x[i]=0;
      Loss[i]=0;
      accuracy[i]=0;
    }
    
  for(Int_t i=0;i<n;i++)
    {
      x[i]=i*10+5;
      file1>>Loss[i]>>accuracy[i];
    }


  TGraph*graph1=new TGraph(n,x,accuracy);  

  graph1->SetTitle("    ");
  graph1->GetXaxis()->SetTitle("Energy [MeV]");
  graph1->GetYaxis()->SetTitle("Accuracy [-]");

  graph1->GetXaxis()->SetTitleSize(0.05);
  graph1->GetXaxis()->SetTitleFont(42);
  graph1->GetXaxis()->CenterTitle();
  graph1->GetXaxis()->SetLabelFont(42);
  graph1->GetXaxis()->SetLabelSize(0.05);
  graph1->GetXaxis()->SetTitleOffset(1.1);
  graph1->GetXaxis()->SetLabelOffset(0.015); 
   graph1->GetYaxis()->SetRangeUser(y_min,y_max);
  graph1->GetXaxis()->SetRangeUser(x_min,x_max);
  
  graph1->GetYaxis()->SetTitleSize(0.05);
  graph1->GetYaxis()->SetTitleFont(42);
  graph1->GetYaxis()->CenterTitle();
  graph1->GetYaxis()->SetLabelFont(42);
  graph1->GetYaxis()->SetLabelSize(0.05);
  graph1->GetYaxis()->SetTitleOffset(1.1);
  graph1->GetYaxis()->SetLabelOffset(0.015);
  graph1->SetLineWidth(3);
  graph1->SetLineColor(2);
  graph1->SetLineStyle(1);
  graph1->SetMarkerStyle(21);
  graph1->SetMarkerSize(2);
  graph1->SetMarkerColor(2);


  graph1->Draw("APL");

  /*
    TLegend *legend = new TLegend(0.7,0.55,0.9,0.75);//凡例
    legend->AddEntry(graph1,"all energy","l");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->Draw();
  */

    
   return;



 
 
 

}


