#include <iostream>
#include <cmath>

using namespace std;


class matrica{
    private:
        int **mat;
        int broj_redaka;
        int broj_stupaca;
        int count;

    int **alociraj_mat(){
        mat=(int**)malloc(sizeof(int*)*broj_redaka);
        if(mat==NULL){
            printf("\nNeuspješna alokacija memorije\n");
            return NULL;
        }
        for(int i=0;i<broj_redaka;i++){
            mat[i]=(int*)malloc(sizeof(int)*broj_stupaca);
            if(mat[i]==NULL){
                printf("\nNeuspješna alokacija\n");
                return NULL;
            }
        }
    return mat;
    }

    void unesi_mat(){
        for(int i=0;i<broj_redaka;i++){
            for(int j=0;j<broj_stupaca;j++){
                scanf("%d",&mat[i][j]);
            }
        }
    return;
    }
    
    public:

    ~matrica(){
        cout<<"Memorija je unistena"<<endl;
        for(int i=0;i<broj_redaka;i++){
            delete[] mat[i];
 
        }
        delete[] mat;
    }

    int suma_dijagonale(){
        int suma=0;
        for(int i=0;i<broj_redaka;i++){
            suma+=mat[i][i];
        }
        return suma;
    }

    matrica(){
        cout<<"Unesi broj redaka"<<endl;
        cin>>broj_redaka;
        cout<<"Unesi broj stupaca"<<endl;
        cin>>broj_stupaca;
        printf("\nSlijedi malociranje i unosenje matrice\n");
        mat=alociraj_mat();
        unesi_mat();
    }

    void ispis_mat(){
        cout<<"Ispis matrice"<<endl;
        for(int i=0;i<broj_redaka;i++){
            for(int j=0;j<broj_stupaca;j++){
                printf("%d ",mat[i][j]);
            }
        printf("\n");
        }
    for(int i=0;i<3;i++){
    }

    return;
    }


    

};

int main(){
    matrica s[3];
    for(int i=0;i<3;i++){
        int suma=s[i].suma_dijagonale();
        cout<<"Suma "<<suma<<endl;
    }

    for(int i=0;i<3;i++){
        s[i].ispis_mat();
        cout<<endl<<endl;
    }

    //destruktor se može pozvati i sam
    //nije dobra praksa sam eksplicitno pozvati destructor
    //ako imamo malociranu memoriju unutar klase, dobro je napraviti svoj destruktor

        for(int i=0;i<3;i++){
        s[i].ispis_mat();
        cout<<endl<<endl;
    }
    
    return 0;
}