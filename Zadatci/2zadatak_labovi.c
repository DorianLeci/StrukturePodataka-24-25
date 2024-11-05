#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_OPENING_FILE -1
#define BUFFER_SIZE 1024

struct _person;
typedef struct _person *position;

typedef struct _person {
char fname[50], lname[50];
int birth_year;
position next;
}person;

position create_person(char* fname, char* lname, int birth_year);
int prepend_list(position head,int br_osoba);
int print_list(position first);
position find_last(position head);
int append_list(position head,int br_osoba);
position find_by_lname(position first, char* lname);
int ObrisiEl(position head,position ref);
position FindPrev(position head,position ref);
int BrisiSve(position head);

int main() {
    int odabir,br_osoba;
    position ref,head;
    char prezime[50];
    head=(position)malloc(sizeof(person));

    if(!head){
        printf("\nNeuspješno alociranje memorije head-a\n");
        return -1;
    }
    head->next=NULL;

    printf("\nUnesi zelis li na pocetak(0) ili kraj(1) liste");
    scanf("%d",&odabir);
    printf("\nUnesi broj osoba koje ces unijeti\n");
    scanf("%d",&br_osoba);

    if(odabir==0){
        append_list(head,br_osoba);
        print_list(head->next);
    }
    else if(odabir==1){
        prepend_list(head,br_osoba);
        print_list(head->next);
    }
    else{
        printf("\nKrivi unos\n");
    }

    printf("\nUnesi prezime koje zelis pretraziti i obrisati\n");
    scanf("%s",prezime);
    ref=find_by_lname(head->next,prezime);
    if(ref){
        ObrisiEl(head,ref);
        printf("\nNakon brisanja elementa\n");
        print_list(head->next);
    }


    BrisiSve(head);
    print_list(head->next);
    free(head);

    return 0;


}


position create_person(char* fname, char* lname,int birth_year) {

position new_person = NULL;

new_person = (position)malloc(sizeof(person));
if (!new_person) {
printf("\nNije uspješno malociranje\n");
return NULL;
}
strcpy(new_person->fname, fname);
strcpy(new_person->lname, lname);
new_person->birth_year = birth_year;
new_person->next = NULL;

return new_person;

}

int prepend_list(position head,int br_osoba) {
position new_person = NULL;
position temp;
int i,birth_year;
char fname[50],lname[50];

for(i=0;i<br_osoba;i++){
    printf("\nUpiši ime,prezime i godinu rođenja\n");
    scanf("%s %s %d",fname,lname,&birth_year);
    new_person = create_person(fname, lname, birth_year);

    if (!new_person) {
    return -1;
    }
    temp = head->next;
    new_person->next = temp;
    head->next = new_person;


}

    return 0;

}

int print_list(position first) {
position temp = first;
if(temp==NULL){
    printf("\nLista nema elemenata\n");
}
while (temp != NULL) {
printf("%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
temp = temp->next;
}

return 0;
}

position find_last(position head) {
position temp = head;
while (temp->next != NULL) {
temp = temp->next;
}

return temp;
}

int append_list(position head,int br_osoba) {
position new_person = NULL;
position last = NULL;
int i,birth_year;
char fname[50],lname[50];


for(i=0;i<br_osoba;i++){
    printf("\nUpiši ime,prezime i godinu rođenja\n");
    scanf("%s %s %d",fname,lname,&birth_year);
    new_person = create_person(fname, lname, birth_year);
    if (!new_person) {
        return -1;
        }

    last = find_last(head);
    last->next = new_person;
    new_person->next = NULL; 

    }


return 0;

}

position find_by_lname(position first, char* lname) {
position temp = first;

while (temp != NULL && strcmp(lname,temp->lname)!=0) {
temp = temp->next;
}
if (temp == NULL) {
return NULL;
}
return temp;
}

int ObrisiEl(position head,position ref){

    position prethodni=FindPrev(head,ref);

    if(!prethodni){
        return -1;
    }

    prethodni->next=ref->next;
    free(ref);

    return 0;
}

position FindPrev(position head,position ref){
    position temp=head;

    while(temp->next!=NULL && temp->next!=ref){
        temp=temp->next;
    }

    if(!temp->next){
        printf("\nNe postoji prethodni\n");
        return NULL;
    }

    return temp;
}

int BrisiSve(position head){
    position temp=head;
    position zadnji;
    position prethodni;
    while(temp->next!=NULL){
        zadnji=find_last(temp->next);
        prethodni=FindPrev(head,zadnji);

        prethodni->next=zadnji->next;
        free(zadnji);
    }

    return 0;
}







