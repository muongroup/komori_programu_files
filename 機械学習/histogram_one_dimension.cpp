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

void histogram_one_dimension(){
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetPadBottomMargin(0.15);
    // gStyle->SetPalette(1);
    gStyle->SetFrameLineWidth(5);
 
  string input_file_name="accuracy80.txt";
  Int_t bin_width=300;//ビンの数
  Double_t x_min=0;
  Double_t x_max=300;
  Double_t y_min=0;
  Double_t y_max=0.12;
  Double_t number_of_verification=50000;
  

  

  TCanvas *cvs1=new TCanvas("cvs1","cvs1",1200,1000);//TCanvasを用いることでいくつものグラフを一斉に表示できる 
  ///  cvs1->SetLineWidth(3);
  std::ifstream file1(input_file_name);                                                                                                                                              
  TH1D *hist1 = new TH1D("hist1","hist1",bin_width,x_min,x_max);
  TH1D *hist2 = new TH1D("hist2","hist2",bin_width,x_min,x_max);

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
  hist1->SetLineColor(4);
  hist1->SetLineStyle(1);
  hist1->SetStats(0);

  hist2->SetLineWidth(3);
  hist2->SetLineColor(2);
  hist2->SetLineStyle(1);
  hist2->SetStats(0);

  
  Int_t i=0;
   Double_t j[300],k[300];
  Double_t average=0;
  Double_t var=0;
   while(!file1.eof())
  {
     
      file1>>j[i]>>k[i] ;
      //      cout<<i<<" "<<k<<" "<<j<<endl;
      hist1->Fill(i,j[i]/number_of_verification);
      hist2->Fill(i,k[i]/number_of_verification);
      average=average+(i+0.5)*k[i];
      i++;
	}
   average=average/number_of_verification;//平均値導出
   cout<<average<<endl;
   for(Int_t i=0;i<300;i++)
     {
       
       var=var+(average-(i+0.5))*(average-(i+0.5))*k[i];
     }
   
   var=var/number_of_verification;
   cout<<var<<" "<<sqrt(var)<<endl;
  hist1->Draw("hist");
     hist2->Draw("hist same");
  /*
  
    TLegend *legend = new TLegend(0.2,0.55,0.4,0.75);//凡例
    legend->AddEntry(hist1,"Correct_data","l");
    legend->AddEntry(hist2,"Output_data","l");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->Draw();

    std::ofstream file2("average_variance.txt",ios::app);
    file2<<input_file_name<<" "<<average<<" "<<var<<" "<<sqrt(var)<<endl;
  */
   return;



 
 
 

}

