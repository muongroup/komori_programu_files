#include <iostream>
#include <fstream>
#include <math.h>
#include<string>
using namespace std;

int main(){
   int a,b;    //fortranで書かれたものはヘッダとフッタがついている。前と後ろにそれぞれ4byteずつ,読み込ませておいて捨てる
   double x,y,z,u,v,w,e;//データが6つあるから6つ用意//エネルギーも追加171016  
   double bch,cas,c;
   double xd,yd;  
   std::ofstream kinsan;
   kinsan.open("data_file.txt");//出力ファイル
      
   
   std::ofstream file;
   file.open("original_energy_spectrum.txt");//出力ファイル
   


 
   int cc=0;  //ccは検出器上面で検出された粒子の数を数えている
   /*  for(int filenumber=1;filenumber<2;filenumber++)
     {
       char outfile[] = "cross_reg_dmp.out.001";  //読み込むファイルの指定   
          char numb_1,numb_10;
       if(filenumber<10)
	 {
	   numb_1='0'+filenumber;
	   outfile[20]=numb_1;  //読み込むファイルの指定                  
	   cout<<outfile<<endl;
	 }
       else{
	 numb_1='0'+filenumber-10;
	 numb_10='0'+filenumber/10;
	 outfile[19]=numb_10;
	 outfile[20]=numb_1;  //読み込むファイルの指定                  
	 cout<<outfile<<endl;
       }
         
       // ifstream fin( outfile, ios::in | ios::binary );

       ifstream fin( outfile );//  ファイルを開く
       //  ios::in は読み込み専用  ios::binary はバイナリ形式
       
       if (!fin){
	 cout << "ファイル file.txt が開けません";
	 return 1;
       }
       //  ファイルが開けなかったときの対策
       */


   char outfile[] = "cross_reg_dmp.out";  //読み込むファイルの指定 
   ifstream fin( outfile );//  ファイルを開く
   int temp_counter=0;
   double temp_x,temp_y,temp_z,temp_u,temp_v,temp_w,temp_e;
   double temp_bch,temp_cas;
   double temp2_x,temp2_y,temp2_z,temp2_u,temp2_v,temp2_w,temp2_e;
   double temp2_bch,temp2_cas;


       int aaa=0;
        while(!fin.eof())
       //        for(int i=0;i<100;i++)
	 {  //ファイルの最後まで続ける
	   fin.read( ( char * ) &a, sizeof( int ) );//ヘッダ                   
	   /*   fin.read( ( char * ) &x, sizeof( double ) );
		fin.read( ( char * ) &y, sizeof( double ) );*/
	   fin.read( ( char * ) &z, sizeof( double ) );
	   /*   fin.read( ( char * ) &u, sizeof( double ) );
	   fin.read( ( char * ) &v, sizeof( double ) );   
	   fin.read( ( char * ) &w, sizeof( double ) );*/
	   fin.read( ( char * ) &e, sizeof( double ) );//energy  
	   fin.read( ( char * ) &cas, sizeof( double ) );             
	   fin.read( ( char * ) &bch, sizeof( double ) );
	   //  fin.read( ( char * ) &c, sizeof( double ) );//energy 
	   fin.read( ( char * ) &b, sizeof( int ) );//フッタ
	   //	   	        cout<<z<<" "<<e<<" "<<" "<<cas<<" "<<bch<<endl;
	   // fin>>x>>y>>z>>u>>v>>w>>e>>cas>>bch>>c; アスキーファイル用に残しておく

	       if(z>5.9 && temp_counter==0){
		 file<<e<<endl;//初期のエネルギーをここに保存
		 kinsan<<e<<" ";
	   }

	   

	   if(temp_cas==cas)//もし同じ粒子の場合引き算で付与エネルギー出せる
	     {
	       kinsan<<temp_e-e<<" ";
	       aaa=aaa+1;
	     }
	   
	   if((temp_cas!=cas) && temp_counter!=0)//粒子が変わった場合残りのところを0で埋める
	     {
	       if(temp_z<-0.5)
		 {
		   kinsan<<" "<<endl;
		   aaa=0;
		 }
	       else
		 {
		   kinsan<<temp_e<<" ";//<<endl;
		   aaa=aaa+1;
		   for(int k=0;k<(5-aaa);k++)
		     {
		       kinsan<<"0  ";
		     }
		   kinsan<<" "<<endl;
		   aaa=0;
		 }
	       
	       
	       if(z>5.9){
		 file<<e<<endl;//初期のエネルギーをここに保存
		 kinsan<<e<<" ";
	       }

	   // }
	       
	       //	       cout<<temp_counter<<endl;
	     }//最後に観測されたイベントのみファイルに書き出す
	   temp2_bch=temp_bch;
	   temp2_cas=temp_cas;
	   temp2_x=temp_x;
	   temp2_y=temp_y;
	   temp2_z=temp_z;
	   temp2_u=temp_u;
	   temp2_v=temp_v;
	   temp2_w=temp_w;
	   temp2_e=temp_e;
	   


	   temp_bch=bch;
	   temp_cas=cas;
	   temp_x=x;
	   temp_y=y;
	   temp_z=z;
	   temp_u=u;
	   temp_v=v;
	   temp_w=w;
	   temp_e=e;
	   temp_counter=temp_counter+1;
	   //    cout<<temp_xu<<" "<<temp_yu<<" "<<temp_z<<" "<<temp_u<<" "<<temp_v<<" "<<temp_w<<" "<<temp_e<<" "<<temp_bach<<" "<<temp_cach<<" "<<endl;
	  
	   // cout<<temp_counter<<endl;
	 }
       /*	   if(filenumber==5)
	     {
	       //   file1<<temp_xu<<" "<<temp_yu<<" "<<temp_z<<" "<<temp_u<<" "<<temp_v<<" "<<temp_w<<" "<<temp_e<<" "<<temp_bach<<" "<<temp_cach<<" "<<endl;
	       // cout<<temp_xu<<" "<<temp_yu<<" "<<temp_z<<" "<<temp_u<<" "<<temp_v<<" "<<temp_w<<" "<<temp_e<<" "<<temp_bach<<" "<<temp_cach<<" "<<endl;
	     }//一番最後のイベントだけ書き出す
       
	   // }
	   */

                                              
 
  
  return 0;
}
  
