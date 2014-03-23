#include <iostream>
#include <math.h>
using namespace std;
double fl_func_okryg(double ch,int zap)
 {
	 return int(ch*pow(10.0,zap))/double(pow(10.0,zap));
	
 }
void main()

{
    double ch;
	int zap;
	cout<<"vvedite chislo"<<endl;
	cin>>ch;
	cout<<"vvedite chislo posle zap`9toi"<<endl;
	cin>>zap;
	
	
	cout<<fl_func_okryg(ch,zap)<<endl;
}

