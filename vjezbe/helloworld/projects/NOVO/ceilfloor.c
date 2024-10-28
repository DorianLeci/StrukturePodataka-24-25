#include <stdio.h>

int findCeiling(int *nums,int low,int high,int x);
int findFloor(int *nums,int low,int high,int x);
int main(){
    int nums[]={1,4,6,8,9};
    int n=sizeof(nums)/sizeof(nums[0]);
    int i;

    for(i=0;i<=10;i++){
        printf("\nNumber: %d->ceiling je %d,floor je %d",i,findCeiling(nums,0,n-1,i);
        findFloor(nums,0,n-1,i));
    }

    return 0;
}

int findCeiling(int *nums,int low,int high,int x){
    //rekurzivna funkcija pa moramo base case
    if(high<low){
        return -1; //u ovom slučaju tražena stvar u funkciji ne postojis
    }

    if(x<=nums[low]){
        return nums[low];
    }
    if(x>nums[high]){
        return -1; //u ovom slučaju krov ne postoji
    }

    int mid=(low+high)/2;

    if(nums[mid]==x){
        return nums[mid];
    }
    else if(nums[mid]<x){
        return findCeiling(nums,mid+1,high,x);
    }
    else if(nums[mid]>x){
        return findCeiling(nums,low,mid,x);
    }
}

int findFloor(int *nums,int low,int high,int x){
    if(low>high){
        return -1;
    }
    if(x<nums[low]){
        return -1;
    }
    if(x>=nums[high]){
        return nums[high];
    }
    int mid=(low+high)/2;

    if(nums[mid]==x){
        return nums[mid];
    }
    else if(nums[mid]>x){
        return findFloor(nums,low,mid-1,x);
    }
    else if(nums[mid]<x){
        return findFloor(nums,mid,high,x);
    }
}