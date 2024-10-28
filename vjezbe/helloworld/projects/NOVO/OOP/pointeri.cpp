#include <bits/stdc++.h>
using namespace std;
int square1(int n);
void square2(int *n);
void square3(int &n);
void swapnum(int &i,int &j);

int main(){
    int var=20;
    int *ptr=&var;

    cout<<"Value: "<<*ptr<<endl;
    cout<<"Var: "<<var<<endl;
    cout<<"Adresa:"<<ptr<<endl;
    
    int n1=8; //adresa je odmah ispisana u heksadekadskom
    cout<<"Adresa od n1 u main "<<&n1<<endl;
    cout<<"Square"<<square1(n1)<<endl;
    cout<<"Nema promjene u n1 "<<n1<<endl;
    cout<<endl<<endl;

    int n2=8;
    cout<<"Adresa od n2 u mainu "<<&n2<<endl;
    square2(&n2); //ovo tu pozivamo isto kao i u c-u
    cout<<"Square od n2 "<<n2<<endl;
    cout<<endl<<endl;

    int n3=8;
    cout<<"adresa od n3 u main "<<&n3<<endl;
    square3(n3);
    cout<<"Sada je n3 "<<n3<<endl;

    cout<<endl<<endl;

    int a=10;
    int b=20;
    int &ref_one=a;
    cout<<"vrijednost a: "<<ref_one<<endl;

    ref_one=b;
    cout<<"nova vrijednost a: "<<ref_one<<endl<<endl;
    //referenca ne može
    
    swapnum(a,b);
    cout<<"Nakon zamjene: "<<a<<"  "<<b<<endl<<endl;

    return 0;

    //U c++-u tri načina za proslijed argumenta u funkciju
    //call by value
    //call by rqeference with a pointer argument
    //call by reference with a reference argument
}

int square1(int n){
    return n*n;
}

void square2(int *n){
    *n=*n*(*n);
}
void square3(int &n){
    n=n*n;
}
//reference ne mogu biti setane na null
//niti ne mogu referirati na drugi objekt
void swapnum(int &i,int &j){
    int temp=i;
    i=j;
    j=temp;
}