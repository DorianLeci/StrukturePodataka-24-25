#include <iostream>
using namespace std;

class test{
    public:
    int px,py;

    test(){
        px=5;
        py=6;
    }
    test(const test &obj1){
        px=obj1.px;
        py=obj1.py;
    }
};

int main(){
    test obj;
    if((int*)&obj==&(obj.px)){
        cout<<"Ista memorijska adresa"<<endl;
    }
    test obj1(obj);
    cout<<&obj<<endl;cout<<&(obj.px)<<endl;cout<<&(obj.py)<<endl;
    cout<<"Drugi objekt"<<endl;
    cout<<&obj1<<endl;cout<<&(obj1.px)<<endl;cout<<&(obj1.py)<<endl;

    return 0;
}