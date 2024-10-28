#include <iostream>
#include <cmath>
using namespace std;

class test{
    public:
        int broj;
        char ime[20];
    test();
    void display();

};



test:: test(){
    display();
    cin>>broj>>ime;
}

void test:: display(){
    cout<<"Unesi broj i ime:"<<endl;
}

int main(){
    test obj;


    cout<<"Broj i ime:"<<obj.broj<<" "<<obj.ime<<endl;

    return 0;
}