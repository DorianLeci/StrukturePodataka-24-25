#include <stdio.h>
#include <math.h>

#define MAX 100000

double Trapez(double[],int,double);
void Jednadzba(double f[],double a,double b,int n,double x);

int main(){
    double x;
    double a,b;
    int n;
    double Integral;
    double f[MAX];
    
    printf("\nUnesi duljinu male i velike poluosi elipse\n");
    scanf("%lf %lf",&a,&b);

    printf("\nUnesi broj podjela\n");
    scanf("%d",&n);


    x=a/n;

    Jednadzba(f,a,b,n,x);

    Integral=Trapez(f,n,x);

    printf("\nRješenje jest: %.25lf\n",4*Integral);



}

double Trapez(double f[],int n,double x){
    double Integral;
    int i;
    Integral=0.0;

    for(i=0;i<n-1;i++){
        Integral+=x*(f[i]+f[i+1])/2.0; //vrijednost x-a uvijek mora ostati ista
    }

    return Integral;
}

void Jednadzba(double f[],double a,double b,int n,double x){
    int i;
    double ord=0;
    for(i=0;i<=n;i++){
        if(i>0){
            ord=ord+x;
        }


        printf("Ord: %lf\n",ord);
        f[i]=b*sqrt(1-((ord*ord)/(a*a)));
        printf("FUnkc: %lf\n",f[i]);
    }
}