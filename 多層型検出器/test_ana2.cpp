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
  
  
  
 
  TH1D*hist1=new TH1D("","",512,0,512);
  TH1D*hist2=new TH1D("","",512,0,512);
  TH1D*hist3=new TH1D("","",512,0,512);
  Int_t counter1,counter2,counter3;
  Double_t time,before_time;
  Int_t number;
  Double_t ch;
  char dummy1,dummy2;
  before_time=0;
  counter1=0;
  counter2=0;
  counter3=0;

  char outfile[] = "cross_reg_dmp.out.001";  //読み込むファイルの指定
   ifstream file1("a000000.csv");
   

  while(!file1.eof())
    {
      
      file1>>time>>dummy1>>number>>dummy2>>ch;
      //    cout<<time<<" "<<number<<" "<<ch<<endl;
      time=time/1000000000;




      if(abs(time-before_time)<0.0001)
	{
	  if(number==1)
	    {
	      hist1->Fill(ch);
	      counter1++:
	    }
	  if(number==2)
	    {
	      hist2->Fill(ch);
	      counter2++:
	    }
	  if(number==3)
	    {
	      hist3->Fill(ch);
	      counter3++:
	    }
	}
    
      before_time=time;
    }
  hist1->Draw("hist");
  hist2->Draw("same");
  hist3->Draw("same");
  
  hist1->SetLineColor(2);
  hist2->SetLineColor(4);
  hist3->SetLineColor(1);

  
  
    return 0;
    }
