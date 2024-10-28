#include <stdio.h>
#include <stdlib.h>

struct _polinom;
typedef struct _polinom *position;

typedef struct _polinom{
    int potencija,koeficijent;
    position next;
}polinom;

void Unos(position head);
void UnosNaPocetak(position head,position q,position temp);
position PronadiZadnji(position head);
void Ispis(position p);
position PronadiPrethodni(position head,position ref);
position PronadiNajmanji(position head);
position PronadiIsti(position head,int temp);
position PronadiZadnjiVeci(position head,int pot,position q);

int main(){
    position head=(position)malloc(sizeof(polinom));
    head->next=NULL;

    if(head==NULL){
        printf("\nPogreška pri alociranju\n");
        return -1;
    }
    Unos(head);

    free(head);

    return 0;
}

void Unos(position head){
    position q=NULL;
    position temp_head=head;
    position temp;
    position prethodni,zadnji_veci;

    for(int i=0;i<5;i++){
        q=(position)malloc(sizeof(polinom));
        printf("\nUnesi koef i pot\n");
        scanf("%d %d",&(q->koeficijent),&(q->potencija));

        if(i==0){
            head->next=q;
            q->next=NULL;

        }

        else{
            temp=head->next;
            while(temp!=NULL){
                if(q->potencija>=temp->potencija){
                    break;
                }
            temp=temp->next;
            }
            if(temp!=NULL){
                prethodni=PronadiPrethodni(head,temp);
                q->next=prethodni->next;
                prethodni->next=q;
            }
            if(temp==NULL){
                    zadnji_veci=PronadiZadnjiVeci(head,q->potencija,q);
                    if(zadnji_veci!=NULL){
                        printf("Zadnji veci: %d\n",zadnji_veci->potencija);
                        q->next=zadnji_veci->next;
                        zadnji_veci->next=q;
                    }



            }
        }
          printf("\nTrenutno stanje\n");
      Ispis(head->next);  

    }




    }

void UnosNaPocetak(position head,position q,position temp){
    position pom;
    pom=head->next;
    head->next=q;
    q->next=pom;
}

void Ispis(position p){
    if(p==NULL){
        printf("\nLista nema elemenata\n");
        printf("\n\n");
        return;
    }
    while(p!=NULL){
    printf("%d x^%d ",p->koeficijent,p->potencija);
    printf("\n\n");
        p=p->next;

    }
    printf("\n\n");
}

position PronadiZadnji(position head){
    while(head->next!=NULL){
        head=head->next;
    }
    return head;
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

position PronadiNajmanji(position head){
    position min=head->next;
    position temp=min->next;
    while(temp!=NULL){
        printf("\nTemp: %d\n",temp->potencija);
        if(temp->potencija<=min->potencija){
            min=temp;
        }
        temp=temp->next;
    }
    return min;
}

position PronadiIsti(position head,int temp){
    while(head!=NULL){
        if(head->potencija==temp){
            return head;
        }
        head=head->next;
    }
    return NULL;
}

position PronadiZadnjiVeci(position head,int pot,position q){
    position temp_head=head;
    head=head->next;
    position zadnji_veci,zadnji;
    while(head!=NULL){
        if(head->potencija>pot){
            zadnji_veci=head;
        }
        head=head->next;
    }
    if(head==NULL){
        zadnji=PronadiZadnji(temp_head);
        q->next=zadnji->next;
        zadnji->next=q;
        return NULL;
    }
    return zadnji_veci;
}
