#include <stdio.h>
#include <stdlib.h>
struct _Tree;
typedef struct _Tree *Node;

typedef struct _Tree{
    int data;
    Node left,right;
}Tree;

struct _Red;
typedef struct _Red *pos;

typedef struct _Red{
    Node tree_el;
    pos next;
}Red;


Node insert(int x,Node root);
Node search(int x,Node root);
Node deleteElement(Node root,int x);
Node findMin(Node root);
void UnosURed(pos head,Node root);
Node VanIzReda(pos head);
void DeleteTree(Node root);
void PrintPreorder(Node root);
void PrintInorder(Node root);
void PrintPostorder(Node root);
void PrintLevelOrder(pos head,Node root);
void PrintStablo(Node root,pos head);
void PrintRed(pos p);
pos FindLast(pos head);
pos Prethodni(pos head, pos ref);

int main(){
    int pronadi;
    Node root=NULL;
    Node search_rez=NULL;
    pos head=(pos)malloc(sizeof(Red));
    if(!head)return -1;
    head->next=NULL;

    root=insert(29,root);
    root=insert(20,root);
    root=insert(25,root);
    root=insert(23,root);
    root=insert(30,root);
    root=insert(31,root);

    PrintStablo(root,head);

    printf("\nUnesi element koji zelis pronaci i izbrisati\n");
    scanf("%d",&pronadi);
    search_rez=search(pronadi,root);
    if(search_rez){
        printf("\nObrisani: %d\n",search_rez->data);
        root=deleteElement(root,search_rez->data);
        printf("\nStablo nakon brisanja\n");
        PrintStablo(root,head);
    }

    DeleteTree(root);
    return 0;
}

Node insert(int x,Node root){
    if(!root){ //na početku je stablo prazno
        root=(Node)malloc(sizeof(Tree));
        if(!root)return NULL;
        root->data=x;
        root->left=NULL;
        root->right=NULL;

    }

    else if(x<root->data){
        root->left=insert(x,root->left);
    }
    else if(x>root->data){
        root->right=insert(x,root->right);
    }

    return root;

}
Node search(int x,Node root){
    if(!root){
        return NULL;
    }
    else if(x<root->data){
        return search(x,root->left);
    }
    else if(x>root->data){
        return search(x,root->right);
    }

    return root;
}

void PrintPreorder(Node root){
    if(!root)return;

    printf("%d\n",root->data);
    PrintPreorder(root->left);
    PrintPreorder(root->right);
}

Node deleteElement(Node root,int x){
    if(!root)return NULL;

    else if(x<root->data){
        root->left=deleteElement(root->left,x);
    }
    else if(x>root->data){
        root->right=deleteElement(root->right,x);
    }
    //ako pronađen element ima dvoje djece
    else if(root->left && root->right){
        Node minRight=findMin(root->right);
        root->data=minRight->data;
        root->right=deleteElement(root->right,minRight->data);
    }
    //0 ili 1 dijete
    else{
        Node temp=root;
        if(!root->left){ //ima samo desno dijete
            root=root->right;
        }
        else if(!root->right){
            root=root->left;
        }
        else{
            root=NULL;
        }

        free(temp);
    }

    return root;
}

Node findMin(Node root){
    if(!root->left)return root;
    return findMin(root->left);
}

void DeleteTree(Node root){
    if(!root)return;

    DeleteTree(root->left);
    DeleteTree(root->right);
    free(root);
}

void PrintLevelOrder(pos head,Node root){
    if(!root)return;
    Node temp=root;
    UnosURed(head,temp);

    while(head->next){
        temp=VanIzReda(head);
        printf("Data: %d\n",temp->data);
        if(temp->left){
            UnosURed(head,temp->left);
        }
        if(temp->right){
            UnosURed(head,temp->right);
        // printf("\ntrenutni red\n");
        // PrintRed(head->next);
    }

}

}

void UnosURed(pos head,Node root){

    pos novi=(pos)malloc(sizeof(Red));
    if(!novi)return;
    novi->tree_el=root;
    novi->next=head->next;
    head->next=novi;
}

Node VanIzReda(pos head){
    pos last=FindLast(head);
    Node van=last->tree_el;
    pos preth=Prethodni(head,last);
    preth->next=NULL;
    free(last);
    return van;
}

void PrintRed(pos p){
    if(!p)return;
    while(p){
        printf("%d\n",p->tree_el->data);
        p=p->next;
    }
}

pos FindLast(pos head) {
    if (!head) return NULL; 
    pos temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    return temp;
}

pos Prethodni(pos head, pos ref) {
    pos temp = head;
    while (temp->next && temp->next != ref) {
        temp = temp->next;
    }
    if (!temp->next) {
        return NULL;  // If we reached the end of the list without finding 'ref'
    }
    return temp;  // Return the node before 'ref'
}

void PrintInorder(Node root){
    if(!root)return;
    PrintInorder(root->left);
    printf("%d\n",root->data);
    PrintInorder(root->right);
}

void PrintPostorder(Node root){
     if(!root)return;
    PrintPostorder(root->left);
    PrintPostorder(root->right);   
    printf("%d\n",root->data);
}

void PrintStablo(Node root,pos head){
    printf("\nPreorder\n");
    PrintPreorder(root);
    printf("\nInorder\n");
    PrintInorder(root);
    printf("\nPostorder\n");
    PrintPostorder(root);
    printf("\nPrint level order\n");
    PrintLevelOrder(head,root);
}






