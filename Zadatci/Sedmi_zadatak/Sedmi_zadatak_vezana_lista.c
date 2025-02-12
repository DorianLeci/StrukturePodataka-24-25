#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct dir* position_dir;
typedef struct dat* position_dat;

typedef struct dat{
    
    char doc_ime[20];
    position_dat next_doc;

}dat;
typedef struct dir{

    char dir_name[20];
    position_dat doc_head;
    position_dir next_dir;
    position_dir sub_head;
    position_dir dot;
    position_dir dbl_dot;

}dir;

void add_dir(position_dir , char*);
void add_doc(position_dir, char*);
void print_path(position_dir);


void print_dir(position_dir);

int main() {
    position_dir c;

    c = malloc(sizeof(dir));
    if (c == NULL) return 1;
    strcpy(c->dir_name, "c:");
    c->dot=c;
    c->dbl_dot=NULL;
    c->next_dir=NULL;
    c->sub_head=NULL;
    c->doc_head=NULL;

 


// probni sub directory koji sadrzi neke "fileove"
    position_dir Korisnik;
    Korisnik = malloc(sizeof(dir));  if (Korisnik == NULL) return 1;
    strcpy(Korisnik->dir_name, "Korisnik");
    Korisnik->dbl_dot = c;
    Korisnik->dot = Korisnik;
    Korisnik->next_dir = NULL;
     Korisnik->sub_head=NULL;
    Korisnik->doc_head=NULL;

    add_doc(Korisnik, "rezultati.txt");
    add_doc(Korisnik, "ucenici.txt");
    add_doc(Korisnik, "ispitni_rokovi.txt");

    // Dodavanje korisnika kao poddirektorija "c:\"
    c->sub_head= Korisnik;

    char command[20];
 
    position_dir curr = c; // Početni direktorij

    printf("Dobrodosli u navigaciju kroz direktorije! Unesite 'help' za popis naredbi.\n");

    while (1) {
            printf("\n");
        print_path(curr);
        printf(">");
        scanf("%s",command);

        if(strcmp(command,"dir")==0){
            print_dir(curr);
        }
        else if (strcmp(command,"cd")==0){
            char pod_direktoriji[20];
            scanf("%s",pod_direktoriji);
            position_dir temp=curr->sub_head;
             while(1){

                if(strcmp(pod_direktoriji,".")==0){
                         break;
                     }
                else if(strcmp(pod_direktoriji,"..")==0){ 
                        
                        if(curr->dbl_dot==NULL){
                            break;
                        }
                        else {

                            curr=curr->dbl_dot;  
                            break;     

                        }
                        }
                else if(temp==NULL){
                    printf("Nepostojeci Direktoriji!\n");
                    break;
                }
                else if(strcmp(pod_direktoriji,temp->dir_name)==0){
                    curr=temp;
                    break;
                }
                else{
                   temp=temp->next_dir; 
                }

          }
            
        }
        else if(strcmp(command,"md")==0){
              char pod_direktoriji[20];
            scanf("%s",pod_direktoriji);
            add_dir(curr,pod_direktoriji);
            continue;
        }
        else if((strcmp(command,"touch")==0)){
             char file_name[20];
            scanf("%s",file_name);
            add_doc(curr,file_name);
            continue;
        }
           else if (strcmp(command, "help") == 0) {
            printf("  dir         - Prikazuje sadržaj trenutnog direktorija.\n");
            printf("  cd [ime]    - Ulazi u poddirektorij 'ime'.\n");
            printf("  md [ime]    - Kreira novi poddirektoriji 'ime'\n");
            printf("  touch [ime] - Kreira novi file u direktoriju 'ime'.\n");
            printf("  cd ..       - Vraća se u roditeljski direktorij.\n");
            printf("  exit         - Izlazi iz programa.\n");
        } else if (strcmp(command, "exit") == 0) {
            printf("Izlaz iz programa.\n");
            break;
        } else {
           printf("Nepoznata naredba. Unesite 'help' za pomoć.\n");
       }



        
    }

    return 0;
}



void add_dir(position_dir curr, char *ime_dir){

//ova funckija služi da dodavanje direktorija u driektoriji u kojem se mi trenutno nalazimo
    position_dir novi=malloc(sizeof(dir)); if (novi==NULL) return;

    strcpy(novi->dir_name,ime_dir);
    novi->dot=novi;
    novi->dbl_dot=curr;
    novi->doc_head=NULL;
    novi->sub_head=NULL;
    novi->next_dir=NULL;

    novi->next_dir=curr->sub_head;
    curr->sub_head=novi;

   
}

void add_doc(position_dir curr, char* ime_dat){

    position_dat novi=malloc(sizeof(dat)); if (novi==NULL) return;
    novi->next_doc=NULL;
   strcpy(novi->doc_ime,ime_dat);

if(curr->doc_head==NULL){
    curr->doc_head=novi;
}else{
    novi->next_doc=curr->doc_head;
    curr->doc_head=novi;
}
 
}


void print_dir(position_dir curr){

        position_dir dire=curr->sub_head;
        position_dat doc_curr=curr->doc_head;

       if (curr->dbl_dot==NULL){
          printf("<DIR>\t.\n");
       }
       else{
          printf("<DIR>\t.\n");
        printf("<DIR>\t..\n");
       }

    while(dire!=NULL){

        printf("<DIR>\t%s\n",dire->dir_name);

          dire= dire->next_dir;

    }

    while(doc_curr!=NULL){
        printf("doc\t%s\n",doc_curr->doc_ime);
        doc_curr=doc_curr->next_doc;
    }


}

void print_path(position_dir curr){

    if(curr->dbl_dot!=NULL){
        
        print_path(curr->dbl_dot);
        printf("\\%s",curr->dir_name);
    }
    else {
        printf("c:");
    }
}