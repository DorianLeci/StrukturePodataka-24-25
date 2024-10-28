#include<cmath>
#include <iostream>
using namespace std;

float mathFunc(float x) {

   return 2*pow(x,2);    //the function 1 - e^(-x/2)
}

float integrate(float a, float b, int n) {
   float h, sum;
   int i;
   h = (b-a)/n;    //calculate the distance between two interval
   sum = (mathFunc(a)+mathFunc(b))/2;    //initial sum using f(a) and f(b)

   for(i = 1; i<n; i++) {
      sum += mathFunc(a+i*h);
      cout<<"vrijednost: "<<mathFunc(a+i*h)<<endl;
   }
   cout<<"Suma "<<sum<<endl;
   return (h*sum);    //The result of integration
}

main() {
   float result, lowLim, upLim;
   int interval;
   cout << "Enter Lower Limit, Upper Limit and interval: "; cin >>lowLim >>upLim >>interval;
   result = integrate(lowLim, upLim, interval);
   cout << "The answer is: " << result;
}