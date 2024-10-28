#include <iostream>
using namespace std;

int funkcija(int br,int broj);
int funkcija(int br,double broj);
double funkcija(double br,double broj2);
float funkcija(float br,float broj2);

int main(){
    int br;
    double dabl1,dabl2;
    float flot1,flot2;
    cout<<"Unesi flot 1 i flot 2"<<endl;
    cin>>flot1>>flot2;
    cout<<"Unesi double 1 i 2"<<endl;
    cin>>dabl1>>dabl2;

    cout<<funkcija(5,10)<<endl;
    cout<<funkcija(flot1,flot2)<<endl;
    cout<<funkcija(dabl1,dabl2)<<endl;
    cout<<funkcija(10,dabl1)<<endl;
    return 0;
}

int funkcija(int br,int broj){
    return br*broj;
}
double funkcija(double br,double broj2){
    return br+broj2;
}
float funkcija(float br,float broj2){
    return br+broj2;
}
int funkcija(int br,double broj){
    return br/broj;
}

