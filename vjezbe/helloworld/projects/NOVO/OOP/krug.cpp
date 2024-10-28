#include <iostream>
#include <cmath>
using namespace std;

const double PI=3.14159;

class Circle{
    private:
        double radius;
        double koord_x;
        double koord_y;
        double srediste_x,srediste_y;

    public:
    Circle(double rad,double x,double y,double sred_x,double sred_y): radius(rad),koord_x(x),koord_y(y),srediste_x(sred_x),srediste_y(sred_y){}
        double calcArea(){
            return PI*pow(radius,2);
        }
        double calcOpseg(){
            return PI*radius*2;
        }
        int ProvjeraTočke(){
            if((pow(koord_x-srediste_x,2)+pow(koord_y-srediste_y,2))>pow(radius,2)){
                cout<<"Točka nije unutar kružnice"<<endl;
                return -1;
            }
            else{
                cout<<"Točka jest unutar kružnice"<<endl;
                return 1;
            }
        }

};

int main(){
  double radius,koord_x,koord_y,srediste_x,srediste_y;
  cout<<"Unesi Radijus kruga,te x i y koordinatu"<<endl;

  cin>>radius>>koord_x>>koord_y;
  cout<<"Unesi x i y koordinate sredista"<<endl;
  cin>>srediste_x>>srediste_y;

  Circle circle(radius,koord_x,koord_y,srediste_x,srediste_y);  //ovo je objekt s točno određenim radijusom

  double area=circle.calcArea();
  cout<<"Area:"<<area<<endl;

  double opseg=circle.calcOpseg();
  cout<<"Opseg:"<<opseg<<endl;

  double točka=circle.ProvjeraTočke();
  cout<<"Vraćena vrijednost iz funkcije"<<točka<<endl;

    Circle circle2(radius+1,koord_x+1,koord_y+1,srediste_x+1,srediste_y+1);
    area=circle2.calcArea();
  cout<<"Area:"<<area<<endl;

    opseg=circle2.calcOpseg();
  cout<<"Opseg:"<<opseg<<endl;

    točka=circle2.ProvjeraTočke();
  cout<<"Vraćena vrijednost iz funkcije"<<točka<<endl;


  return 0;
}