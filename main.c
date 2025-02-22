#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX 200


typedef struct{
    int fideID;
    char jmeno[20];
    char prijeni[20];
    int elo;
    int maxelo;
    char nation[20];
    char titul[5];
    int rokNarozeni;
    bool smazano;
} Thraci;

int nacti(FILE *in, Thraci p[]){
    int i=0;
    while( i<MAX && fscanf(in,"%d %4s %19s %19s %d %d %19s %d",&p[i].fideID,p[i].titul , p[i].jmeno, p[i].prijeni, &p[i].elo, &p[i].maxelo, p[i].nation, &p[i].rokNarozeni)==8){
       p[i].smazano=false;
       i++;
    }
    return i;
}

int menu(){
    int volba;
    do{
        system("cls");
        printf("\t Seznam hracu\n");
        printf("1 - Vypsat\n");
        printf("2 - Vyhledat\n");
        printf("3 - advanced settings\n");
        printf("0 - Exit\n");
        scanf("%d",&volba);

    }while(volba<0 || volba>5);
    return volba;


}

int main(){
    FILE *in = fopen("hraci.txt","r");
    if(in == NULL){
        printf("Error - soubor nenalezen");
        return -3;
        }
    Thraci player[MAX];
    int n = nacti(in, player);
    int volba;
    do{
    volba = menu();
    switch
    {
    case 1:
        //vypsat();
        break;
    case 2:
        //vyhledat();
        break;
    case 3:
        //menu++();


    }
    }while(volba!=0);
    fclose(in);
    return 0;
}
