#include <stdio.h>
#include <math.h>
#define Pi 3.14159
//program za rješavanje općenite nelinearne jednadzbr

double Jedn(double);

int main(){
    int i,Nit; //Nit--brojac iteracija
    double Tol;
    double Xd,Fd;
    double Xg,Fg;
    double XgS,XdS;
    double X,F;
    printf("\nUpisite donju granicu podrucja\n");
    scanf("%lf",&Xd);
    printf("\nUpisite gornju granicu podrucja\n");
    scanf("%lf",&Xg);
    printf("\nUpisite trazenu tocnost\n");
    scanf("%lf",&Tol);

    //iznosi funkcija u početnim točkama
    //dva puta ćemo pozvati funkciju jednadzba kako bi dobili tu informaciju
    //kao rješenje jednadžbe tražimo nultočku

    Nit=(int)log((Xg-Xd)/Tol)/log(2.0)+1;
    Fd=Jedn(Xd);
    Fg=Jedn(Xg);
        i=0;

    while(i++<=Nit){
        X=(Xd+Xg)/2.0; //x koordinate
        F=Jedn(X);
        
        if(F*Fd<0.0){
            XdS=Xd;
            XgS=Xg;
            Xg=X; //promjena granice
            Fg=F;
        }
        else if(F*Fd>0.0){
        XdS=Xd;
        XgS=Xg;
        Xd=X;
        Fd=F;    //iznos funkcije u procesu raspolavljanja
    }
    else{
        printf("\nRješenje je točka X=%lf s vrijednosti F(X)=%lf",X,F);
    }

    }

    printf("\nKonačno rješenje je točka X=%lf s vrijednosti F(X)=%lf",X,F);

    return 0;

}








double Jedn(double x) {
    //jednadzba koja se rjesava
    double Fx;
    Fx=0.5*exp(-x/(2.0*Pi))*sin(x)-0.25;
    return Fx;
}
