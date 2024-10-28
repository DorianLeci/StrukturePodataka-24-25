#include <iostream>
#include <cmath>
using namespace std;

#define N 2
class Krug{
    private:
        double radius;
    public:
        Krug(){
            radius=0;
        }
    void Set_Radius(double rad_temp){
        if(rad_temp>0){
            radius=rad_temp;
        }
    }
    double Return_Radius(){
        return radius;
    }
};
class Tocka{
    private:
        double *px,*py;
        double **lista_točaka;
    public:
        Krug *lista_kruznica;

        Tocka();
        Tocka(Tocka &obj);
        ~Tocka();
        void Set_Tocka(double tocka_x,double tocka_y);
        void Get_tocka();
        void Get_Adresa();
        void Set_Tocka_Usporedba(double tocka_x,double tocka_y,int indeks);

        friend void Provjera_Tocke(Tocka *obj);
        friend void Provjera_Tocke2(Tocka &obj);

};

Tocka::Tocka(){
    printf("\nPozvan konstruktor\n");
    px=new (nothrow) double;
    py=new (nothrow) double;
    lista_kruznica=new (nothrow) Krug;
    lista_točaka=new (nothrow)double*[N];
    for(int i=0;i<N;i++){
        lista_točaka[i]=new (nothrow)double[2];
    }
    if(lista_kruznica==nullptr){
        cout<<"Greška pri alokaciji liste kruznica"<<endl;
        exit(1);
    }
    if(px==nullptr){
        cout<<"Greška pri alokaciji px"<<endl;
        exit(1);
    }
    if(py==nullptr){
        cout<<"Greška pri alokaciji py"<<endl;
        exit(1);
    }
    if(lista_točaka==nullptr){
        cout<<"Greška pri alokaciji liste"<<endl;
    }

}
Tocka::~Tocka(){
    printf("\nPozvan destruktor\n");
    delete px;
    delete py;
    for(int i=0;i<N;i++){
        delete [] lista_točaka[i];
    }
    delete [] lista_točaka;

    delete lista_kruznica;
}

void Tocka::Set_Tocka(double tocka_x,double tocka_y){
    //točke mogu samo biti pozitivne
    if(tocka_x>=0 && tocka_y>=0){
        *px=tocka_x;
        *py=tocka_y;
    }
    else{
        *px=0;
        *py=0;
    }


}
void Tocka::Get_tocka(){
    cout<<"Točka x i y: "<<*px<<" "<<*py<<endl<<endl;
    cout<<"Radijus: "<<lista_kruznica->Return_Radius()<<endl;
    cout<<"Matrica točaka"<<endl;

    for(int i=0;i<N;i++){
        for(int j=0;j<2;j++){
            cout<<lista_točaka[i][j]<<" ";
        }
    cout<<endl;
    }
}
void Tocka::Get_Adresa(){
    cout<<px<<py<<endl;
}

Tocka:: Tocka(Tocka &obj){ //duboko kopiranje

    if(obj.px && obj.py && obj.lista_točaka && obj.lista_kruznica){
        px=new (nothrow) double;
        py=new (nothrow) double;
        lista_točaka=new (nothrow)double*[N];
        lista_kruznica=new (nothrow)Krug;
        for(int i=0;i<N;i++){
            lista_točaka[i]=new (nothrow)double[2];
        }
    }
    if(px && py && lista_točaka && lista_kruznica){
        *px=*obj.px;
        *py=*obj.py;
        *lista_kruznica=*(obj.lista_kruznica);
        for(int i=0;i<N;i++){
            for(int j=0;j<2;j++){
                lista_točaka[i][j]=obj.lista_točaka[i][j];
            }
        }
    }


}

void Tocka::Set_Tocka_Usporedba(double tocka_x,double tocka_y,int indeks){
    if(tocka_x>=0 && tocka_y>=0){
        lista_točaka[indeks][0]=tocka_x;
        lista_točaka[indeks][1]=tocka_y;    
    }
    else{
        lista_točaka[indeks][0]=0;
        lista_točaka[indeks][1]=0;
    }
}

void Provjera_Tocke(Tocka *obj){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if((pow(((obj+i)->lista_točaka[j][0]-*((obj+i)->px)),2)+pow(((obj+i)->lista_točaka[j][1]-*((obj+i)->px)),2))<=pow((obj+i)->lista_kruznica->Return_Radius(),2)){
                cout<<"Točka je unutar kružnice: "<<(obj+i)->lista_točaka[j][0]<<" "<<(obj+i)->lista_točaka[j][1]<<endl;
            }
            else{
                cout<<"Točka je izvan kružnice.Postavljanje na rub kružnice"<<(obj+i)->lista_točaka[j][0]<<" "<<(obj+i)->lista_točaka[j][1]<<endl;
                (obj+i)->lista_točaka[j][0]=(obj+i)->lista_kruznica->Return_Radius();
                (obj+i)->lista_točaka[j][1]=*((obj+i)->px);
                cout<<"Nove točke: "<<(obj+i)->lista_točaka[j][0]<<" "<<(obj+i)->lista_točaka[j][1]<<endl<<endl;
            }
    }
        }


}

void Provjera_Tocke2(Tocka &obj){
    for(int i=0;i<N;i++){
        if((pow(obj.lista_točaka[i][0]-*(obj.px),2)+pow(obj.lista_točaka[i][1]-*(obj.py),2))<=pow(obj.lista_kruznica->Return_Radius(),2)){
            cout<<"Točka je unutar kružnice"<<obj.lista_točaka[i][0]<<" "<<obj.lista_točaka[i][1]<<endl<<endl;
        }
        else{
            cout<<"Točka je van kružnice.Postavljanje na unutar"<<obj.lista_točaka[i][0]<<" "<<obj.lista_točaka[i][1]<<endl<<endl;
            obj.lista_točaka[i][0]=*(obj.px);
            obj.lista_točaka[i][1]=obj.lista_kruznica->Return_Radius();
        }
    }
}

int main(){

    Tocka *obj=new (nothrow) Tocka[N];

    if(obj==nullptr){
        cout<<"Greška pri alokaciji"<<endl;
        exit(1);
    }
    double tocka_x,tocka_y,tocka_x_usporedba,tocka_y_usporedba,rad;

    for(int i=0;i<N;i++){
        cout<<"Unesi srediste kruznice"<<endl;
        cin>>tocka_x>>tocka_y;
        (obj+i)->Set_Tocka(tocka_x,tocka_y);
        cout<<"Unesi radijus kruznice"<<endl;
        cin>>rad;
        (obj+i)->lista_kruznica->Set_Radius(rad);

        for(int j=0;j<N;j++){
            cout<<"Unesi točke za usporedbu"<<endl;
            cin>>tocka_x_usporedba>>tocka_y_usporedba;
            (obj+i)->Set_Tocka_Usporedba(tocka_x_usporedba,tocka_y_usporedba,j);
        }

    }
    cout<<"Ispis"<<endl;
    for(int i=0;i<N;i++){
        (obj+i)->Get_tocka();
    }
    for(int i=0;i<N;i++){
        Provjera_Tocke2(*(obj+i));
    }


    Tocka obj2(obj[0]);

    delete [] obj;


    return 0;
}