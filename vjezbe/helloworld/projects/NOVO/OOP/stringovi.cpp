#include <iostream>
#include <string>

using namespace std;

int main(){
    string s;
    cout<<"Unesi string"<<endl;
    getline(cin,s);
    char *pointer;

    pointer=&s[0];

    while(*pointer!='\0'){
        cout<<*pointer;
        pointer++;
    }
    cout<<endl;

    cout<<"Duljina stringa "<<s.length()<<endl;

    return 0;
}