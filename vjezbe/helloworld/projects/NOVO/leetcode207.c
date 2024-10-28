#include <stdio.h>
#include <math.h>

int main(){
    int arr[7];
    int target,i,j,q,z;
    int count=0,count_temp[7];
    int broj;
    int suma[7],pom=0;

                for(int k=0;k<7;k++){
                count_temp[k]=0;
                suma[k]=0;
            }

    printf("\nUnesi 7 brojeva\n");
    for(i=0;i<7;i++){
        scanf("%d",&arr[i]);
    }

    printf("\nUnesi target\n");
    scanf("%d",&target);

    for(i=0;i<7;i++){
        if(arr[i]==target){
            count=1;
            suma[pom]=target;
        }
        else{
            j=i;
            broj=0;
        while(suma[pom]!=target){
            if(j==7){
                break;
            }
            if(suma[pom]>target){
                count_temp[pom]-=broj;
            }
            suma[pom]+=arr[j];
            j++;
            broj++;
            count_temp[pom]++;
        }


        }

        pom++;
    }
    printf("\nCount temp\n");

        for(i=0;i<7;i++){
            printf("%d ",count_temp[i]);
        }
    
    for(i=0;i<7;i++){
            if((suma[i]==target)&&count_temp[i]>0){
                q=0;
                z=i;
                printf("\nSubarray koji daje zbroj\n");
                while(q<count_temp[i]){

                    printf("%d ",arr[z]);
                    q++;
                    z++;
                }
            }

        }
    printf("\n\n");
        for(i=0;i<7;i++){
            printf("%d ",suma[i]);

        }


    printf("\n\n");

           int maks=count_temp[0];
    int indeks_maks=0;

    for(i=1;i<7;i++){
        if((count_temp[i]>maks) &&(suma[i]==target)){
            maks=count_temp[i];
            indeks_maks=i;
        }
    }

    printf("\nIndeks maks: %d\n",indeks_maks);


    printf("\nNajveći subbaray\n");

        for(i=0;i<7;i++){
            if(i==indeks_maks){
                q=0;
                z=indeks_maks;
                while(q<count_temp[indeks_maks]){

                    printf("%d ",arr[z]);
                    q++;
                    z++;
                }
                if(count_temp[i]==0){
                    printf("%d ",arr[indeks_maks]);
                }
            }

        }

    printf("\n\n");


    int min=count_temp[0];
    int indeks=0;

    if(min<0){
        min=-1*min;
    }

    for(i=1;i<7;i++){
        if(count_temp[i]<0){
            count_temp[i]=-1*count_temp[i];
        }
        if((count_temp[i]<min) &&(suma[i]==target)){
            min=count_temp[i];
            indeks=i;
        }
    }


    printf("\nNajmanji subbaray\n");

        for(i=0;i<7;i++){
            if(i==indeks){
                q=0;
                z=indeks;
                while(q<count_temp[indeks]){

                    printf("%d ",arr[z]);
                    q++;
                    z++;
                }
                if(count_temp[i]==0){
                    printf("%d ",arr[i]);
                }
            }

        }

    printf("\n\n");

 




    return 0;

}