#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#define OTAZKY_M "otazkyM.txt"                  //soubor pro otázky z Matematiky
#define OTAZKY_E "otazkyE.txt"                  //soubor pro otázky z Elektrotechniky
#define VYSLEDKOVA_LISTINA "vysledky.txt"       //soubor pro ulozeni vysledku
#define ODDELOVACE "\n;"                        //oddelovace pro parsovani pri nacitani do struktury
#define VELIKOST 400                            //velikost stringu pro cteni jednotlivych radku souboru s otazky
#define DLVL 10                                 //pocet otazek na dokonceni levelu
#define PRODLEVA 75                             //prodleva na casovany vypis (ms)

/*casovany vypis outra*/
void outro() {
    system("cls");
    printf("88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n");
    Sleep(PRODLEVA);printf("\n");
    printf("\033[1;31m");
    Sleep(PRODLEVA);printf("  .oooooo.     .oooooo.   ooooo      ooo   .oooooo.    ooooooooo.         .o.       ooooooooooooo  .oooooo..o \n");
    Sleep(PRODLEVA);printf(" d8P'  `Y8b   d8P'  `Y8b  `888b.     `8'  d8P'  `Y8b   `888   `Y88.      .888.      8'   888   `8 d8P'    `Y8 \n");
    Sleep(PRODLEVA);printf("888          888      888  8 `88b.    8  888            888   .d88'     .8'888.          888      Y88bo.      \n");
    Sleep(PRODLEVA);printf("888          888      888  8   `88b.  8  888            888ooo88P'     .8' `888.         888       `'Y8888o.  \n");
    Sleep(PRODLEVA);printf("888          888      888  8     `88b.8  888     ooooo  888`88b.      .88ooo8888.        888           `'Y88b \n");
    Sleep(PRODLEVA);printf("`88b    ooo  `88b    d88'  8       `888  `88.    .88'   888  `88b.   .8'     `888.       888      oo     .d8P \n");
    Sleep(PRODLEVA);printf(" `Y8bood8P'   `Y8bood8P'  o8o        `8   `Y8bood8P'   o888o  o888o o88o     o8888o     o888o     8''88888P'  \n");
    Sleep(PRODLEVA);printf("\n");
    Sleep(PRODLEVA);printf("\n");
    printf("\033[0;0m");
    Sleep(PRODLEVA);printf("88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n");
    Sleep(PRODLEVA);printf("\n");
    printf("\033[0;34m");
    Sleep(PRODLEVA);printf("oooooo   oooo                                                                                                 \n");
    Sleep(PRODLEVA);printf(" `888.   .8'                                                                                                  \n");
    Sleep(PRODLEVA);printf("  `888. .8'    .ooooo.  oooo  oooo                                                                            \n");
    Sleep(PRODLEVA);printf("   `888.8'    d88' `88b `888  `888                                                                            \n");
    Sleep(PRODLEVA);printf("    `888'     888   888  888   888                                                                            \n");
    Sleep(PRODLEVA);printf("     888      888   888  888   888                                                                            \n");
    Sleep(PRODLEVA);printf("    o888o     `Y8bod8P'  `V88V'V8P'                                                                           \n");
    Sleep(PRODLEVA);printf("\n");
    Sleep(PRODLEVA);printf("\n");
    Sleep(PRODLEVA);printf("oooooooooooo  .oooooo..o   .oooooo.         .o.       ooooooooo.   oooooooooooo oooooooooo.                   \n");
    Sleep(PRODLEVA);printf("`888'     `8 d8P'    `Y8  d8P'  `Y8b       .888.      `888   `Y88. `888'     `8 `888'   `Y8b                  \n");
    Sleep(PRODLEVA);printf(" 888         Y88bo.      888              .8'888.      888.    d88' 888          888      888                 \n");
    Sleep(PRODLEVA);printf(" 888oooo8     `'Y8888o.  888             .8' `888.     888ooo88P'   888oooo8     888      888                 \n");
    Sleep(PRODLEVA);printf(" 888    '         `'Y88b 888            .88ooo8888.    888          888    '     888      888                 \n");
    Sleep(PRODLEVA);printf(" 888       o oo     .d8P `88b    ooo   .8'     `888.   888          888       o  888     d88'                 \n");
    Sleep(PRODLEVA);printf("o888ooooood8 8''88888P'   `Y8bood8P'  o88o     o8888o o888o        o888ooooood8 o888bood8P'                   \n");
    printf("\033[0m");
    Sleep(PRODLEVA);printf("\n");
    Sleep(PRODLEVA);printf("88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n");
    Sleep(2500);
}

/*Funkce pro ulozeni hry -> vyzadani nazevu souboru k ulozeni save -> otevreni souboru -> zapis*/
int saveAndQuit(char * jmenoHrace,char  titul, int pocetSpravnych, int pocetSpatnych) {
    char soubor[50];
    printf("\n\n\n\n\n\n\n\n\n %40c ZADEJ SOUBOR PRO ULOZENI SAVE (.txt): ", ' ');
    scanf_s("%s",soubor, 50);
    FILE* pFile;
    errno_t err;
    err = fopen_s(&pFile, soubor, "w");
    if (err != 0)
    {
        printf("Nepodarilo se ulozit vysledky! \n\n");
        Sleep(1000);
        return EXIT_FAILURE;
    }
    if (pFile != 0) {
        fprintf(pFile, "%s;%c;%d;%d\n", jmenoHrace, titul, pocetSpravnych, pocetSpatnych);
        fclose(pFile);
    }
}

/*zapis do vysledkove listiny stejny princip jako ulozeni progresu
-> otevreni souboru -> zapis -> uzavreni souboru*/
void saveToLead(char* jmenoHrace, char titul, int spravne, int spatne) {
    FILE* pFile;
    errno_t err;
    err = fopen_s(&pFile, VYSLEDKOVA_LISTINA, "a"); //parametr a je pridani na konec souboru
    if (err != 0)
    {
        printf("Nepodarilo se ulozit vysledky! \n\n");
    }
    if (pFile != 0) {
        fprintf(pFile, "%s;%c;%d;%d\n", jmenoHrace, titul, spravne, spatne);
        fclose(pFile);
    }   
}

int startHry(char * jmenoHrace, char titul, int progres, int spatne) {
    //struktura pro nacteni otazky
    typedef struct {
        char otazka[300];
        char odpovedA[50];
        char odpovedB[50];
        char odpovedC[50];
        char spravna;
        char typ;
    }OTAZKY;

    OTAZKY* otazky = NULL; //ukazatel typu struktura -> budeme mít pole struktur 

    char mystring[VELIKOST];
    int pocet = 0;
    int pocetSloupcu = 0;
    char* pch;
    char odpovedUzavrena;
    int odpovedOtevrena;
    int pocetSpatnych = spatne;
    int pocetSpravnych = progres;

    FILE* pFile;
    errno_t err;

    //podle zvoleneho titulu se otevre dany soubor s otazkami
    if (titul == 'm') {
        err = fopen_s(&pFile, OTAZKY_M, "r"); 
    }
    else if (titul == 'e') {
        err = fopen_s(&pFile, OTAZKY_E, "r");
    }
    else err = fopen_s(&pFile, OTAZKY_M, "r"); //defaultne otevrit neco jinak bere jako vyuziti potencialne neinicializované prom pFile
    
    //v pripade absence souboru s otazkami bude program ukoncen
    if (err != 0)
    {
        printf("Chybi soubor s otazkami, program bude ukoncen! \n\n");
        return EXIT_FAILURE;
    }
   
    //funkce pro nacteni otazek do pole struktur
    while (fgets(mystring, VELIKOST, pFile) != NULL) {
        if (pocet > 0) {
            pocetSloupcu = 0;
            //dynamicke alokovani pameti vzdy pro nasledujici otazku
            otazky = (OTAZKY*)realloc(otazky, pocet * sizeof(OTAZKY)); 
            //v pch ulozeny aktualni vyraz mezi oddelovacemi
            pch = strtok(mystring, ODDELOVACE);
            //dokud neni konec souboru
            while (pch != NULL) { 
                switch (pocetSloupcu)
                {
                case 0:
                    strcpy(otazky[pocet - 1].otazka, pch);
                    break;
                case 1:
                    strcpy(otazky[pocet - 1].odpovedA, pch);
                    break;
                case 2:
                    strcpy(otazky[pocet - 1].odpovedB, pch);
                    break;
                case 3:
                    strcpy(otazky[pocet - 1].odpovedC, pch);
                    break;
                case 4:
                    otazky[pocet - 1].spravna = *pch;
                    break;
                case 5:
                    otazky[pocet - 1].typ= *pch;
                    break;
                }
                pocetSloupcu++; //posunuti na dalsi atribut ve strukture
                pch = strtok(NULL, ODDELOVACE); //vyprazdneni pch
            }
        }
        pocet++;
    }

    for (int i = progres;i < DLVL;i++) {
        /*uzavreny typ otazek -> moznosti a,b,c -> vypsani otazky a odpovedi
        cekani na zmacknuti klavesy odpovedi/volby funkce _getch()*/
        if (otazky[i].typ == 'u') {
            printf("\033[1;36m");
            printf("%s\n", otazky[i].otazka);
            printf("\033[1;0m");
            printf("A) %s\n", otazky[i].odpovedA);
            printf("B) %s\n", otazky[i].odpovedB);
            printf("C) %s\n", otazky[i].odpovedC);
            printf("\033[1;36m");
            printf("STISKNI KLAVESU a,b,c, kterou povazujes za SPRAVNOU odpoved.\n");
            printf("------------------------------------------------------------\n");
            printf("Pro odchod ze hry a ulozeni progresu stiskni klavesu q.\n");
            printf("------------------------------------------------------------\n");
            printf("\033[1;0m");
            do {
                odpovedUzavrena = _getch();
                //volba q vola funkci na ulozeni progresu do souboru s parametry aktualni hry a vraci do hl. menu
                if (odpovedUzavrena == 'q') {
                    saveAndQuit(jmenoHrace, titul, pocetSpravnych, pocetSpatnych);
                    return EXIT_FAILURE;
                }
                //overeni jestli je otazka spravna/spatna
                if (odpovedUzavrena == otazky[i].spravna) {
                    pocetSpravnych++;
                    printf("\033[1;34m");
                    printf("Spravna odpoved, pokracujes dal.\n");
                    Sleep(2500);
                    system("cls");
                    printf("\033[0m");
                }
                else {
                    pocetSpatnych++;
                    printf("\033[1;31m");
                    printf("Spatne! Zkus to jeste jednou!\n");
                    printf("\033[0m");
                }

            } while (odpovedUzavrena != otazky[i].spravna); //uzivatel zadava odpoved dokud nezada spravne
        }
        //otevreny typ otazek -> bez moznosti -> vypsana otazka a odpoved uzivatel zada
        else if (otazky[i].typ == 'o') {
            printf("\033[1;36m");
            printf("%s\n", otazky[i].otazka);
            printf("------------------------------------------------------------\n");
            printf("Pro odchod ze hry a ulozeni progresu zadej hodnotu -1.\n");
            printf("------------------------------------------------------------\n");
            printf("\033[1;0m");
            do {
                //pro uknoceni zadani hodnoty -1, stejne jako u uzavrene otazky -> volani funkce pro ulozeni hry
                printf("ODPOVED: ");
                scanf_s("%d", &odpovedOtevrena);
                if (odpovedOtevrena == -1) {
                    saveAndQuit(jmenoHrace, titul, pocetSpravnych, pocetSpatnych);
                    return EXIT_FAILURE;
                }
                //overeni jestli je otazka spravna/spatna
                if (odpovedOtevrena == atof(otazky[i].odpovedA)) {
                    pocetSpravnych++;
                    printf("\033[1;34m");
                    printf("Spravna odpoved, pokracujes dal.\n");
                    Sleep(1500);
                    system("cls");
                    printf("\033[0m");
                }
                else {
                    pocetSpatnych++;
                    printf("\033[1;31m");
                    printf("Spatne! Zkus to jeste jednou!\n");
                    printf("\033[0m");
                }

            } while (odpovedOtevrena != atoi(otazky[i].odpovedA)); //uzivatel zadava odpoved dokud nezada spravne
        }
    }
    /*po sparvnem zodpovezeni vsech otazek dojde k ulozeni do vys. listiny*/
    saveToLead(jmenoHrace, titul, pocetSpravnych, pocetSpatnych); 
    outro(); //vykresleni outra
    free(otazky); //vyprazdneni pameti
    return 0;
}
