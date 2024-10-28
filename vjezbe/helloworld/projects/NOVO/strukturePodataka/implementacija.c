#include <stdio.h>


typedef struct{
    char ime[10];
    int broj;

}student;

int main(){
    student var;
    printf("\nUnesi ime\n");
    scanf("%s",var.ime);
    printf("\nUnesi broj\n");
    scanf("%d",&var.broj);
    printf("%d\n",&var);
    printf("%d\n",var.ime);
    printf("%d\n",&var.broj);

    return 0;
}