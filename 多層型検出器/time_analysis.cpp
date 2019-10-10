




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
int time_analysis(){
  
  gStyle->SetFrameLineWidth(3);  
  
  TCanvas *cvs1=new TCanvas("cvs1","cvs1",1200,1000); 
  TH1D *hist=new TH1D("hist","hist",1000000,0,1000000);
  TH1D *hist1=new TH1D("hist1","hist1",10000,0,1000000000);
  TH1D *hist2=new TH1D("hist2","hist2",10000,0,1000000000);
  TH1D *hist3=new TH1D("hist3","hist3",10000,0,1000000000);
  Int_t COUNTER;//全体を数えるカウンター
  Int_t counter1,counter2,counter3;
  Double_t time,before_time,before_time1,before_time2,before_time3;
  Int_t number,before_number;
  Double_t ch;
  char dummy1,dummy2;
  Double_t measurement_hour=24;
  before_number=1;
  before_time=0;
  before_time1=0;
  before_time2=0;
  before_time3=0;
  COUNTER=0;
  counter1=0;
  counter2=0;
  counter3=0;


   ifstream file1("d000000.csv");
   
   
  while(!file1.eof())
    {
      
      file1>>time>>dummy1>>number>>dummy2>>ch;
      //  cout<<time<<" "<<number<<" "<<ch<<endl;
      //   time=time;




      // hist->Fill(time-before_time);
      /*   
	  if(number==1)
	    {
	     
	      hist1->Fill(time-before_time1);
	      counter1++;
	       before_time1=time;	      
	    }
	  if(number==2)
	    {
	      hist2->Fill(time-before_time2);
	      counter2++;
	       before_time2=time;	      
	    }
	  if(number==3)
	    {
	      hist3->Fill(time-before_time3);
	      counter3++;
	       before_time3=time;	      
	      }
      */
      //  cout<<number<<" "<<before_number<<endl;      
      if((before_number==1 && number==2) || (before_number==2 && number==1))
	{
	  
	  hist->Fill(time-before_time);
	}
    
      before_number=number;  
      before_time=time;//一つ前の時間情報を取得
      COUNTER++;
    }
  hist->Draw("hist");
  // hist1->Draw("same hist");
  // hist2->Draw("same hist");
  // hist3->Draw("same hist");
  
  hist->SetLineColor(3);
  hist->SetLineWidth(3);
 
  hist1->SetLineColor(2);
  hist1->SetLineWidth(3);
  hist2->SetLineColor(4);
  hist2->SetLineWidth(3);
  hist3->SetLineColor(1);
  hist3->SetLineWidth(3);

  // hist1->Fit("landau");

  cout<<"COUNTER counter1 counter2 counter3"<<endl;
  cout<<COUNTER<<" "<<counter1<<" "<<counter2<<" "<<counter3<<endl;  
  
    return 0;
    }
