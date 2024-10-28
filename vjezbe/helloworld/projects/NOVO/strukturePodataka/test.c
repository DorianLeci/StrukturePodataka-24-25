#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

struct _lista;
typedef struct _lista *position;

typedef struct _lista{
int broj;
position next;

}lista;

void BrisiSveOdPocetka (position p);
int Umetni(position p);
int UnesiPodatke(position p);
int Ispis(position p);
int UmetanjeNaKrajListe(position p);

void SortList(position head);
position RevList(position head);//na ovaj način nismo zamijenili lokacije nodova, nego samo vrijednosti u strukturi
position PronadiPrethodni2(position p, int broj);

int Umetanje_I_Sortiranje(position p);
position PronadiMjesto(position p,int broj);
int Brojac(position p,int broj);

position removeDupl(position pocetni);
position PronadiZadnji(position p);

position PronadiPrethodni(position p,int trazeni,int brojac_istih);
void Zamjena(position,position,position,position);
void Zamjena_Drugacije(position,position,position,position);
position OkreniListuNapraviNovu(position p,int broj);

position Prethodni_Zadnji(position head);
position PronadiPrethodni_Od_Predzadnjeg(position head); 
position PrviManji(position head,int trazeni,int broj_jednakih);
int BrJedankih(position head,int trazeni);

position InsertionSort(position p);
position SortedInsert(position createNode,position sorted);
//funkcija za brisanje duplikata iz ne sortirane liste

position InsertionSortSilazno(position p);
position SortedInsertSilazno(position createNode,position sorted);

int main(){

  int odabir;
    position head=NULL;
    position pocetni=NULL;
head=(position) malloc (sizeof(lista));
head->next=NULL;
position head_sorted=NULL;
head_sorted=(position) malloc (sizeof(lista));
head_sorted->next=NULL;

position head2=NULL;
head2=(position) malloc (sizeof(lista));
head2->next=NULL;

  printf("\nUnesi način unosa\n");
  scanf("%d",&odabir);
  if(odabir==0){
    printf("\nUmetanje na početak\n\n");
  for(int i=0;i<5;i++){
    Umetni(head);
  }
  }

  else if(odabir==1){
    printf("\nUmetanje na kraj\n\n");
    for(int i=0;i<5;i++){
      UmetanjeNaKrajListe(head);
    }
  }

    else if(odabir==2){
    printf("\nUmetanje i sortiranje odjednom\n\n");
    for(int i=0;i<6;i++){
      if(i==0){
        printf("\nUnesi prvi broj u listu\n");
        head->next=(position)malloc(sizeof(lista));

        if(head->next==NULL){
          printf("\nMalociranje nije uspjelo\n\n");
          return -1;
        }

        scanf("%d",&(head->next->broj));
        head->next->next=NULL;
      }
      Umetanje_I_Sortiranje(head);
    }
  }

  


printf("\nIspis liste(prije brisanja)\n");
Ispis(head->next);
printf("\n\n");

int sortiranje_odabir;
printf("\nOdaberi 0 za uzlazno,a 1 za silazno sortiranje\n");
scanf("%d",&sortiranje_odabir);
if(sortiranje_odabir==0){
position sorted=InsertionSort(head->next);
head_sorted->next=sorted;
}
else if(sortiranje_odabir==1){
  position sorted=InsertionSortSilazno(head->next);
  head_sorted->next=sorted;
}

printf("\n\n\\\\\\\\\\\\\\\\\\\\\\\n");
printf("\nIspis liste nakon sortiranja\n");
Ispis(head_sorted->next);
printf("\\\\\\\\\\\\\\\\\\\n\n");

head=RevList(head_sorted);
printf("\nIspis liste nakon obrtanja\n");
Ispis(head);
printf("\n\n");

printf("\nOkreni listu ponovno i napravi novu\n");
int pozicija;
printf("\nUnesi poziciju do koje zelis okrenuti listu\n");
scanf("%d",&pozicija);
position novi_head=OkreniListuNapraviNovu(head,pozicija);

printf("\nDruga lista\n");
Ispis(novi_head);

printf("\nIspis nakon uklanjanja duplikata\n");
pocetni=removeDupl(head);
Ispis(pocetni);
printf("\n\n\n");

BrisiSveOdPocetka(head);

Ispis(head);

printf("%p\n",head);

return 0;

}

void BrisiSveOdPocetka(position p){
    position temp;
while(p->next!=NULL)
{
temp=p->next;
p->next=p->next->next;
free(temp);

}
printf("%p\n",p);
printf("Temp: %p\n",temp);
printf("%p\n",p->next);
}

int Umetni(position p){
 position q=NULL;
q=(position) malloc (sizeof (lista)); //alociramo prostor za novi element
if (q==NULL)
return -1;
UnesiPodatke(q); //unosi podatke u novi element
q->next=p->next;    
p->next=q; //neka head element pokazuje na taj dodani element
return 0;
}

int UnesiPodatke(position q){

  printf("\nUnesi maticni broj\n");
  scanf("%d",&(q->broj));

  return 0;

}

int Ispis(position p){
if(p==NULL)
{
printf("Nema elemenata, lista je prazna!\n");
return -1;
}
else
{
while(p!=NULL)
{
printf("%d \n", p->broj);
p=p->next;
}
}
return 0;    
}

position removeDupl(position pocetni){ //u ovu funkciju šaljemo prvi element liste,a ne head
  position curr1=pocetni;
  position curr2=NULL;
  position temp=NULL;

  while(curr1!=NULL){
    curr2=curr1;
    while(curr2->next!=NULL){
          if(curr2->next->broj==curr1->broj){
        temp=curr2->next;
        curr2->next=curr2->next->next;
        free(temp);
            }
            else{
              curr2=curr2->next;
            }
    }


    curr1=curr1->next;
  }
  return pocetni;
}

int UmetanjeNaKrajListe(position p){
  position last=NULL;
  position novi=NULL;
  last=PronadiZadnji(p); 
  //sada trebamo nakon svakog unosa provjeriti adresu zadnjeg elementa

  novi=(position)malloc(sizeof(lista));

  UnesiPodatke(novi);

  last->next=novi;
  novi->next=NULL;


  return 0;
}

position PronadiZadnji(position p){
  while(p->next!=NULL){
    p=p->next;
  }

  return p;
}

int Umetanje_I_Sortiranje(position p){
  position novi=NULL;
  int temp_broj;
  position unos=NULL;

  printf("\nUnesi broj(taj broj koji su unio moramo prvo provjeriti\n"); //ovo je drugi broj u listi
  scanf("%d",&temp_broj);

  novi=PronadiMjesto(p,temp_broj);

  if(novi!=NULL){
    unos=(position)malloc(sizeof(lista));
    unos->broj=temp_broj;
    novi->next=unos;
    unos->next=NULL;

    printf("\nTrenutno stanje\n");
    Ispis(p->next);

  }



  return 0;

}

position PronadiMjesto(position p,int broj){
  position unos=NULL;
  int flag;
  position temp=p;
  position prethodni=NULL;
  position temp_manji;

  int brojac_istih;


  while(p->next!=NULL){
    flag=0;
    if(p->next->broj==broj){
      flag=1;
    }
    p=p->next;
  }
  if(flag==1){
    printf("\nSvi brojevi su jednaki\n");
    unos=(position)malloc(sizeof(lista));
    unos->broj=broj;
    p->next=unos;
    unos->next=NULL;
    printf("\nTrenutno stanje\n");
    Ispis(temp->next);
    return NULL;
    
  }
  //do ovog stadija funkcije smo prošli sve testove
  else if(flag==0){
    unos=(position)malloc(sizeof(lista));
    unos->broj=broj;
    p->next=unos;
    unos->next=NULL;
  }
  //resetiranje pointera
  p=temp;

  while(p->next->next!=NULL){
    p=p->next;
    temp_manji=p;
  }
  printf("\nTemp na manji: %d\n",temp_manji->broj);
  if(temp_manji->broj>unos->broj){
    brojac_istih=Brojac(temp,temp_manji->broj);
    printf("\nBroj istih jest: %d\n",brojac_istih);

    for(int i=0;i<brojac_istih;i++){
      if(i==0){
        prethodni=PronadiPrethodni(temp,temp_manji->broj,brojac_istih-i);
        printf("\nPrethodni: %d\n",prethodni->broj);
        Zamjena(prethodni,unos,temp_manji,temp);
      }
      else{
        prethodni=PronadiPrethodni(temp,temp_manji->broj,brojac_istih-i);
        printf("\nPrethodni: %d\n",prethodni->broj);
        Zamjena_Drugacije(prethodni,unos,temp_manji,temp);        
      }
      printf("\nTrenutno\n");
      Ispis(temp->next);

    }

    return NULL;
  }
  //////////////////
   //resetiranje pointera
  p=temp;
  while((p->next!=NULL)&&(broj>p->next->broj)){
    p=p->next;
  }



  printf("\nBroj koji se nalazi na vraćenoj adresi jest: %d\n",p->broj);
  return p;
}


position PronadiPrethodni(position p,int trazeni,int brojac_istih){
  position prev=NULL;
  position curr=NULL;
  int count=0;

  prev=p;
  curr=p->next;

  printf("Curr: %d\n",curr->broj);

  while(curr!=NULL){
    if(curr->broj==trazeni){
      count++;
      printf("\nCount: %d\n",count);
    }
    if(count==brojac_istih){
      return prev;
    }

    prev=curr;
    curr=curr->next;

  }
  if(curr==NULL){
    printf("\nNije pronađen el\n"); //ako nije pronađen niti jedan element
   return NULL;
  }

  return prev;
}

int Brojac(position p,int trazeni){
  int count=0;

  while(p->next!=NULL){
    p=p->next;
    if(p->broj==trazeni){
      count++;
    }

  }

  return count;
}

void Zamjena(position prethodni,position unos,position temp_manji,position temp){


      if(prethodni!=NULL){
      printf("\nPrethodni: %d\n",prethodni->broj);
      prethodni->next=unos;
      unos->next=temp_manji;
      temp_manji->next=NULL;

    printf("\nTrenutno stanje\n");
    Ispis(temp->next);
    }

    return;
}
void Zamjena_Drugacije(position prethodni,position unos,position temp_manji,position temp){
  position zadnji_el=temp_manji;
  position prethodni_next_temp;
  printf("\nNa što pokazuje zadnji el: %p\n",zadnji_el->next);

  if(prethodni!=NULL){
    printf("\nPrethodni: %d\n",prethodni->broj);
    prethodni_next_temp=prethodni->next;
    printf("\nPrethodni next temp: %d\n",prethodni_next_temp->broj);

    prethodni->next=prethodni->next->next;


    printf("\nPrethodni na next: %d\n",prethodni->next->broj);
    printf("\nPrethodni na next na next: %d\n",prethodni->next->next->broj);
    printf("\ntrenutno(Zamejena drugacije)\n");
    temp_manji->next=prethodni_next_temp;
    prethodni_next_temp->next=NULL;
    Ispis(temp->next);
  }

  return;
}

void SortList(position head){
 position curr=NULL;
 position prev=head->next;
 position temp;

 position pokazivac_temp=NULL;
 position prethodni=NULL;

 position zadnji=NULL;
 position prethodni_od_zadnjeg=NULL;
 position prethodni_specijalni_slucaj=NULL;


 while(prev->next!=NULL){

  curr=prev->next;
  while(curr!=NULL){
    printf("\nCurrent u vanjskoj petlji: %d\n",curr->broj);
    printf("Prev u vanjskoj vanjskoj petlji: %d\n",prev->broj);
    if(curr->broj<prev->broj){
      printf("\nNađena dva broja: %d %d\n",curr->broj,prev->broj);
      pokazivac_temp=curr->next;
      prethodni=PronadiPrethodni2(head,prev->broj);
      if(prethodni!=NULL){
        printf("\nPrethodni: %d\n",prethodni->broj);
      }

        temp=prev;
        prev=curr;
        curr=temp;

        zadnji=PronadiZadnji(head);
        printf("Zadnji: %d\n",zadnji->broj);

        prethodni_od_zadnjeg=Prethodni_Zadnji(head);
        printf("\nPrethodni od zadnjeg: %d\n",prethodni_od_zadnjeg->broj);

        if(prev->broj==prethodni_od_zadnjeg->broj){
          printf("\nNašao\n");
          prethodni_specijalni_slucaj=PronadiPrethodni_Od_Predzadnjeg(head);
          printf("\nPrethodni specijalan slučaj: %d\n",prethodni_specijalni_slucaj->broj);

          prev->next=curr;
          prethodni->next=prev;
          curr->next=prethodni_specijalni_slucaj;
          prethodni_specijalni_slucaj->next=zadnji;

        }
      else if(prev->next==NULL){
        int brojac=BrJedankih(head,(zadnji->broj)-1);
        printf("\nZadnji je jednako current\n");
        position prvi_manji=PrviManji(head,zadnji->broj,brojac);
        printf("\nPrvi manji: %d\n",prvi_manji->broj);

        prethodni_od_zadnjeg=Prethodni_Zadnji(head);

        prethodni_specijalni_slucaj=PronadiPrethodni_Od_Predzadnjeg(head);
        printf("\nPrethodni od predzadnjeg: %d\n",prethodni_specijalni_slucaj->broj);

        zadnji->next=prethodni_specijalni_slucaj;

        prvi_manji->next=zadnji;

        zadnji->next->next=prethodni_od_zadnjeg;
        prethodni_od_zadnjeg->next=NULL;
      }

      else{
        if(prethodni!=NULL){
          prethodni->next=prev;
          prev->next=curr;
          curr->next=pokazivac_temp;
        }
        else{
          pokazivac_temp=curr->next;
          head->next=prev;
          prev->next=curr;
          curr->next=pokazivac_temp;
        }

      }


        printf("\nTrenutno stanje\n");
        Ispis(head->next);
        printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\n\n\n");







    }
  curr=curr->next;
  }


    prev=prev->next;
 }

}

position RevList(position p){
  position prev=NULL;
  position curr=p->next;
  position next;

  while(curr!=NULL){
    next=curr->next;
    curr->next=prev;

    prev=curr;
    curr=next;

  
  }
  return prev;
}

position OkreniListuNapraviNovu(position p,int pozicija){
  position prev=NULL;
  position curr=p; //p mora biti head->next
  position next;

  position novi_head=NULL;
  position novi_head2=NULL;
  
  for(int i=0;i<pozicija;i++){
    next=curr->next;
    curr->next=prev;
    
    prev=curr;
    curr=next;

  }


  novi_head=(position)malloc(sizeof(lista)); //ovu drugu listu moramo ponovno obrnuti
  novi_head2=(position)malloc(sizeof(lista));
    if(novi_head2==NULL){
    printf("\nNije moguće malociranje\n");
    return NULL;
  }
  if(novi_head==NULL){
    printf("\nNije moguće malociranje\n");
    return NULL;
  }
  novi_head->next=curr;
  novi_head=RevList(novi_head); //pomoću ovog ponovno obrćemo i drugu listu,jer u ovom programu nismo do kraja obrnuli listu nego smo samo radzvojili nodove
  novi_head2->next=prev;

  printf("\nPrva lista\n");
  Ispis(novi_head2->next);

  return novi_head;

}

position PronadiPrethodni2(position p, int broj){
  position curr=NULL;
  position prev=NULL;
  prev=p;
  curr=p->next;
  if(curr->broj==broj){
    return NULL;
  }
  while((curr!=NULL)&&(curr->broj!=broj)){
    prev=curr;
    curr=curr->next;
  }

  if(curr==NULL){
    printf("\nNije pronađeno\n");
    return NULL;
  }

  return prev;
}

position Prethodni_Zadnji(position head){
  position prethodni=NULL;
  head=head->next;
  while(head->next!=NULL){
    prethodni=head;
    head=head->next;
  }

  return prethodni;
}

position PronadiPrethodni_Od_Predzadnjeg(position head){
  head=head->next;
  position temp;

  while(head->next->next!=NULL){
    temp=head;
    head=head->next;
  }

  return temp;
}

position PrviManji(position head,int trazeni,int broj_jednakih){
  position p=head->next;
  position prev=NULL;
  position temp=p;

  int broj=0;

  while(p->next!=NULL){
    if(p->broj==trazeni){
      return p;
    }
    p=p->next;
  }
  p=temp;

  while(broj_jednakih>(broj-1)){
    if(p->broj<trazeni){
      broj++;
    }
    prev=p;
    p=p->next;
  }

  return prev;
}

int BrJedankih(position head,int trazeni){
  position p=head->next;
  int brojac=0;

  while(p!=NULL){
    if(p->broj==trazeni){
      brojac++;
    }
    p=p->next;
  }
  return brojac;
}


position InsertionSort(position p){
  position sorted=NULL;
  position curr=p;

  while(curr!=NULL){
    position next=curr->next;
    printf("Current: %d\n",curr->broj);
    sorted=SortedInsert(curr,sorted);
    printf("\nSorted: %d\n",sorted->broj);

    curr=next; //na ovaj način smo svaki put sačuvali ono na što je curr pokazivao
  }
  return sorted;
}


position SortedInsert(position createNode,position sorted){
  if(sorted==NULL||sorted->broj>=createNode->broj){
    createNode->next=sorted;
    sorted=createNode;
  }
  //mi u ovoj funkciji uzlazno sortiramo listu
  else{
    position curr=sorted;
    while(curr->next!=NULL && curr->next->broj<createNode->broj){
      curr=curr->next;
    }
    createNode->next=curr->next;

    curr->next=createNode;
  }
      printf("Create node na next: %p\n",sorted->next);   
  printf("Sorted: %d\n",sorted->broj);
  printf("\\\\\\\\n\n");
  return sorted;
}

position InsertionSortSilazno(position p){
  position vracena_lista=NULL;
  position curr=p;
  position next;

  while(curr!=NULL){
    next=curr->next;
    vracena_lista=SortedInsertSilazno(curr,vracena_lista);
    printf("\nCurrent: %d\n",curr->broj);
    printf("\nVraćena lista silazno: %d\n",vracena_lista->broj);

    curr=next;
  }

  return vracena_lista;
}
position SortedInsertSilazno(position curr,position vracena_lista){
   if((vracena_lista==NULL)||(curr->broj>=vracena_lista->broj)){
    printf("\nDa\n");
    curr->next=vracena_lista;
    vracena_lista=curr;
   }
   else{
    //da sačuvamo vracena lista
    position temp=vracena_lista;
    while((temp->next!=NULL)&&(temp->next->broj>curr->broj)){
      temp=temp->next;
    }
    curr->next=temp->next;

    temp->next=curr;
   }
   return vracena_lista;
}




