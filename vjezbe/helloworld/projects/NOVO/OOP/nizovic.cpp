#include <bits/stdc++.h>
#include <new>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

class matrica{
    private:
        int broj;
        char slovo;
        
    public:
        matrica(){
            broj=0;
            slovo='\0';
        }
        int provjera(int temp);
        char provjera_slova(char temp);

        void ispis(){
            cout<<broj<<" ";
            cout<<slovo<<"  ";
        }

        int vrati(){
            return broj;
        }
        char vrati_slovo(){
            return slovo;
        }

        int unesi_ponovno(int temp){
            broj=temp;
            return broj;
        }
        



        
};

int matrica:: provjera(int temp){
    if(temp<0){
        cout<<"Pogreška u upisu,broj ne može biti negativan"<<endl;
    }
    else{
        broj=temp;
        return temp;
    }

}
char matrica:: provjera_slova(char temp){
    if(temp=='\0' || temp=='\n' || temp==' '){
        cout<<"Pogreška u upisu slova"<<endl;
    }
    else{
        slovo=temp;
        return temp;
    }
}
void no_memory(){
    cerr<<"operator new: nema slobodne memorije"<<endl;
    exit(1);
}

int algebra_po_redu(matrica **mat,int red,int stup,int broj,string operacija);
int algebra_po_stupcu(matrica **mat,int stup_određeni,int red,int broj,string operacija);
void ispis_matrice(matrica **mat,int red,int stup);
int operacija(int temp,int broj,string odaberi_operaciju);
int provjera_trokutaste_matrice(matrica **mat,int red,int stup);
void usporedba_rijeci(matrica **mat,int red,int stup);
void copy_string(string s1,string s2);

//stringovi u c++ se passaju u funkciju isto kao i character array

int main(){

    set_new_handler(no_memory);

    int el_temp;
    int red,stup;
    int odabir;
    string odaberi_operaciju; //ključna je riječ string ispred imena varijable
    int odaberi_broj;
    int red_odabir,stup_odabir;
    int trokutasta_matrica;

    char sl;

    matrica **mat=NULL;

    cout<<"Unesi broj redaka"<<endl;
    cin>>red;
    cout<<"Unesi broj stupaca"<<endl;
    cin>>stup;

    mat=new matrica*[red];
    for(int i=0;i<red;i++){
        mat[i]=new matrica[stup];
    }
    cout<<"Ispis matrice nakon alokacije"<<endl;
    for(int i=0;i<red;i++){
        for(int j=0;j<stup;j++){
            mat[i][j].ispis();
        }
    cout<<endl;
    }
    for(int i=0;i<red;i++){
        for(int j=0;j<stup;j++){
            cout<<"Unesi el matrice(broj)"<<endl;
            cin>>el_temp;
            cout<<"Unesi el matrice(slovo)"<<endl;
            cin>>sl;
            (*(*(mat+i)+j)).provjera(el_temp);
            (*(*(mat+i)+j)).provjera_slova(sl);

            }


        }
    cout<<"Ispis matrice nakon unosa"<<endl;
    ispis_matrice(mat,red,stup);


    usporedba_rijeci(mat,red,stup);

    while(trokutasta_matrica!=1){
            cout<<"Odaberi 0 za red i 1 za stupac"<<endl;
    cin>>odabir;
    if(odabir==0){
        cout<<"Odaberi operaciju"<<endl;
        cin>>odaberi_operaciju;
        cout<<"Odaberi broj"<<endl;
        cin>>odaberi_broj;
        cout<<"Odaberi red"<<endl;
        cin>>red_odabir;;
        int rez=algebra_po_redu(mat,red_odabir,stup,odaberi_broj,odaberi_operaciju);
    }
    else if(odabir==1){
        cout<<"Odaberi operaciju"<<endl;
        cin>>odaberi_operaciju;
        cout<<"Odaberi broj"<<endl;
        cin>>odaberi_broj;
        cout<<"Odaberi stupac"<<endl;
        cin>>stup_odabir;
       int rez=algebra_po_stupcu(mat,stup_odabir,red,odaberi_broj,odaberi_operaciju); 
    }


    cout<<"Ispis matrice nakon algebre"<<endl;
    ispis_matrice(mat,red,stup);
    trokutasta_matrica=provjera_trokutaste_matrice(mat,red,stup);
    }


    

   
    for(int i=0;i<red;i++){
        delete[] mat[i];

    }
    delete mat;

    //nothwor predstavlja praznu klasu
    //nothrow traži od kompajlera da vrati null pointer, umjesto da odma prekine alokaciju i ispiše grešku

    return 0;


}

int algebra_po_redu(matrica **mat,int red_odredeni,int stup,int br,string odaberi_operaciju){
    int temp;

    

    for(int i=0;i<stup;i++){
        temp=mat[red_odredeni][i].vrati();
        temp=operacija(temp,br,odaberi_operaciju);

        mat[red_odredeni][i].unesi_ponovno(temp);
    }

    return 0;
}

void ispis_matrice(matrica **mat,int red,int stup){

    for(int i=0;i<red;i++){
        for(int j=0;j<stup;j++){
            (*(*(mat+i)+j)).ispis();
        }
    cout<<endl;
    }
}

int operacija(int temp,int broj,string odaberi_operaciju){
    if(odaberi_operaciju.compare("plus")==0){
        temp=temp+broj;
    }
    else if(odaberi_operaciju.compare("minus")==0){
        temp=temp-broj;
    }
    else if(odaberi_operaciju.compare("množenje")==0){
        temp=temp*broj;
    }
    else if(odaberi_operaciju.compare("dijeljenje")==0){
        temp=temp/broj;
    }
    else{
        cout<<"Nepravilno unesena operacija"<<endl;
        return -1;
    }

    return temp;




}
int algebra_po_stupcu(matrica **mat,int stup_određeni,int red,int br,string odaberi_operaciju){
    int temp;

    for(int i=0;i<red;i++){
        temp=mat[i][stup_određeni].vrati();
        temp=operacija(temp,br,odaberi_operaciju);

        mat[i][stup_određeni].unesi_ponovno(temp);
    }

    return 0;
}

int provjera_trokutaste_matrice(matrica **mat,int red,int stup){
    int flag_red,flag_stup;
    int temp;

    for(int i=1;i<red;i++){
        flag_stup=0;
        temp=mat[i][0].vrati();
        if(temp==0){
            flag_stup=1;
        }
    }
    for(int i=0;i<stup;i++){
        flag_red=0;
        temp=mat[red-1][i].vrati();
        if(temp==0){
            flag_red=1;
        }
    }

    if(flag_red==1 && flag_stup==1){
        cout<<"Nađena trokutasta matrica"<<endl;
        return 1;
    }
}

void usporedba_rijeci(matrica **mat,int red,int stup){
    set_new_handler(no_memory);

    char **s_temp1=new char*[red];


    int i,j;

    for(i=0;i<red;i++){
                    s_temp1[i]=new char[stup];
        for(j=0;j<stup;j++){
            cout<<mat[i][j].vrati_slovo()<<endl;

            s_temp1[i][j]=mat[i][j].vrati_slovo();
        }
    s_temp1[i][j]='\0';

    }
    cout<<"S_temp1 ispis"<<endl<<endl;
    for(i=0;i<red;i++){
        for(j=0;j<stup;j++){
            cout<<s_temp1[i][j]<<" ";
        }
    cout<<endl;
    }
    for(i=0;i<red-1;i++){
        for(j=i+1;j<red;j++){
            cout<<strcmp(s_temp1[i],s_temp1[j])<<endl;
        }
    }

    for(i=0;i<red;i++){
        delete[] s_temp1[i];
    }
    delete[] s_temp1;



}

