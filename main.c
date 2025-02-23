#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 200
#define ERR 48


typedef struct{
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


int zapis(Thraci player[], int n){
   FILE *in = fopen("hraci.txt","w");
            if(in == NULL){
                system("color 04");
                printf("Error 404: File hraci.txt not found :(");
                system("timeout /t 1");
                return -3;
            }
            for(int i=0;i<n;i++){
                    if(player[i].smazano==0){
                        fprintf(in,"%d %s %s %s %d %d %s %d %d\n",player[i].fideID,player[i].titul, player[i].jmeno, player[i].prijmeni, player[i].elo, player[i].maxelo, player[i].nation, player[i].rokNarozeni, player[i].smazano);
                    }
            }
            fclose(in);

return 0;
}


void vypisJedna(Thraci player){
char nazev[8][20]={"FIDE ID","Titul","Jmeno","Prijmeni","Elo","Max Elo","Narod","Narozeni"};
system("cls");
        system("color 08");
        printf("\t Profil hrace\n");
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
    system("color 07");
    char volba;
    do{
        system("cls");
        printf("\t Hlavni menu\n");
        printf("1 - Vypsat\n");
        printf("2 - Vyhledat\n");
        printf("3 - xZobraz info\n");
        printf("4 - xSerad podle ela\n");
        if(admin==0){
        printf("5 - sudo su\n");
        }else{
        printf("Root nastaveni:\n");
        printf("\t5 - nastaveni\n");
        printf("\t6 - Pridat\n");
        printf("\t7 - Upravit\n");
        printf("\t8 - XXXX\n");
        printf("\t9 - Zapsat???\n");
        }
        printf("0 - Exit\n");
        scanf("%c",&volba);
        fflush(stdin);
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
                system("color 04");
            	printf("\nPouze pismena!\n");
            	system("pause");
            	return 1;
        	}
    	calc++;
	}
if(calc>=max){
    system("color 04");
	printf("\nPrilis dlouhe!\n");
	system("pause");
	return 1;}

if(calc<2){
    system("color 04");
	printf("\nPrilis kratke!\n");
    system("pause");
	return 1;
}

return 0;
}


int vyhledat(Thraci h[], int n, int druh)
{
    char volba;
    int x;
    do{
    system("cls");
    system("color 07");
    if(druh ==0){
        printf("Jak chces vyhledat hrace:\n");
    }else{
        printf("Jak chces vyhledat hrace na upravu:\n");
    }
    printf("\t1 - Podle FIDE ID\n");
    printf("\t2 - Podle parametru\n");
    printf("\t0 - Domu, do Prahy...\n");
    fflush(stdin);
    scanf("%c",&volba);
    }while(volba>50||volba<48);
    switch(volba){
        case 48:
            {
                return -1;
                break;
            }
        case 49:
            {
                int key;
                do{
                do{
                    system("cls");
                    system("color 07");
                    printf("Zadej FIDE ID hrace, nebo 0\n");
                    scanf("%d",&key);
                if(key==0)
                    return -1;

                if(key<1000000||key>99999999){
                    system("color 04");
                    printf("Mimo rozsah\n");
                    system("pause");
                }
                }while(key<1000000||key>99999999);
                x = vyhledatID(key, n, h);
                if(x==-1){
                    system("color 04");
                    printf("Hrac nenalezen\n");
                    system("pause");
                }
                }while(x==-1);
                vypisJedna(h[x]);
                break;
            }
        case 50:
            {
                int count =n;
                do{
                    do{
                        system("cls");
                        system("color 07");
                        printf("Zbyva %d hracu\n",count);
                        if(druh ==0){
                            printf("Podle jakych parametru chces vyhledat hrace:\n");
                        }else{
                            printf("Podle jakych parametru chces vyhledat hrace na upravu:\n");
                        }

                        printf("\t1 - Podle jmena\n");
                        printf("\t2 - Podle prijmeni\n");
                        printf("\t3 - Podle roku narozeni\n");
                        printf("\t0 - Domu, do Prahy...\n");
                        fflush(stdin);
                        scanf("%c",&volba);
                        }while(volba>51||volba<48);
                        count = 0;
                        switch(volba){
                        case 48:
                            {
                                return -1;
                                break;
                            }
                        case 49:
                            {
                                char jmeno[20];
                                do{
                                    system("cls");
                                    system("color 07");
                                    printf("Zadej jmeno hrace:");
                                    scanf("%19s",jmeno);
                                }while(validace(jmeno,19));
                                for(int i=0;i<n;i++){
                                    if(strcmp(h[i].jmeno,jmeno)!=0){
                                        h[i].smazano = 1;
                                    }else{
                                        count++;
                                        x=i;
                                    }
                                }
                            }

                        }
                if(count == 0){
                    system("color 04");
                    printf("Nikdo nenalezen\n");
                    for(int i=0;i<n;i++){
                    h[i].smazano = 0;
                }
                system("pause");
                }else{
                    vypsat(h,n);
                }
                }while(count !=1);
                for(int i=0;i<n;i++){
                    h[i].smazano = 0;
                }

                break;
            }
    }
return x;
}


void upravitMenu(int n, Thraci h[]){
    char volba;
    int x = vyhledat(h,n,1);
    if(x==-1){
        return;
    }
    char nazev[8][20]={"FIDE ID","Titul","Jmeno","Prijmeni","Elo","Max Elo","Narod","Narozeni"};
    system("cls");
    //vypisJedna(h[x]);
    do{
    system("cls");
    printf("Co chces upravit:\n");
    printf("\t1 - Titul\n");
    printf("\t2 - Jmeno\n");
    printf("\t3 - Prijmeni\n");
    printf("\t4 - Elo\n");
    printf("\t5 - Max elo\n");
    printf("\t6 - Narodnost\n");
    printf("\t7 - Rok narozeni\n");
    printf("\t8 - Smazat\n");
    printf("\t0 - Domu, do Prahy...\n");
    fflush(stdin);
    scanf("%c",&volba);
    }while(volba>56||volba<48);

    switch(volba)
    {
    case 48:{
        return;
        break;}
    case 56:{
        h[x].smazano=1;
        break;}
    case 49:{
        volba = ERR;
        do{
        system("cls");
        system("color 08");
        vypisJedna(h[x]);
        printf("\t Uprava titulu hrace\n");
        printf("%s:\n",nazev[1]);
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
        scanf("%c",&volba);
    switch(volba){
    case 48:
        strcpy(h[x].titul,"None");
        break;
    case 49:
        strcpy(h[x].titul,"CM");
        break;
    case 50:
        strcpy(h[x].titul,"FM");
        break;
    case 51:
        strcpy(h[x].titul,"IM");
        break;
    case 52:
        strcpy(h[x].titul,"GM");
        break;
    case 53:
        strcpy(h[x].titul,"NM");
        break;
    case 54:
        strcpy(h[x].titul,"WCM");
        break;
    case 55:
        strcpy(h[x].titul,"WFM");
        break;
    case 56:
        strcpy(h[x].titul,"WIM");
        break;
    case 57:
        strcpy(h[x].titul,"WGM");
        break;
    case 47:
        strcpy(h[x].titul,"WNM");
        break;
    default:
        system("color 04");
        printf("mimo rozsah\n");
        system("pause");
        break;
    }
    }while(volba<47 || volba>57);
    break;}

    case 50:{
        do{
        system("cls");
        system("color 08");
        printf("\t Uprava jmena hrace\n");
        printf("%-11s",nazev[2]);
        fflush(stdin);
        scanf("%19s",h[x].jmeno);

    }while(validace(h[x].jmeno,19));

    break;
    }
    case 51:{
        do{
        system("cls");
        system("color 08");
        printf("\t Uprava prijmeni hrace\n");
        printf("%-11s",nazev[3]);
        fflush(stdin);
        scanf("%19s",h[x].prijmeni);

    }while(validace(h[x].prijmeni,19));

    break;
    }
    case 52:{
        do{
        system("cls");
        system("color 08");
        printf("\t Uprava ela hrace:\t");
        printf("1000-3000\n");
        printf("%-11s",nazev[4]);
        scanf("%d",&h[x].elo);
        if(h[x].elo<1000 || h[x].elo>3000){
            system("color 04");
            printf("mimo rozsah\n");
            system("pause");
    }

    }while(h[x].elo<1000 || h[x].elo>3000);
    if(h[x].elo>h[x].maxelo)
        h[x].maxelo=h[x].elo;

    break;
    }
     case 53:{
        do{
        system("cls");
        system("color 08");
        printf("\t Uprava Max ela hrace:\t");
        printf("%d-3000\n",h[x].elo);
        printf("%-11s",nazev[5]);
        scanf("%d",&h[x].maxelo);
        if(h[x].maxelo<h[x].elo || h[x].maxelo>3000){
            system("color 04");
            printf("mimo rozsah\n");
            system("pause");
    }

    }while(h[x].maxelo<h[x].elo || h[x].maxelo>3000);

    break;
    }
     case 54:{
            do{
        system("cls");
        system("color 08");
        printf("\t Uprava narodnosti hrace\n");
        printf("%-11s",nazev[6]);
        fflush(stdin);
        scanf("%4s",h[x].nation);

    }while(validace(h[x].nation,4));
    break;
    }

    case 55:{
        do{
        system("cls");
        system("color 08");
        printf("\t Uprava roku narozeni hrace:\t");
        printf("1500-2025\n");
        printf("%-11s",nazev[7]);
        scanf("%d",&h[x].rokNarozeni);
        if(h[x].rokNarozeni<1500 || h[x].rokNarozeni>2025){
            system("color 04");
            printf("mimo rozsah\n");
            system("pause");
    }

    }while(h[x].rokNarozeni<1500 || h[x].rokNarozeni>2025);
    break;
    }

    }
    zapis(h,n);

}




int login(FILE *p)
{
    char password[20];
    char heslo[20];
    system("cls");
    if(fscanf(p,"%19s",password)==1){
            do{
        system("color 07");
        system("cls");
        printf("Zadej heslo, nebo 0 k vraceni zpet\n");
        scanf("%19s",heslo);
        //printf("%s",heslo);
        if(strcmp(heslo,"0")==0){
            //printf("exiting");
            //system("timeout /t 2");
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
            //return 0;
        }
    }while(strcasecmp(heslo,"0")!=0);
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
        printf("heslo zmeneno!\n");
        system("pause");
        return 1;
        }
        system("color 04");
        printf("hesla se neshoduji!\n");
        system("pause");
        return 0;

}

void vypsat(Thraci p[], int n){
    system("cls");
    printf("\t\t\t\t\tTabulka hracu\n");
    char nazev[8][20]={"FIDE ID","Titul","Jmeno","Prijmeni","Elo","Max Elo","Narod","Narozeni"};
    printf(" %-7s %-5s %-19s %-21s %-9s %-7s %-6s %-6s\n",nazev[0],nazev[1],nazev[2],nazev[3],nazev[4],nazev[5],nazev[6],nazev[7]);
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

Thraci pridat(){
    Thraci player;
    char nazev[8][20]={"FIDE ID","Titul","Jmeno","Prijmeni","Elo","Max Elo","Narod","Narozeni"};
    do{
        system("cls");
        system("color 08");
        printf("\t Pridani noveho hrace:\t");
        printf("1000000-99999999\n");
        printf("%-11s",nazev[0]);
        player.fideID=89745632;
        //scanf("%d",&player.fideID);
        if(player.fideID<1000000 || player.fideID>99999999){
            system("color 04");
            printf("mimo rozsah\n");
            system("pause");
    }
    }while(player.fideID<1000000 || player.fideID>99999999);
     char volba;
    do{

        system("cls");
        system("color 08");
        printf("\t Pridani noveho hrace\n");
        printf("%-10s %d\n",nazev[0],player.fideID);
        printf("%s:\n",nazev[1]);
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
        scanf("%c",&volba);
    switch(volba){
    case 48:
        strcpy(player.titul,"None");
        break;
    case 49:
        strcpy(player.titul,"CM");
        break;
    case 50:
        strcpy(player.titul,"FM");
        break;
    case 51:
        strcpy(player.titul,"IM");
        break;
    case 52:
        strcpy(player.titul,"GM");
        break;
    case 53:
        strcpy(player.titul,"NM");
        break;
    case 54:
        strcpy(player.titul,"WCM");
        break;
    case 55:
        strcpy(player.titul,"WFM");
        break;
    case 56:
        strcpy(player.titul,"WIM");
        break;
    case 57:
        strcpy(player.titul,"WGM");
        break;
    case 47:
        strcpy(player.titul,"WNM");
        break;
    default:
        system("color 04");
        printf("mimo rozsah\n");
        system("pause");
        break;
    }
    }while(volba<47 || volba>57);


    do{
        system("cls");
        system("color 08");
        printf("\t Pridani noveho hrace\n");
        printf("%-10s %d\n",nazev[0],player.fideID);
        printf("%-10s %-5s\n",nazev[1],player.titul);
        printf("%-11s",nazev[2]);
        fflush(stdin);
        scanf("%19s",player.jmeno);

    }while(validace(player.jmeno,19));

    do{
        system("cls");
        system("color 08");
        printf("\t Pridani noveho hrace\n");
        printf("%-10s %d\n",nazev[0],player.fideID);
        printf("%-10s %-5s\n",nazev[1],player.titul);
        printf("%-10s %-20s\n",nazev[2],player.jmeno);
        printf("%-11s",nazev[3]);
        fflush(stdin);
        scanf("%19s",player.prijmeni);

    }while(validace(player.prijmeni,19));

    do{
        system("cls");
        system("color 08");
        printf("\t Pridani noveho hrace:\t");
        printf("1000-3000\n");
        printf("%-10s %d\n",nazev[0],player.fideID);
        printf("%-10s %-5s\n",nazev[1],player.titul);
        printf("%-10s %-20s\n",nazev[2],player.jmeno);
        printf("%-10s %-20s\n",nazev[3],player.prijmeni);
        printf("%-11s",nazev[4]);
        scanf("%d",&player.elo);
        if(player.elo<1000 || player.elo>3000){
            system("color 04");
            printf("mimo rozsah\n");
            system("pause");
    }

    }while(player.elo<1000 || player.elo>3000);


    do{
        system("cls");
        system("color 08");
        printf("\t Pridani noveho hrace:\t");
        printf("%d-3000\n",player.elo);
        printf("%-10s %d\n",nazev[0],player.fideID);
        printf("%-10s %-5s\n",nazev[1],player.titul);
        printf("%-10s %-20s\n",nazev[2],player.jmeno);
        printf("%-10s %-20s\n",nazev[3],player.prijmeni);
        printf("%-10s %d\n",nazev[4],player.elo);
        printf("%-11s",nazev[5]);
        scanf("%d",&player.maxelo);
        if(player.maxelo<player.elo || player.maxelo>3000){
            system("color 04");
            printf("mimo rozsah\n");
            system("pause");
    }

    }while(player.maxelo<player.elo || player.maxelo>3000);


    do{
        system("cls");
        system("color 08");
        printf("\t Pridani noveho hrace\n");
        printf("%-10s %d\n",nazev[0],player.fideID);
        printf("%-10s %-5s\n",nazev[1],player.titul);
        printf("%-10s %-20s\n",nazev[2],player.jmeno);
        printf("%-10s %-20s\n",nazev[3],player.prijmeni);
        printf("%-10s %d\n",nazev[4],player.elo);
        printf("%-10s %d\n",nazev[5],player.maxelo);
        printf("%-11s",nazev[6]);
        fflush(stdin);
        scanf("%4s",player.nation);

    }while(validace(player.nation,4));


    do{
        system("cls");
        system("color 08");
        printf("\t Pridani noveho hrace:\t");
        printf("1500-2025\n");
        printf("%-10s %d\n",nazev[0],player.fideID);
        printf("%-10s %-5s\n",nazev[1],player.titul);
        printf("%-10s %-20s\n",nazev[2],player.jmeno);
        printf("%-10s %-20s\n",nazev[3],player.prijmeni);
        printf("%-10s %d\n",nazev[4],player.elo);
        printf("%-10s %d\n",nazev[5],player.maxelo);
        printf("%-10s %-5s\n",nazev[6],player.nation);
        printf("%-11s",nazev[7]);
        scanf("%d",&player.rokNarozeni);
        if(player.rokNarozeni<1500 || player.rokNarozeni>2025){
            system("color 04");
            printf("mimo rozsah\n");
            system("pause");
    }

    }while(player.rokNarozeni<1500 || player.rokNarozeni>2025);

    player.smazano = 0;
    system("cls");
        system("color 08");
        printf("\t Pridani noveho hrace\n");
        printf("%-10s %d\n",nazev[0],player.fideID);
        printf("%-10s %-5s\n",nazev[1],player.titul);
        printf("%-10s %-20s\n",nazev[2],player.jmeno);
        printf("%-10s %-20s\n",nazev[3],player.prijmeni);
        printf("%-10s %d\n",nazev[4],player.elo);
        printf("%-10s %d\n",nazev[5],player.maxelo);
        printf("%-10s %-5s\n",nazev[6],player.nation);
        printf("%-10s %d\n",nazev[7],player.rokNarozeni);
        system("pause");

return player;
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
    fclose(in);

    int volba;
    int admin = false;
    do{
    volba = menu(admin);
    printf("OK");
    system("pause");
    switch(volba)
{
    case 49:
        vypsat(player, n);
        break;
    case 50:
        vyhledat(player,n,0);
        break;
    case 51:
        //menu++();
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
            system("cls");
            printf("We trust you have received the usual lecture from the local System\nAdministrator. It usually boils down to these three things:\n\n\t#1) Respect the privacy of others.\n\t#2) Think before you type.\n\t#3) With great power comes great responsibility\n");
            system("pause");
            admin = login(password);
            fclose(password);
        }
        break;
        case 54:
           player[n] = pridati();
           in = fopen("hraci.txt","a");
            if(in == NULL){
                system("color 04");
                printf("Error 404: File hraci.txt not found :(");
                system("timeout /t 1");
                return -3;
            }
            fprintf(in,"\n%d %s %s %s %d %d %s %d %d",player[n].fideID,player[n].titul, player[n].jmeno, player[n].prijmeni, player[n].elo, player[n].maxelo, player[n].nation, player[n].rokNarozeni, player[n].smazano);
            fclose(in);

           n++;
        break;

        case 55:
            upravitMenu(n, player);
            break;

        case 57:
            if(zapis(player,n)==-3)
                return -3;
        break;

}

    }while(volba!=48);
    return 0;
}
