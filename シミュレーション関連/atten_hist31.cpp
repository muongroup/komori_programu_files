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

void atten_hist31(){
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPalette(1);
   

  TCanvas *cvs1=new TCanvas("background","background",900,900);//TCanvasを用いることでいくつものグラフを一斉に表示できる 
  std::ifstream back("back_compress.txt");//バックグラウンドのデータ                                                                                                                                              
  TH2D *background =new TH2D("background measurement","",31,-15.5,15.5,31,-15.5,15.5);//バックグラウンドデータをプロット  
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
  background->SetContour(99);//グラデーションを99分割
  background->Draw("colz");


    
 
  TCanvas *cvs2=new TCanvas("object","object",900,900);
  std::ifstream ob("compressno.txt");
  TH2D *object =new TH2D("object measument","",31,-15.5,15.5,31,-15.5,15.5);//                                                                                                        
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
  object->SetContour(99);//グラデーションを99分割
  object->Draw("COLZ");
    



 TCanvas *cvs3=new TCanvas("substraction","substraction",900,900);
  TH2D *substraction =new TH2D("substraction ","",31,-15.5,15.5,31,-15.5,15.5);
 substraction-> SetTitle("substraction");
 substraction->Add(background,object,1,-1);//両データを計測時間で割る
 substraction->GetXaxis()->SetTitle("deltaX");
 substraction->GetXaxis()->CenterTitle();
 substraction->GetYaxis()->SetTitle("deltaY");
 substraction->GetYaxis()->CenterTitle();
 substraction->SetContour(99);//グラデーションを99分割
 substraction->Draw("COLZ");
 
 

 TCanvas *cvs4=new TCanvas("attenuation","attenuation",900,900);
 TH2D *attenuation =new TH2D("attenuation rate","",31,-15.5,15.5,31,-15.5,15.5);
 attenuation->Divide(substraction,background,1,1);
 attenuation->SetTitle("Attenuation");
 attenuation->GetXaxis()->SetTitle("deltaX");
 attenuation->GetXaxis()->CenterTitle();
 attenuation->GetYaxis()->SetTitle("deltaY");
 attenuation->GetYaxis()->CenterTitle();
 attenuation->SetContour(99);//グラデーションを99分割
 attenuation->Draw("COLZ");
 //  attenuation->SetMaximum(1);
 // attenuation->SetMinimum(0);
 attenuation->SetStats(0);


 TCanvas *cvs5=new TCanvas("attenuation-custam","attenuation-custam",900,900);//減衰率が0より小さい点に0.001を打ち込む
 TH2D *attenuation2 =new TH2D("attenuation rate","",31,-15.5,15.5,31,-15.5,15.5);
 
 double minius_reg;
 for(int i=0;i<32;i++)
   {  
     for(int j=0;j<32;j++)
       {
	 
	 minius_reg = attenuation->GetBinContent(i,j);
	 if(minius_reg<=0)
	   {
	     
	     minius_reg=0.0001;
	     attenuation2->Fill(i-16,j-16,minius_reg);
	     //  bitdata<<"0 ";
	   }
	 else if(minius_reg<1)
	   {
	     attenuation2->Fill(i-16,j-16,minius_reg);
	     //  bitdata<<minius_reg*256<<" ";
	   }
	 else if(minius_reg<100)
	   {
	     minius_reg=0;
	     attenuation2->Fill(i-16,j-16,minius_reg);
	     //  bitdata<<"0 ";
	   }
       }
     //  bitdata<<endl;
   }
 attenuation2->SetTitle("Attenuation_custom");
 attenuation2->GetXaxis()->SetTitle("deltaX");
 attenuation2->GetXaxis()->CenterTitle();
 attenuation2->GetYaxis()->SetTitle("deltaY");
 attenuation2->GetYaxis()->CenterTitle();
 attenuation2->SetContour(99);//グラデーションを99分割
 attenuation2->Draw("COLZ");
 attenuation2->SetStats(0);
 




 //ここの二つのヒストグラムは正直未完成
 //狙いとしては
 //back_plot.txtとobject_plot.txtに
 //ベクトルプロットをまとめて書くこと
 //それさえできればプロットはできなくても問題なし
 
 
 TCanvas *cvs6=new TCanvas("back_error","back_error",900,900);
  TH2D*back_error =new TH2D("back_error","",31,-15.5,15.5,31,-15.5,15.5);
  double error_valueb;
  
  for(int i=1;i<32;i++)
    {
      for(int j=1;j<32;j++)
	{
	 error_valueb=background->GetBinContent(i,j);
	 //	 backplot<<i-16<<" "<<j-16<<" "<<error_valueb<<endl;
	 error_valueb=1/sqrt(error_valueb);
	 back_error->Fill(i-16,j-16,error_valueb);
       }
   }
  back_error->Draw("colz");
  back_error->SetContour(99);
  TCanvas *cvs7=new TCanvas("object_error","object_error",900,900);
  TH2D*object_error =new TH2D("object_error","",31,-15.5,15.5,31,-15.5,15.5);
   double error_valueo;
   
   for(int i=1;i<32;i++)
     {
       for(int j=1;j<32;j++)
         {
	   error_valueo=object->GetBinContent(i,j);
	   // objectplot<<i-16<<" "<<j-16<<" "<<error_valueo<<endl;
	   error_valueo=1/sqrt(error_valueo);
	   object_error->Fill(i-16,j-16,error_valueo);
	 }
     }
   object_error->Draw("colz");
   object_error->SetContour(99);



   TCanvas *cvs8=new TCanvas("attenuation_error","attenuation_error",900,900);
   TH2D*attenuation_error =new TH2D("attenuation_error","",31,-15.5,15.5,31,-15.5,15.5);
   double error_attenuation;
   for(int i=1;i<32;i++)
     {
       for(int j=1;j<32;j++)
         {

	   error_valueb=background->GetBinContent(i,j);	   
	   error_valueo=object->GetBinContent(i,j);
	   error_attenuation=sqrt((error_valueo)/pow(error_valueb,2.0)+pow(error_valueo,2.0)/pow(error_valueb,3.0));
       
	   attenuation_error->Fill(i-16,j-16,error_attenuation);
	 }
     }

   attenuation_error->Draw("colz");
   attenuation_error->SetContour(99);

   
   return;



 
 
 

}

