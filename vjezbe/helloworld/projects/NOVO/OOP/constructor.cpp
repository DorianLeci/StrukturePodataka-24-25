#include <iostream>
using namespace std;

class student{
    private:
        int mb;
        char name[50];
        //funkcija koja nema return type
        //po defaultu constructor ne očekuje nikakve parametre i ima prazno tijelo
        //nema nikakav return type
        //također ne vraća nikakve vrijednosti ako nema return type
        //moramo ga deklarirati u public dijelu klase
        //konstruktor se poziva automatski kada kreiramo objekt klase
     public:  
     student();
     double fee;
     void UnesiFee(){
        cin>>fee;
     }
     void display(){
            cout << endl << mb << "\t" << name << "\t" << fee;
     }

        //da bi definirali konstruktor izvan klase moramo ga prvo deklarirati unutar klase

};

//možemo napraviti i konstruktor izvan klase
student::student(){ //kada ga definiramo izvan klase moramo sa dvije dvotočke definirati iz koje je klase
    cout<<"Unesi mb";
    cin>>mb;
    cout<<"Unesi ime";
    cin>>name;

}



int main(){
    student s;

    s.UnesiFee();
    cout<<"Fee public za s:"<<s.fee;
    s.display();

    student s_novi;

    s_novi.UnesiFee();
    s_novi.display();


    //konstruktor se automatski poziva u trenutku kada je objekt deklariran
    


    
    return 0; //ovo je sada objekt, a ne varijabla,ali radim isto kao i sa strukturama u c-u

}