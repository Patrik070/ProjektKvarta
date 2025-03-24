#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdint.h>
#include <inttypes.h>


#define MAX 200
#define ERR 48
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
#define BLACK "\e[4;30m"


typedef struct{//definice struktury
    int fideID;
    char jmeno[20];
    char prijmeni[20];
    int elo;
    int maxelo;
    char nation[5];
    char titul[5];
    int rokNarozeni;
    int smazano;
} Thraci;

int narozeni(int rok){//kontrola platnosti zadaneho narozeni pro while cyklus

if(rok<1500 || rok > 2025){
    return 1;
}
return 0;
}


void vypsat(Thraci p[], int n){//vypisovani na terminal
    system("cls");
    printf("\t\t\t\t\tTabulka hracu\n");
    char nazev[8][20]={"FIDE ID","Titul","Jmeno","Prijmeni","Elo","Max Elo","Narod","Narozeni"};
    printf(CYAN" %-7s %-5s %-19s %-21s %-9s %-7s %-6s %-6s\n"RESET,nazev[0],nazev[1],nazev[2],nazev[3],nazev[4],nazev[5],nazev[6],nazev[7]);
    for(int i=0;i<n;i++){
        if(p[i].smazano == 0){
            printf("%8d",p[i].fideID);
            if(strcmp(p[i].titul,"None")==0){
            printf("       ");
        }else
        {
            printf(" %-6s",p[i].titul);
        }

            printf("%-19s %-19s %6d %9d    %-4s %6d\n",p[i].jmeno, p[i].prijmeni, p[i].elo, p[i].maxelo, p[i].nation, p[i].rokNarozeni);

    }}
    system("pause");

}

int zapis(Thraci player[], int n){
   FILE *in = fopen("hraci.txt","w");
            if(in == NULL){
                printf(RED"Error 404: File hraci.txt not found :("RESET);
                system("timeout /t 1");
                return -3;
            }
            for(int i=0;i<n;i++){
                    if(player[i].smazano==0){
                        fprintf(in,"%d %s %s %s %d %d %s %d %d\n",player[i].fideID,player[i].titul, player[i].jmeno, player[i].prijmeni, player[i].elo, player[i].maxelo, player[i].nation, player[i].rokNarozeni, player[i].smazano);
                    }
            }
            fclose(in);

return 1;
}


void vypisJedna(Thraci player){
char nazev[8][20]={"FIDE ID","Titul","Jmeno","Prijmeni","Elo","Max Elo","Narod","Narozeni"};
system("cls");
        printf(CYAN"\t Profil hrace\n"RESET);
        printf("%-10s %d\n",nazev[0],player.fideID);
        printf("%-10s %-5s\n",nazev[1],player.titul);
        printf("%-10s %-20s\n",nazev[2],player.jmeno);
        printf("%-10s %-20s\n",nazev[3],player.prijmeni);
        printf("%-10s %d\n",nazev[4],player.elo);
        printf("%-10s %d\n",nazev[5],player.maxelo);
        printf("%-10s %-5s\n",nazev[6],player.nation);
        printf("%-10s %d\n",nazev[7],player.rokNarozeni);
        system("pause");

}
int nacti(FILE *in, Thraci p[]){
    int i=0;
    while( i<MAX && fscanf(in,"%d %4s %19s %19s %d %d %4s %d %d",&p[i].fideID,p[i].titul , p[i].jmeno, p[i].prijmeni, &p[i].elo, &p[i].maxelo, p[i].nation, &p[i].rokNarozeni, &p[i].smazano)==9){
       i++;
    }
    return i;
}

int menu(int admin){
    char volba;
    do{
        system("cls");
        printf("\e[1;92m""\t Hlavni menu\n"RESET);
        printf("1 - Vypsat\n");
        printf("2 - Vyhledat\n");
        printf("3 - Zobraz info\n");
        printf("4 - Serad podle ela\n");
        if(admin==0){
        printf("5 - sudo su\n");
        }else{
        printf(MAGENTA"Root nastaveni:\n"RESET);
        printf("\t5 - nastaveni\n");
        printf("\t6 - Pridat\n");
        printf("\t7 - Upravit\n");
        printf("\t8 - About me\n");
        printf("\t9 - Zapsat\n");
        }
        printf(RED "0 - Exit\n"RESET);
        fflush(stdin);
        volba = getch();
    if(admin==0 && volba>53){
        volba = ERR-1;
    }
    }while(volba<48 || volba>57);
    return volba;


}

int vyhledatID(int key, int n, Thraci h[]){
int i =0;
while(i<n && h[i].fideID!=key){
    i++;
}
if(i<n)
    return i;
return -1;

}

bool validace(char ch[], int max){//
	int calc = 0;
	for(int i = 0;ch[i]!='\0';i++){
        	if(!(((ch[i]>='a')&&(ch[i]<='z')) || ((ch[i]>='A')&&(ch[i]<='Z')))){
            	printf(RED"\nPouze pismena!\n"RESET);
            	system("pause");
            	return 1;
        	}
    	calc++;
	}
if(calc>=max){
	printf(RED"\nPrilis dlouhe!\n"RESET);
	system("pause");
	return 1;}

if(calc<2){
	printf(RED"\nPrilis kratke!\n"RESET);
    system("pause");
	return 1;
}

return 0;
}


int vyhledat(Thraci h[], int n, int druh)
{
    if(n==1){
            printf("Mas jednoho hrace, ti to ulehcim :)\n");
    system("pause");
        return 0;
    }
    char volba;
    int x;
                int count =n;
                int countCheck=count;
                do{
                    do{
                        system("cls");
                        printf("Zbyva %d hracu\n",count);
                        if(druh ==0){
                            printf("Podle jakych parametru chces vyhledat hrace:\n");
                        }else{
                            printf("Podle jakych parametru chces vyhledat hrace na upravu:\n");
                        }

                        printf("\t1 - Podle jmena\n");
                        printf("\t2 - Podle prijmeni\n");
                        printf("\t3 - Podle roku narozeni\n");
                        printf("\t4 - Podle FIDE ID\n");
                        printf("\t5 - Vypis hrace\n");
                        printf(RED"\t0 - Domu, do Prahy...\n"RESET);
                        fflush(stdin);
                        volba = getch();
                        }while(volba>53||volba<48);
                        count = 0;
                        switch(volba){
                        case 48:
                            {
                                return -1;
                                break;
                            }
                        case 53:
                            {
                                //vypsat(h,n);
                                count = countCheck;
                                break;
                            }
                        case 49:
                            {
                                char jmeno[20];
                                do{
                                    system("cls");
                                    printf("Zadej jmeno hrace:");
                                    scanf("%19s",jmeno);
                                    fflush(stdin);
                                }while(validace(jmeno,19));
                                strupr(jmeno);
                                char pomocna[20];
                                for(int i=0;i<n;i++){

                                        if(h[i].smazano ==0){
                                        strcpy(pomocna,h[i].jmeno);
                                    if(strcmp(strupr(pomocna),jmeno)!=0){
                                        h[i].smazano = 2;
                                    }else{
                                        count++;
                                        x=i;
                                    }}
                                }
                                break;
                            }
                        case 50:
                            {
                                char prijmeni[20];
                                do{
                                    system("cls");
                                    printf("Zadej prijmeni hrace:");
                                    scanf("%19s",prijmeni);
                                    fflush(stdin);
                                }while(validace(prijmeni,19));
                                strupr(prijmeni);
                                char pomocna[20];
                                for(int i=0;i<n;i++){
                                    if(h[i].smazano ==0){
                                        strcpy(pomocna,h[i].prijmeni);
                                    if(strcmp(strupr(pomocna),prijmeni)!=0){
                                        h[i].smazano = 2;
                                    }else{
                                        count++;
                                        x=i;
                                    }}
                                }
                                break;
                            }
                        case 51:
                            {
                                int rok;
                                do{
                                    system("cls");
                                    printf("Zadej rok narozeni hrace (2015-2025) nebo 0:\n");
                                    scanf("%d",&rok);
                                    if(rok==0){volba=53;break;}
                                    if(narozeni(rok)){
                                        printf(RED"mimo rozsah\n"RESET);
                                        system("pause");
                                    }
                                }while(narozeni(rok));
                                for(int i=0;i<n;i++){
                                    if(h[i].smazano ==0){
                                    if(rok!=h[i].rokNarozeni){
                                        h[i].smazano = 2;
                                    }else{
                                        count++;
                                        x=i;
                                    }}
                                }
                                break;
                            }
                        case 52:
            {
                int key;

                do{
                    system("cls");
                    printf("Zadej FIDE ID hrace, nebo 0\n");
                    scanf("%d",&key);
                    if(key ==0){volba = 53;break;}

                if(key<1000000||key>99999999){
                    printf(RED"Mimo rozsah\n"RESET);
                    system("pause");
                }
                }while(key<1000000||key>99999999);
                x = vyhledatID(key, n, h);
                if(x!=-1 && h[x].smazano==0){
                count = 1;

                }
                break;
            }

                        }
                if(count == 0 && volba!=53){
                    printf(RED"Nikdo nenalezen\n"RESET);
                    count = countCheck;
                    for(int i=0;i<n;i++){
                        if(h[i].smazano==2){
                    h[i].smazano = 0;}

                }
                count<n ? vypsat(h,n) : system("pause");
                }else if(count>1){
                    for(int i=0;i<n;i++){
                        if(h[i].smazano==2){
                    h[i].smazano = 1;}
                }
                    vypsat(h,n);
                    countCheck = count;
                }
                }while(count !=1);
                for(int i=0;i<n;i++){
                    h[i].smazano = 0;
                }
        return x;
            }





Thraci Zmenatitul(int moznost, Thraci h, char nazev[]){
        int volba;
        do{
        system("cls");
        if(moznost ==1){
        vypisJedna(h);
        printf("\t Uprava titulu hrace\n");
        }else{
        printf("\t Nastaveni titulu hrace\n");

        }
        printf("%s:\n",nazev);
        printf("\t0 - None\n");
        printf("\t1 - CM\n");
        printf("\t2 - FM\n");
        printf("\t3 - IM\n");
        printf("\t4 - GM\n");
        printf("\t5 - NM\n");
        printf("\t6 - WCM\n");
        printf("\t7 - WFM\n");
        printf("\t8 - WIM\n");
        printf("\t9 - WGM\n");
        printf("\t/ - WNM\n");
        fflush(stdin);
        volba=getch();
    switch(volba){
    case 48:
        strcpy(h.titul,"None");
        break;
    case 49:
        strcpy(h.titul,"CM");
        break;
    case 50:
        strcpy(h.titul,"FM");
        break;
    case 51:
        strcpy(h.titul,"IM");
        break;
    case 52:
        strcpy(h.titul,"GM");
        break;
    case 53:
        strcpy(h.titul,"NM");
        break;
    case 54:
        strcpy(h.titul,"WCM");
        break;
    case 55:
        strcpy(h.titul,"WFM");
        break;
    case 56:
        strcpy(h.titul,"WIM");
        break;
    case 57:
        strcpy(h.titul,"WGM");
        break;
    case 47:
        strcpy(h.titul,"WNM");
        break;
    default:
        printf(RED"mimo rozsah\n"RESET);
        system("pause");
        break;}
        }while(volba<47 || volba>57);
return h;
}


Thraci Zmenajmeno(int moznost, Thraci h, char nazev[]){
do{
        system("cls");
         if(moznost ==1){
        vypisJedna(h);
        printf("\t Uprava jmena hrace\n");
        }else{
        printf("\t Nastaveni jmena hrace\n");}
        printf("%-11s",nazev);
        fflush(stdin);
        scanf("%19s",h.jmeno);
        fflush(stdin);

    }while(validace(h.jmeno,19));
    strlwr(h.jmeno);
    h.jmeno[0]=toupper(h.jmeno[0]);
    return h;

}

Thraci Zmenaprijmeni(int moznost, Thraci h, char nazev[]){
do{
        system("cls");
         if(moznost ==1){
        vypisJedna(h);
        printf("\t Uprava prijmeni hrace\n");
        }else{
        printf("\t Nastaveni prijmeni hrace\n");}
        printf("%-11s",nazev);
        fflush(stdin);
        scanf("%19s",h.prijmeni);
        fflush(stdin);

    }while(validace(h.prijmeni,19));
    strlwr(h.prijmeni);
    h.prijmeni[0]=toupper(h.prijmeni[0]);
    return h;

}


Thraci Zmenaelo(int moznost, Thraci h, char nazev[]){
do{
        system("cls");
        if(moznost ==1){
        vypisJedna(h);
        printf("\t Uprava ela hrace\n");
        }else{
        printf("\t Nastaveni ela hrace\n");}
        printf("1000-3000\n");
        printf("%-11s",nazev);
        scanf("%d",&h.elo);
        if(h.elo<1000 || h.elo>3000){
            printf(RED"mimo rozsah\n"RESET);
            system("pause");
    }

    }while(h.elo<1000 || h.elo>3000);
    if(h.elo>h.maxelo)
        h.maxelo=h.elo;
    return h;

}



Thraci Zmenamaxelo(int moznost, Thraci h, char nazev[]){
        do{
        system("cls");
        if(moznost ==1){
        vypisJedna(h);
        printf("\t Uprava maximalniho ela hrace\n");
        }else{
        printf("\t Nastaveni maximalniho ela hrace\n");}
        printf("%d-3000\n",h.elo);
        printf("%-11s",nazev);
        scanf("%d",&h.maxelo);
        if(h.maxelo<h.elo || h.maxelo>3000){
            printf(RED"mimo rozsah\n"RESET);
            system("pause");
    }

    }while(h.maxelo<h.elo || h.maxelo>3000);
    return h;

}




Thraci Zmenanarodnosti(int moznost, Thraci h, char nazev[]){
do{
        system("cls");
        if(moznost ==1){
        vypisJedna(h);
        printf("\t Uprava narodnosti hrace\n");
        }else{
        printf("\t Nastaveni narodnosti hrace\n");}
        printf("%-11s",nazev);
        fflush(stdin);
        scanf("%4s",h.nation);
        fflush(stdin);

    }while(validace(h.nation,4));
    strupr(h.nation);
    return h;

}



Thraci Zmenaroknarozeni(int moznost, Thraci h, char nazev[]){
do{
        system("cls");
        if(moznost ==1){
        vypisJedna(h);
        printf("\t Uprava roku narozeni hrace\n");
        }else{
        printf("\t Nastaveni roku narozeni hrace\n");}
        printf("1500-2025\n");
        printf("%-11s",nazev);
        scanf("%d",&h.rokNarozeni);
        if(narozeni(h.rokNarozeni)){
            printf(RED"mimo rozsah\n"RESET);
            system("pause");
    }

    }while(narozeni(h.rokNarozeni));
    return h;

}

Thraci Zmenafide(int moznost, Thraci player, char nazev[], Thraci p[],int n){
do{
        system("cls");
        if(moznost ==1){
        vypisJedna(player);
        printf("\t Uprava FIDE ID hrace\n");
        }else{
        printf("\t Nastaveni FIDE ID hrace\n");}
        printf("1.000.000-99.999.999\n");
        printf("%-11s",nazev);
        //player.fideID=89745632;
        scanf("%d",&player.fideID);
        for(int i=0;i<n;i++){
            if(player.fideID==p[i].fideID){
            printf(RED"obsazeno\n"RESET);
            player.fideID=ERR;
            system("pause");
            }
        }
        if(player.fideID<1000000 || player.fideID>99999999){
            printf(RED"mimo rozsah\n"RESET);
            system("pause");
    }
    }while(player.fideID<1000000 || player.fideID>99999999);
    return player;

}



int upravitMenu(int n, Thraci h[]){
    char volba;
    int x = vyhledat(h,n,1);
    if(x==-1){
        return n;
    }
    char nazev[8][20]={"FIDE ID","Titul","Jmeno","Prijmeni","Elo","Max Elo","Narod","Narozeni"};
    system("cls");
    //vypisJedna(h[x]);
    do{
    do{
    system("cls");
    printf(GREEN"Co chces upravit:\n"RESET);
    printf("\t/ - FIDE ID\n");
    printf("\t1 - Titul\n");
    printf("\t2 - Jmeno\n");
    printf("\t3 - Prijmeni\n");
    printf("\t4 - Elo\n");
    printf("\t5 - Max elo\n");
    printf("\t6 - Narodnost\n");
    printf("\t7 - Rok narozeni\n");
    printf(RED"\t8 - Smazat\n\n"RESET);
    printf(MAGENTA"\t9 - Zrusit\n"RESET);
    printf(GREEN"\t0 - Ulozit...\n"RESET);
    fflush(stdin);
    volba = getch();
    }while(volba>57||volba<47);

    switch(volba)
    {
    case 48:{
        if(zapis(h,n)==-3){
            return -3;
        }
        return n;
        break;}
    case 56:{
        system("cls");
        printf(YELLOW"Jste si jisty [y/n]?"RESET);
        int potvrzeni;
        fflush(stdin);
        potvrzeni=getch();
        if(potvrzeni=='y'){
            h[x].smazano=1;
            if(zapis(h,n)==-3){
            return -3;
        }
            return n-1;
        }
        break;}
    case 57:{
        return n;
        break;}
    case 49:{
        h[x]=Zmenatitul(1,h[x],nazev[1]);
        break;}

    case 50:{
        h[x]=Zmenajmeno(1,h[x],nazev[2]);

    break;
    }
    case 51:{
        h[x]=Zmenaprijmeni(1,h[x],nazev[3]);

    break;
    }
    case 52:{
        h[x]=Zmenaelo(1,h[x],nazev[4]);

    break;
    }
     case 53:{
    h[x]=Zmenamaxelo(1,h[x],nazev[5]);

    break;
    }
     case 54:{
        h[x]=Zmenanarodnosti(1,h[x],nazev[6]);
    break;
    }

    case 55:{
        h[x]=Zmenaroknarozeni(1,h[x],nazev[7]);
    break;
    }
    case 47:
        h[x]=Zmenafide(1,h[x],nazev[0],h,n);

    }}while(volba!=0);
    if(zapis(h,n)==-3){
            return -3;
        }//pro jistotu
return n;
}



 uint64_t hash(char password[]) {
     uint64_t hash = 0;
    int len = strlen(password);

    for (int i = 0; i < len; i++) {
        hash ^= password[i];  // XOR each character
        hash = (hash << 5) | (hash >> 27);  // Rotate left by 5 bits
    }
    return hash;
}



void zapisheslo(char heslo[], int moznost){
int i=0;
        while (1) {
        char ch = getch();

        if (ch == 13) { //enter
            //heslo[i] = '\0';
            break;
        } else if (ch == 8) {  //backspace
            if (i > 0) {
                i--;
                printf("\b \b"); //zpet nahrad mezera zpet
                heslo[i]='\0';
            }
        } else if (ch == 27){
            for(int y=0; y<i;y++){
                printf("\b");
            }
            printf("%-19s\n",heslo);
            system("pause");
            system("cls");
            if(moznost==0)
                printf("Zadej heslo, nebo 0 k vraceni zpet:");
            if(moznost==1)
                printf("Zadej nove heslo o max. delce 19: ");
            if(moznost==2)
                printf("\nZadej heslo znovu: ");

            for(int y=0; y<i;y++){
                printf("*");
            }
        }
         else if(i<19){
            heslo[i++] = ch;
            heslo[i]='\0';
            printf("*");
        }
    }
}

int login(FILE *p)
{
     uint64_t password;
    char heslo[25];
    system("cls");
    if(fscanf(p,"%"SCNu64,&password)==1){
            do{
        system("cls");
        printf("Zadej heslo, nebo 0 k vraceni zpet:");
        zapisheslo(heslo,0);
        if(strcmp(heslo,"0")==0){
            return 0;
            }
            //printf("%" PRIu64,hash(heslo));
            //system("pause");
        if(hash(heslo)==password){
            return 1;
        }else{
            system("cls");
            printf(RED"Spatne heslo\n"RESET);
            system("pause");
            //return 0;
        }
    }while(1);
    }
    printf(RED"Error"RESET);
    system("pause");
    return 0;


}

int adminset(){
    //system("color 07");
    char volba;
    do{
        system("cls");
        printf(BLACK"\e[47m\tBIOS\n"RESET);
        printf("1 - Zmena hesla\n");
        printf(MAGENTA"2 - Odhlasit\n"RESET);
        printf("3 - Comming soon\n");
        printf(RED"0 - Exit\n"RESET);
        volba = getch();
        fflush(stdin);
    }while(volba<48 || volba>51);
    return volba;

}

int changepass(char nove[]){
    char heslo[25];
    char kontrola[25];
    system("cls");
    printf("Zadej nove heslo o max. delce 19: ");
    zapisheslo(heslo,1);
    fflush(stdin);
    system("cls");
    printf("Zadej heslo znovu: ");
    zapisheslo(kontrola,2);
    fflush(stdin);
    if(strcmp(kontrola,heslo)==0){
        system("cls");
        strcpy(nove,heslo);
        printf(GREEN"heslo zmeneno!\n"RESET);
        system("pause");
        return 1;
        }
        printf(RED"\nhesla se neshoduji!\n"RESET);
        system("pause");
        return 0;

}



Thraci pridati(){
Thraci player;
player.elo = 2000;
player.fideID = 500;
strcpy(player.jmeno,"Jan");
player.maxelo = 2500;
strcpy(player.nation,"Rus");
strcpy(player.prijmeni,"Novak");
player.rokNarozeni = 2004;
player.smazano = 0;
strcpy(player.titul,"WFM");

return player;
}

void pridavani(int x, char nazev[][20], Thraci player, Thraci p[],int n)
{
    system("cls");
        printf(GREEN"\t Pridani noveho hrace\n"RESET);
        if(x>0)
        printf("0 - %-10s %d\n",nazev[0],player.fideID);
        if(x>1)
        printf("1 - %-10s %-5s\n",nazev[1],player.titul);
        if(x>2)
        printf("2 - %-10s %-20s\n",nazev[2],player.jmeno);
        if(x>3)
        printf("3 - %-10s %-20s\n",nazev[3],player.prijmeni);
        if(x>4)
        printf("4 - %-10s %d\n",nazev[4],player.elo);
        if(x>5)
        printf("5 - %-10s %d\n",nazev[5],player.maxelo);
        if(x>6)
        printf("6 - %-10s %-5s\n",nazev[6],player.nation);
        if(x>7)
        printf("7 - %-10s %d\n",nazev[7],player.rokNarozeni);
        printf("Adekvatni cislo pro zmenu nebo press any key to continue\n");
        int volba = getch();
        if(volba>=x+48){
            volba=5;
        }
        switch(volba){
        case 48:
            player = Zmenafide(0,player,nazev[0],p,n);
            break;
        case 49:
            player = Zmenatitul(0,player,nazev[1]);
            break;
        case 50:
            player = Zmenajmeno(0,player,nazev[2]);
            break;
        case 51:
            player = Zmenaprijmeni(0,player,nazev[3]);
            break;
        case 52:
            player = Zmenaelo(0,player,nazev[4]);
            break;
        case 53:
            player = Zmenamaxelo(0,player,nazev[5]);
            break;
        case 54:
            player = Zmenanarodnosti(0,player,nazev[6]);
            break;
        case 55:
            player = Zmenaroknarozeni(0,player,nazev[7]);
            break;
        break;
        default:
            return;

        }
        pridavani(x,nazev,player,p,n);

}

Thraci pridat(Thraci p[],int n){
    Thraci player;
    char nazev[8][20]={"FIDE ID","Titul","Jmeno","Prijmeni","Elo","Max Elo","Narod","Narozeni"};

    player=Zmenafide(0,player,nazev[0],p,n);
    pridavani(1,nazev,player,p,n);
    player = Zmenatitul(0,player,nazev[1]);
    pridavani(2,nazev,player,p,n);
    player = Zmenajmeno(0,player,nazev[2]);
    pridavani(3,nazev,player,p,n);
    player = Zmenaprijmeni(0,player,nazev[3]);
    pridavani(4,nazev,player,p,n);
    player = Zmenaelo(0,player,nazev[4]);
    pridavani(5,nazev,player,p,n);
    player = Zmenamaxelo(0,player,nazev[5]);
    pridavani(6,nazev,player,p,n);
    player = Zmenanarodnosti(0,player,nazev[6]);
    pridavani(7,nazev,player,p,n);
    player = Zmenaroknarozeni(0,player,nazev[7]);

    player.smazano = 0;
    pridavani(8,nazev,player,p,n);

return player;
}

void seradES(Thraci h[],int n){
    Thraci pom;
    int d;
    for(int i=1;i<n;i++){
        pom = h[i];
        d=i;
        while(d>0 && h[d-1].elo<pom.elo){
            h[d]=h[d-1];
            d--;
        }
        h[d]=pom;
    }

}
void seradEV(Thraci h[],int n){
    Thraci pom;
    int d;
    for(int i=1;i<n;i++){
        pom = h[i];
        d=i;
        while(d>0 && h[d-1].elo>pom.elo){
            h[d]=h[d-1];
            d--;
        }
        h[d]=pom;
    }

}

void seradMS(Thraci h[],int n){
    Thraci pom;
    int d;
    for(int i=1;i<n;i++){
        pom = h[i];
        d=i;
        while(d>0 && h[d-1].maxelo<pom.maxelo){
            h[d]=h[d-1];
            d--;
        }
        h[d]=pom;
    }

}

void seradMV(Thraci h[],int n){
    Thraci pom;
    int d;
    for(int i=1;i<n;i++){
        pom = h[i];
        d=i;
        while(d>0 && h[d-1].maxelo>pom.maxelo){
            h[d]=h[d-1];
            d--;
        }
        h[d]=pom;
    }

}

void aboutUs(){
    system("cls");
    char informace[2][5][50] = {{"Autor:","Trida:","Zdroj:","Dokument:","Vyrobil:"},{"Patrik Nadvornik","4.G","https://github.com/Patrik070/projektheslo.git","dlkjf","Patrik Nadvornik 2025"}};
    printf(CYAN"\t\tAbout me\n"RESET);
    printf("%-10s%s\n",informace[0][0],informace[1][0]);
    printf("%-10s%s\n",informace[0][1],informace[1][1]);
    printf("%-10s%s\n",informace[0][2],informace[1][2]);
    printf("%-10s%s\n",informace[0][3],informace[1][3]);
    printf("%-10s%s\n",informace[0][4],informace[1][4]);




    system("pause");


}

void ISprogram(Thraci h[],int n){
    Thraci pom[MAX];
    for(int i=0;i<n;i++){
        pom[i]=h[i];
    }
    seradES(pom,n);
int soucet=0;
int maxPoz = 0;
char informace[5][50] = {"pocet hracu jest:","prumerne elo jest:","nejvyssi elo jest:","nejvyssi elo ma:","median ela jest:"};
    system("cls");
    printf("%-20s%d\n",informace[0],n);
    for(int i=0;i<n;i++){
        soucet+=h[i].elo;
        if(h[maxPoz].elo<h[i].elo)
            maxPoz=i;
    }
    printf("%-20s%f\n",informace[1],1.0*soucet/n);
    printf("%-20s%-4d\n",informace[2],h[maxPoz].elo);
    printf("%-20s%s %s\n",informace[3],h[maxPoz].jmeno,h[maxPoz].prijmeni);
    if(n%2==0){
        printf("%-20s%.2f\n",informace[4],(pom[n/2].elo+pom[n/2-1].elo)*1.0/2);
    }else{
        printf("%-20s%.2d\n",informace[4],pom[n/2].elo);
    }



    system("pause");

}

int main(){
    //printf("%"PRIu64,hash("heslo"));
    //system("pause");
    FILE *in = fopen("hraci.txt","r");
    if(in == NULL){
        printf(RED"Error 404: File hraci.txt not found :("RESET);
        system("timeout /t 1");
        return -3;
        }
    //oblig�tn� pr�ce se soubory

    Thraci player[MAX];
    int n = nacti(in, player);
    fclose(in);

    int volba;
    int admin = false;
    do{
    volba = menu(admin);
    if(n<1 && volba !=0){
            system("cls");
        printf(RED"nedostatek hracu, nektere funkce nemusi fungovat spravne!!!\n"RESET);
        if(admin==1){
            printf(RED"pridat hrace? [y/n]\n"RESET);
            int nedostatekHracu = getch();
            if(nedostatekHracu=='y')
                volba = 54;
        }else {
            printf(RED"Prihlate se prosim a zmente tuto nemilou skutecnost!\n"RESET);
        volba=53;
        system("pause");

        }
    }
   /* printf("OK");
    system("pause");*/
    int moznostSwitch;
    switch(volba)
{
    case 49:
        vypsat(player, n);
        break;
    case 50:
        moznostSwitch = vyhledat(player,n,0);
        if(moznostSwitch!=-1)
        vypisJedna(player[moznostSwitch]);
        break;
    case 51:
        ISprogram(player,n);
        break;
    case 52:
        do{
        system("cls");
        printf("Podle ceho seradit?\n\t1 - Elo sestupne\n\t2 - Elo vzestupne\n\t0 - neradit");
        moznostSwitch=getch();
        }while(moznostSwitch<48 || moznostSwitch>50);
        switch(moznostSwitch){
            case 49:
        seradMS(player,n);
        seradES(player,n);
        break;
        case 50:
        seradMV(player,n);
        seradEV(player,n);
        break;
        }
        break;

    case 53:
        if(admin == 1){
            int vol;
            do{
            vol = adminset();
            system("cls");
            switch(vol){
                case 50:
                    admin = 0;
                    printf(GREEN"Jsi odhlasen\n"RESET);
                    vol = ERR;
                    system("pause");
                    break;
                case 49:
                    {
                        FILE *password = fopen("heslo.txt","r");
                        if(password == NULL){
                            system("cls");
                            printf(RED"Error 404: File heslo.txt not found :(\n"RESET);
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
                                printf(RED"Error 404: File heslo.txt not found :(\n"RESET);
                                system("pause");
                                break;
                            }
                            fprintf(password,"%"PRIu64,hash(noveHeslo));}
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
                printf(RED"Error 404: File heslo.txt not found :(\n"RESET);
                system("pause");
                break;
            }
            system("cls");
            printf("We trust you have received the usual lecture from the local System\nAdministrator. It usually boils down to these three things:\n\n\t#1) Respect the privacy of others.\n\t#2) Think before you type.\n\t#3) With great power comes great responsibility\n");
            system("pause");
            admin = login(password);
            fclose(password);
        }
        break;
        case 54:
           player[n] = pridat(player,n);
           in = fopen("hraci.txt","a");
            if(in == NULL){
                printf(RED"Error 404: File hraci.txt not found :("RESET);
                system("timeout /t 1");
                return -3;
            }
            fprintf(in,"\n%d %s %s %s %d %d %s %d %d",player[n].fideID,player[n].titul, player[n].jmeno, player[n].prijmeni, player[n].elo, player[n].maxelo, player[n].nation, player[n].rokNarozeni, player[n].smazano);
            fclose(in);

           n++;
        break;

        case 55:
            {


            FILE *in = fopen("hraci.txt","r");
            if(in == NULL){
                printf(RED"Error 404: File hraci.txt not found :("RESET);
                system("timeout /t 1");
                return -3;
                }
            //oblig�tn� pr�ce se soubory

            if(upravitMenu(n, player)==-3){
                return -3;
            }
            n = nacti(in, player);
            fclose(in);
            break;}
        case 56:
            aboutUs();
            break;

        case 57:
            system("cls");
            printf(MAGENTA"Tato moznost propise neulozene zmeny v uprava! Chcete to provest? [y/n]\n"RESET);
            moznostSwitch=getch();
            if(moznostSwitch=='y'){
            if(zapis(player,n)==-3){
                return -3;}
                printf("provedeno\n");
                system("pause");}
        break;

}

    }while(volba!=48);
    return 0;
}
