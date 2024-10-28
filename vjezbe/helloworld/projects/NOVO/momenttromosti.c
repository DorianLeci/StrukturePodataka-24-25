#include <stdio.h>
#define NMAX 100000

double Trapez(int n,double f[],double x);
void Jednadzba(double f[],double a,int n,double x);
 //najveci broj točaka integracije
int main(){
     //h-visina trokuta
double x;
int n,i; //broj točaka integracije
double a,b;
double Integral;
double f[NMAX];

printf("\nUpišite broj točaka integracije\n");
scanf("%d",&n);

printf("\nUnesite područje integracije\n");
scanf("%lf",&a);
scanf("%lf",&b);

x=(b-a)/n;
printf("\nVrijednost varijable x: %lf\n",x); //širina područja integracije

Jednadzba(f,a,n,x);
printf("\nFunkcija po točkama\n");
for(i=0;i<=n;i++){
    printf("%lf\n",f[i]);
}
//podintegralna funkcija

Integral=Trapez(n,f,x);

printf("\nRezultat: %lf\n",Integral);

return 0;

}

double Trapez(int n,double f[],double x){
    double Integral;
    int i;
    Integral=0.0;

    for(i=0;i<n-1;i++){

        Integral+=x*(f[i]+f[i+1])/2.0;
    }

    return Integral;
}

void Jednadzba(double f[],double a,int n,double x){
    int i;
    double ord=a;
    for(i=0;i<=n;i++){
        if(i>0){
            ord=ord+x;
        }


        printf("Ord: %lf\n",ord);
        f[i]=(-0.5*ord*ord)+7*ord+5;
    }
}