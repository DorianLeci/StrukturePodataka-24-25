#include <stdio.h>
#include <math.h>

double funkc(double x);
int main(){
    double X; //pretpostavljeno rješenje
    int i;
    double Gradijent;
    double F;
    double Tol=0.0001;
    double Eps=1.0E-5;//vrijednost funkcije u nekoj točki X
    //brojac iteracija //vrijednosti funkcije u gornjoj i donjoj granici

    printf("\nUpisite pretpostavljeno rješenje\n");
    scanf("%lf",&X);

    F=funkc(X);


    i=0;

    while(fabs(F)>=Tol){

        Gradijent=(funkc(X+Eps)-F)/Eps;
        //nova procjena rješenja
        X=X-F/Gradijent;
        F=funkc(X);
        printf("\nNovi X: %.12lf\n",X);

        i++;         
        }

    printf("\nNultočka jest: %.12lf s vrijednosti funkcije: %.12lf\n",X,F);




        return 0;

    }



double funkc(double x){
    double f;
    f=-(x*x*x*x)+3;

    return f;
}