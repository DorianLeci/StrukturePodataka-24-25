#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

struct _lista;
typedef struct _lista *position;

typedef struct _lista{
    int br;
    position next;
}lista;

position FindLast(position head);
void Ispis(position p);
position PronadiPrethodni(position head,position ref);
void PushNaPocetak(position head,char *filename);
void PopOdPocetka(position head);
void BrisanjeOdPocetka(position head);

int main(){
    position head=(position)malloc(sizeof(lista));
    if(!head)return 0;

    head->next=NULL;
    //implementacija push na početak i brisanje od pocetka (LIFO)
    PushNaPocetak(head,"postfix.txt");

    PopOdPocetka(head);
    free(head);

    return 0;
}



position FindLast(position head){
    while(head->next){
        head=head->next;
    }

    return head;
}

void Ispis(position p){
    if(!p)return;
    while(p){
        printf("%d\n",p->br);
        p=p->next;
    }

    
}

position PronadiPrethodni(position head,position ref){
    position temp=head;
    while(temp->next!=NULL && temp->next!=ref){
        temp=temp->next;
    }
    if(temp->next==NULL){
        return NULL;
    }
    return temp;
}

void PushNaPocetak(position head, char *filename) {
    position new;
    int broj, numBytes, offset,result,operand1,operand2;
    char buffer[BUFFER_SIZE];
    char operator;
    FILE *fp = fopen(filename, "r");
 

    if (!fp) return;

    if (fgets(buffer, BUFFER_SIZE, fp)) {
        offset = 0;
    }

    while (sscanf(buffer + offset, " %c%n", &operator, &numBytes) == 1) { //preskačemo sve space-ove unutar filea
        if (isdigit(operator)) {
            sscanf(buffer + offset, " %d%n", &broj, &numBytes); //ponovno učitavamo is buffera,ali ovoga puta broj(i dalje s istim offsetom)

            new = (position)malloc(sizeof(lista));
            if (!new) return;

            new->br = broj;
            new->next = head->next;
            head->next = new;

        } 

        else if(!isdigit(operator)) {

        if(operator!='+' && operator!='*' && operator!='-' && operator!='/'){
            printf("\nNeispravan operator\n");
            return;
        }

        if(!head->next || !head->next->next){
            //ako smo učitali operator a imamo nula ili jedan element na stacku,ne mozemo provesti operaciju
            printf("\nPremalo operanada\n");
            return;
        }


        position prvi=head->next;
        position drugi=head->next->next;

        operand2=drugi->br;
        operand1=prvi->br;
        head->next=drugi->next;

        free(prvi);
        free(drugi);

                switch (operator) {
                    case '+':
                        result = operand2 + operand1;
                        printf("\nRezultat: %d\n",result);
                        printf("\n___________\n");
                        break;
                    case '-':
                        result = operand2 - operand1;
                        printf("\nRezultat: %d\n",result);
                        printf("\n___________\n");
                        break;

                    case '*':
                        result = operand2 * operand1;
                        printf("\nRezultat: %d\n",result);
                        printf("\n___________\n");
                        break;

                    case '/':
                        if (operand1 == 0) {
                            printf("\nPrvi operand ne smije biti nula\n");
                            return;
                        }
                        result = operand2 / operand1;
                        break;
                    default:
                        return;
                }

                new = (position)malloc(sizeof(lista));
                if (!new) return;

                new->br = result;
                new->next = head->next;
                head->next = new;


        }
        offset += numBytes;
        printf("\nTrenutni stack\n");
        Ispis(head->next);
    }

    //nakon završetka petlje provjeravamo je li na stacku ostao samo jedan element
    if(head->next && head->next->next){
        printf("\nPostfix izraz nije valjan\n");
    }

    printf("\nTrenutni stack\n");
    Ispis(head->next);

    fclose(fp);
}

void PopOdPocetka(position head){

    position temp;
    while(head->next){
        temp=head->next;
        head->next=head->next->next; //head->next->next
        free(temp);

    }
}

void BrisanjeOdPocetka(position head){
    position temp=head,brisi;
    while(temp->next){
        brisi=temp->next;
        temp->next=temp->next->next;

        free(brisi);
    }
}
