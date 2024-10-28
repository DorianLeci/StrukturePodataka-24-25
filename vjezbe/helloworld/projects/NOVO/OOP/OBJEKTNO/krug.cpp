#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
class Kocka;
typedef struct Kocka *position;


class Vrijednosti{
    public:
        int rand_a,rand_b,rand_c;

        Vrijednosti(){
            rand_a=rand_b=rand_c=0;
        }
        


};

class Kocka{
    private:
        double a,b,c;
        Vrijednosti *pok;

    public:
        Kocka();
        void Set_Kocka(double a1,double b1,double c1);
        friend void Set_Pokazivac(position head,Kocka obj,Vrijednosti obj2);
        friend void Ispis(position p);
        position next;

        friend void Delete(position p);
};



Kocka::Kocka(){
    a=b=c=0;
    pok=new(nothrow) Vrijednosti;

    if(!pok){
        cout<<"Greška"<<endl;
        exit(1);
    }

}
void Kocka::Set_Kocka(double a1,double b1,double c1){
    a=a1;
    b=b1;
    c=c1;
}



int main(){
    srand(time(0));
    Kocka obj;
    Vrijednosti obj2;
    double a,b,c;
    cout<<"Unesi 3 stranice kocke"<<endl;
    cin>>a>>b>>c;
    obj.Set_Kocka(a,b,c);

    position head=new (nothrow)Kocka;
    head->next=NULL;

    position temp_head=head;

    Set_Pokazivac(head,obj,obj2);
    temp_head=temp_head->next;

    for(int i=0;i<5;i++){
        Delete(temp_head);
        temp_head=temp_head->next;
    }

    delete head;

    return 0;
}

void Set_Pokazivac(position head,Kocka obj,Vrijednosti obj2){ //vrijednost obj2 nam ne treba zbog pointera
    position q;
    position temp_head=head;
    int min_a,min_b,min_c;
    int max=100;
    min_a=obj.a;
    min_b=obj.b;
    min_c=obj.c;

    for(int i=0;i<5;i++){
        q=new (nothrow) Kocka;
        if(!q->pok){ //dodatna provjera ako konstruktor nije dobro inicijaliziro pointer// ne zaboravi ga inicijalizirat
            q->pok=new Vrijednosti;
            if(!q->pok){
                cout<<"Opet greška"<<endl;
                return;
            }
        }
        cout<<"Pozvan konstruktor"<<endl;
        if(!q){
            cout<<"Greška"<<endl;
            return;
        }
        q->pok->rand_a=rand()%(max-min_a+1)+min_a;
        q->pok->rand_b=rand()%(max-min_b+1)+min_b;
        q->pok->rand_c=rand()%(max-min_c+1)+min_c;

        q->next=head->next;
        head->next=q;

        head=head->next;

    }
    Ispis(temp_head->next);
}

void Ispis(position p){
    while(p!=NULL){
        cout<<p->pok->rand_a<<" "<<p->pok->rand_b<<" "<<p->pok->rand_c<<endl<<endl;
        p=p->next;
    }
}

void Delete(position p){
   delete p->pok;
}