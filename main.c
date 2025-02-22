#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 200
#define ERR 48


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

int menu(int admin){
    system("color 07");
    char volba;
    do{
        system("cls");
        printf("\t Seznam hracu\n");
        printf("1 - Vypsat\n");
        printf("2 - Vyhledat\n");
        printf("3 - Zobraz info\n");
        if(admin==0){
        printf("4 - sudo su\n");
        }else{
        printf("Admin nastaveni:\n");
        printf("\t4 - nastaveni\n");
        printf("\t5 - Pridat\n");
        printf("\t6 - Upravit\n");
        printf("\t7 - Smazat\n");
        printf("\t8 - Davkove upravy\n");
        printf("9 - XXX\n");
        }
        printf("0 - Exit\n");
        scanf("%c",&volba);
        fflush(stdin);
       // printf("%d",volba);
      //  system("pause");
    if(admin==0 && volba>52){
        volba = ERR-1;
    }
    }while(volba<48 || volba>57);
    return volba;


}

int login(FILE *p)
{
    char password[20];
    char heslo[20];
    system("cls");
    if(fscanf(p,"%19s",password)==1){
        printf("Zadej heslo, nebo 0 k vraceni zpet\n");
        scanf("%19s",heslo);
        //printf("%s",heslo);
        if(strcmp(heslo,"0")==0){
            printf("exiting");
            system("timeout /t 2");
            return 0;
            }
        if(strcmp(heslo,password)==0){
            printf("Heslo uspesne zadano");
            return 1;
        }else{
            system("cls");
            system("color 04");
            printf("Spatne heslo\n");
            system("pause");
            return 0;
        }

    }
    system("color 04");
    printf("Error");
    system("pause");
    return 0;


}

int adminset(){
    system("color 07");
    char volba;
    do{
        system("cls");
        printf("\t BIOS\n");
        printf("1 - Zmena hesla\n");
        printf("2 - Odhlasit\n");
        printf("3 - Comming soon\n");
        printf("0 - Exit\n");
        scanf("%c",&volba);
        fflush(stdin);
       // printf("%d",volba);
      //  system("pause");
    }while(volba<48 || volba>51);
    return volba;

}

int changepass(char nove[]){
    char heslo[20];
    char kontrola[20];
    system("cls");
    printf("Zadej nove heslo: ");
    scanf("%19s",heslo);
    printf("\nZadej heslo znovu: ");
    scanf("%19s",kontrola);
    if(strcmp(kontrola,heslo)==0){
        strcpy(nove,heslo);
        system("color 0A");
        printf("heslo zmeneno\n");
        system("pause");
        return 1;
        }
        system("color 04");
        printf("hesla se neshoduji\n");
        system("pause");
        return 0;

}


int main(){
    FILE *in = fopen("hraci.txt","r");
    if(in == NULL){
        system("color 04");
        printf("Error 404: File hraci.txt not found :(");
        system("timeout /t 1");
        return -3;
        }
    //obligátní práce se soubory

    Thraci player[MAX];
    int n = nacti(in, player);


    int volba;
    int admin = 0;
    do{
    volba = menu(admin);
    printf("OK");
    system("pause");
    switch(volba)
{
    case 49:
        //vypsat();
        break;
    case 50:
        //vyhledat();
        break;
    case 51:
        //menu++();
        break;
    case 52:
        if(admin == 1){
            int vol;
            do{
            vol = adminset();
            system("cls");
            switch(vol){
                case 50:
                    admin = 0;
                    printf("Jsi odhlasen\n");
                    vol = ERR;
                    system("pause");
                    break;
                case 49:
                    {
                        FILE *password = fopen("heslo.txt","r");
                        if(password == NULL){
                            system("cls");
                            system("color 04");
                            printf("Error 404: File heslo.txt not found :(\n");
                            system("pause");
                            break;
                        }
                        if(login(password)){
                            char noveHeslo[20];
                            fclose(password);
                            if(changepass(noveHeslo)){

                            password = fopen("heslo.txt","w");
                            if(password == NULL){
                                system("cls");
                                system("color 04");
                                printf("Error 404: File heslo.txt not found :(\n");
                                system("pause");
                                break;
                            }
                            fprintf(password,"%s",noveHeslo);}
                        }
                        fclose(password);
                    }
                    break;
            }
            }while(vol!=ERR);
        } else {
            FILE *password = fopen("heslo.txt","r");
            if(password == NULL){
                system("cls");
                system("color 04");
                printf("Error 404: File heslo.txt not found :(\n");
                system("pause");
                break;
            }
            admin = login(password);
            fclose(password);
        }
        break;
}

    }while(volba!=48);
    fclose(in);
    return 0;
}
