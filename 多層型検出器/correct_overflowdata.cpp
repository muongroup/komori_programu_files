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
int correct_overflowdata(){


  TCanvas *cvs1=new TCanvas("RAW_DATA","RAW_DATA",1200,1000);
  TH1D *hist1=new TH1D("HIGH_GAIN","HIGH_GAIN",4000,0,4000);
  TH1D *hist2=new TH1D("HIGH_GAIN_C","HIGH_GAIN_C",4000,0,4000);//三大コインシデンス
  cvs1->SetLogy();

  ifstream file1("h000000.csv");
  ifstream file2("randomsample.txt");
    double sample[1585];
    for(int i=0;i<1585;i++)
      {
	sample[i]=0;
     
      }

    for(int i=0;i<1585;i++)
      {
	file2>>sample[i];
	cout<<sample[i]<<endl;
      }
    

    
  char dummy1,dummy2;
  double time,number,ch;
  double before_time=0;
  double before_number=0;
  double before_ch=0;
  double threshold_time=0.000005;
  int counter=0;
  int i=0;
  double measurement_hour=0.75;
  while(!file1.eof())
    {

      file1>>time>>dummy1>>number>>dummy2>>ch;
      time=time/1000000000;
      if(abs(before_time-time)<threshold_time)
	{
	  if(before_ch==1023)
	    {cout<<before_time<<" "<<before_number<<" "<<before_ch<<" "<<ch*sample[i]<<endl;
	      hist2->Fill(ch*sample[i],1/measurement_hour);
	      i++;
	      counter++;
	    }
	  if(ch==1023)
	    {
	      cout<<time<<" "<<number<<" "<<ch<<" "<<before_ch*sample[i]<<endl;
	      hist2->Fill(before_ch*sample[i],1/measurement_hour);
	      counter++;
	      i++;
	    }



	

	  

	}
        if(number==2)
	    {
	      hist1->Fill(ch,1/measurement_hour);
		if(ch!=1023)
		  {hist2->Fill(ch,1/measurement_hour);}

		}

	  before_ch=ch;
	  before_number=number;
	  before_time=time;

	 
	  
	  
	



    }
  hist1->Draw("hist");
  hist2->Draw("hist same");
  hist1->SetLineColor(4);
  hist1->SetLineWidth(2);
  hist2->SetLineColor(2);
  hist2->SetLineWidth(2);
 cout<<counter<<endl;

  return 0;
  
}
