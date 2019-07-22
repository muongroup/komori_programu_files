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

void attenuation_histgram_experiment(){
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPalette(1);
  char output1[]="BGoutput.txt";
  char output2[]="OBoutput.txt";
  Double_t background_time;
  Double_t object_measurement_time;
  Double_t rate;

  background_time=219;
  object_measurement_time=316;

  rate=background_time/object_measurement_time;

  TCanvas *cvs1=new TCanvas("background","background",900,900);//TCanvasを用いることでいくつものグラフを一斉に表示できる 
  std::ifstream file1(output1);//バックグラウンドのデータ                                                                                                                                              
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
  hist1->Draw("colz");


    
 
  TCanvas *cvs2=new TCanvas("object","object",900,900);
  std::ifstream file2(output2);
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
      hist2->Draw("COLZ");
    




 TCanvas *cvs3=new TCanvas("substraction","substraction",900,900);
  TH2D *hist3 =new TH2D("substraction ","",31,-15.5,15.5,31,-15.5,15.5);
 hist3-> SetTitle("substraction");
 hist3->Add(hist1,hist2,1,-rate);//両データを計測時間で割る
 hist3->GetXaxis()->SetTitle("deltaX");
 hist3->GetXaxis()->CenterTitle();
 hist3->GetYaxis()->SetTitle("deltaY");
 hist3->GetYaxis()->CenterTitle(); 
 hist3->Draw("COLZ");
 
 

 TCanvas *cvs4=new TCanvas("attenuation","attenuation",900,900);
 TH2D *hist4 =new TH2D("attenuation rate","",31,-15.5,15.5,31,-15.5,15.5);
 hist4->Divide(hist3,hist1);
 hist4->SetTitle("Attenuation");
 hist4->GetXaxis()->SetTitle("deltaX");
 hist4->GetXaxis()->CenterTitle();
 hist4->GetYaxis()->SetTitle("deltaY");
 hist4->GetYaxis()->CenterTitle();

 hist4->Draw("COLZ");
 //  attenuation->SetMaximum(1);
 // attenuation->SetMinimum(0);
 hist4->SetStats(0);


 TCanvas *cvs5=new TCanvas("attenuation-custam","attenuation-custam",900,900);//減衰率が0より小さい点に0.001を打ち込む
 TH2D *hist5 =new TH2D("attenuation-custom","",31,-15.5,15.5,31,-15.5,15.5);
 
 double minius_reg;
 for(Int_t i=1;i<32;i++)
   {  
     for(Int_t j=1;j<32;j++)
       {
	 
	 minius_reg = hist4->GetBinContent(i,j);
	 if(minius_reg<=0)
	   {
	     
	     minius_reg=0.001;
	     hist5->Fill(i-16,j-16,minius_reg);
	   }
	 else if(minius_reg<1)
	   {
	     hist5->Fill(i-16,j-16,minius_reg);
	   }
	 else if(minius_reg<100)
	   {
	     minius_reg=0;
	     hist5->Fill(i-16,j-16,minius_reg);
	   }
       }
   }
 hist5->SetTitle("Attenuation_custom");
 hist5->GetXaxis()->SetTitle("deltaX");
 hist5->GetXaxis()->CenterTitle();
 hist5->GetYaxis()->SetTitle("deltaY");
 hist5->GetYaxis()->CenterTitle();
 hist5->Draw("COLZ");
 hist5->SetStats(0);
 

 
 
 TCanvas *cvs6=new TCanvas("back_error","back_error",900,900);
 TH2D*hist6 =new TH2D("back_error","",31,-15.5,15.5,31,-15.5,15.5);
 double error_valueb;
 
 for(int i=1;i<32;i++)
   {
     for(int j=1;j<32;j++)
       {
	 double error;
	 error_valueb=hist1->GetBinContent(i,j);
	 // backplot<<i-16<<" "<<j-16<<" "<<error_valueb<<endl;
	  error=1/sqrt(error_valueb);
	  hist6->Fill(i-16,j-16,error);
       }
   }
 hist6->Draw("COLZ");

  TCanvas *cvs7=new TCanvas("object_error","object_error",900,900);
  TH2D *hist7 =new TH2D("object_error","",31,-15.5,15.5,31,-15.5,15.5);
  double error_valueo;
  
  for(int i=1;i<32;i++)
    {
      for(int j=1;j<32;j++)
	{
	  double error;
	  error_valueo=hist2->GetBinContent(i,j);
	  // objectplot<<i-16<<" "<<j-16<<" "<<error_valueo<<endl;
	  error=1/sqrt(error_valueo);
	  hist7->Fill(i-16,j-16,error);
	}
    }
  hist7->Draw("COLZ");

 TCanvas *cvs8=new TCanvas("attenuation_error","attenuation_error",900,900);
 TH2D*hist8 =new TH2D("attenuation_error","",31,-15.5,15.5,31,-15.5,15.5);
 double attenuation_error;

 for(Int_t i=1;i<32;i++)
   {
     for(Int_t j=1;j<32;j++)
       {
	 error_valueb=hist1->GetBinContent(i,j);
	 //	 error_valueb=sqrt(error_valueb);
	 error_valueo=hist2->GetBinContent(i,j);
	 // error_valueo=sqrt(error_valueo);
	 attenuation_error=rate*sqrt(((error_valueo)/((error_valueb)*(error_valueb)))+(error_valueo*error_valueo)/(error_valueb*error_valueb*error_valueb));
	 hist8->Fill(i-16,j-16,attenuation_error);
       }
   }
 hist8->Draw("COLZ");
 
   return; 

}

