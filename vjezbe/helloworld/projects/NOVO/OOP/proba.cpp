#include <iostream>
using namespace std;
void ispisi(int broj);
void ispisi(float temp);
double ispisi(double broj);


//funkcije mogu overloadat pomoću imena i različitog argumenta
//funkcije ne mogu overloadat samo pomoću return type-a
//mogu overloadad ako je i argument drugog tipa

int main(){
    int broj=5;
    float br1=5.0;
    double br=5.00;
    ispisi(broj);
    ispisi(br1);

    br=ispisi(br);
    ispisi(broj);

    cout<<br<<endl<<endl;


    return 0;
}

void ispisi(int broj){
    cout<<"Pozvana je funkcija int"<<endl;
    cout<<broj<<endl;
}
void ispisi(float temp){
        cout<<"Pozvana je funkcija float"<<endl;
    cout<<temp<<endl;
}
double ispisi(double broj){
    cout<<"Pozvana je funkcija double"<<endl;
    return broj;
}