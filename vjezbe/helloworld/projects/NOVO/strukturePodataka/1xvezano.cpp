#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

struct _lista;
typedef struct _lista *position;

typedef struct _lista{
char ime[10];
int broj;
int ocjene[5];
position next;

}lista;

int UnosPrije(position p,FILE *f);
int UnosPrije_Rucno(position p);
void Ispis(position p);
int Unos_Podataka(position q,FILE *f);
int Unos_Podataka_Rucno(position q);
int Umetni_nakon(position p,char *ime,FILE *f);
position Pronadi(position prev,char *ime);

int Umetni_prije(position p,char *ime);
position PronadiPrethodni(position p,char *ime);


int UmetniNaKraj(position p);
position PronadiZadnji(position p);

int Izbrisi(position p,char *ime);

void BrisiSveOdPocetka(position p);
void BrisiSveOdKraja(position p);

position PronadiPrethodniZaBrisanje(position temp);

void IzbrisiSvaImena(position p,char *ime);
int PrebrojiSvaImena(position p,char *ime);

void IzbrisiSvaImenaDuplikate(position p,position head);
position NadiDuplikat(position p,position head);

position PronadiMjesto(char *ime,position p);


int main(){
    int br_ucenika=0;
    int izbor,odabir;
    char ime[10];
    FILE *f=NULL;

    f=fopen("studenti.txt","r");

        if(f==NULL){
        printf("\nNije moguće otvoriti datoteku\n");
        return -1;
    }

    while(fgetc(f)!='\n'){
        
    }
    while(!feof(f)){
        if(fgetc(f)=='\n'){
            br_ucenika++;
        }
    }
    rewind(f);

    position head=NULL;
    head=(position)malloc(sizeof(lista));

    if(head==NULL){
        printf("\nPogreška pri alokaciji\n");
        return -1;
    }

    head->next=NULL;
    for(int i=0;i<br_ucenika;i++){
        UnosPrije(head,f);
    }

    Ispis(head->next);

    printf("\nOdaberi nula ili jedan\n");
    scanf("%d",&izbor);
    if(izbor==1){
    printf("\nUnesi ime koje zelis naci\n");
    scanf("%s",ime);

    Umetni_nakon(head,ime,f);
    Ispis(head->next);    

    Umetni_prije(head,ime);
    Ispis(head->next);
    }

    printf("\nUnesi element na kraj vezane liste\n");
    UmetniNaKraj(head);
    Ispis(head->next);



        printf("\nOdaberi koju funkciju zelis aktivirati\n");
    scanf("%d",&odabir);

    if(odabir==1){
    printf("\nSada je na redu brisanje\n");
    printf("\nUnesi ime koje zelis izbrisati\n");
    scanf("%s",ime);



    IzbrisiSvaImena(head,ime);
    printf("\nIspis nakon brisanja svih imena\n\n");
    Ispis(head->next);
    printf("\n");
    }
    else if(odabir==2){
        printf("\nSada je na redu brisanje svih duplikata\n\n");
        IzbrisiSvaImenaDuplikate(head->next,head);
        printf("\nIspis nakon brisanja svih imena duplikata\n\n");
        Ispis(head->next);
        printf("\n");
    }



    printf("\nLista nakon brisanja svih elemenata od početka\n");
    BrisiSveOdPocetka(head);
    Ispis(head->next);

    printf("\nLista nakon brisanja svih elemenata od kraja\n");
    BrisiSveOdKraja(head);
    Ispis(head->next);




  

    return 0;
}

int UnosPrije(position p,FILE *f){
    position q;
    q=(position)malloc(sizeof(lista));

    if(q==NULL){
        return -1;
    }

    Unos_Podataka(q,f);



    q->next=p->next;
    p->next=q;

    return 0;
}

int Unos_Podataka(position q,FILE *f){

    while(fgetc(f)!='\n'){

    }
        fscanf(f,"%s %d",q->ime,&(q->broj));
        for(int j=0;j<5;j++){
            fscanf(f,"%d",&(q->ocjene[j]));
        }

        return 0;


}

void Ispis(position p){

    if(p==NULL){
        printf("\nLista nema elemenata\n");
        return;
    }
    while(p!=NULL){
        printf("Ime: %s\n",p->ime);
        printf("Maticni broj: %d\n",p->broj);
        printf("Ocjene\n");
        for(int j=0;j<5;j++){
            printf("%d ",p->ocjene[j]);
        }
        printf("\n\n");
    p=p->next;
    }


    return;
}

int Umetni_nakon(position p,char *ime,FILE *f){
    position prev;
    prev=Pronadi(p->next,ime);

    if(prev==NULL){
        return -1;
    }
    else{
        UnosPrije_Rucno(prev);
    }
}

position Pronadi(position prev,char *ime){
    while((prev!=NULL)&&(strcmp(ime,prev->ime)!=0)){
        prev=prev->next;
    }

    if(prev==NULL){ //tj ako smo dosli do kraja liste
        printf("\nTraženi element nije pronađen\n");
        return prev;
    }

    return prev;
}

int UnosPrije_Rucno(position p){
    position q;
    q=(position)malloc(sizeof(lista));


    if(q==NULL){
        return -1;
    }

    Unos_Podataka_Rucno(q);

    q->next=p->next;
    p->next=q;

    q=PronadiMjesto(q->ime,p);

    return 0;
}

int Unos_Podataka_Rucno(position q){
  printf("\nUnesi ime\n");
  scanf("%s",q->ime);
  printf("\nUnesi maticni broj\n");
  scanf("%d",&(q->broj));
  printf("\nUnesi ocjene\n");
  for(int i=0;i<5;i++){
    scanf("%d",&(q->ocjene[i]));
  }  

}


int Umetni_prije(position p,char *ime){
    position prev;
    prev=PronadiPrethodni(p,ime);

    if(prev==NULL){
        printf("\nIme nije pronađeno\n");
        return -1;
    }
    UnosPrije_Rucno(prev);

    return 0;
}

position PronadiPrethodni(position p,char *ime){
    position prev=NULL,curr=NULL;
    prev=p; //prev postavljamo da je head
    curr=prev->next;//head->next, što i mora biti prvi element za usporedbu

    while((curr!=NULL)&&(strcmp(ime,curr->ime)!=0)){
        printf("\nJoš smo u petlji\n");
        prev=curr;
        curr=curr->next;
    }

    if(curr==NULL){
      printf("\nNije traženo pronađeno ime\n");
      return NULL;  
    }
    return prev;
}

int UmetniNaKraj(position p){
    position zadnji=p->next;
    zadnji=PronadiZadnji(zadnji);
    UnosPrije_Rucno(zadnji);

    return 0;
}

position PronadiZadnji(position p){
    while(p->next!=NULL){
        p=p->next;
    }
    return p;
}

int Izbrisi(position p,char *ime){
    position prev=NULL;
    position curr=NULL;

    prev=PronadiPrethodni(p,ime);

    if(prev==NULL){
        return -1;
    }

    curr=prev->next;
    prev->next=prev->next->next;
    free(curr);

    return 0;
}

void BrisiSveOdPocetka(position p){
    position temp;
   while(p->next!=NULL){
        temp=p->next;
        p->next=p->next->next;

        free(temp);
   }
}

void BrisiSveOdKraja(position p){
    position zadnji=NULL;
    position prethodni=NULL;

    while(p->next!=NULL){
    zadnji=PronadiPrethodniZaBrisanje(p);

    prethodni=PronadiPrethodni(p,zadnji->ime);
    prethodni->next=NULL;

    free(zadnji);
    }

}

position PronadiPrethodniZaBrisanje(position temp){
    while(temp->next!=NULL){
        temp=temp->next;
    }
    return temp;
}

void IzbrisiSvaImena(position p,char *ime){
    position prev=NULL;
    position curr=NULL;
    
    int rez=PrebrojiSvaImena(p,ime);
    int counter=0;
    printf("\nBroj istih imena: %d\n",rez);

    while(rez!=counter){
        prev=PronadiPrethodni(p,ime);

        if(prev!=NULL){
            printf("\nPronađeno ime\n");
            counter++;
        }

        curr=prev->next;
        prev->next=prev->next->next;

        free(curr);
    }


    return;
}

int PrebrojiSvaImena(position p,char *ime){
    int brojac=0;

    while(p!=NULL){
        if(strcmp(ime,p->ime)==0){
            brojac++;
        }
    p=p->next;
    }
    return brojac;
}

void IzbrisiSvaImenaDuplikate(position p,position head){

    position prev=NULL;
    position curr=NULL;
    position prev2=NULL;
    position curr2=NULL;
    position temp=head->next;

    int rez;

    while(temp->next!=NULL){
        prev=NadiDuplikat(temp,head); //p-->jest head->next u ovom slučaju

        if(prev!=NULL){

            rez=PrebrojiSvaImena(p,temp->ime);

            curr=prev->next;
            prev->next=prev->next->next;
            free(curr);   

            printf("\nTrenutačno stanje\n\n");
            Ispis(head->next);

                       
            for(int i=0;i<(rez-1);i++){
                printf("\nPrev na next na ime: %s\n",prev->next->ime);
                prev2=PronadiPrethodni(head,prev->next->ime);
                printf("\nPrev2: %p\n",prev2);

                curr2=prev2->next;
                prev2->next=prev2->next->next;
                free(curr2);
            }

 
            temp=prev2;
        }
        if(prev==NULL){
            printf("\nPrev je\n");
            temp=temp->next;
        }
        else{
            printf("\nNije ni prev niti prev2 NULL :%p\n",temp);
        }
        printf("\nNovo trenutačno stanje\n");
        Ispis(head->next);

        printf("\nNovi temp jest: %p\n",temp);
        printf("\nNovi temp na next jest: %p\n",temp->next);
    }


    return;

}

position NadiDuplikat(position p,position head){

    position temp=NULL;
        printf("\nProvjera imena koja su uspoređuju: %s %s\n",p->ime,p->next->ime);
        if(strcmp(p->ime,p->next->ime)==0){
            printf("\nPronađen duplikat\n");
            temp=PronadiPrethodni(head,p->next->ime);
        }

    return temp;
}

position PronadiMjesto(char *ime,position p){
    while()
}



