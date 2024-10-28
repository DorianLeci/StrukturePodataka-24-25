#include <iostream>
using namespace std;

class kocka{
    public:
    double x,y,z;

    kocka(){
        cout<<"Unesi x i y i z"<<endl;
        cin>>x>>y>>z;
    }
};


int main(){
    kocka koc;
    kocka &p=koc;

    int arr[]={1,2,3,4,5};
    int n=sizeof(arr)/sizeof(arr[0]);

    p.x+=1;
    p.y+=1;
    p.z+=1;
    cout<<"Ispis"<<endl;
    cout<<p.x<<endl<<p.y<<endl<<p.z<<endl;


    return 0;
}

