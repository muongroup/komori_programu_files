


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
  TCanvas *cvs2=new TCanvas("DETECTOR2","DETECTOR2",1200,1000);
  TCanvas *cvs3=new TCanvas("DETECTOR3","DETECTOR3",1200,1000);

  cvs1->SetLogy();
  cvs2->SetLogy();
  cvs3->SetLogy();



  TH1D *hist1=new TH1D("DETECTOR1_row","Detector1_row",1024,0,1024);//三大コインシデンス
  TH1D *hist2=new TH1D("DETECTOR2_row","DETECTOR2_row",1024,0,1024);//三大コインシデンス
  TH1D *hist3=new TH1D("DETECTOR3_row","DETECTOR3_row",1024,0,1024);//三大コインシデンス
  TH1D *hist4=new TH1D("DETECTOR1_triple_coin","Detector1_triple_coin",1024,0,1024);//三大コインシデンス
  TH1D *hist5=new TH1D("DETECTOR2_triple_coin","DETECTOR2_triple_coin",1024,0,1024);//三大コインシデンス
  TH1D *hist6=new TH1D("DETECTOR3_triple_coin","DETECTOR3_triple_coin",1024,0,1024);//三大コインシデンス
  TH1D *hist7=new TH1D("DETECTOR1_1_and_2","DETECTOR1_1_and_2",1024,0,1024);//2大コインシデンス
  TH1D *hist8=new TH1D("DETECTOR1_1_and_3","DETECTOR1_1_and_3",1024,0,1024);//2大コインシデンス
  TH1D *hist9=new TH1D("DETECTOR2_1_and_2","DETECTOR2_1_and_2",1024,0,1024);//2大コインシデンス
  TH1D *hist10=new TH1D("DETECTOR3_1_and_3","DETECTOR3_1_and_3",1024,0,1024);//2大コインシデンス
  TH1D *hist11=new TH1D("DETECTOR2_2_and_3","DETECTOR2_1_and_2",1024,0,1024);//2大コインシデンス
  TH1D *hist12=new TH1D("DETECTOR3_2_and_3","DETECTOR3_1_and_3",1024,0,1024);//2大コインシデンス


  hist1->SetStats(0);
  hist2->SetStats(0);
  hist3->SetStats(0);
  
	     
  Int_t counter1,counter2,counter3,counter4,counter5,counter6,counter7,counter8,counter9,counter10,counter11,counter12;
  Double_t time,before_time,before2_time,before3_time;
  Int_t number,before_number,before2_number,before3_number;
  Double_t ch,before_ch,before2_ch,before3_ch;
  char dummy1,dummy2;
  Double_t measurement_hour=3;
  Double_t threshold_time=0.0000005;
  Double_t threshold_time_double=0.0000005;
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
  counter4=0;
  counter5=0;
  counter6=0;
  counter7=0;
  counter8=0;
  counter9=0;
  counter10=0;
  counter11=0;
  counter12=0;


   ifstream file1("n000000.csv");
   
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
      if(number==3)
	{ hist3->Fill(ch,1/measurement_hour);
	  counter3++;}





      
      if(number != before_number && before_number != before2_number && number != before2_number)//3台コインシデンスのイベントを抽出する
	{
	  if(abs(time-before_time)<threshold_time && abs(before_time-before2_time)<threshold_time)//連続するイベントの時間差が1μs以下
	    {
	      if(number==1)
		{
		  
		  hist4->Fill(ch,1/measurement_hour);
		  // cout<<"1 "<<ch<<endl;
		}
	      if(before_number==1)
		{
		 
		  hist4->Fill(before_ch,1/measurement_hour);
		  //  cout<<"2 "<<before_ch<<endl;
		}
	      if(before2_number==1)
		{
		 
		  hist4->Fill(before2_ch,1/measurement_hour);
		  // cout<<"3 "<<before2_ch<<endl;
		}


	      if(number==2)
		{
		 
		  hist5->Fill(ch,1/measurement_hour);
		  
		}
	      if(before_number==2)
		{
		 
		  hist5->Fill(before_ch,1/measurement_hour);
		}
	      if(before2_number==2)
		{
		 
		  hist5->Fill(before2_ch,1/measurement_hour);
		  
		}


	       if(number==3)
		{
		 
		  hist6->Fill(ch,1/measurement_hour);
		  
		}
	      if(before_number==3)
		{
		 
		  hist6->Fill(before_ch,1/measurement_hour);
		}
	      if(before2_number==3)
		{
		 
		  hist6->Fill(before2_ch,1/measurement_hour);
		  
		}
	     
	      counter4++;
	      counter5++;
	      counter6++;
	      
	    }
	}



          
      
      
      if(abs(time-before_time)>threshold_time_double && abs(before_time-before2_time)<threshold_time_double && abs(before3_time-before2_time)>threshold_time_double)//1と2のみコインシデンス
	{
	  if(before_number==1 && before2_number==2)
	    {
	      
	      hist7->Fill(before_ch,1/measurement_hour);
	      hist9->Fill(before2_ch,1/measurement_hour);	
	      // cout<<"1 "<<before_ch<<endl;
	      counter7++;
	      counter9++;
	    }
	  if(before_number==2 && before2_number==1)
	    {
	      
	      hist7->Fill(before2_ch,1/measurement_hour);
	      hist9->Fill(before_ch,1/measurement_hour);	
	      // cout<<"2 "<<before2_ch<<endl;
	      counter7++;
	  counter9++;
	    }
	  
	}    
      

      
      if(abs(time-before_time)>threshold_time_double && abs(before_time-before2_time)<threshold_time_double && abs(before3_time-before2_time)>threshold_time_double)//
	{
	  if(before_number==1 && before2_number==3)
	    {
	     
		  hist8->Fill(before_ch,1/measurement_hour);
		  hist10->Fill(before2_ch,1/measurement_hour);	
		  //		  cout<<"1 "<<before_ch<<endl;
		   counter8++;
		   counter10++;
	    }
	  if(before_number==3 && before2_number==1)
	    {
	     
	      hist8->Fill(before2_ch,1/measurement_hour);
	      hist10->Fill(before_ch,1/measurement_hour);	
	      //  cout<<"2 "<<before2_ch<<endl;
	       counter8++;
	       counter10++;
	    }
	 
	}    





       if(abs(time-before_time)>threshold_time_double && abs(before_time-before2_time)<threshold_time_double && abs(before3_time-before2_time)>threshold_time_double)//
	{
	  if(before_number==2 && before2_number==3)
	    {
	     
	      hist11->Fill(before_ch,1/measurement_hour);
	      hist12->Fill(before2_ch,1/measurement_hour);	
	      //		  cout<<"1 "<<before_ch<<endl;
	      counter11++;
	      counter12++;
	    }
	  if(before_number==3 && before2_number==2)
	    {
	     
	      hist11->Fill(before2_ch,1/measurement_hour);
	      hist12->Fill(before_ch,1/measurement_hour);	
	      //  cout<<"2 "<<before2_ch<<endl;
	       counter11++;
	       counter12++;
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
    cvs1->cd();
    hist1->Draw("hist");
    hist4->Draw("same hist");
    hist7->Draw("same hist");
    hist8->Draw("same hist");
    
    cvs2->cd();
    hist2->Draw("hist");
    hist5->Draw("same hist");
    hist9->Draw("same hist");
    hist11->Draw("same hist");
    
    cvs3->cd();
    hist3->Draw("hist");
    hist6->Draw("same hist");
    hist10->Draw("same hist");
    hist12->Draw("same hist");
    
    hist1->SetLineColor(1);
    hist1->SetLineWidth(2);
    hist2->SetLineColor(1);
    hist2->SetLineWidth(2);
    hist3->SetLineColor(1);
    hist3->SetLineWidth(2);
    
    hist4->SetLineColor(2);
    hist4->SetLineWidth(3);
    hist5->SetLineColor(2);
    hist5->SetLineWidth(3);
    hist6->SetLineColor(2);
    hist6->SetLineWidth(3);

    hist7->SetLineColor(4);
    hist7->SetLineWidth(2);
    hist8->SetLineColor(6);
    hist8->SetLineWidth(2);
    hist9->SetLineColor(4);
    hist9->SetLineWidth(2);
    
    hist10->SetLineColor(6);
    hist10->SetLineWidth(2);
    hist11->SetLineColor(3);
    hist11->SetLineWidth(2);
    hist12->SetLineColor(3);
    hist12->SetLineWidth(2);

  // hist3->Fit("landau");

  cout<<"counter1 counter4 counter7 counter8"<<endl;
  cout<<counter1<<" "<<counter4<<" "<<counter7<<" "<<counter8<<endl;  
  cout<<"counter2 counter5 counter9 counter11"<<endl;
  cout<<counter2<<" "<<counter5<<" "<<counter9<<" "<<counter11<<endl;
  cout<<"counter3 counter6 counter10 counter12"<<endl;
  cout<<counter3<<" "<<counter6<<" "<<counter10<<" "<<counter12<<endl;
  
 
  
    return 0;
    }
