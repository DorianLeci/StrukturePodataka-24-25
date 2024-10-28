#include <iostream>
using namespace std;

double StrToDouble(char *s,int len);
double StrToDouble(string s);
void Obrni(string &s);

int main(){
    string s="Dorian";
    int len=s.length();
    char *p=&s[0];

    StrToDouble(p,len);
    StrToDouble(s);

    cout<<s<<endl;

    Obrni(s);

    return 0;
}

double StrToDouble(char *s,int len){
    for(int i=0;i<len;i++){
        cout<<(int)s[i]<<endl;
    }
    cout<<endl;
}

double StrToDouble(string s){
    for(int i=0;s[i]!='\0';i++){
        cout<<(int)s[i]<<endl;
    }



}


   

