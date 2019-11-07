












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

void two_hist_test(){
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPalette(1);


  TCanvas *cvs1=new TCanvas("cvs1","cvs1",900,900);//TCanvasを用いることでいくつものグラフを一斉に表示できる
  std::ifstream back("output3.txt");//バックグラウンドのデータ
  TH2D *hist1 =new TH2D("hist1","hist1",31,-15.5,15.5,31,-15.5,15.5);//バックグラウンドデータをプロット
  hist1->SetStats(0);//統計ボックス
  hist1->SetTitle("Background_measurement");
  hist1->GetXaxis()->SetTitle("deltaX");
  hist1->GetXaxis()->CenterTitle();
  hist1->GetYaxis()->SetTitle("deltaY");
  hist1->GetYaxis()->CenterTitle();
  int counter=0;
  while(!back.eof())
    {
      Float_t j,k,n,o,p,q,r,s,t,u,v,l,m;
      back  >>j>>k>>l>>m>>n>>o>>p>>q>>r>>s>>t>>u>>v ;
      
      counter++;
      hist1->Fill(l,m);
	
    }

  cout<<counter++<<endl;
  hist1->SetContour(99);//グラデーションを99分割
  hist1->Draw("colz");



  return;







}

