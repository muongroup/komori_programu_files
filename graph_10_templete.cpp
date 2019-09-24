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

void graph_10_templete(){
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPalette(1);
  gStyle->SetFrameLineWidth(4);
  
  string input_file_name="ten_deposit.txt";
  string input_file_name2="std.txt";
  Double_t x_min=0;
  Double_t x_max=300;
  Double_t y_min=0;
  // Double_t y_max=1;
  

  

  TCanvas *cvs1=new TCanvas("cvs1","cvs1",1200,1000);//TCanvasを用いることでいくつものグラフを一斉に表示できる 
  ///  cvs1->SetLineWidth(3);
  std::ifstream file1(input_file_name);
   std::ifstream file2(input_file_name2);

  const Int_t n=600;
  Double_t one[n],two[n],three[n],four[n],five[n],six[n],seven[n],eight[n],nine[n],ten[n],x[n];
  Double_t std[300],xx[300];
  for(Int_t i=0;i<n;i++)
    {
      std[i]=0;
	xx[i]=0;
      x[i]=0;
      one[i]=0;
      two[i]=0;
      three[i]=0;
      four[i]=0;
      five[i]=0;
      six[i]=0;
      seven[i]=0;
      eight[i]=0;
      nine[i]=0;
      ten[i]=0;
    }
    
  for(Int_t i=0;i<n;i++)
    {
      x[i]=(i+1)*0.5;
      file1>>one[i]>>two[i]>>three[i]>>four[i]>>five[i]>>six[i]>>seven[i]>>eight[i]>>nine[i]>>ten[i];
    }

  for(Int_t i=0;i<300;i++)
    {
      xx[i]=i;
      file2>>std[i];
    }


  TGraph*graph1=new TGraph(n,x,one);
  TGraph*graph2=new TGraph(n,x,two);
  TGraph*graph3=new TGraph(n,x,three);
  TGraph*graph4=new TGraph(n,x,four);
  TGraph*graph5=new TGraph(n,x,five);
  TGraph*graph6=new TGraph(n,x,six);
  TGraph*graph7=new TGraph(n,x,seven);
  TGraph*graph8=new TGraph(n,x,eight);
  TGraph*graph9=new TGraph(n,x,nine);
  TGraph*graph10=new TGraph(n,x,ten);
  TGraph*graph11=new TGraph(300,xx,std);

  graph1->SetTitle("    ");
  graph1->GetXaxis()->SetTitle("Energy [MeV]");
  graph1->GetYaxis()->SetTitle("Loss [-]");

  graph1->GetXaxis()->SetTitleSize(0.05);
  graph1->GetXaxis()->SetTitleFont(42);
  graph1->GetXaxis()->CenterTitle();
  graph1->GetXaxis()->SetLabelFont(42);
  graph1->GetXaxis()->SetLabelSize(0.05);
  graph1->GetXaxis()->SetTitleOffset(1.1);
  graph1->GetXaxis()->SetLabelOffset(0.015); 
  //   graph1->GetYaxis()->SetRangeUser(y_min,y_max);
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
  //    graph1->SetMarkerStyle(20);
  // graph1->SetMarkerSize(2);
  graph1->SetMarkerColor(2);

 
  graph2->SetLineWidth(3);
  graph2->SetLineColor(4);
  graph2->SetLineStyle(1);
  // graph2->SetMarkerStyle(20);
  // graph2->SetMarkerSize(2);
  graph2->SetMarkerColor(4);

 
  graph3->SetLineWidth(3);
  graph3->SetLineColor(4);
  graph3->SetLineStyle(1);
  //  graph3->SetMarkerStyle(20);
  // graph3->SetMarkerSize(2);
  graph3->SetMarkerColor(4);

   graph4->SetLineWidth(3);
  graph4->SetLineColor(4);
  graph4->SetLineStyle(1);
  // graph4->SetMarkerStyle(20);
  // graph4->SetMarkerSize(2);
  graph4->SetMarkerColor(4);

 
  graph5->SetLineWidth(3);
  graph5->SetLineColor(4);
  graph5->SetLineStyle(1);
  //graph5->SetMarkerStyle(20);
  // graph5->SetMarkerSize(2);
  graph5->SetMarkerColor(4);

    graph6->SetLineWidth(3);
  graph6->SetLineColor(2);
  graph6->SetLineStyle(1);
  // graph6->SetMarkerStyle(20);
  // graph6->SetMarkerSize(2);
  graph6->SetMarkerColor(2);

 
  graph7->SetLineWidth(3);
  graph7->SetLineColor(4);
  graph7->SetLineStyle(1);
  // graph7->SetMarkerStyle(20);
  //graph7->SetMarkerSize(2);
  graph7->SetMarkerColor(4);

 
  graph8->SetLineWidth(3);
  graph8->SetLineColor(4);
  graph8->SetLineStyle(1);
  // graph8->SetMarkerStyle(20);
  //graph8->SetMarkerSize(2);
  graph8->SetMarkerColor(4);

   graph9->SetLineWidth(3);
  graph9->SetLineColor(4);
  graph9->SetLineStyle(1);
  //graph9->SetMarkerStyle(20);
  //graph9->SetMarkerSize(2);
  graph9->SetMarkerColor(4);

 
  graph10->SetLineWidth(3);
  graph10->SetLineColor(4);
  graph10->SetLineStyle(1);
  //graph10->SetMarkerStyle(20);
  //graph10->SetMarkerSize(2);
  graph10->SetMarkerColor(4);


  graph1->Draw("APL");
graph2->Draw("PL");
  graph3->Draw("PL");
  graph4->Draw("PL");
  graph5->Draw("PL");
  graph6->Draw("PL");
  graph7->Draw("PL");
  graph8->Draw("PL");
  graph9->Draw("PL");
  graph10->Draw("PL");
    graph11->Draw("PL");
 

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


