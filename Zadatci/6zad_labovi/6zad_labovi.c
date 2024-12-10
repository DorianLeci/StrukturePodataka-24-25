
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 255
#define ERROR_OPENING_FILE -1

struct _article;
typedef struct _article* ArticlePosition;

typedef struct _article {
	char name[MAX_LEN];
	int quant;
	double price;
	ArticlePosition next_article;
}article;

struct _racun;
typedef struct _racun* RacunPosition;

typedef struct _racun {
	int dan,mj,god;

	RacunPosition next_racun;
	ArticlePosition head_article;

}racun;



int ucitaj_racuni(RacunPosition head, char* filename);
int otvori_zasebni_racun(RacunPosition head, char* filename);
void Ispis(RacunPosition p);
int SortiraniUnos(RacunPosition head_glavni,RacunPosition uneseni);
void UcitajDatum(RacunPosition p,char *filename);
void IspisSamoGlavneListe(RacunPosition p);
void UnosSortArtikl(RacunPosition racun,ArticlePosition novi_artikl);
void Pretrazi(RacunPosition uneseni,char*,char*);
void IzbrisiSve(RacunPosition head_glavni);


int main() {
	RacunPosition head_glavni = (RacunPosition)malloc(sizeof(racun));
	if (!head_glavni)return -1;

	head_glavni->next_racun = NULL; //next je u strukturi racun pokazivac na iduci racun

    ucitaj_racuni(head_glavni,"racuni.txt");

    printf("\nIspis na kraju\n");
    IspisSamoGlavneListe(head_glavni->next_racun);
    printf("\n_________\n");

    Pretrazi(head_glavni,"2-2-2023","15-10-2027");
    IzbrisiSve(head_glavni);
    Ispis(head_glavni->next_racun);
    free(head_glavni);

    return 0;
}
int ucitaj_racuni(RacunPosition head_glavni, char* filename) {
    int i,duljina_imena_racuna;
    RacunPosition novi;
    RacunPosition head_glavni_temp=head_glavni;
	char buffer[MAX_LEN];
	FILE* fp = fopen(filename, "r");
	if (!fp)return ERROR_OPENING_FILE;


	while(fgets(buffer,MAX_LEN,fp)) {
		 //s ovime čitamo ime računa, tj petlja se vrti dok god postoje računi
            novi=(RacunPosition)malloc(sizeof(racun));
            if(!novi)return -1;
            duljina_imena_racuna=strlen(buffer);
            buffer[duljina_imena_racuna-1]='\0';

            novi->head_article=(ArticlePosition)malloc(sizeof(article));
            if(!novi->head_article)return -1;
            novi->head_article->next_article=NULL;

            UcitajDatum(novi,buffer);


    
		otvori_zasebni_racun(novi, buffer);
        SortiraniUnos(head_glavni_temp,novi); //temp_novi=uneseni

        memset(buffer,0,sizeof(buffer)); //svaki put buffer resetiramo
	}

    fclose(fp);
 

    return 0;
}

int otvori_zasebni_racun(RacunPosition novi_el_racun,char* filename) {
	FILE* fp = fopen(filename, "r");
    if(!fp){
        printf("\nNemoguće otvoriti file\n");
        return ERROR_OPENING_FILE;
    }
    
	char buffer[MAX_LEN];
	char name_temp[MAX_LEN];
	int quant_temp;
	double price_temp;


	ArticlePosition novi_artikl;

    fgets(buffer,MAX_LEN,fp);
    memset(buffer,0,sizeof(buffer)); //preskačemo prvi red

	while(fgets(buffer,MAX_LEN,fp)) { //vrtimo petlju dok ne prođemo sve artikle
		novi_artikl= (ArticlePosition)malloc(sizeof(article));
		if (!novi_artikl)return -1;

		if(sscanf(buffer, "%s %d %lf", name_temp, &quant_temp, &price_temp)!=3){
            printf("\nNije dobro učitano\n");
            return -1;
        }
        else{
            strcpy(novi_artikl->name, name_temp);
            novi_artikl->price = price_temp;
            novi_artikl->quant = quant_temp;
            memset(buffer,0,sizeof(buffer));
        }

        UnosSortArtikl(novi_el_racun,novi_artikl);
	}

    fclose(fp);
}

void Ispis(RacunPosition p){
    ArticlePosition temp;
    if(!p){
        printf("\nVezana lista računa nema elemenata\n");
        return;
    }
    while(p){
        printf("\nDatum: %d %d %d\n",p->dan,p->mj,p->god);

        temp=p->head_article->next_article;
        if(!temp){
            printf("\nPrazna lista datuma\n");
        }
        while(temp){
            printf("\n%s %d %lf",temp->name,temp->quant,temp->price);
            temp=temp->next_article;
        }
        p=p->next_racun;
    }
}



void UcitajDatum(RacunPosition p,char *filename){
    FILE *fp=fopen(filename,"r");
    if(!fp)return;
    int dan_temp,mj_temp,god_temp;
    char buffer[MAX_LEN];
    fgets(buffer,MAX_LEN,fp); //prvi red u računu je uvijek datum koji ćemo formatirati pomoću sscanfa nakon što ga pokupimo iz datoteke
    sscanf(buffer,"%d-%d-%d",&dan_temp,&mj_temp,&god_temp);

    p->dan=dan_temp;
    p->mj=mj_temp;
    p->god=god_temp;

    fclose(fp);
}

void IspisSamoGlavneListe(RacunPosition p){
    if(!p){
        printf("\nGlavna lista nema elemenata\n");
        return;
    }
    while(p){
        printf("Datum: %d %d %d\n",p->dan,p->mj,p->god);
        p=p->next_racun;
    }
}


void UnosSortArtikl(RacunPosition racun,ArticlePosition novi_artikl){
    ArticlePosition prev=racun->head_article;
    ArticlePosition curr=racun->head_article->next_article;


    while(curr){
        if(strcmp(novi_artikl->name,curr->name)==0){
            //zbrojiti ćemo količinu artikla i ostaviti istu cijenu
            if(curr->price==novi_artikl->price){
                curr->quant+=novi_artikl->quant;
                free(novi_artikl);
            }
            else{
                ArticlePosition curr2=curr;
                ArticlePosition prev2=prev;
                while(curr2){
                    if(novi_artikl->price<curr2->price || strcmp(novi_artikl->name,curr2->name)!=0){
                        break;
                    }

                    prev2=curr2;
                    curr2=curr2->next_article;
                }
                novi_artikl->next_article=curr2;
                prev2->next_article=novi_artikl;

            }
		return;
        }

        if(strcmp(novi_artikl->name,curr->name)<0)break;

        prev=curr;
        curr=curr->next_article;
    }
    novi_artikl->next_article=curr;
    prev->next_article=novi_artikl;
}

int SortiraniUnos(RacunPosition head_glavni,RacunPosition uneseni){
    RacunPosition curr=head_glavni->next_racun; //prvi element liste
    RacunPosition prev=head_glavni; //prev počinje od heada
    //usporedba po godinama
    while(curr){
        if(uneseni->god<curr->god){ //tu breakamo te
            break;
        }
        if(uneseni->god==curr->god){
            if(uneseni->mj<curr->mj)break;
            if(uneseni->mj==curr->mj){
                if(uneseni->dan<curr->dan)break;
                if(uneseni->dan==curr->dan){
                    //isti datum
			break;
                }
            }
        }

        prev=curr;
        curr=curr->next_racun;
    }

    uneseni->next_racun=curr;
    prev->next_racun=uneseni;
}

void Pretrazi(RacunPosition head_glavni,char *datum1,char *datum2){
    RacunPosition temp=head_glavni->next_racun;
    ArticlePosition artikli;
    int god1,mj1,dan1,dan2,god2,mj2;
    sscanf(datum1,"%d-%d-%d",&dan1,&mj1,&god1);
    sscanf(datum2,"%d-%d-%d",&dan2,&mj2,&god2);
    int zbroj_troskova=0;

    printf("Raspon: %s %s\n",datum1,datum2);

    while(temp){
        if(temp->god>=god1 && temp->god<=god2){ //sada smo naišli na prvi zadovoljeni datum
            RacunPosition temp2=temp; 
            while(temp2 && temp2->god<=god2){   
                if(temp2->god==god1){
                    if(temp2->mj>=mj1 && temp2->mj<=12){
   
                        if(temp2->mj==mj1){
                            if(temp2->dan>=dan1){
                                artikli=temp2->head_article->next_article;
                            printf("Datum koji je zadovoljio uvjete: %d %d %d\n",temp2->dan,temp2->mj,temp2->god);
                                while(artikli){
                                    zbroj_troskova+=(artikli->price*artikli->quant);
                                    printf("Artikli: %s %d %lf\n",artikli->name,artikli->quant,artikli->price);
                                    artikli=artikli->next_article;
                                }
                                printf("\n\n\n_________________\n\n\n");
                            }
                        }
                        else if(temp2->mj>=mj1){
                            artikli=temp2->head_article->next_article;
                            printf("Datum koji je zadovoljio uvjete: %d %d %d\n",temp2->dan,temp2->mj,temp2->god);
                            while(artikli){
                                zbroj_troskova+=(artikli->price*artikli->quant);
                                printf("Artikli: %s %d %lf\n",artikli->name,artikli->quant,artikli->price);
                                artikli=artikli->next_article;
                            }
                                printf("\n\n\n_________________\n\n\n");
                        }
                    }
                }
                else if(temp2->god==god2){
                    if(temp2->mj>mj2){
                        printf("Sada breakamo: %d %d %d\n",temp2->dan,temp2->mj,temp2->god);
                        break;
                    }
                    else if(temp2->mj<mj2){
                            artikli=temp2->head_article->next_article;
                            printf("Datum koji je zadovoljio uvjete: %d %d %d\n",temp2->dan,temp2->mj,temp2->god);
                            while(artikli){
                                zbroj_troskova+=(artikli->price*artikli->quant);
                                printf("Artikli: %s %d %lf\n",artikli->name,artikli->quant,artikli->price);
                                artikli=artikli->next_article;
                            }   
                                printf("\n\n\n_________________\n\n\n"); 
                    }
                    else if(temp2->mj==mj2){

                        if(temp2->dan<=dan2){
                            artikli=temp2->head_article->next_article;
                            printf("Datum koji je zadovoljio uvjete: %d %d %d\n",temp2->dan,temp2->mj,temp2->god);
                            while(artikli){
                                zbroj_troskova+=(artikli->price*artikli->quant);
                                printf("Artikli: %s %d %lf\n",artikli->name,artikli->quant,artikli->price);
                                artikli=artikli->next_article;
                            }
                                printf("\n\n\n_________________\n\n\n");
                        }                     
                    }
                }


                else if(temp2->god<god2 && temp2->god>god1){
                            artikli=temp2->head_article->next_article;
                            printf("Datum koji je zadovoljio uvjete: %d %d %d\n",temp2->dan,temp2->mj,temp2->god);
                            while(artikli){
                                zbroj_troskova+=(artikli->price*artikli->quant);
                                printf("Artikli: %s %d %lf\n",artikli->name,artikli->quant,artikli->price);
                                artikli=artikli->next_article;
                            }   
                                printf("\n\n\n_________________\n\n\n"); 

                }

            temp2=temp2->next_racun;
            }
        break;
        }
        temp=temp->next_racun;
    }

    if(!temp){
        printf("\nNije pronađena donja granica datuma\n");
        return;
    }

    printf("\nUkupni troškovi u razdoblju %s %s su: %d eura\n",datum1,datum2,zbroj_troskova);
}

void IzbrisiSve(RacunPosition head_glavni){
    RacunPosition temp=head_glavni;
    RacunPosition brisi_racun;

    while(temp->next_racun){
        ArticlePosition temp2=temp->next_racun->head_article;
        ArticlePosition brisi;
        while(temp2){
            brisi=temp2;
            temp2=temp2->next_article;
            free(brisi);
        }

        brisi_racun=temp->next_racun;
        temp->next_racun=temp->next_racun->next_racun;
        free(brisi_racun);
    }
}


    
    

   

