#include <iostream>
#include <string>
using namespace std;

#define N 5

class Student{
    private:
        string ime;
        string prezime;
        int ocjene[N];
    public:
        Student();
        Student(const string &name,const string &surname);
        void Get_Ime_Prezime();
        void Set_Ocjena(int ocjena,int indeks);
        Student(const Student &obj);
};

Student::Student(){
    for(int i=0;i<5;i++){
        ocjene[i]=0;
    }
    printf("\nPozvan prvi konstruktor\n");
    ime="";
    prezime="";
}
Student::Student(const string &name,const string &surname){
    printf("\nPozvan konstruktor s argumentima\n");
    if(name.length()>0){
        ime=name;
    }
    if(surname.length()>0){
        prezime=surname;
    }

}

void Student::Get_Ime_Prezime(){
    cout<<"Ime i prezime: "<<ime<<" "<<prezime<<endl<<endl;
    for(int i=0;i<N;i++){
        cout<<"Ocjena:"<<ocjene[i]<<endl;
    }

}

void Student:: Set_Ocjena(int ocjena,int indeks){
    if(ocjena>=1 && ocjena<=5){
        ocjene[indeks]=ocjena;
    }
    else{
        ocjene[indeks]=0;
    }
}

Student::Student(const Student &obj){
    for(int i=0;i<N;i++){
        ocjene[i]=obj.ocjene[i];
    }
    ime=obj.ime;
    prezime=obj.prezime;
}

int main(){
    Student obj;
    Student s1(obj);
    int ocjena;
    for(int i=0;i<N;i++){
        cout<<"Unesi ocjenu"<<endl;
        cin>>ocjena;
        obj.Set_Ocjena(ocjena,i);
    }
     //kopirni konstruktor
    Student s2(obj);

    obj.Get_Ime_Prezime();cout<<endl;
    s1.Get_Ime_Prezime();cout<<endl;
    s2.Get_Ime_Prezime();cout<<endl;

    return 0;


}