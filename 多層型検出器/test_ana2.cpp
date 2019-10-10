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
int test_ana2(){
  
  gStyle->SetFrameLineWidth(3);  
  
  TCanvas *cvs1=new TCanvas("cvs1","cvs1",1200,1000); 
  TH1D *hist1=new TH1D("hist1","hist1",512,0,512);
  TH1D *hist2=new TH1D("hist2","hist2",512,0,512);
  TH1D *hist3=new TH1D("hist3","hist3",512,0,512);
  Int_t counter1,counter2,counter3;
  Double_t time,before_time;
  Int_t number;
  Double_t ch;
  char dummy1,dummy2;
  Double_t measurement_hour=24;
  before_time=0;
  counter1=0;
  counter2=0;
  counter3=0;


   ifstream file1("d000000.csv");
   

  while(!file1.eof())
    {
      
      file1>>time>>dummy1>>number>>dummy2>>ch;
      //    cout<<time<<" "<<number<<" "<<ch<<endl;
      time=time/1000000000;




      if(abs(time-before_time)<0.000001)
	{
	  if(number==1)
	    {
	      hist1->Fill(ch,1/measurement_hour);
	      counter1++;
	    }
	  if(number==2)
	    {
	      hist2->Fill(ch,1/measurement_hour);
	      counter2++;
	    }
	  if(number==3)
	    {
	      hist3->Fill(ch,1/measurement_hour);
	      counter3++;
	    }
	}
    
      before_time=time;
    }
  hist1->Draw("hist");
  hist2->Draw("same hist");
  hist3->Draw("same hist");
  
  hist1->SetLineColor(2);
  hist1->SetLineWidth(3);
  hist2->SetLineColor(4);
  hist2->SetLineWidth(3);
  hist3->SetLineColor(1);
  hist3->SetLineWidth(3);

  // hist1->Fit("landau");

  cout<<"counter1 counter2 counter3"<<endl;
  cout<<counter1<<" "<<counter2<<" "<<counter3<<endl;  
  
    return 0;
    }
