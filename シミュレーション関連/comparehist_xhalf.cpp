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

void comparehist_xhalf(){
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPalette(1);

  // std::ofstream backplot("back_plot.txt");
  //  std::ofstream objectplot("object_plot.txt");
  Double_t x_bin=15;
  Double_t y_bin=31;
  Double_t x_min=-7.5;
  Double_t x_max=7.5;
  Double_t y_min=-15.5;
  Double_t y_max=15.5; 
  std::ofstream bitdata("bitdata.txt");   

  TCanvas *cvs1=new TCanvas("background","background",900,900);//TCanvasを用いることでいくつものグラフを一斉に表示できる 
  std::ifstream back("compress_xhalf.txt");//バックグラウンドのデータ                                                                                                                                              
  TH2D *background =new TH2D("background measurement","",x_bin,x_min,x_max,y_bin,y_min,y_max);//バックグラウンドデータをプロット  
  background->SetStats(0);//統計ボックス
  background->SetTitle("Background_measurement");
  background->GetXaxis()->SetTitle("deltaX");
  background->GetXaxis()->CenterTitle();
  background->GetYaxis()->SetTitle("deltaY");
  background->GetYaxis()->CenterTitle(); 
  while(!back.eof())
    {
      float j,k,l;
      back  >>j>>k>>l ; 
      background->Fill(j,k,l);      
    }    
  background->Draw("colz");


    
 
  TCanvas *cvs2=new TCanvas("object","object",900,900);
  std::ifstream ob("compressno_xhalf.txt");
  TH2D *object =new TH2D("object measument","",x_bin,x_min,x_max,y_bin,y_min,y_max);//                                                                                                        
  object->SetTitle("Object_measurement");
  object->GetXaxis()->SetTitle("deltaX");
  object->GetXaxis()->CenterTitle();
  object->GetYaxis()->SetTitle("deltaY");
  object->GetYaxis()->CenterTitle();
 
  object->SetStats(0);
  while(!ob.eof())
    {
      float p,q,r;
      ob >>p>>q>>r;
      object->Fill(p,q,r);
    }
      object->Draw("COLZ");
    



 TCanvas *cvs3=new TCanvas("substraction","substraction",900,900);
  TH2D *substraction =new TH2D("substraction ","",x_bin,x_min,x_max,y_bin,y_min,y_max);
 substraction-> SetTitle("substraction");
 substraction->Add(background,object,1,-1);//両データを計測時間で割る
 substraction->GetXaxis()->SetTitle("deltaX");
 substraction->GetXaxis()->CenterTitle();
 substraction->GetYaxis()->SetTitle("deltaY");
 substraction->GetYaxis()->CenterTitle(); 
 substraction->Draw("COLZ");
 
 

 TCanvas *cvs4=new TCanvas("attenuation","attenuation",900,900);
 TH2D *attenuation =new TH2D("attenuation rate","",x_bin,x_min,x_max,y_bin,y_min,y_max);
 attenuation->Divide(background,object,1,1);
 attenuation->SetTitle("Attenuation");
 attenuation->GetXaxis()->SetTitle("deltaX");
 attenuation->GetXaxis()->CenterTitle();
 attenuation->GetYaxis()->SetTitle("deltaY");
 attenuation->GetYaxis()->CenterTitle();

 attenuation->Draw("COLZ");
 //  attenuation->SetMaximum(1);
 // attenuation->SetMinimum(0);
 attenuation->SetStats(0);




   return;



 
 
 

}

