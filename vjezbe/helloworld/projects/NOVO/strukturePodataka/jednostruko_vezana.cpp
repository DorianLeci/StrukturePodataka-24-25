#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _lista;
typedef struct _lista *position;

typedef struct _lista{
    int element;
    char ime[100];
    char prezime[100];

    position next; //pokazivač na slijedeći član liste

}lista;

int Umetni(position p);
int UmetniNakon(position p,char *prezime);
position Pronadi(position p,char *prezime);
void UnesiPodatke(position q);
void Ispis(position p);

int main(){
    position head=NULL;
    head=(position)malloc(sizeof(lista));
    head->next=NULL;

    int izbor;

    while(1){
        printf("\nUnesi zelis li nastaviti\n");
        scanf("%d",&izbor);
        if(izbor==0){
            break;
        }
        Umetni(head); //Umetanje elementa na početak
    }

    printf("\nIspis liste\n");
    Ispis(head->next);

    UmetniNakon(head->next,{"Leci"});

    printf("\nNakon umetanja\n");
    Ispis(head->next);

    return 0;

    
} //sada smo strukture lista radi jednostavnosti nazvali lista

int Umetni(position p){
    //pokazivač p je poprimio vrijednost 100
    position q=NULL;
    q=(position)malloc(sizeof(lista)); //alociramo prostor za novi element

    if(q==NULL){
        return -1; //jednostavna provjera
    }

    UnesiPodatke(q);

    q->next=p->next; //p je pokazivao na NULL
    p->next=q; 

    return 0;

}

void UnesiPodatke(position q){
    printf("\nUnesi ime i prezime\n");
    scanf("%s %s",q->ime,q->prezime);
    scanf("%d",&(q->element));
}

void Ispis(position p){
    if(p==NULL){
        printf("\nNema elemenata,lista je prazna\n");
        return;
    }
    else{
        while(p!=NULL){
            printf("%d\n",p->element);
            printf("%s %s\n",p->ime,p->prezime);
            p=p->next;
        }

    }

    return;
}

int UmetniNakon(position p,char *prezime){
    position prev=NULL;
    prev=Pronadi(p,prezime);
    
    if(prev==NULL){
        printf("\nTraženo prezime nije pronađeno\n");
        return -1;
    }
    else{
        Umetni(prev);
    }
    
    
    return 0;//ova funkcija mora vratiti pointer
}

position Pronadi(position p,char *prezime){
    while((p!=NULL)&&(strcmp(p->prezime,prezime)!=NULL)){
        p=p->next;
    }
    
    if(p==NULL){
        printf("\nTakav element ne postoji\n");
        return p;
    }

    return p;
}