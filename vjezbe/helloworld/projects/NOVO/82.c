#include <stdio.h>
#include <stdlib.h>


void kombinacija(int *lista,int *data,int st,int end,int index,int r);

int main(){
    int *lista=NULL;
    int *data=NULL;
    int i;
    int broj,r; //r-broj brojeva koje želimo kombinirati
    printf("\nUnesi broj el liste\n");
    scanf("%d",&broj);

        lista=malloc(sizeof(int)*broj);
    
    printf("\nUnesi sve brojeve koje zelis kombinirati\n");
    for(i=0;i<broj;i++){
        scanf("%d",&lista[i]);
    }

    printf("\nUnesi br kombinacija\n");
    scanf("%d",&r);


    data=malloc(sizeof(int)*r);



    if(lista==NULL){
        printf("\nGreška\n");
        exit(1);
    }

    kombinacija(lista,data,0,broj-1,0,r);

    return 0;

    free(lista);
    free(data);

}


void kombinacija(int *lista,int *data,int st,int end,int index,int r){

    int i,j;

    if(index==r){
        printf("\nNađeno\n");
        for(j=0;j<r;j++){
            printf("%d ",data[j]);


        }
        printf("\n");
    return;
    }

        data[index]=lista[st];

        kombinacija(lista,data,st+1,end,index+1,r);

                printf("\nJes\n");
        printf("%d ",st);


    

}