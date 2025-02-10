#include <stdlib.h>
#include <stdio.h>


typedef struct{
    char jmeno[20];
    char prijeni[20];
    int elo;
    int maxelo;
    int nation;
    int rok;
    int delete;
} Thraci;

int pocet(FILE *in){
    int n=0;
    Thraci test;
    //while(7==fscanf())
}


int main(){
    FILE *in = fopen("hraci.txt","r");
    int n = pocet(in);
    Thraci hraci[n];

    return 0;
}
