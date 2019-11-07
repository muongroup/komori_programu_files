#include <iostream>
#include <fstream>
#include <math.h>
#include<string>
using namespace std;

int main(){
  int a,b;    //fortranで書かれたものはヘッダとフッタがついている。前と後ろにそれぞれ4byteずつ,読み込ませておいて捨てる
  double x,y,z,e;
  double cas;
  double xd,yd; 
  char outfile[] = "cross_reg_dmp.out.001";  //読み込むファイルの指定
  ifstream fin( outfile );//  ファイルを開く
  ofstream ofs("output.txt");
  int counter=0;
  double temp_x,temp_y,temp_z,temp_e,temp_cas;
  temp_x=0;
  temp_y=0;
  temp_z=0;
  temp_e=0;
  temp_cas=0;
  counter=0;
  int counter_temp=0;
   while(!fin.eof())
     // for(int i=0;i<15;i++)
    {  //ファイルの最後まで続ける
      fin.read( ( char * ) &a, sizeof( int ) );//ヘッダ
      fin.read( ( char * ) &x, sizeof( double ) );
      fin.read( ( char * ) &y, sizeof( double ) );//energy 
      fin.read( ( char * ) &z, sizeof( double ) );
      fin.read( ( char * ) &e, sizeof( double ) );//energy
      fin.read( ( char * ) &cas, sizeof( double ) );
      fin.read( ( char * ) &b, sizeof( int ) );//フッタ
      
      // fin>>x>>y>>z>>e>>cas;
      //  cout<<z<<" "<<e<<" "<<cas<<endl;
     
	
      if(temp_cas==cas)//もしも上下でcas番号が一緒の場合
	{
	  if(temp_z>0 && z<0 && z>-16)//もしも連続で上下のmu-PSDを通った場合
	    {//cout<<temp_z<<" ";
	     // cout<<temp_x<<" "<<ceil(temp_x/0.8375)+7<<"  "<<x<<" "<<ceil(x/0.8375)+7<<" "<<ceil(x/0.8375)+7-ceil(temp_x/0.8375)+7<<endl;
	     // cout<<temp_y<<" "<<ceil(temp_y/0.8375)+7<<"  "<<y<<" "<<ceil(y/0.8375)+7<<" "<<ceil(y/0.8375)+7-ceil(temp_y/0.8375)+7<<endl;
	      counter_temp++;
	      // ofs<<temp_z<<" "<<temp_x-x<<" "<<temp_y-y<<" ";
	      ofs<<temp_z<<" "<<temp_e<<" "<<-ceil(x/0.8375)+ceil(temp_x/0.8375)<<" "<<-ceil(temp_y/0.8375)+ceil(y/0.8375)<<" ";//上のmu-PSD番号、下のmu-PSD番号、xのベクトルプロット、yのベクトルプロットを書き込む
	    }
	  else if(counter==1){//cout<<"000"<<" ";
	  }

	  counter++;
	  // cout<<counter<<endl;
	  // cout<<temp_e-e<<" ";
	  // ofs<<temp_e-e<<" ";//続けて付与エネルギーを書き出していく
	    ofs<<"-999"<<" "<<temp_e-e<<" ";//続けて付与エネルギーを書き出していく
	}
      if(temp_cas!=cas)//番号が違った段階で
	{counter=1;
	  // cout<<counter<<endl;
	  // cout<<endl;
	  ofs<<endl;//改行
	}
      temp_x=x;
      temp_y=y;
      temp_z=z;
      temp_e=e;
      temp_cas=cas;
      


      
    }
   cout<<counter_temp<<endl;  
}


 
