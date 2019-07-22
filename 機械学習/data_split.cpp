#include <iostream>
#include <fstream>
#include <math.h>
#include<string>
using namespace std;

int main(){

  std::ifstream input1;
  input1.open("data_file.txt");

  std::ofstream output1;
  output1.open("output1.txt");
  std::ofstream output2;
  output2.open("output2.txt");
  std::ofstream output3;
  output3.open("output3.txt");
std::ofstream output4;
 output4.open("output4.txt");
  std::ofstream output5;
  output5.open("output5.txt");
  std::ofstream output6;
 output6.open("output6.txt");
  std::ofstream output7;
  output7.open("output7.txt");
  std::ofstream output8;
  output8.open("output8.txt");
  std::ofstream output9;
  output9.open("output9.txt");
  std::ofstream output10;
  output10.open("output10.txt");
  

  int counter=0;
  while(!input1.eof())
    {
      double incident,p1,p2,p3,p4,i1,i2,i3,i4;
      input1>>incident>>p1>>i1>>p2>>i2>>p3;
      counter=counter+1;
      
      if(counter<1000001)
	{
	  // output1<<incident<<" "<<p1<<" "<<i1<<" "<<p2<<" "<<i2<<" "<<p3<<endl;
	  output1<<p1<<" "<<p2<<" "<<p3<<" "<<i1<<" "<<i2<<" "<<incident<<endl;
	  
	}
      else if(counter<2000001)
	{
	  // output2<<incident<<" "<<p1<<" "<<i1<<" "<<p2<<" "<<i2<<" "<<p3<<endl;
	  output2<<p1<<" "<<p2<<" "<<p3<<" "<<i1<<" "<<i2<<" "<<incident<<endl;
	}
      else if(counter<3000001)
	{
	  // output3<<incident<<" "<<p1<<" "<<i1<<" "<<p2<<" "<<i2<<" "<<p3<<endl;
	  output3<<p1<<" "<<p2<<" "<<p3<<" "<<i1<<" "<<i2<<" "<<incident<<endl;
	}
      else if(counter<4000001)
	{
	  //  output4<<incident<<" "<<p1<<" "<<i1<<" "<<p2<<" "<<i2<<" "<<p3<<endl;
	  output4<<p1<<" "<<p2<<" "<<p3<<" "<<i1<<" "<<i2<<" "<<incident<<endl;
	}
      else if(counter<5000001)
	{
	  // output5<<incident<<" "<<p1<<" "<<i1<<" "<<p2<<" "<<i2<<" "<<p3<<endl;
	  output5<<p1<<" "<<p2<<" "<<p3<<" "<<i1<<" "<<i2<<" "<<incident<<endl;
	}
      else if(counter<6000001)
	{
	  // output6<<incident<<" "<<p1<<" "<<i1<<" "<<p2<<" "<<i2<<" "<<p3<<endl;
	  output6<<p1<<" "<<p2<<" "<<p3<<" "<<i1<<" "<<i2<<" "<<incident<<endl;
	}
      else if(counter<7000001)
	{
	  // output7<<incident<<" "<<p1<<" "<<i1<<" "<<p2<<" "<<i2<<" "<<p3<<endl;
	  output7<<p1<<" "<<p2<<" "<<p3<<" "<<i1<<" "<<i2<<" "<<incident<<endl;
	}
      else if(counter<8000001)
	{
	  // output8<<incident<<" "<<p1<<" "<<i1<<" "<<p2<<" "<<i2<<" "<<p3<<endl;
	  output8<<p1<<" "<<p2<<" "<<p3<<" "<<i1<<" "<<i2<<" "<<incident<<endl;
	}
      else if(counter<9000001)
	{
	  // output9<<incident<<" "<<p1<<" "<<i1<<" "<<p2<<" "<<i2<<" "<<p3<<endl;
	  output9<<p1<<" "<<p2<<" "<<p3<<" "<<i1<<" "<<i2<<" "<<incident<<endl;
	}
      else if(counter<10000001)
	{
	  // output10<<incident<<" "<<p1<<" "<<i1<<" "<<p2<<" "<<i2<<" "<<p3<<endl;
	  output10<<p1<<" "<<p2<<" "<<p3<<" "<<i1<<" "<<i2<<" "<<incident<<endl;
	}
      
      





    }


  return 0;
}

  
