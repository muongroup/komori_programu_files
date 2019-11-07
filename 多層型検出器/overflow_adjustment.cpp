


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
int overflow_adjustment(){
  
  gStyle->SetFrameLineWidth(3);  
  
  TCanvas *cvs1=new TCanvas("RAW_DATA","RAW_DATA",1200,1000);
  TCanvas *cvs2=new TCanvas("COMP","COMP",1200,1000);
  TCanvas *cvs3=new TCanvas("DIVIDE","DIVIDE",1200,1000);


   cvs1->SetLogy();
   cvs2->SetLogy();



  TH1D *hist1=new TH1D("LOW_GAIN","LOW_GAIN",1024,0,1024);
  TH1D *hist2=new TH1D("HIGH_GAIN","HIGH_GAIN",1024,0,1024);//三大コインシデンス
  TH1D *hist3=new TH1D("LOW_COMP","LOW_COMP",1024,0,1024);//三大コインシデンス
  TH1D *hist4=new TH1D("HIGH_COMP","HIGH_COMP",1024,0,1024);//三大コインシデンス
  
  TH1D *hist5=new TH1D("divide","divide",200,0,10);//三大コインシデンス
  /*
  TH1D *hist6=new TH1D("DETECTOR3_triple_coin","DETECTOR3_triple_coin",512,0,512);//三大コインシデンス
  TH1D *hist7=new TH1D("DETECTOR1_1_and_2","DETECTOR1_1_and_2",512,0,512);//2大コインシデンス
  TH1D *hist8=new TH1D("DETECTOR1_1_and_3","DETECTOR1_1_and_3",512,0,512);//2大コインシデンス
  TH1D *hist9=new TH1D("DETECTOR2_1_and_2","DETECTOR2_1_and_2",512,0,512);//2大コインシデンス
  TH1D *hist10=new TH1D("DETECTOR3_1_and_3","DETECTOR3_1_and_3",512,0,512);//2大コインシデンス
  TH1D *hist11=new TH1D("DETECTOR2_2_and_3","DETECTOR2_1_and_2",512,0,512);//2大コインシデンス
  TH1D *hist12=new TH1D("DETECTOR3_2_and_3","DETECTOR3_1_and_3",512,0,512);//2大コインシデンス
  */

  hist1->SetStats(0);
  hist2->SetStats(0);
  hist3->SetStats(0);
  hist4->SetStats(0);
  
	     
  Int_t counter1,counter2,counter3,counter4,counter5,counter6,counter7,counter8,counter9,counter10,counter11,counter12;
  Double_t time,before_time,before2_time,before3_time;
  Int_t number,before_number,before2_number,before3_number;
  Double_t ch,before_ch,before2_ch,before3_ch;
  char dummy1,dummy2;
  Double_t measurement_hour=0.75;
  Double_t threshold_time=0.000005;
 
  before_time=0;
  before_number=1;
  before_ch=0;
  counter1=0;
  counter2=0;
 

   ifstream file1("h000000.csv");
   
   // for(Int_t i=0;i<200;i++)
     
   while(!file1.eof())
	{
      
      file1>>time>>dummy1>>number>>dummy2>>ch;
      //    cout<<time<<" "<<number<<" "<<ch<<endl;
      time=time/1000000000;








      if(number==1)
	{ hist1->Fill(ch,1/measurement_hour);
	  counter1++;}
      if(number==2)
	{ hist2->Fill(ch,1/measurement_hour);
	  counter2++;}
      
      if(abs(before_time-time)<threshold_time)
	{
	  if(number==1 && before_number==2)
	    {
	      hist3->Fill(ch,1/measurement_hour);
	      hist4->Fill(before_ch,1/measurement_hour);
	      if(before_ch<1010 && before_ch>850)
		{
		  cout<<before_ch<<endl;
		  cout<<ch<<endl;
	      hist5->Fill(before_ch/ch);
		}
	    }
	  if(number==2 && before_number==1)
	    {
	      hist3->Fill(before_ch,1/measurement_hour);
	      hist4->Fill(ch,1/measurement_hour);
	      if(ch<1010 && ch>850)
		{
		  cout<<before_ch<<endl;
		  cout<<ch<<endl;
		  hist5->Fill(ch/before_ch);
		}
	    }
	  
	}


     


	  before_time=time;
	  before_number=number;
	  before_ch=ch;
    }
    cvs1->cd();
    hist1->Draw("hist");
    hist2->Draw("same hist");
    cvs2->cd();
    hist3->Draw("hist");
    hist4->Draw("same hist");
    cvs3->cd();
    hist5->Draw("hist");
    
    hist1->SetLineColor(4);
    hist1->SetLineWidth(2);
    hist2->SetLineColor(2);
    hist2->SetLineWidth(2);
    hist3->SetLineColor(4);
    hist3->SetLineWidth(2);
    hist4->SetLineColor(2);
    hist4->SetLineWidth(2);
    hist5->SetLineColor(2);
    hist5->SetLineWidth(2);
    cout<<counter1<<" "<<counter2<<endl;
    
    return 0;
    }
