#include <stdio.h>
#include <stdlib.h>

struct _lista;
typedef struct _lista *position;

typedef struct _lista{
    int broj;
    position next;
}lista;

void umetni_na_kraj(position head);
position FindLast(position head);
int Unos(position p);
void Ispis(position p);
void IzbrisiPrvoNajveci(position p);
void SortList(position p);
position FindPrev(position p,position last);
position PronadiPrethodni(position p,position ref);

void IzbrisiPrvoNajmanji(position p);
int BrojElemenata(position p);

void BrisanjeParnih(position p);
position PronadiPrviParni(position p);

void BrisanjeParnihOdKraja(position p);
position ZadnjiParni(position p);

void SortiranjeListe(position p);

void IzbrisiMax(position p);
void IzbrisiMin(position p);

int main(){
    position head=NULL;
    head=(position)malloc(sizeof(lista));

    if(head==NULL){
        printf("\nPogreška u alokaciji memorije\n");
        return -1;
    }
    for(int i=0;i<5;i++){
        umetni_na_kraj(head);
    }
    printf("\n");
    Ispis(head->next);

    SortiranjeListe(head->next);
    printf("\nIspis nakon sortiranja liste\n");
    Ispis(head->next);

    IzbrisiMax(head);

    printf("\nLista nakon brisanja svih elemenata\n");
    Ispis(head->next);

    






    return 0;

}

position FindLast(position head){

    while(head->next!=NULL){
        head=head->next;
    }

    return head;
}

void umetni_na_kraj(position head){
    position p=FindLast(head);
    Unos(p);

}

int Unos(position p){
    int element;
    position q=NULL;
    q=(position)malloc(sizeof(lista));

        if(q==NULL){
        printf("\nPogreška u alokaciji memorije\n");
        return -1;
    }
    printf("\nUnesi el\n");
    scanf("%d",&element);
    q->broj=element;
    q->next=p->next;
    p->next=q;
}

void Ispis(position p){
    if(p==NULL){
        printf("\nLista nema elemenata\n");
        printf("\n\n");
        return;
    }
    while(p!=NULL){
    printf("%d ",p->broj);
        p=p->next;

    }
    printf("\n\n");
}

void IzbrisiPrvoNajveci(position p){
    SortList(p->next);
    //brisanje od kraja
    position last=FindLast(p);
    position prev=FindPrev(p,last);
    position temp;

    while(prev!=p){
        temp=last;
        prev->next=last->next;
        free(temp);

        last=FindLast(p);
        prev=FindPrev(p,last);

        printf("\nTrenutačno stanje\n");
        Ispis(p->next);
    }
    temp=prev->next;
    p->next=last->next;
    free(temp);

}

void SortList(position p){
    //sortiramo uzlazno
    position head_next=p;
    position temp;
    int pom;

    while(p->next!=NULL){
        temp=p->next;
        while(temp!=NULL){
            if(temp->broj<p->broj){
                pom=temp->broj;
                temp->broj=p->broj;
                p->broj=pom;
            }
            temp=temp->next;
        }
        p=p->next;
    }
    printf("\nSortirana lista\n");
    Ispis(head_next);


}

position FindPrev(position p,position last){

    while((p->next!=NULL)&&(p->next!=last)){
        p=p->next;
    }
    if(p->next==NULL){
        printf("\nTraženi broj nema prethodnika\n");
        return NULL;
    }

    return p;
}

void IzbrisiPrvoNajmanji(position p){
    SortList(p->next);
    position pom=p;
    position temp;

    int br_el=BrojElemenata(p);
    printf("\nBroj elemenata na početku: %d\n",br_el);

    while(br_el!=0){
        temp=pom->next;
        pom->next=temp->next;
        //pom je uvijek head,tj p
        free(temp);

        br_el=BrojElemenata(p);
        printf("\nBroj elemenata: %d\n",br_el);

        printf("\nTrenutno stanje\n");
        Ispis(p->next);
    }

    //brisanje od početka

}

int BrojElemenata(position p){
    p=p->next;
    int br=0;

    while(p!=NULL){
        br++;
        p=p->next;
    }

    return br;
}

void BrisanjeParnih(position p){
    SortList(p->next);
    position prvi_parni;
    position temp;
    position prethodni;

    int br_el=BrojElemenata(p);
    printf("\nBroj elemenata na početku: %d\n",br_el);

    //ovo je brisanje parnih od početka
    while(br_el!=0){
        prvi_parni=PronadiPrviParni(p);
        if(prvi_parni==NULL){ //tj niti jedan parni broj više nije ostao u vezanoj listi
            printf("\nGotova funkcija\n");
            return;
        }
        prethodni=FindPrev(p,prvi_parni);
        temp=prethodni->next;
        prethodni->next=prvi_parni->next;
        free(temp);

        br_el=BrojElemenata(p);
        printf("\nTrenutni br el: %d\n",br_el);

        printf("\nTrenutno stanje\n");
        Ispis(p->next);

    }

}

position PronadiPrviParni(position p){

    p=p->next;
    while((p!=NULL)&&(p->broj%2!=0)){
        p=p->next;
    }

    return p;
}

void BrisanjeParnihOdKraja(position p){
    SortList(p->next);
    position last=ZadnjiParni(p);
    printf("Zadnji: %d\n",last->broj);
    position prev=FindPrev(p,last);
    position temp;

    while(prev!=p){
        if(last==NULL){
            printf("\nIzlaz iz funkcije\n");
            return;
        }
        temp=last;
        prev->next=last->next;
        free(temp);

        last=ZadnjiParni(p);
        prev=FindPrev(p,last);

        printf("\nTrenutno stanje\n");
        Ispis(p->next);
    }
    temp=p->next;
    p->next=last->next;
    free(temp);
}

position ZadnjiParni(position p){
    p=p->next;
    position curr;
    int flag=0;

    while(p!=NULL){
        if(p->broj%2==0){
            flag=1;
            curr=p;
        }
        p=p->next;
    }

    if(flag==1){
        return curr;
    }
    else{
        return p;
    }

}

void IzbrisiMax(position p){
    //pretraživanje
    int temp_max;
    position p_max=p->next;
    position temp=p;

    position ref;

    position prev=NULL;

    position pomocni_za_petlju;

    while(temp->next!=NULL){ //u ovom slučaju ostavljamo jedan element
        p=temp;
        p=p->next;
        pomocni_za_petlju=p;
        temp_max=pomocni_za_petlju->broj;

        while(pomocni_za_petlju!=NULL){
            if(pomocni_za_petlju->broj>=temp_max){
                p_max=pomocni_za_petlju;    
                temp_max=p_max->broj;
            }
            pomocni_za_petlju=pomocni_za_petlju->next;
        }

        printf("\nMaksimalni: %d\n",p_max->broj);
        prev=PronadiPrethodni(temp,p_max);
        if(prev!=NULL){
        ref=p_max;
        prev->next=ref->next;
        free(ref);
        printf("\ntrenutno stanje\n");
        Ispis(temp->next);
        }

}

}

position PronadiPrethodni(position p,position ref){
    while((p->next!=NULL)&&(p->next!=ref)){
        p=p->next;
    }
    if(p->next==NULL){
        printf("\nTraženi broj ne postoji ili element nema prethodnika\n");
        return NULL;
    }
    return p;
}

void IzbrisiMin(position p){
    position p_min=p->next;
    position temp=p;
    position prev;
    position ref;
    position pom_za_petlju;
    int min_temp=p->next->broj;

    while(temp->next!=NULL){
        pom_za_petlju=temp->next;
        min_temp=temp->next->broj;
        while(pom_za_petlju!=NULL){
            if(pom_za_petlju->broj<=min_temp){
                p_min=pom_za_petlju;
                min_temp=pom_za_petlju->broj;
            }
            pom_za_petlju=pom_za_petlju->next;

        }
            printf("\nMinimalni: %d\n",p_min->broj);
            prev=PronadiPrethodni(temp,p_min);
            if(prev!=NULL){
                ref=p_min;
                prev->next=ref->next;
                free(ref);
            }
    printf("\nTrenutno stanje\n");
    Ispis(temp->next);
    }
}

void SortiranjeListe(position p){
    //u funkciju šaljemo head na next
    position temp=p;
    int pom;
    while(temp->next!=NULL){
        p=temp->next; //p uvijek mora biti ispred varijable temp,inače neće usporedba raditi
        while(p!=NULL){
            if(temp->broj>p->broj){
                pom=temp->broj;
                temp->broj=p->broj;
                p->broj=pom;
            }
        p=p->next;
        }
    temp=temp->next;
    }
}
