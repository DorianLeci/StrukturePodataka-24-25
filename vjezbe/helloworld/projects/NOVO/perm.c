#include <stdio.h>

void permutations(int res[][100],int *arr,int idx,int size,int *resSize);
void swap(int *a,int *b);
int main(){
    int arr[]={1,2,3};
    int res[100][100]; //2d array za storanje permutacija
    int rezSize=0;
}

void permutations(int res[][100],int *arr,int idx,int size,int *resSize){
    int i;

    for(i=idx;i<size;i++){
        swap(&arr[idx],&arr[i]);
    }

}

void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}