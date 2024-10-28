#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE_OF_BUFFER 1024

struct _student;
typedef struct _student *position;

typedef struct _student{
    char ime[20],prezime[20];
    int ocjene[5];
    position next;
}student;

int FileOtvori(const char *ime);
void Unos(const char *ime,int br_studenata,position p);
void UnosNaKraj(position p,position q);
int UnosNaPocetak(position p,position q,position ref);
position PronadiIza(position p,position ref);
position PronadiZadnji(position p);
void Ispis(position p);
void BrisanjeOdNajPrez(position p);
int UnosNaKrajRucno(position p,int br_studenata);

int BrisanjeNasumično(position p,int br_studenata);

void BrisanjeOdNaprijedAbecedeno(position p);
position PronadiPrethodni(position head,position ref);

position OdvajanjeElemenata(position head,int pozicija);
position ObrtanjeListe(position head);

int main(){
    srand(time(0));
    int br_studenata;
    int odabir;
    position novi=NULL;
    position head_novi=NULL;
    br_studenata=FileOtvori("lista.txt");
    printf("\nBroj studenata: %d\n",br_studenata);

    position head=(position)malloc(sizeof(student));
    if(head==NULL){
        printf("\nPogreška pri alokaciji memorije\n");
        return -1;
    }
    head->next=NULL;
    printf("\nOdaberi 0 za običan, a 1 za automatski unos\n");
    scanf("%d",&odabir);
    if(odabir==1){
    Unos("lista.txt",br_studenata,head);
    }
    else if(odabir==0){
        UnosNaKrajRucno(head,br_studenata);
    }

    printf("\nIspis konačno\n");
    Ispis(head->next);

    novi=OdvajanjeElemenata(head,3);
    printf("Ispis dvije nove razdvojene liste\n\n");
    Ispis(head->next);
    printf("\n");
    Ispis(novi->next);

    head_novi=ObrtanjeListe(head);
    printf("\nPrva lista nakon obrtanja\n");
    Ispis(head_novi->next);

    free(novi);
    free(head_novi);




    return 0;
}

int FileOtvori(const char *ime){
    FILE *fp=fopen(ime,"r");

    if(fp==NULL){
        printf("\ngreška pri otvaranju datoteke\n");
        return 0;
    }
    int br_studenata=0;
    char buffer[SIZE_OF_BUFFER];

    while(fgetc(fp)!='\n'){

    }

    while(fgets(buffer,SIZE_OF_BUFFER,fp)!=NULL){
        br_studenata++;
    }
    return br_studenata-1;
}

void Unos(const char *ime,int br_studenata,position p){
    position q=NULL;
    position temp=p;
    position zadnji;
    int unos_pocetak=0;
    int flag;

    FILE *fp=fopen(ime,"r");

    if(fp==NULL){
        printf("\nGreška pri otvaranju datoteke\n");
        return;
    }
    while(fgetc(fp)!='\n');

    for(int i=0;i<br_studenata;i++){
        p=temp->next;
        unos_pocetak=0;
        flag=0;
        printf("\nTrenutni i: %d\n",i);
        q=(position)malloc(sizeof(student));

        if(q==NULL){
            printf("\nPogreška pri malociranju\n");
            return;
        }

        fscanf(fp,"%s %s",q->ime,q->prezime);
        for(int j=0;j<5;j++){
            fscanf(fp,"%d",&(q->ocjene[j]));
        }

        if(i==0){
            temp->next=q;
            q->next=NULL;
            printf("\nTrenutno stanje\n");
            Ispis(temp->next);
        }
        else{
            //provjera
            printf("\nIzvršava se\n");
            printf("Trenutni p: %s\n",p->ime);
            printf("\nTrenutni q: %s\n",q->ime);

            while(p!=NULL){
            if(strcmp(p->ime,q->ime)==0){
                printf("\nPronađeno isto ime\n");
                if(strcmp(p->prezime,q->prezime)<0){
                    printf("\nPronađeno isto ime,ali različito prezime\n");
                    printf("\nUnos na početak\n");
                    unos_pocetak=UnosNaPocetak(temp,q,p);
                    flag=1;
                    break;    
                }
                else if(strcmp(p->prezime,q->prezime)==0){
                    printf("\nPronađeno isto ime i prezime\n");
                    printf("\nUnos na početak\n");
                    unos_pocetak=UnosNaPocetak(temp,q,p);
                    flag=1;                
                }
            }
            
            else if(strcmp(p->prezime,q->prezime)==0){
                printf("\nPronađeno isto prezime\n");
                if(strcmp(p->ime,q->ime)<0){
                printf("\nUnos na pocetak\n");
                unos_pocetak=UnosNaPocetak(temp,q,p);
                flag=1;
            }       
            }
            if(flag==1){
                break;
            }
            else{

            }

            if((strcmp(p->prezime,q->prezime)<0)){
                printf("\nUnos na pocetak\n");
                unos_pocetak=UnosNaPocetak(temp,q,p);
                break;
            }

            p=p->next;
            }

            if(unos_pocetak==0){
            zadnji=PronadiZadnji(temp);
            printf("\nUnos na kraj\n");
            //ako nismo brakeali program
            UnosNaKraj(zadnji,q);
                printf("\nTrenutno\n");
                Ispis(temp->next);
            }


        }
    }

}

void UnosNaKraj(position p,position q){
    p->next=q;
    q->next=NULL;

}
int UnosNaPocetak(position head,position q,position ref){
    position temp=head;
    position iza=PronadiIza(head,ref);

    position pom=iza->next;
    iza->next=q;
    q->next=pom;

    printf("\nTrenutno\n");
    Ispis(temp->next);

    return 1;
}

position PronadiIza(position p,position ref){
    position temp=p;
    while((temp->next!=NULL)&&(temp->next!=ref)){
        temp=temp->next;
    }

    if(temp->next==NULL){
        printf("\nNema ničeg iza.Ovaj je element liste zadnji\n");
        return NULL;
    }
    return temp;
}

void Ispis(position p){
    if(p==NULL){
        printf("\nLista nema elemenata\n");
        printf("\n\n");
        return;
    }
    while(p!=NULL){
    printf("%s %s ",p->ime,p->prezime);
    for(int j=0;j<5;j++){
        printf("%d ",p->ocjene[j]);
    }
    printf("\n\n");
        p=p->next;

    }
    printf("\n\n");
}

position PronadiZadnji(position p){
    while(p->next!=NULL){
        p=p->next;
    }
    return p;
}

void BrisanjeOdNajPrez(position p){
    //u funkciju šaljemo head
    //sortiranje po duljini prezimena
    position temp_head=p;
    position prev;
    int max_duljina;
    int curr_duljina;
    int flag;
    position max=p->next;
    position curr;
    position pocetni;
    position zadnji;

    position temp;
    position prethodni;

    while(temp_head->next->next!=NULL){
        flag=0;
        prev=temp_head->next; //prvi element
        temp=prev->next; //drugi element
        curr=temp;
        max_duljina=strlen(prev->prezime);
        printf("\nMax_duljina: %d\n",max_duljina);
        while(curr!=NULL){
            curr_duljina=strlen(curr->prezime);
            printf("\nCurrent duljina: %d\n",curr_duljina);
            if(curr_duljina>=max_duljina){
                printf("\nNađen novi maksimum");
                max=curr;
                max_duljina=strlen(max->prezime);
                flag=1;

            }
        curr=curr->next;
        }
        if(flag==0){
            pocetni=temp_head->next;
            max=pocetni;
        }
        printf("\nMaksimalno dugačko prezime,a ime toga jest: %s %s\n",max->prezime,max->ime);
        prethodni=PronadiIza(temp_head,max);
        
            prethodni->next=max->next;
            free(max);

        printf("\nTrenutno stanje\n");
        Ispis(temp_head->next);
    }

    zadnji=PronadiZadnji(temp_head);
    temp_head->next=zadnji->next;
    free(zadnji);

}

int UnosNaKrajRucno(position p,int br_studenata){
    position q=NULL;
    position zadnji;

    for(int i=0;i<br_studenata;i++){
    zadnji=PronadiZadnji(p);
    q=(position)malloc(sizeof(student));

        if(q==NULL){
        printf("\nPogreška u alokaciji memorije\n");
        return -1;
    }
    printf("\nUnesi ime i prezime\n");
    scanf("%s",q->ime);
    scanf("%s",q->prezime);
    printf("\nUnesi ocjene\n");
    for(int j=0;j<5;j++){
        scanf("%d",&(q->ocjene[j]));
    }
    q->next=zadnji->next;
    zadnji->next=q;
    }


    return 0;
}

void BrisanjeOdNaprijedAbecedeno(position p){
    position temp_head=p;
    position curr;
    position max=p->next;
    position prethodni;
    position zadnji;
    int flag;

    while(temp_head->next->next!=NULL){
        flag=0;
        curr=temp_head->next->next;//drugi element
        max=temp_head->next;
        printf("\nNovi max: %s\n",max->prezime);
        while(curr!=NULL){
            if(strcmp(curr->ime,max->ime)<=0){
                printf("\nPronađeno isto ime\n");
                if(strcmp(curr->prezime,max->prezime)<=0){
                    flag=1;
                    max=curr;
                }
            }
            else if(strcmp(curr->prezime,max->prezime)==0){
                if(strcmp(curr->ime,max->ime)<=0){
                    flag=1;
                    max=curr;
                }

            }
            else if(strcmp(curr->prezime,max->prezime)<0){
                    flag=1;
                    max=curr;               
            }
            curr=curr->next;
        }
        if(flag==0){
            max=temp_head->next;
        }
        printf("\nMaks prezime po abecedi: %s,a ime %s\n",max->prezime,max->ime);
        prethodni=PronadiIza(temp_head,max);

        prethodni->next=max->next;
        free(max);

        printf("\nTrenutno stanje\n");
        Ispis(temp_head->next);

    }
    zadnji=PronadiZadnji(temp_head);
    temp_head->next=zadnji->next;
    free(zadnji);

}

int BrisanjeNasumično(position p,int br_studenata){
    int indeks;
    int max=br_studenata-1;
    position temp_head=p;
    position prethodni;

    while(temp_head->next!=NULL){
        p=temp_head->next;
        indeks=rand()%(max-0+1)+0;
        printf("\nIndeks: %d\n",indeks);
        for(int j=0;j<indeks;j++){
            p=p->next;
        }
    printf("\nElement na kojem smo trenutno: %s %s\n",p->ime,p->prezime);
    prethodni=PronadiPrethodni(temp_head,p);
    printf("\nPrethodni: %s %s\n",prethodni->ime,prethodni->prezime);
    prethodni->next=p->next;
    free(p);

    printf("\nTrenutno stanje\n");
    Ispis(temp_head->next);

    max--;
    }


    return 0;

}

position PronadiPrethodni(position head,position ref){

    while((head->next!=NULL)&&(head->next!=ref)){
        head=head->next;
    }
    if(head->next==NULL){
        printf("\nTaj element nema prethodnog\n");
        return NULL;
    }

    return head;
}

position OdvajanjeElemenata(position head,int pozicija){
    position prev,temp;
    position novi=(position)malloc(sizeof(student));

    prev=head->next;

    if(novi==NULL){
        printf("\nPogreška u malociranju\n");
        return NULL;
    }

    for(int i=0;i<pozicija;i++){
        prev=prev->next;
    }
    printf("\nEl na toj poziciji: %s %s\n",prev->ime,prev->prezime);

    temp=prev->next;

    novi->next=temp;

    prev->next=NULL;

    return novi;
    


}

position ObrtanjeListe(position head){
    position prev,curr,next,zadnji,prethodni_od_zadnjeg,temp;
    position head_novi=(position)malloc(sizeof(student));

    if(head_novi==NULL){
        printf("\nPogreška pri malociranju\n");
        return NULL;
    }

    prev=head;
    curr=prev->next;


    while(curr!=NULL){

        next=curr->next;

        curr->next=prev;

        prev=curr;
        curr=next;
    }

    head_novi->next=prev;

    temp=head_novi;
    while(temp!=head){
        temp=temp->next;
    }
    zadnji=temp;
    prethodni_od_zadnjeg=PronadiPrethodni(head_novi,zadnji);

    prethodni_od_zadnjeg->next=NULL;
    free(zadnji);
    

    return head_novi;

}

