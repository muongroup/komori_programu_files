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
#include "TLegend.h"

void histogram_one_dimension_eight(){
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetPadBottomMargin(0.15);
    // gStyle->SetPalette(1);
    gStyle->SetFrameLineWidth(5);
    string num="29"; 
    string input_file_name="プラシン10/accuracy"+num+".txt";
    string input_file_name2="プラシン9/accuracy"+num+".txt";
    string input_file_name3="プラシン8/accuracy"+num+".txt";
    string input_file_name4="プラシン7/accuracy"+num+".txt";
    string input_file_name5="プラシン6/accuracy"+num+".txt";
    string input_file_name6="プラシン5/accuracy"+num+".txt";
    string input_file_name7="プラシン4/accuracy"+num+".txt";
    string input_file_name8="プラシン3/accuracy"+num+".txt";
  Int_t bin_width=300;//ビンの数
  Double_t x_min=0;
  Double_t x_max=300;
  Double_t y_min=0;
  Double_t y_max=0.12;
  Double_t number_of_verification=50000;
  

  

  TCanvas *cvs1=new TCanvas("cvs1","cvs1",1200,1000);//TCanvasを用いることでいくつものグラフを一斉に表示できる 
  ///  cvs1->SetLineWidth(3);
  std::ifstream file1(input_file_name);
  std::ifstream file2(input_file_name2);
  std::ifstream file3(input_file_name3);
  std::ifstream file4(input_file_name4);
  std::ifstream file5(input_file_name5);
  std::ifstream file6(input_file_name6);
  std::ifstream file7(input_file_name7);
  std::ifstream file8(input_file_name8);
  TH1D *hist1 = new TH1D("hist1","hist1",bin_width,x_min,x_max);
  TH1D *hist2 = new TH1D("hist2","hist2",bin_width,x_min,x_max);
  TH1D *hist3 = new TH1D("hist3","hist3",bin_width,x_min,x_max);
  TH1D *hist4 = new TH1D("hist4","hist4",bin_width,x_min,x_max);
  TH1D *hist5 = new TH1D("hist5","hist5",bin_width,x_min,x_max);
  TH1D *hist6 = new TH1D("hist6","hist6",bin_width,x_min,x_max);
  TH1D *hist7 = new TH1D("hist7","hist7",bin_width,x_min,x_max);
  TH1D *hist8 = new TH1D("hist8","hist8",bin_width,x_min,x_max);

  hist1->SetTitle("                     ");
  hist1->GetXaxis()->SetTitle("Energy [MeV]");
  hist1->GetYaxis()->SetTitle("Probability [-]");

  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->GetXaxis()->SetLabelSize(0.05);
  hist1->GetXaxis()->SetTitleFont(42);
  hist1->GetXaxis()->CenterTitle();
  hist1->GetXaxis()->SetLabelFont(42);
  hist1->GetXaxis()->SetTitleOffset(1.1);
  hist1->GetXaxis()->SetLabelOffset(0.015);
  hist1->GetYaxis()->SetRangeUser(y_min,y_max);
  hist1->GetYaxis()->SetTitleSize(0.05);
  hist1->GetYaxis()->SetLabelSize(0.05);
  hist1->GetYaxis()->SetTitleFont(42);
  hist1->GetYaxis()->CenterTitle();
  hist1->GetYaxis()->SetLabelFont(42);
  hist1->GetYaxis()->SetTitleOffset(1.4);
  hist1->GetYaxis()->SetLabelOffset(0.015);

  hist1->SetLineWidth(3);
  hist1->SetLineColor(2);
  hist1->SetLineStyle(1);
  hist1->SetStats(0);

  hist2->SetLineWidth(3);
  hist2->SetLineColor(4);
  hist2->SetLineStyle(1);
  hist2->SetStats(0);

  hist3->SetLineWidth(3);
  hist3->SetLineColor(1);
  hist3->SetLineStyle(1);
  hist3->SetStats(0);

  hist4->SetLineWidth(3);
  hist4->SetLineColor(3);
  hist4->SetLineStyle(1);
  hist4->SetStats(0);

  hist5->SetLineWidth(2);
  hist5->SetLineColor(2);
  hist5->SetLineStyle(2);
  hist5->SetStats(0);

  hist6->SetLineWidth(2);
  hist6->SetLineColor(4);
  hist6->SetLineStyle(2);
  hist6->SetStats(0);

  hist7->SetLineWidth(2);
  hist7->SetLineColor(1);
  hist7->SetLineStyle(2);
  hist7->SetStats(0);

  hist8->SetLineWidth(2);
  hist8->SetLineColor(3);
  hist8->SetLineStyle(2);
  hist8->SetStats(0);



 Double_t j,k;
 Int_t i=0;
  while(!file1.eof())
    {
      // Double_t j,k;
      file1>>j>>k;
      
      hist1->Fill(i,k/number_of_verification);
      i++;
      cout<<k<<endl;
     }
   
  i=0;   
  
  while(!file2.eof())
    
     {
       // Double_t j,k;
       file2>>j>>k;
       cout<<k<<endl;
       hist2->Fill(i,k/number_of_verification);
       i++;
     }
     
   i=0;
   while(!file3.eof())
     {
    file3>>j>>k;
    cout<<k<<endl;
    hist3->Fill(i,k/number_of_verification);
    i++;
    	}
   
   i=0;
   while(!file4.eof())
     {
    file4>>j>>k;
    
    hist4->Fill(i,k/number_of_verification);
    i++;
	}

    i=0;
   while(!file5.eof())
     {
    file5>>j>>k;
    
    hist5->Fill(i,k/number_of_verification);
    i++;
	}

   i=0;
   while(!file6.eof())
     {
    file6>>j>>k;
    
    hist6->Fill(i,k/number_of_verification);
    i++;
	}
   
   i=0;
   while(!file7.eof())
     {
    file7>>j>>k;
    
    hist7->Fill(i,k/number_of_verification);
    i++;
	}
   
   i=0;
   while(!file8.eof())
     {
       file8>>j>>k;
       cout<<k<<endl;
       hist8->Fill(i,k/number_of_verification);
       i++;
     }
   

  
   hist1->Draw("hist ");
   hist2->Draw("same hist");
   hist3->Draw("same hist");
   hist4->Draw("same hist");
   hist5->Draw("same hist");
   hist6->Draw("same hist");
   hist7->Draw("same hist");
   hist8->Draw("same hist");


 
  
  
    TLegend *legend = new TLegend(0.7,0.55,0.9,0.80);//凡例
    legend->AddEntry(hist1,"10","l");
    legend->AddEntry(hist2,"9","l");
    legend->AddEntry(hist3,"8","l");
    legend->AddEntry(hist4,"7","l");
    legend->AddEntry(hist5,"6","l");
    legend->AddEntry(hist6,"5","l");
    legend->AddEntry(hist7,"4","l");
    legend->AddEntry(hist8,"3","l");

    legend->SetTextSize(0.04);
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->Draw();

  
   return;



  
 

}

