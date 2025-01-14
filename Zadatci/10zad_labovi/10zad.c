#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

struct _grad;
typedef struct _grad *node;

typedef struct _grad{
    node left,right;
    char ime_grada[MAX_LEN];
    int stan;
}grad;

struct _drzave;
typedef struct _drzave* pos;

typedef struct _drzave{
    char ime_drzave[MAX_LEN];
    pos next;
    node root;
}drzave;

struct _red;
typedef struct _red *redPos;

typedef struct _red{
    redPos next;
    node el;
}red;

int UcitajIzDatoteke(char *fname,pos head);
int SortiraniUnosDrzava(pos head,char *ime_drzave,char *ime_datoteke);
int OtvaranjeDatotekeSGradovima(pos novi,char *ime_datoteke);
void Ispis(pos p);
int Provjera(char *temp);
int SkeniranjeIzStringa(char *temp);
node SortiraniUnosGradova(int br_stanovnika,char *ime_grada,node root);
void IspisGradovaPreorder(node root);
void IspisiPoTresholdu(pos head,char *drzava,int broj);
pos TraziPoListi(pos head,char *drzava);
void InOrderTreshold(redPos head,node root,int br);
void UnosURed(redPos head,node root);
void IspisTreshold(redPos head,int broj);

int main(){
    pos head=(pos)malloc(sizeof(drzave));
    if(!head)return -1;
    head->next=NULL;

    UcitajIzDatoteke("drzave.txt",head);
    Ispis(head->next);
    IspisiPoTresholdu(head,"Hrvatska",120000);
    return 0;
}

int UcitajIzDatoteke(char *fname,pos head){
    FILE *fp=fopen(fname,"r");
    if(!fp)return -1;

    char buffer[MAX_LEN];
    char ime_drzave[MAX_LEN],ime_datoteke[MAX_LEN];
    int numBytes;

    while(fgets(buffer,MAX_LEN,fp)){
        int offset=0;
        int len=strlen(buffer);
        buffer[len-1]='\0';
        while(strlen(buffer+offset)>0){
            if(sscanf(buffer+offset,"%s %s %n",ime_drzave,ime_datoteke,&numBytes)==2){
                offset+=numBytes;
                SortiraniUnosDrzava(head,ime_drzave,ime_datoteke);
            }
            else{
                break;
            }
        }

    }
}

int SortiraniUnosDrzava(pos head,char *ime_drzave,char *ime_datoteke){
    pos novi=(pos)malloc(sizeof(drzave));
    if(!novi)return -1;
    strcpy(novi->ime_drzave,ime_drzave);
    novi->root=(node)malloc(sizeof(grad));
    if(!novi->root)return -1;
    novi->root=NULL;

    pos prev=head;
    pos curr=head->next;
    
    while(curr){
        if(strcmp(curr->ime_drzave,ime_drzave)<0)break;
        if(!strcmp(curr->ime_drzave,ime_drzave)){
            free(novi);
            return -1;
        }
        prev=curr;
        curr=curr->next;
    }
    prev->next=novi;
    novi->next=curr;
    OtvaranjeDatotekeSGradovima(novi,ime_datoteke);
}

void Ispis(pos p){
    if(!p)return;

    while(p){
        printf("%s\n",p->ime_drzave);
        IspisGradovaPreorder(p->root);
        p=p->next;
    }
}

int OtvaranjeDatotekeSGradovima(pos novi,char *ime_datoteke){
    FILE *fp=fopen(ime_datoteke,"r");
    if(!fp){
        printf("\nNije nađeno\n");
        return -1;
    }

    int numBytes;
    char buffer[MAX_LEN],grad[MAX_LEN],stan[MAX_LEN];
    while(fgets(buffer,MAX_LEN,fp)){
        int len=strlen(buffer);
        int offset=0;
        buffer[len-1]='\0';
        while(strlen(buffer+offset)>0){
            if(sscanf(buffer+offset,"%s %s %n",grad,stan,&numBytes)==2){
                printf("Grad: %s,Stan:%s\n",grad,stan);
                    offset+=numBytes;
                    int br_stanovnika;
                    char ime[MAX_LEN],temp[MAX_LEN];
                    if(sscanf(grad,"Naziv_%s",ime)==1 && sscanf(stan,"%d_%s",&br_stanovnika,temp)==2){
                        if(strlen(temp)!=10)break;
                        novi->root=SortiraniUnosGradova(br_stanovnika,ime,novi->root);
                    }
                    else{
                        break;
                    }

            }
            else{
                break;
            }
        }

    }
    fclose(fp);
}

int Provjera(char *temp){
    for(int i=0;temp[i]!='\0';i++){
        if(temp[i]=='_')return 1;
    }
    return 0;
}

int SkeniranjeIzStringa(char *temp){
    int vrati;
    if(sscanf(temp,"%d",&vrati)==1)return vrati;
}

node SortiraniUnosGradova(int br_stanovnika,char *ime_grada,node root){
    if(!root){
        root=(node)malloc(sizeof(grad));
        root->stan=br_stanovnika;
        strcpy(root->ime_grada,ime_grada);
        if(!root)return NULL;
        root->left=root->right=NULL;
    }
    else if(br_stanovnika<root->stan && strcmp(ime_grada,root->ime_grada)!=0){
        root->left=SortiraniUnosGradova(br_stanovnika,ime_grada,root->left);
    }
    else if(br_stanovnika>root->stan && strcmp(ime_grada,root->ime_grada)!=0){
        root->right=SortiraniUnosGradova(br_stanovnika,ime_grada,root->right);
    }
    else if(br_stanovnika==root->stan && strcmp(ime_grada,root->ime_grada)!=0){
        if(strcmp(ime_grada,root->ime_grada)<0){
            root->left=SortiraniUnosGradova(br_stanovnika,ime_grada,root->left);          
        }
        else if(strcmp(ime_grada,root->ime_grada)>0){
            root->right=SortiraniUnosGradova(br_stanovnika,ime_grada,root->right);  
        }

    }
    return root;
}

void IspisGradovaPreorder(node root){
    if(!root)return;

    printf("Ime: %s,Br stanovnika: %d\n",root->ime_grada,root->stan);
    IspisGradovaPreorder(root->left);
    IspisGradovaPreorder(root->right);
}

void IspisiPoTresholdu(pos head,char *drzava,int broj){
    pos trazi=TraziPoListi(head,drzava);
    if(trazi){
        redPos head=(redPos)malloc(sizeof(red));
        if(!head)return;
        head->next=NULL;
        printf("\nTrazena drzava:%s\n",trazi->ime_drzave);
        printf("\nSvi gradovi za državu koji su prešli treshold\n");
        InOrderTreshold(head,trazi->root,broj);
        printf("\nIspis po tresholdu\n");
        IspisTreshold(head,broj);
    }
}
pos TraziPoListi(pos head,char *drzava){
    pos temp=head->next;
    if(!temp)return NULL;

    while(temp){
        if(strcmp(temp->ime_drzave,drzava)==0)return temp;
        temp=temp->next;
    }

    return NULL;
}

void InOrderTreshold(redPos head,node root,int br){ //ispisivanje svih gradova koji imaju veći broj stanovnika
    if(!root)return;
    if(root->stan>br){
        UnosURed(head,root);
    }

    InOrderTreshold(head,root->left,br);
    InOrderTreshold(head,root->right,br);
}

void UnosURed(redPos head,node root){

    redPos novi=(redPos)malloc(sizeof(red));
    if(!novi)return;
    novi->el=root;
    redPos prev=head;
    redPos curr=head->next;

    while(curr){
        if(novi->el->stan>curr->el->stan)break;
        if(novi->el->stan==curr->el->stan){
            if(strcmp(novi->el->ime_grada,curr->el->ime_grada)>0)break;
        }
        prev=curr;
        curr=curr->next;
    }

    prev->next=novi;
    novi->next=curr;
}


void IspisTreshold(redPos head,int broj){
    redPos temp=head->next;
    while(temp){
        if(temp->el->stan>broj){
            printf("Ime: %s,Br stanovnika: %d\n",temp->el->ime_grada,temp->el->stan);
        }
        temp=temp->next;
    }
}
void IspisRed(redPos p){
    while(p){            
        printf("Ime: %s,Br stanovnika: %d\n",p->el->ime_grada,p->el->stan);
        p=p->next;
    }
}
