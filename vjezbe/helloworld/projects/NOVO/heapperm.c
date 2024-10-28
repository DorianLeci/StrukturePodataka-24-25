#include <stdio.h>

void heapPermutation(int a[],int size,int n);
void swap(int *a,int *b);
void printArr(int *a,int n);

int main(){
    int a[]={1,2,3};
    int n=sizeof(a)/sizeof(a[0]);
    heapPermutation(a,n,n);
}

void heapPermutation(int a[],int size,int n){
    int i;

    if(size==1){
        printArr(a,n);
        return;
    }
    for(i=0;i<size;i++){
                printf("\nI: %d\n",i);
                printf("Size: %d\n",size);
        heapPermutation(a,size-1,n);


        if(size%2==1){
            swap(&a[0],&a[size-1]);
        }
        else{
            swap(&a[i],&a[size-1]);
        }
    }
}

void swap(int *a,int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void printArr(int *a,int n){
    int i;
    for(i=0;i<n;i++){
        printf("%d ",a[i]);
    }

    printf("\n\n");
}