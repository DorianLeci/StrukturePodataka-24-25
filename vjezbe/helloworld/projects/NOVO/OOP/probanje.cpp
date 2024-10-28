#include <iostream>
using namespace std;
int funcA(int x) {
x += 7;
return x;
}
void funcB(int& y) {
y = 42;
}
void funcC(int z, int& w) {
z = 0;
w = 0;
}
int main() {
int r = 13, s = 11;
cout << r + s << " r + s" << endl;
r = funcA(s);
cout << r << " " << s << endl;
funcB(s);
cout << r << " " << s << endl;
funcC(r, s) ;
cout << r << " " << s << endl;
return 0;
}