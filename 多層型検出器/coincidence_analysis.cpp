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
int coincidence_analysis(){
  
  gStyle->SetFrameLineWidth(3);  
  
  TCanvas *cvs1=new TCanvas("DETECTOR1","DETECTOR1",1200,1000); 
  TH1D *hist1=new TH1D("hist1","hist1",512,0,512);//三大コインシデンス
  TH1D *hist2=new TH1D("hist2","hist2",512,0,512);//三大コインシデンス
  TH1D *hist3=new TH1D("hist3","hist3",512,0,512);//三大コインシデンス
  TH1D *hist4=new TH1D("hist4","hist4",512,0,512);//2大コインシデンス
  TH1D *hist5=new TH1D("hist5","hist5",512,0,512);//2大コインシデンス
  TH1D *hist6=new TH1D("hist6","hist6",512,0,512);//2大コインシデンス
 
	     
  Int_t counter1,counter2,counter3;
  Double_t time,before_time,before2_time,before3_time;
  Int_t number,before_number,before2_number,before3_number;
  Double_t ch,before_ch,before2_ch,before3_ch;
  char dummy1,dummy2;
  Double_t measurement_hour=24;
  before_time=0;
  before2_time=0;
  before3_time=0;
  before_number=1;
  before2_number=1;
  before3_number=1;
  before_ch=0;
  before2_ch=0;
  before3_ch=0;
  
  counter1=0;
  counter2=0;
  counter3=0;


   ifstream file1("d000000.csv");
   
   // for(Int_t i=0;i<200;i++)
     
   while(!file1.eof())
    {
      
      file1>>time>>dummy1>>number>>dummy2>>ch;
      //    cout<<time<<" "<<number<<" "<<ch<<endl;
      time=time/1000000000;


      if(number != before_number && before_number != before2_number && number != before2_number)//3台コインシデンスのイベントを抽出する
	{
	  if(abs(time-before_time)<0.000001 && abs(before_time-before2_time)<0.000001)
	    {
	      if(number==1)
		{
		  hist1->Fill(ch,1/measurement_hour);
		  //  cout<<"1 "<<ch<<endl;
		}
	      if(before_number==1)
		{
		  hist1->Fill(before_ch,1/measurement_hour);
		  //  cout<<"2 "<<before_ch<<endl;
		}
	      if(before2_number==1)
		{
		  hist1->Fill(before2_ch,1/measurement_hour);
		  // cout<<"3 "<<before2_ch<<endl;
		}


	      if(number==2)
		{
		  hist2->Fill(ch,1/measurement_hour);
		  
		}
	      if(before_number==2)
		{
		  hist2->Fill(before_ch,1/measurement_hour);
		}
	      if(before2_number==2)
		{
		  hist2->Fill(before2_ch,1/measurement_hour);
		  
		}


	       if(number==3)
		{
		  hist3->Fill(ch,1/measurement_hour);
		  
		}
	      if(before_number==3)
		{
		  hist3->Fill(before_ch,1/measurement_hour);
		}
	      if(before2_number==3)
		{
		  hist3->Fill(before2_ch,1/measurement_hour);
		  
		}
	     
	      /*
	      if(number==2)
	      {
		hist2->Fill(ch,1/measurement_hour);
		  
		  }
		if(before_number==2)
		{
		hist2->Fill(before_ch,1/measurement_hour);
		  }
		if(before2_number==2)
		{
		hist2->Fill(before2_ch,1/measurement_hour);
		  }
	      */
	      
	    }
	}



          
      
      
      if(abs(time-before_time)>0.000001 && abs(before_time-before2_time)<0.000001 && abs(before3_time-before2_time)>0.000001)//
	{
	  if(before_number==1 && before2_number==2)
	    {
		  hist4->Fill(before_ch,1/measurement_hour);
		  hist5->Fill(before2_ch,1/measurement_hour);	
	       cout<<"1 "<<before_ch<<endl;
	    }
	  if(before_number==2 && before2_number==1)
	    {
		  hist4->Fill(before2_ch,1/measurement_hour);
		  hist5->Fill(before_ch,1/measurement_hour);	
	       cout<<"2 "<<before2_ch<<endl;
	    }	  
	}    
	  
      



      	  before3_time=before2_time;
	  before3_number=before2_number;
	  before3_ch=before2_ch;
	  before2_time=before_time;
	  before2_number=before_number;
	  before2_ch=before_ch;
	  before_time=time;
	  before_number=number;
	  before_ch=ch;
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
