#include <iostream>
using namespace std;

int main(){
    int arr[5]={1,2,3,4,5};
    int i=150;

    int *p=NULL;
    p=&i;
    cout<<*p<<endl;
    
    for(int i=0;i<5;i++){
        cout<<*(arr+i)<<endl;
    }
    cout<<endl;

    return 0;
}