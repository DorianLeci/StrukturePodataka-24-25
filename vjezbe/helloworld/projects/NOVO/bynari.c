#include <stdio.h>

int binary(int *nums,int n,int target);
int brojRotacija(int *nums,int n);
int findCeiling(int *nums,int n);


int main(){
    int nums[]={1,5,2,2,2,5,5,4};
    int k;

    int rot;

    int n=sizeof(nums)/sizeof(nums[0]);

    //sortiranje
    rot=brojRotacija(nums,n);
    printf("\nBroj rotacija:%d\n",rot);

    printf("\nUpiši razliku k\n");
    scanf("%d",&k);

    return 0;
    
}

int binary(int *nums,int n,int target){
    int low=0;
    int high=n-1; 
    //početni i završni indeks,tj.područje pretraživanja
    while(low<=high){

    int mid=(low+high)/2; //središnji indeks

    if(target==nums[mid]){
        return mid; //ne treba daljnje pretraživanje
        //traženi element je odmah pronađen na sredini
    }

    else if(target<nums[mid]){
        high=mid-1;
    }
    else if(target>nums[mid]){
        low=mid+1;
    }

}
//u slucaju da element ne postoji
return -1;

}

int brojRotacija(int *nums,int n){
    int low=0;
    int high=n-1;

    while(low<=high){
        //ako je lista već sortirana, onda ćemo vratiti low, tj.u prvom slučaju nula
        if(nums[low]<=nums[high]){
            return low;
        }

        int mid=(low+high)/2;
        int next,prev;

        next=(mid+1)%n; //prethodnik i nasljednik središnjeg elementa(tj.indeksi tog elementa)
        prev=(mid-1+n)%n;

        if(nums[mid]<=nums[next] && nums[mid]<=nums[prev]){
            printf("\nNađeno: %d %d %d \n",nums[prev],nums[mid],nums[next]);
            return mid;
        }
        else if(nums[mid]<=nums[high]){
            high=mid-1;
        }
        else if(nums[mid]>=nums[low]){
            low=mid+1;
        }
    }

    return -1;
}

void FindPair(int *nums,int n){
    int low=0;
    int high=n-1;


}