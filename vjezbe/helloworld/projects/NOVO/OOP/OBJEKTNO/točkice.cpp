#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define N 5
#define BROJ_PODJELA 1000
class Pravac;
class Koordinate;
typedef struct Pravac *position;
typedef struct Koordinate *position_koord;



class Pravac{
    private:
        int potencija; //točka x na pravcu
        int koeficijent; //vrijednost pravca
        position next;
        double a,b;

    public:
        Pravac();
        void Set_Pravac(int pot1,int koef1);
        friend void Unos_Pravca(position head,Pravac &obj);
        friend position PronadiPrethodni(position head,position temp);
        friend position ZadnjiVeci(position head,int koef);
        friend position PronadiZadnji(position head);
        friend void Ispis(position head);

        int Return_Potencija(){
            return potencija;
        }
        int Return_Koef(){
            return koeficijent;
        }
        friend double VrijednostPravca(position head,double x);
        friend double Integracija(position head,Pravac obj);

        void Set_Granice(double vrijednost_a,double vrijednost_b,double a1,double b1,position head);
        int ProvjeraKoordinata(double x);

        double ret_a(){
            return a;
        }
        double ret_b(){
            return b;
        }
};

class Koordinate{
    public:
        double x,y;
        position_koord next;


};

class LinearnaInterpolacija{
    private:
        double *lista_vrijednosti;
        double **matrica_x_i_y;
        int broj_interpolacija;
        double a1,b1;
        double vrijednost_a,vrijednost_b;
        Pravac *ref;  
    public:

        LinearnaInterpolacija(Pravac obj,position head);
        void Vrijednosti(position head);
        void Ispis();

        int RetBrojInterpolacija(){
            return broj_interpolacija;
        }
        int RetA(){
            return a1;
        }
        int RetB(){
            return b1;
        }
        void Delete();

        friend void UnosListeKoordinata(position_koord head_koord,LinearnaInterpolacija linear,position head);
        friend void Lista_Najudaljenijih(position_koord head_koord,LinearnaInterpolacija linear,position head);

        
};

void LinearnaInterpolacija::Delete(){
    delete[] lista_vrijednosti;
    for(int i=0;i<broj_interpolacija+1;i++){
        delete []matrica_x_i_y[i];
    }
    delete []matrica_x_i_y;
}

LinearnaInterpolacija::LinearnaInterpolacija(Pravac obj,position head){
    ref=&obj;
    cout<<"Unesi broj točaka na koje zelis podijeliti pravac"<<endl;
    cin>>broj_interpolacija;
    while(broj_interpolacija<=0){
        cout<<"Krivi unos.Ponovno unesi"<<endl;
        cin>>broj_interpolacija;
        }
    cout<<"Unesi granice a i b"<<endl;
    cin>>a1>>b1;

    vrijednost_a=VrijednostPravca(head,a1);
    vrijednost_b=VrijednostPravca(head,b1);

    ref->Set_Granice(vrijednost_a,vrijednost_b,a1,b1,head);
    if(ref->ret_a()!=0 || ref->ret_b()!=0){
        cout<<"Točno unesene granice"<<endl;
    }
    else if(ref->ret_a()==0 && ref->ret_b()==0){
        while(1){
              if(ref->ret_a()!=0 || ref->ret_b()!=0){
        cout<<"Točno unesene granice"<<endl;
        break;
        }  
        cout<<"Ponovno unesi granice"<<endl;
        cin>>a1>>b1;
        vrijednost_a=VrijednostPravca(head,a1);
        vrijednost_b=VrijednostPravca(head,b1);
        }

    }

    lista_vrijednosti=new (nothrow) double[broj_interpolacija+1];

    if(lista_vrijednosti==nullptr){
        cout<<"Greška pri malociranju"<<endl;
        exit(1);
    }
    matrica_x_i_y=new (nothrow)double*[broj_interpolacija+1];
    for(int i=0;i<broj_interpolacija+1;i++){
        matrica_x_i_y[i]=new (nothrow)double[2];
    }
    if(matrica_x_i_y==nullptr){
        cout<<"Greška pri malociranju"<<endl;
        exit(1);
    }
    else if(matrica_x_i_y!=nullptr){
        for(int i=0;i<broj_interpolacija;i++){
            if(matrica_x_i_y[i]==nullptr){
                cout<<"Greška pri malociranju"<<endl;
                exit(1);
            }
        }
    }
    //nakon uspješne malokacije
        lista_vrijednosti[0]=vrijednost_a;
    lista_vrijednosti[broj_interpolacija]=vrijednost_b;
    matrica_x_i_y[0][0]=a1;
    matrica_x_i_y[0][1]=vrijednost_a;
    matrica_x_i_y[broj_interpolacija][0]=b1;
    matrica_x_i_y[broj_interpolacija][1]=vrijednost_b;
}


void LinearnaInterpolacija::Vrijednosti(position head){
    double h=fabs((a1-b1))/broj_interpolacija;
    double x;
    for(int i=1;i<broj_interpolacija;i++){
        x=a1+i*h;
        lista_vrijednosti[i]=VrijednostPravca(head,x);
        matrica_x_i_y[i][0]=x;
        matrica_x_i_y[i][1]=lista_vrijednosti[i];
    }

}

void LinearnaInterpolacija::Ispis(){
    cout<<"Lista vrijednosti"<<endl;
    for(int i=0;i<broj_interpolacija+1;i++){
        cout<<lista_vrijednosti[i]<<" ";
    }
    cout<<endl;

    cout<<"Matrica x i y koordinata"<<endl;
    for(int i=0;i<broj_interpolacija+1;i++){
        cout<<matrica_x_i_y[i][0]<<" "<<matrica_x_i_y[i][1]<<endl;
    }
    cout<<endl;
}

int Pravac::ProvjeraKoordinata(double x){
    if(x<a || x>b){
        return 0;
    }
    return 1;
}


Pravac::Pravac(){
    potencija=-1;;
    koeficijent=-1;
    next=nullptr;
    a=0;
    b=0;
}

void Pravac::Set_Granice(double vrijednost_a,double vrijednost_b,double a1,double b1,position head){
    while(vrijednost_a>1000 || vrijednost_b>1000){
        cout<<"Ponovno unesi granice"<<endl;
        cin>>a1>>b1;
        vrijednost_a=VrijednostPravca(head,a1);
        vrijednost_b=VrijednostPravca(head,b1);
    }
    a=a1;
    b=b1;
}


void Pravac::Set_Pravac(int pot1,int koef1){
    if(pot1<100 && koef1<100){
        potencija=pot1;
        koeficijent=koef1;
    }
}

position_koord PronadiPrethodniKoord(position_koord head_koord,position_koord temp);
position_koord PronadiZadnjiVeci(position_koord head_koord,double q);
void IspisKoord(position_koord p);
void Zamjena(position_koord p,position_koord temp,position_koord tempHead);
position_koord Lista_NajdaljihKoordinata();
position_koord PronadiSljedeci(position_koord head,position_koord ref);

int main(){
    srand(time(0));
    Pravac obj;
    position head=new(nothrow) Pravac;
    double integral,a,b,vrijednost_a,vrijednost_b;

    position_koord head_novi=NULL;

    position_koord head_koord=new (nothrow)Koordinate;

    if(head_koord==nullptr){
        cout<<"Pogreška u malociranju"<<endl;
        return -1;
    }
    head_koord->next=nullptr;




    if(head==nullptr){
        cout<<"Pogreška"<<endl;
        exit(1);
    }

    Unos_Pravca(head,obj);

    cout<<"Unesi područje integracije"<<endl;
    cin>>a>>b;
    vrijednost_a=VrijednostPravca(head,a);
    vrijednost_b=VrijednostPravca(head,b);
    cout<<"Vrijednosti granica: "<<vrijednost_a<<" "<<vrijednost_b<<endl;
    obj.Set_Granice(vrijednost_a,vrijednost_b,a,b,head);

    integral=Integracija(head,obj);
    cout<<"Površina pravca na intervalu jest "<<integral<<endl<<endl;

    LinearnaInterpolacija linear(obj,head);
    linear.Vrijednosti(head);

    cout<<"Ispis podatak iz linear"<<endl;
    linear.Ispis();

    UnosListeKoordinata(head_koord,linear,head);



    linear.Delete();

    delete head;
    delete head_koord;

    return 0;
}

void Unos_Pravca(position head,Pravac &obj){
    int pot,koef;
    position q;
    position temp;
    position prethodni;
    position zadnji_veci;
    position zadnji;
    for(int i=0;i<N;i++){
        temp=head->next;
        q=new(nothrow) Pravac;

        if(q==nullptr){
            cout<<"Pogreška u alociranju"<<endl;
            exit(1);
        }
        cout<<"Unesi pot i koef"<<endl;
        cin>>pot>>koef;
        obj.Set_Pravac(pot,koef);

        if(obj.koeficijent!=-1 && obj.potencija!=-1){
            q->koeficijent=obj.koeficijent;
            q->potencija=obj.potencija;
        }
        else{
            q->koeficijent=0;
            q->potencija=0;
        }

        if(i==0){
            q->next=head->next;
            head->next=q;   
        }
        else{
            while(temp!=nullptr){
                if(q->potencija>=temp->potencija){
                    cout<<"Q na koef "<<q->potencija<<" Temp na koef "<<temp->potencija;
                    cout<<"Prekid"<<endl;
                    break;
                }
            temp=temp->next;
            }
            if(temp!=nullptr){
                cout<<"Temp: "<<temp->potencija<<endl;
                prethodni=PronadiPrethodni(head,temp);

                q->next=prethodni->next;
                prethodni->next=q;
            }
            else if(temp==nullptr){
                cout<<"Temp je nullptr"<<endl;
                zadnji_veci=ZadnjiVeci(head,q->potencija);
                if(zadnji_veci!=nullptr){
                    q->next=zadnji_veci->next;
                    zadnji_veci->next=q;
                }
                else if(zadnji_veci==nullptr){
                    zadnji=PronadiZadnji(head);
                    q->next=zadnji->next;
                    zadnji->next=q;
                }

            }
        }
    cout<<"Trenutno stanje"<<endl;
    Ispis(head->next);
    }
}

position PronadiPrethodni(position head,position temp){
    while((head->next!=nullptr)&&(head->next!=temp)){
        head=head->next;
    }
    if(head->next==nullptr){
        cout<<"Nema prethodnog"<<endl;
        return nullptr;
    }
    return head;
}

position ZadnjiVeci(position head,int koef){
    head=head->next; //prvi el
    position zadnji=nullptr;
    while(head!=nullptr){
        if(head->koeficijent>koef){
            zadnji=head;
        }
        head=head->next;
    }
    if(zadnji==nullptr){
        cout<<"Nije nađeno"<<endl;
        return zadnji;
    }
    return zadnji;
}

position PronadiZadnji(position head){
    while(head->next!=NULL){
        head=head->next;
    }

    return head;
}

void Ispis(position head){
    while(head!=nullptr){
        cout<<head->koeficijent<<" x^"<<head->potencija<<endl;
        head=head->next;
    }
}

double VrijednostPravca(position head,double x){
    //vrijednost pravca u nekoj točki
    head=head->next;
    double vrijednost=0;

    while(head!=nullptr){
        vrijednost+=head->koeficijent*pow(x,head->potencija);
        head=head->next;
    }
    return vrijednost;
}

double Integracija(position head,Pravac obj){
    double h=fabs((obj.b-obj.a))/BROJ_PODJELA;
    double suma=0;
    double x,integral;
    cout<<"a "<<obj.a<<endl;
    for(int i=1;i<BROJ_PODJELA;i++){
        x=obj.a+i*h;
        suma+=VrijednostPravca(head,x);
    }
    cout<<"Suma*2 "<<suma*2<<endl;
    integral=(h/2)*(VrijednostPravca(head,obj.a)+VrijednostPravca(head,obj.b)+2*suma);

    return integral;

}
void UnosListeKoordinata(position_koord head_koord,LinearnaInterpolacija linear,position head){
    double x_temp;
    position_koord head_koord_temp=head_koord;
    position_koord q;
    position_koord temp;
    position_koord prethodni;
    position_koord zadnji_veci;
    for(int i=0;i<linear.broj_interpolacija;i++){

        q=new (nothrow) Koordinate;
        if(q==NULL){
            cout<<"Pogreška u malociranju"<<endl;
            return;
        }
        cout<<"Unesi x koordinatu"<<endl;
        cin>>x_temp;

        q->x=x_temp;
        q->y=VrijednostPravca(head,x_temp);

        if(i==0){
            q->next=head_koord->next;
            head_koord->next=q;
        }
        else{
            temp=head_koord->next;
            while((temp!=NULL)){
                if(q->x>=temp->x){
                    break;
                }
                temp=temp->next;
            }
        if(temp!=NULL){
            prethodni=PronadiPrethodniKoord(head_koord,temp);
            q->next=prethodni->next;
            prethodni->next=q;
        }
        else if(temp==NULL){
            zadnji_veci=PronadiZadnjiVeci(head_koord,q->x);
            if(zadnji_veci!=NULL){
                q->next=zadnji_veci->next;
                zadnji_veci->next=q;
            }

        }
        }

    }
        cout<<"Trenutno stanje"<<endl;
    IspisKoord(head_koord_temp->next);

}

position_koord PronadiPrethodniKoord(position_koord head_koord,position_koord temp){

    while((head_koord->next!=NULL)&&(head_koord->next!=temp)){
        head_koord=head_koord->next;
    }
    if(head_koord->next==NULL){
        cout<<"Nije pronađeno"<<endl;
        return NULL;
    }
    return head_koord;

}

position_koord PronadiZadnjiVeci(position_koord head_koord,double q){
    head_koord=head_koord->next; //prvi el
    position_koord zadnji=nullptr;
    while(head_koord!=nullptr){
        if(head_koord->x>q){
            zadnji=head_koord;
        }
        head_koord=head_koord->next;
    }
    if(zadnji==nullptr){
        cout<<"Nije nađeno"<<endl;
        return zadnji;
    }
    return zadnji;
}

void IspisKoord(position_koord p){
    while(p!=NULL){
        cout<<p->x<<" "<<p->y<<endl;
        p=p->next;
    }
}
position_koord Lista_NajdaljihKoordinata(){
    double rand_x,rand_y;
    position_koord head_novi;
    position_koord q;
    head_novi=new (nothrow)Koordinate;
    if(head_novi==nullptr){
        cout<<"Pogreška u malociranju"<<endl;
        return nullptr;
    }
    head_novi->next=nullptr;

    for(int i=0;i<5;i++){
        q=new (nothrow)Koordinate;
            if(q==nullptr){
        cout<<"Pogreška u malociranju"<<endl;
        return nullptr;
    }
        rand_x=rand()%(20-10+1)+10;
        rand_y=rand()%(20-10+1)+10;
        q->x=rand_x;
        q->y=rand_y;

        q->next=head_novi->next;
        head_novi->next=q;
    }
    
    cout<<"Head novi"<<endl;
    IspisKoord(head_novi->next);

    position_koord temp_head_novi=head_novi;
    position_koord temp_temp;
    position_koord sljedeci;
    position_koord sljedeci_p;

    double udaljenost_max=sqrt(pow(head_novi->next->x-0,2)+pow(head_novi->next->y-0,2));
    double temp_udaljenost;


    return temp_head_novi;


}
void Lista_Najudaljenijih(position_koord head_koord,LinearnaInterpolacija linear,position head){
    int brojac=1;
    position_koord temp=head_koord->next;
    position_koord tempHead=head_koord;
    head_koord=head_koord->next;
    double udaljenost_max=sqrt(pow(head_koord->x-0,2)+pow(head_koord->y-0,2));
    double temp_udaljenost;
    double sredina_x,sredina_y;

    sredina_x=0;
    sredina_y=0;

    cout<<"Sredina x "<<sredina_x<<endl;
    cout<<"Sredina y "<<sredina_y<<endl;

    head_koord=head_koord->next;

    while(head_koord!=NULL){

        temp_udaljenost=sqrt(pow(head_koord->x-sredina_x,2)+pow(head_koord->y-sredina_y,2));
        if(temp_udaljenost>udaljenost_max){
            cout<<"Nađeno"<<" Trenutno: "<<head_koord->x<<endl;
            cout<<"Prijašnje "<<temp->x<<endl;
            udaljenost_max=temp_udaljenost;
            Zamjena(head_koord,temp,tempHead);
            temp=head_koord;
            head_koord=temp;
        }
        brojac++;
        cout<<endl<<"Trenutačno stanje"<<endl;
        IspisKoord(tempHead->next);

        head_koord=head_koord->next;
    }

}

void Zamjena(position_koord p,position_koord temp,position_koord tempHead){
    position_koord pom;
    double pom_x,pom_y;
    position_koord prethodni_p=PronadiPrethodniKoord(tempHead,p);
    position_koord prethodni_temp=PronadiPrethodniKoord(tempHead,temp);
    position_koord next_temp=temp->next;

    pom_x=p->x;
    pom_y=p->y;
    p->x=temp->x;
    p->y=temp->y;
    temp->x=pom_x;
    temp->y=pom_y;

    pom=p;
    p=temp;   
    temp=pom;


    prethodni_temp->next=p;
    p->next=next_temp;

    prethodni_p->next=temp;


    
}

position_koord PronadiSljedeci(position_koord head,position_koord ref){
    while(head!=NULL){
        if(head==ref){
            return head->next;
        }
        head=head->next;
    }
    return head->next;
}