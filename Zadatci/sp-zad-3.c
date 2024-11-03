#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include<stdbool.h>
#define ERROR_OPENING_FILE -1
#define BUFFER_SIZE 1024

#define M 100

typedef struct cvor* pozicija;
typedef struct cvor {
    int god;
    char ime[M];
    char prezime[M];
    pozicija next;
}cvor;

void unos_varijabli(char*, char*, int*);
void print_liste(pozicija);
void dodaj_na_kraj(pozicija, char*, char*, int);
void dodaj_na_pocetak(pozicija, char*, char*, int);
pozicija find(pozicija, char*);
pozicija find_previous(pozicija, char*);
void dodaj_izmejdu(pozicija, char*, char*, int, pozicija);
void dodaj(pozicija, char*, char*, int, char*);
void sort(pozicija);
int upisi_u_datoteku(pozicija,char *);
int ispisi_iz_datoteke(pozicija,char *);
void IzbrisiSve(pozicija head);

int main() {

    pozicija head = malloc(sizeof(cvor));
    head->next = NULL;
    int odabir,br_osoba,j;

    char i[M], p[M], traz[M]; int g;

    printf("\nOdaberi 0(unos na kraj) ili 1(unos na pocetak)\n");
    scanf("%d",&odabir);
    printf("\nOdaberi br osoba koje unosis\n");
    scanf("%d",&br_osoba);
    
    //////////////
    if(odabir==0){
        for(j=0;j<br_osoba;j++){
            unos_varijabli(i, p, &g);
            dodaj_na_kraj(head, i, p, g);
            print_liste(head);
        }
    }

    else if(odabir==1){
        for(j=0;j<br_osoba;j++){
            unos_varijabli(i, p, &g);
            dodaj_na_pocetak(head, i, p, g);
            print_liste(head);
        }

    }
    else{
        printf("\nPogrešan odabir\n");
    }

    unos_varijabli(i,p,&g);
    printf("Unesite prezime reference: "); scanf("%s", traz);
    dodaj(head, i, p, g, traz);
    print_liste(head);


    ispisi_iz_datoteke(head,"lista_iscitavanje.txt");
    print_liste(head);

    sort(head);
    print_liste(head);

    upisi_u_datoteku(head,"lista.txt");

    IzbrisiSve(head);
    print_liste(head);

    free(head);


   
    return 0;
}

void unos_varijabli(char* ime, char* prezime, int* god) {

    printf("Unesi osobu :\n");
    printf("Unesi ime : ");
    scanf("%s", ime);
    printf("Unesi prezime : ");
    scanf("%s", prezime);
    printf("Unesi God : ");
    scanf("%d", god);
    return;
}
void print_liste(pozicija head) {
    printf("\nIme\tPrezime\tGod:\n");

    pozicija curr = head->next;
    if(curr==NULL){
        printf("\nLista nema elemenata\n");
        return;
    }
    while (curr != NULL) {
        printf("%s\t%s\t%d\n", curr->ime, curr->prezime, curr->god);
        curr = curr->next;
    }
    printf("\n");
}
void dodaj_na_kraj(pozicija head, char* ime, char* prezime, int god) {

    pozicija novi = malloc(sizeof(cvor));
    if (novi == NULL) {
        return;
    }
    pozicija curr = head;

    strcpy(novi->ime, ime);
    strcpy(novi->prezime, prezime);
    novi->god = god;

    while (curr->next != 0) {
        curr = curr->next;
    }
    novi->next = NULL;
    curr->next = novi;


}
void dodaj_na_pocetak(pozicija head, char* ime, char* prezime, int god) {


    pozicija novi = malloc(sizeof(cvor));
    if (novi == NULL) {
       return;
    }
    pozicija curr = head;

    strcpy(novi->ime, ime);
    strcpy(novi->prezime, prezime);
    novi->god = god;

    novi->next = curr->next;
    curr->next = novi;

}
pozicija find(pozicija head, char* prezime) {

    pozicija curr = head;

    while (curr != NULL) {

        if (strcmp(curr->prezime, prezime) == 0) {
            return curr;
        }


        curr = curr->next;
    }
    printf("Dogodila se greska");
    return NULL;
}
pozicija find_previous(pozicija head, char* prezime) {

    pozicija curr = head;

    while (curr->next != NULL) {

        if (strcmp(curr->next->prezime, prezime) == 0) {
            return curr;
        }

        curr = curr->next;
    }

if(curr->next==NULL) {
    printf("\nNije nađeno prezime\n");
    return NULL;
}

}
void dodaj_izmedju(pozicija head, char* ime, char* prezime, int god, pozicija trazeni) {

  if(trazeni==NULL) return;

    pozicija novi = malloc(sizeof(cvor));
    if (novi == NULL) {
        return;
    }
    pozicija curr = head;

    strcpy(novi->ime, ime);
    strcpy(novi->prezime, prezime);
    novi->god = god;

    novi->next = trazeni->next;
    trazeni->next = novi;


}
void dodaj(pozicija head, char* ime, char* prezime, int god, char* trazeno_prezime) {
    int i;
    pozicija previous;
    printf("Odaberite zelite li dodati prije tog prezimena ili poslje:\n-1-prije\n-2-poslje\n");
    scanf("%d", &i);

    if (i == 1) {
        previous=find_previous(head, trazeno_prezime);
        if(previous){
            dodaj_izmedju(head, ime, prezime, god,previous);
        }
        else{
            printf("\nNije moguće dodavanje\n");
        }
        return;
    }
    else if (i == 2) {
        previous=find_previous(head, trazeno_prezime);
        if(previous){
        dodaj_izmedju(head, ime, prezime, god, find(head, trazeno_prezime));
        }
        else{
            printf("\nNije moguće dodavanje\n");
        }

        return;
    }
    else {
        printf("Kriv unos");
        return;
    }

}
void sort(pozicija head) {

    pozicija curr = head;

    if (curr->next == NULL || curr->next->next == NULL) {
        return;
    }

    bool zamjena = true;

    while (zamjena) {
        zamjena = false;
        curr = head;
        while (curr->next != NULL && curr->next->next != NULL) {

            if (strcmp(curr->next->prezime, curr->next->next->prezime) > 0) {
                zamjena = true;
                pozicija prvi = curr->next;
                pozicija drugi = curr->next->next;

                prvi->next = drugi->next;
                curr->next = drugi;
                drugi->next = prvi;

            }

            curr = curr->next;
        }
    }



}
int upisi_u_datoteku(pozicija head,char *filename) {

    pozicija curr = head->next;

    FILE* fp = NULL;
    fp = fopen(filename, "w");

if(fp==NULL) return ERROR_OPENING_FILE;

    fprintf(fp, "Ime:\tPrezime:\tGod:\n");

    while (curr != NULL) {

        fprintf(fp, "%s\t%s\t%d\n", curr->ime, curr->prezime, curr->god);

        curr = curr->next;
    }
    fclose(fp);
    return 0;
}

int ispisi_iz_datoteke(pozicija head,char *filename) {

    char ime[M], prez[M];
    int god,rez_ime,rez_prez,br_osoba=0,i;
    char temp_ime[M],temp_prez[M];

    char buffer[BUFFER_SIZE];
    FILE* fp = NULL;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        return ERROR_OPENING_FILE;
    }

    while(fgets(buffer,BUFFER_SIZE,fp)){
        br_osoba++;
    }
    br_osoba--;


    rewind(fp);
    while(fgetc(fp)!='\n');

    for(i=0;i<br_osoba;i++){
    fscanf(fp,"%s %s %d",temp_ime,temp_prez,&god);
    rez_ime=sscanf(temp_ime,"%s",ime);
    rez_prez=sscanf(temp_prez,"%s",prez);

    if(rez_ime==1 && rez_prez==1){
        dodaj_na_kraj(head, ime, prez, god);
    }
 


} 

        
    
   
    
}

void IzbrisiSve(pozicija head){
    pozicija temp;
    while(head->next!=NULL){
        temp=head->next;
        head->next=head->next->next;
        free(temp);
    }
}
