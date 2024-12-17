#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1024

typedef struct Datoteke{
    char ime_datoteke[MAX_LEN];
    char tip_datoteke[MAX_LEN];

}Datoteke;
typedef struct Dir{
    int vel_liste,vel_liste_datoteka;
    struct Dir *lista;
    char ime[MAX_LEN];
    Datoteke *lista_datoteka;

}Dir;

struct _stack;
typedef struct _stack *StackPosition;

typedef struct _stack{
    Dir *el;
    Dir *cd;
    StackPosition next;
}stack;




void md(Dir *trenutni,char *ime_temp);
void ispis(Dir trenutni);
Dir *cd(Dir *trenutni,char *ime);
Dir back(Dir trenutni);
void push(StackPosition stack_head,Dir *element,Dir *cd);
Dir* pop(StackPosition stack_head);
void ispis_stacka(StackPosition p);
void pop_dir(Dir *root);
void komande(StackPosition stack_head,Dir *trenutni,char *root_ime);

void datoteke_unutar_foldera(Dir *trenutni,char *ime,char *tip);
void ispis_datoteka(Dir trenutni);

int main(){
    Dir root;

    root.lista=NULL;
    root.vel_liste=2;
    strcpy(root.ime,"root");

    root.lista=realloc(root.lista,sizeof(Dir)*root.vel_liste+1);
    if(!root.lista)return -1;

    strcpy(root.lista[0].ime,"..");
    root.lista[0].lista=NULL;
    root.lista[0].vel_liste=0;
    strcpy(root.lista[1].ime,".");
    root.lista[1].lista=NULL;
    root.lista[1].vel_liste=0;

    root.vel_liste_datoteka=0;
    root.lista_datoteka=NULL;


    StackPosition stack_head=(StackPosition)malloc(sizeof(stack));
    if(!stack_head)return -1;
    stack_head->next=NULL;

    komande(stack_head,&root,root.ime);
    
    printf("\nIspis svih direktorija\n");
    ispis(root);

    pop_dir(&root);
    ispis(root);

    return 0;
}

void md(Dir *trenutni,char *ime_temp){
    trenutni->vel_liste++;

    trenutni->lista=(Dir*)realloc(trenutni->lista,sizeof(Dir)*trenutni->vel_liste);
    if(!trenutni->lista)return;
   
    strcpy(trenutni->lista[trenutni->vel_liste-1].ime,ime_temp);
    trenutni->lista[trenutni->vel_liste-1].vel_liste=2;
    trenutni->lista[trenutni->vel_liste-1].lista=NULL;

    trenutni->lista[trenutni->vel_liste-1].lista=(Dir*)realloc(trenutni->lista[trenutni->vel_liste-1].lista,sizeof(Dir)*trenutni->lista[trenutni->vel_liste-1].vel_liste);
    if(!trenutni->lista[trenutni->vel_liste-1].lista){
        return;
    }

    strcpy(trenutni->lista[trenutni->vel_liste-1].lista[0].ime,"..");
    strcpy(trenutni->lista[trenutni->vel_liste-1].lista[1].ime,".");

    trenutni->lista[trenutni->vel_liste-1].vel_liste_datoteka=0;
    trenutni->lista[trenutni->vel_liste-1].lista_datoteka=NULL;

    trenutni->lista[trenutni->vel_liste-1].lista[0].lista=NULL;
    trenutni->lista[trenutni->vel_liste-1].lista[0].vel_liste=0;   
    trenutni->lista[trenutni->vel_liste-1].lista[0].lista_datoteka=NULL;
    trenutni->lista[trenutni->vel_liste-1].lista[0].vel_liste_datoteka=0;   

    trenutni->lista[trenutni->vel_liste-1].lista[1].lista=NULL;
    trenutni->lista[trenutni->vel_liste-1].lista[1].vel_liste=0;
    trenutni->lista[trenutni->vel_liste-1].lista[1].lista_datoteka=NULL;
    trenutni->lista[trenutni->vel_liste-1].lista[1].vel_liste_datoteka=0;   


}   

void ispis(Dir trenutni){
    if(!trenutni.lista){
        printf("\nNema elemenata\n");
        return;
    }
    for(int i=2;i<trenutni.vel_liste;i++){
            printf("%s\n",trenutni.lista[i].ime);

    }
}

Dir* cd(Dir *trenutni,char *ime){
    //u ovoj funkciji pretrazujemo ime foldera
    for(int i=0;i<trenutni->vel_liste;i++){
        if(strcmp(trenutni->lista[i].ime,ime)==0){
            return &(trenutni->lista[i]);
        }
    }
    printf("\nNije nađeno ime\n");
    return NULL;
}

void push(StackPosition stack_head,Dir *element,Dir *cd){ //push na pocetak
    StackPosition temp=stack_head;

    StackPosition novi=(StackPosition)malloc(sizeof(stack));
    if(!novi)return;

    novi->el=element;
    novi->cd=cd;

    novi->next=temp->next;
    temp->next=novi;

}

void ispis_stacka(StackPosition p){
    if(!p)return;

    ispis_stacka(p->next);
    printf("\\: %s ",p->cd->ime);
}

Dir* pop(StackPosition stack_head){
    StackPosition temp=stack_head;

    //popamo samo prvi element,ne sve
    StackPosition brisi=temp->next;
    Dir *vrati=brisi->el;

    temp->next=brisi->next;
    free(brisi);

    return vrati;

}

void pop_dir(Dir *root){
    if(root->lista_datoteka){
        free(root->lista_datoteka);
        root->lista_datoteka=NULL;
    }


    for(int i=root->vel_liste-1;i>=2;i--){
        pop_dir(&(root->lista[i]));
    }
    free(root->lista);
    root->lista=NULL;
}

void komande(StackPosition stack_head,Dir *trenutni,char *root_ime){
    Dir *pom;
    char odabir[MAX_LEN],ime_temp[MAX_LEN];
    char ime_dat[MAX_LEN],tip_dat[MAX_LEN];
    while(1){
        printf("\nUnesi radnju\n");
        scanf("%s",odabir);
        getchar();

        if(strcmp(odabir,"md")==0){
            do{
                printf("\nUnesi ime foldera\n");
                scanf("%s",ime_temp);
                getchar();
            }while(strcmp(ime_temp,"..")==0 || strcmp(ime_temp,"..")==0);


            md(trenutni,ime_temp); //funkcija za pravljenje liste
        }
        else if(strcmp(odabir,"cd")==0){
            do{
                printf("\nUnesi ime foldera u koji zelis uci\n");
                scanf("%s",ime_temp);
                getchar();
            }while(strcmp(ime_temp,"..")==0 || strcmp(ime_temp,".")==0);

            pom=cd(trenutni,ime_temp);
            if(pom){
                push(stack_head,trenutni,pom);
                printf("\nTrenutni folder u kojem se nalazimo\n");
                printf("\nRoot:\\   ");
                ispis_stacka(stack_head->next);

                trenutni=pom;
            }
            else if(!pom){
                printf("\nOstajemo u trenutnom folderu :%s\n",trenutni->ime);
            }

        }

        else if(strcmp(odabir,"cd..")==0){
            if(strcmp(trenutni->ime,root_ime)!=0){
                ispis_stacka(stack_head->next);
                Dir *pomocni=pop(stack_head);
                trenutni=pomocni;
                printf("\nVratili smo se u: %s\n",trenutni->ime);
                
            }
            else if(strcmp(trenutni->ime,root_ime)==0){
                printf("\nNe mozemo izac iz roota\n");

            }

        }
        else if(strcmp(odabir,"dir")==0){
            printf("\nIspis trenutnog foldera\n");
            ispis(*trenutni);
            printf("\n------\n");
            printf("Datoteke u folderu\n");
            ispis_datoteka(*trenutni);
            printf("\n------\n");
        }
        else if(strcmp(odabir,"touch")==0){
            printf("\nUnesi ime datoteke\n");
            scanf("%s",ime_dat);
            getchar();
            printf("\nUpiši tip datoteke\n");
            scanf("%s",tip_dat);
            getchar();
            datoteke_unutar_foldera(trenutni,ime_dat,tip_dat);
        }
        else if(strcmp(odabir,"exit")==0){
            break;
        }
        else{
            break;
        }
    }
}

void datoteke_unutar_foldera(Dir *trenutni,char *ime_dat,char *tip_dat){
    trenutni->vel_liste_datoteka++;
    trenutni->lista_datoteka=realloc(trenutni->lista_datoteka,sizeof(Datoteke)*trenutni->vel_liste_datoteka);
    if(!trenutni->lista_datoteka)return;

    strcpy(trenutni->lista_datoteka[trenutni->vel_liste_datoteka-1].ime_datoteke,ime_dat);
    strcpy(trenutni->lista_datoteka[trenutni->vel_liste_datoteka-1].tip_datoteke,tip_dat);
}

void ispis_datoteka(Dir trenutni){
    if(trenutni.vel_liste_datoteka==0){
        printf("\nU folderu se ne nalazi nikakve datoteke\n");
    }
    for(int i=0;i<trenutni.vel_liste_datoteka;i++){
        printf("%s.%s",trenutni.lista_datoteka[i].ime_datoteke,trenutni.lista_datoteka[i].tip_datoteke);
        printf("\n");
    }
}





