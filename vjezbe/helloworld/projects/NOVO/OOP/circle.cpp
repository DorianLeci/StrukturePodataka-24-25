#include <iostream>
using namespace std;

class kocka{
    public:

    double a;
    double b;

    double opseg(){
        return 2*a+2*b;
    }

};

class krug{
    public:
        double x;
        double y;
        kocka var;

        krug(){
            cout<<"Unesi x i y"<<endl;
            cin>>x>>y;
            cout<<"Unesi a i b stranicu kocke"<<endl;
            cin>>var.a>>var.b;


            
        }
        double površina(){
            return x*y;
        }
        double vrati_x(){
            return x;
        }
        double vrati_y(){
            return y;
        }
};



void promjena(krug &k){
    k.x=5;
    k.y=6;
}

void copy_value(krug &k,kocka &koc){

    koc.a=k.var.a;
    koc.b=k.var.b;
    
}
void copy_value(krug *k,kocka *koc){
    koc->a=k->var.a;
    koc->b=k->var.b;
}

int main(){
    krug k;
    krug *p=&k;
    kocka koc;

    kocka &ref=koc;

    copy_value(k,ref);
    cout<<"Ref"<<ref.a<<ref.b<<endl;
    cin>>ref.a>>ref.b;

    cout<<"Ref_novi"<<ref.a<<ref.b<<endl;


    cout<<p->vrati_x()<<endl<<p->površina()<<endl;
    promjena(k);
    cout<<"Nakon promjene"<<p->vrati_x()<<endl<<p->površina()<<endl;

    cout<<"Kocka"<<koc.a<<" "<<koc.b<<endl;


    ref=koc;
    kocka &ref2=koc;
    cout<<"prije"<<ref2.a<<endl<<ref2.b<<endl<<endl;
    ref2.a=ref2.a+ref2.a;
    ref2.b=ref2.b+ref2.b;

    cout<<ref.a<<endl<<ref.b<<endl<<endl;


    promjena(k);

}

