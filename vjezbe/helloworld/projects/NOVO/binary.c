#include <stdio.h>

void binary(int *arr,int n,int target,int low,int high);

int main(){
    int arr[]={1,2,5,4,6};

    int n=sizeof(arr)/sizeof(arr[0]);

    binary(arr,n,1,0,n-1);


}

void binary(int *arr,int n,int target,int low,int high){

    int mid=(low+high)/2;

    if(low>high){
        printf("\nTarget nije nađen\n");
        return;
    }

    if(target==arr[mid]){
        printf("\nTarget je nađen: %d\n",target);
        return;
    }
    else if(target>arr[mid]){
        binary(arr,n,target,mid+1,high);
    }
    else if(target<arr[mid]){
        binary(arr,n,target,low,mid-1);
    }

}