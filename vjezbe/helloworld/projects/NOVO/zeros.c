#include <stdio.h>

int red(char str[]);
void pom(char str[]);

int main(){
    char str[100]="aaabbbaaacdddddddf";
    pom(str);

    printf("\nNakon brisanja\n");
    printf("%s\n",str);

    return 0;
}

int red(char str[]){
    int i,j,k,brojac;
    int flag=0;
    for(i=2;str[i];i++){ //krecemo od i=2 jer nema smisla krenuti od manje
        if(str[i]==str[i-1] && str[i-1]==str[i-2]){
            printf("\nNađeno\n");
            printf("%d",i);
            j=i+1; //bitno je svaki put osvjeziti vrijednost jota
            k=3;
            brojac=0;
            printf("\njot: %d\n",j);
            while(str[j]){
                str[j-k]=str[j];
                j++;
                brojac++;
            }
            str[j-k]='\0';
        printf("\nTrenutno stanje\n");
        printf("%s\n",str);

        flag++;
        }
    }

    printf("\nFlag: %d\n",flag);

    return flag>0;



}

void pom(char str[]){
    while(red(str));
}