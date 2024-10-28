#include <stdio.h>
#include <string.h>

void perm(char str[],int st,int end);
void swap(char *a,char *b);
int freq(char str[]);

int main(){
    char str[20];
    int len;
    int brojac;

    fgets(str,20,stdin);

    len=strlen(str);


    for(int j=0;j<len;j++){
        if(str[j]=='\n'){
            str[j]='\0';
        }   
    }

    printf("\nLista\n");

    printf("%s\n\n",str);

    len=strlen(str);

    perm(str,0,len-1);

    brojac=freq(str);
    printf("\nBrojac: %d\n",brojac);

    return 0;
}

void perm(char str[],int st,int end){

    int i;

    if(st==end){
        printf("\nNova permutacija\n");
        printf("%s",str);
    printf("\n");
    }

    else{
        for(i=st;i<=end;i++){
        swap(&str[st],&str[i]);
        perm(str,st+1,end);
        swap(&str[st],&str[i]);
        }

    }

}

void swap(char *a,char *b){
 char temp=*a;
 *a=*b;
 *b=temp; //zamjena dviju vrijednosti iz liste
}

int freq(char str[]){

    if(*str=='\0'){
        return 0;
    }

    return 1+freq(str+1);
}