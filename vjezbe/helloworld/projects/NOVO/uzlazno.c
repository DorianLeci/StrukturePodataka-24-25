#include <stdio.h>
#include <stdlib.h>

int main(){
    int *arr=NULL,n,i,j,pom,brojac;
    int *indeks=NULL;
    int *lista_jednakih=NULL;
    int min,maks,ind_min,ind_maks;
    printf("\nUnesi velicinu liste\n");
    scanf("%d",&n);

    arr=malloc(sizeof(int)*n);
    indeks=malloc(sizeof(int));
    indeks[0]=0;

    if(arr==NULL){
        printf("\nError pri alokaciji\n");
        exit(1);
    }

    printf("\nUnesi listu\n");
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }


    pom=0;

    for(i=0;i<n-1;i++){
        if(arr[i+1]>arr[i]){
            printf("\nNađeno\n: %d\n",arr[i+1]);
            printf("Pom: %d\n",pom);
            indeks[pom]++;

            if(i==n-2){
                indeks[pom]++;
            }
        }
        if(arr[i+1]<arr[i] || arr[i+1]==arr[i]){
            printf("\nKraj\n: %d\n",arr[i+1]);
            indeks[pom]++;
            pom++;
            indeks=realloc(indeks,sizeof(int)*(pom+1));

            indeks[pom]=0;
            printf("\nPom: %d\n",pom);
        }
        
    }

    maks=indeks[0];
    ind_maks=0;

    for(i=1;i<=pom;i++){
        if(indeks[i]<min && indeks[i]>1){
            min=indeks[i];
            ind_min=i;
        }
        if(indeks[i]>maks){
            maks=indeks[i];
            ind_maks=i;
        }
    }


    min=indeks[ind_maks];
    ind_min=ind_maks;

        for(i=0;i<=pom;i++){
        if(indeks[i]<min && indeks[i]>1){
            min=indeks[i];
            ind_min=i;
        }

    }



    printf("\nIndeks maks: %d\n",ind_maks);
        printf("\nIndeks min: %d\n\n",ind_min);

    for(i=0;i<=pom;i++){
        printf("%d ",indeks[i]);
    }
    printf("\nKraj ispisa______________\n");

    printf("\nMaksimalna i minimalna podlista\n");
    if(ind_maks>0){
        i=ind_maks+indeks[ind_maks-1]-1;
    }
    else{
        i=ind_maks;
    }

    printf("\nI: %d\n",i);

    if(ind_min>0 && ind_min!=ind_maks){
    j=ind_min+indeks[ind_maks]-1;
    }
    if(indeks[ind_min-1]==1 && indeks[ind_min-2]==1){
        j=ind_min+indeks[ind_min]+1;
    }
    else if(ind_min==ind_maks){
        j=ind_maks;
    }

    printf("\nJ: %d\n",j);
    brojac=0;
    while(brojac!=indeks[ind_maks]){
        printf("%d ",arr[i]);
        i++;
        brojac++;
    }

        for(i=0;i<=pom;i++){
        if(indeks[i]==maks && i!=ind_maks){
            printf("\nJoš jedna ista podlista\n");
            brojac=0;
            j=ind_maks;
        while(brojac!=indeks[ind_maks]){
        printf("%d ",arr[j]);
        j++;
        brojac++;
    }
        }
    }

    brojac=0;
    printf("\n\n");

        if(indeks[ind_min]==0){
        printf("%d ",arr[j]);
    }

        while(brojac!=indeks[ind_min]){
        printf("%d ",arr[j]);
        j++;
        brojac++;
    }
    for(i=0;i<=pom;i++){
        if(indeks[i]==min && i!=ind_min){
            printf("\nJoš jedna ista podlista\n");
            brojac=0;
            j=ind_min;
        while(brojac!=indeks[ind_min]){
        printf("%d ",arr[j]);
        j++;
        brojac++;
    }
        }
    }


    printf("\n\n");

    return 0;
}