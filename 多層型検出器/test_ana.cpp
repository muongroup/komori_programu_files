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
int test_ana(){
  
  
  
  ifstream file1("a000000.csv");
  TH1D*hist1=new TH1D("","",512,0,512);
  TH1D*hist2=new TH1D("","",512,0,512);
  TH1D*hist3=new TH1D("","",512,0,512);
  Int_t counter1,counter2,counter3;
  counter1=0;
  counter2=0;
  counter3=0;
  
  while(!file1.eof())
    {
      Double_t time;
      Int_t number;
      Double_t ch;
      char dummy1,dummy2;
      file1>>time>>dummy1>>number>>dummy2>>ch;
      //    cout<<time<<" "<<number<<" "<<ch<<endl;
    if(number==1)
      {
	hist1->Fill(ch);    
      }
    if(number==2)
      {
	hist2->Fill(ch);    
      }
    if(number==3)
      {
	hist3->Fill(ch);    
      }
    }
  hist1->Draw("hist");
  hist1->SetLineColor(2);
  hist2->Draw("same");
  hist2->SetLineColor(4);
  hist3->Draw("same");
  hist3->SetLineColor(1);
  
  cout<<"counter1 counter2 counter3"<<endl;
  cout<<counter1<<" "<<counter2<<" "<<counter3<<endl;
  
  
  
    return 0;
    }
