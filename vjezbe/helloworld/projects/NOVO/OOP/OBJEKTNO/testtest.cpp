#include <iostream>
using namespace std;
class Krug{
    public:
        int radius;
        double x,y;
    public:
        Krug(){
            radius=0;
            x=0;
            y=0;
        }
        void Ispis(){
            cout<<"Ispis "<<radius<<endl<<x<<endl<<y<<endl<<endl;
        }
};



int main(){
    int radius;double x,y;
    cout<<"Unesi radijus i srediste"<<endl;
    cin>>radius>>x>>y;
   Krug obj;
   Krug &ref=*(&obj);

   *(&ref.radius)=radius;
   *(&ref.x)=x;
   *(&ref.y)=y;

    obj.Ispis();

    obj.radius=5;
    obj.x=6;
    obj.y=4;

    cout<<endl<<"Ispis ref"<<endl<<*(&ref.radius)<<endl<<*(&ref.x)<<endl<<*(&ref.y)<<endl;

    return 0;

}