#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct stablo;
typedef struct stablo *cvor;

typedef struct stablo {
    int br;
    cvor left, right;
} stablo;

void replace(cvor root,int *rez);
cvor preorder_replace(cvor root);
cvor insert(int br, cvor root);
void alociraj_l(int br,cvor root);
void alociraj_d(int br,cvor root);
void preorder(cvor root);
void ispis_stabla(cvor root, int space);
void inorder_upis(cvor,FILE*);
void DeleteTree(cvor root);

int main() {
    srand(time(0));
    cvor root =NULL;

    root=insert(2,root);
    root=insert(5, root);  
    root=insert(1, root);  
    root=insert(7, root);  
    root=insert(4, root);   
    root=insert(8, root);   
    root=insert(2, root);   
    root=insert(11, root);  
    root=insert(7, root);   
    root=insert(3, root);   

     FILE *fp=NULL;
    fp=fopen("zad_a_inorder.txt", "w"); if(!fp) return -1;

     printf("Ispis stabla:\n");
     preorder(root);
    
    inorder_upis(root,fp);


      FILE *fp_b=NULL;
    fp_b=fopen("zad_b_inorder.txt", "w"); if(!fp_b) return -1;

    preorder_replace(root);
    printf("Nakon zammjene\n");
    preorder(root);
    inorder_upis(root,fp_b);


    cvor root_novi =NULL;
    for(int i=0;i<10;i++){
        root_novi=insert(rand()%81+10,root_novi);
    }
    printf("Ispis random stabla:\n");
    preorder(root_novi);
    FILE *fp_c=NULL;
    fp_c=fopen("zad_c_inorder.txt", "w"); if(!fp_c) return -1;
    inorder_upis(root_novi,fp_c);

    printf("\nRandom drvo nakon zamjene\n");
    preorder_replace(root_novi);
    preorder(root_novi);
    FILE *fp_d=NULL;
    fp_d=fopen("zad_d_inorder.txt", "w"); if(!fp_d) return -1;
    inorder_upis(root_novi,fp_d);

    fclose(fp);
    fclose(fp_b);
    fclose(fp_c);
    fclose(fp_d);

    DeleteTree(root);
    return 0;
}


cvor insert(int br, cvor root) {
    if (root == NULL) {
        cvor novi = malloc(sizeof(stablo)); 
        if (!novi) return NULL; 
        novi->br = br;
        novi->left = NULL;
        novi->right = NULL;
        return novi;
    }
    if (br >=root->br) {
        root->left = insert(br, root->left);
    } 
    else if (br < root->br) {
        root->right = insert(br, root->right);
    }
    
    return root;
}


void alociraj_l(int br,cvor root){
    cvor novi = malloc(sizeof(stablo)); 
    novi->br = br;
    novi->left = NULL;
    novi->right = NULL;
    
    root->left = novi;
}

void alociraj_d(int br,cvor root){
    cvor novi = malloc(sizeof(stablo)); 
    novi->br = br;
    novi->left = NULL;
    novi->right = NULL;

    root->right = novi;
}
void replace(cvor root,int *rez) {
    if(!root)return;
    *rez=*rez+root->br;
    replace(root->left,rez);
    replace(root->right,rez);

}

cvor preorder_replace(cvor root){
    if(!root)return NULL;
    int rez=0;
    replace(root,&rez);
    root->br=rez-root->br;

    preorder_replace(root->left);
    preorder_replace(root->right);

    return root;
}

void preorder(cvor root){
    if(!root)return;
    printf("%d\n",root->br);
    preorder(root->left);
    preorder(root->right);
}

void ispis_stabla(cvor root, int space) {
    if (root == NULL) {
        return;
    }

    space += 10;

    ispis_stabla(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->br);
    ispis_stabla(root->left, space);
}

void inorder_upis(cvor root, FILE *datoteka) {
    if (root == NULL) {
        return;  // Ako je čvor NULL, ne radimo ništa
    }

    // Prvo prolazimo lijevo podstablo
    inorder_upis(root->left, datoteka);

    // Zapisujemo trenutni čvor u datoteku
    fprintf(datoteka, "%d ", root->br);

    // Zatim prolazimo desno podstablo
    inorder_upis(root->right, datoteka);
}

void DeleteTree(cvor root){
    if(!root)return;

    DeleteTree(root->left);
    DeleteTree(root->right);
    free(root);
}
