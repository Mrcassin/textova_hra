#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>    //knihovna pro _getch();
#include <windows.h>  //knihovna pro spravu konsole (Sleep,
#include "otazkyZeSouboru.h"

#define PRODLEVA 75 //prodleva pro casovane vykreslovani
#define ODDELOVACE ";\n"

//vypujcena funkce pro skryti kurzoru v okne
void hidecursor() 
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

//vypis udaju o hre -> pri stisknuti klavesy prokracovani v programu
void about() {
	system("cls");
	char konec;
	printf("\033[1;34m%30c-----------------------------------------------------\033[1;0m", ' ');
	printf("\n\033[1;31m%45c --- ESCAPE GAME ----\n\033[1;0m", ' ');
	printf("\033[1;34m%30c-----------------------------------------------------\n\033[1;0m",' ');
	printf("%30cTextova hra na principu unikove hry.\n", ' ');
	printf("%30cPro dokonceni musi hrac zodpovedet na vsechny otazky.\n", ' ');
	printf("\033[1;34m%30c-----------------------------------------------------\n\033[1;0m", ' ');
	printf("%30cHru lze zacit zcela odzacatku, ale je zde i moznost \n", ' ');
	printf("%30cpokracovat presne tam, kde hrac naposledy skoncil \n", ' ');
	printf("%30czadanim save souboru pri vyzve.\n", ' ');
	printf("\033[1;34m%30c-----------------------------------------------------\n\033[1;0m", ' ');
	printf("%30cPri kazdem dokonceni hry dojde k zapsani vysledku\n", ' ');
	printf("%30cdo listiny vitezu, ktera je razena od nejnizsiho\n", ' ');
	printf("%30cpoctu spatnych odpovedi.\n", ' ');
	printf("\033[1;34m%30c-----------------------------------------------------\n\033[1;0m", ' ');
	printf("%30cHru vytvorili:\n\n", ' ');
	printf("\033[1;31m%40cMartin Simkovsky - 230679(id)\n", ' ');
	printf("%40cPeter Svagerko   - 230331(id)\n\033[1;0m", ' ');
	printf("\033[1;34m%30c-----------------------------------------------------\n\033[1;0m", ' ');
	konec = _getch();
}
//intro hry -> vypis s meziparametrem Sleep(); -> prodleva
void intro() {
	printf("88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n");
	Sleep(PRODLEVA);printf("\n");
	printf("\033[1;31m");
	Sleep(PRODLEVA);printf("	        oooooooooooo  .oooooo..o   .oooooo.         .o.       ooooooooo.   oooooooooooo         \n");
	Sleep(PRODLEVA);printf("	        `888'     `8 d8P'    `Y8  d8P'  `Y8b       .888.      `888   `Y88. `888'     `8         \n");
	Sleep(PRODLEVA);printf("	         888         Y88bo.      888              .8'888.      888.   d88'  888                 \n");
	Sleep(PRODLEVA);printf("	         888oooo8     `'Y8888o.  888             .8' `888.     888ooo88P'   888oooo8            \n");
	Sleep(PRODLEVA);printf("	8888888  888    '         `'Y88b 888            .88ooo8888.    888          888    '    8888888 \n");
	Sleep(PRODLEVA);printf("	         888       o oo     .d8P `88b    ooo   .8'     `888.   888          888       o         \n");
	Sleep(PRODLEVA);printf("	        o888ooooood8 88888888P'   `Y8bood8P'  o88o     o8888o o888o        o888ooooood8         \n");
	Sleep(PRODLEVA);printf("\n");
	Sleep(PRODLEVA);printf("\n");
	printf("\033[0;34m");
	Sleep(PRODLEVA);printf("	                    .oooooo.          .o.       ooo        ooooo oooooooooooo                   \n");
	Sleep(PRODLEVA);printf("	                   d8P'  `Y8b        .888.      `88.       .888' `888'     `8                   \n");
	Sleep(PRODLEVA);printf("	                  888               .8'888.      888b     d'888   888                           \n");
	Sleep(PRODLEVA);printf("	                  888              .8' `888.     8 Y88. .P  888   888oooo8                      \n");
	Sleep(PRODLEVA);printf("	          8888888 888     ooooo   .88ooo8888.    8  `888'   888   888    '    8888888           \n");
	Sleep(PRODLEVA);printf("	                  `88.    .88'   .8'     `888.   8    Y     888   888       o                   \n");
	Sleep(PRODLEVA);printf("	                   `Y8bood8P'   o88o     o8888o o8o        o888o o888ooooood8                   \n");
	Sleep(PRODLEVA);printf("\n");
	printf("\033[0m");
	Sleep(PRODLEVA);printf("88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n");
	Sleep(2500);
	system("cls");
}

int showLeaderboard() {
	system("mode 110,50"); //zvetseni okna pro pripad vetsiho mnozstvi vysledku
	system("cls");

	//struktura pro nacitani udaju ze souboru (vysledkove listiny (data na jednotlivych radcich odd. strednikem))
	struct ZAZNAM {
		char jmeno[50];
		char titul;
		int pocetSpravnych;
		int pocetSpatnych;
	};
	
	ZAZNAM* leaderboard = NULL;  //ukazatel typu struktura
	struct ZAZNAM pomocna;	     //pomocna struktura pro bubblesort

	char mystring[100];
	int pocet = 1;  //pocet zaznamu v souboru
	int pocetSloupcu;
	char* pch;

	char konec; //pomocna promenna pro vy

	FILE* pFile;
	errno_t err;
	err = fopen_s(&pFile, "vysledky.txt", "r");
	if (err != 0)
	{
		printf("%38c Nebyl nalezen soubor s vysledky.", ' ');
		Sleep(2000);
		return EXIT_FAILURE;
	}
	rsize_t strmax = sizeof(mystring);
	leaderboard = (ZAZNAM*)calloc(100, sizeof(ZAZNAM));
	while (fgets(mystring, 100, pFile) != NULL) { //nacteni radku do promenne mystring
			pocetSloupcu = 0;
			pch = strtok(mystring, ODDELOVACE);
			while (pch != NULL) {
				switch (pocetSloupcu)
				{
				case 0:
					strcpy(leaderboard[pocet - 1].jmeno, pch);
					break;
				case 1:
					leaderboard[pocet - 1].titul = *pch;
					break;
				case 2:
					leaderboard[pocet - 1].pocetSpravnych = atoi(pch);
					break;
				case 3:
					leaderboard[pocet - 1].pocetSpatnych = atoi(pch);
					break;
				}
				pocetSloupcu++;
				pch = strtok(NULL, ODDELOVACE);
			}
		
		pocet++;
	}
	int i, j;
	
	for (i = 0; i < pocet - 1; i++)
	{
		for (j = 0; j < pocet - i - 1; j++)
		{
			
			if (leaderboard[j].pocetSpatnych > leaderboard[j + 1].pocetSpatnych)  
			{
				strcpy(pomocna.jmeno,"");
				pomocna.titul = '\0';
				pomocna.pocetSpravnych = NULL;
				pomocna.pocetSpatnych = NULL;

				strcpy(pomocna.jmeno, leaderboard[j].jmeno);
				strcpy(leaderboard[j].jmeno, leaderboard[j + 1].jmeno);
				strcpy(leaderboard[j + 1].jmeno, pomocna.jmeno);

				pomocna.titul = leaderboard[j].titul;
				leaderboard[j].titul = leaderboard[j + 1].titul;
				leaderboard[j + 1].titul = pomocna.titul;

				pomocna.pocetSpravnych = leaderboard[j].pocetSpravnych;
				leaderboard[j].pocetSpravnych = leaderboard[j + 1].pocetSpravnych;
				leaderboard[j + 1].pocetSpravnych = pomocna.pocetSpravnych;

				pomocna.pocetSpatnych = leaderboard[j].pocetSpatnych;
				leaderboard[j].pocetSpatnych = leaderboard[j + 1].pocetSpatnych;
				leaderboard[j + 1].pocetSpatnych = pomocna.pocetSpatnych;
			}
		}
	}
	
	j = 1; //cislovani radku (misto)
	fclose(pFile);
	printf("\033[1;34m%15c ---------------------------------------------------------------------------- \n\033[1;0m", ' ');
	printf("\033[1;31m%43c TABULKA VYSLEDKU\n\033[1;0m", ' ');
	printf("\033[1;34m%15c ---------------------------------------------------------------------------- \n\033[1;0m", ' ');
	printf("%15c | poradi |  jmeno hrace  |        odehrany titul        | spravne | spatne |\n", ' ');
	printf("\033[1;34m%15c ---------------------------------------------------------------------------- \n\033[1;0m", ' ');
	for (i = 0;i < pocet;i++) {
		if (leaderboard[i].titul == 'm') {
			printf(" %15c|%8d|%15s|%30s|%9d|%8d|\n", ' ', j++, leaderboard[i].jmeno, "Sileny matematik",
				leaderboard[i].pocetSpravnych, leaderboard[i].pocetSpatnych);
		}
	}
	j = 1;
	printf("\033[1;34m%15c ---------------------------------------------------------------------------- \n\033[1;0m", ' ');
	for (i = 0;i < pocet;i++) {
		if (leaderboard[i].titul == 'e') {
			printf(" %15c|%8d|%15s|%30s|%9d|%8d|\n", ' ', j++, leaderboard[i].jmeno, "Elektrotechnika hrou",
				leaderboard[i].pocetSpravnych, leaderboard[i].pocetSpatnych);
		}
	}
	printf("\033[1;34m%15c ---------------------------------------------------------------------------- \n\033[1;0m", ' ');
	printf("%38c pro odchod stiskni libovolnou klavesu\n", ' ');
	printf("\033[1;34m%15c ---------------------------------------------------------------------------- \n\033[1;0m", ' ');
	free(leaderboard);
	konec = _getch();
}

/*Pokracovani hry funguje na principu zadani souboru kde se nachazi informace o progresu (jmenoHrace,
titul, pocet spravnych odpovedi = otazka na ktere uzivatel skoncil, pocet spatnych (udaj do vys. listiny)
volani funkce startHry()*/
int continueGame() {
	char jmenoHrace[50];
	char titul;
	int progres;
	int spatne;
	char save[50];

	char mystring[50];
	char* pch;
	int atribut = 0;
	

	printf("\n\n\n\n\n\n\n\n\n %40c ZADEJ SAVE K NACTENI: ", ' ');
	scanf_s("%s", save, 50);

	FILE* pFile;
	errno_t err;
	err = fopen_s(&pFile, save, "r"); //otevreni souboru s 

	//v pripade zadani spatneho souboru se save je returnovana 1 a vrati uzivatele do hlavni nabidky
	if (err != 0)
	{
		printf("%38c Chybny save soubor! Zkuste znovu!",' ');
		Sleep(2000);
		return EXIT_FAILURE;
	}

	//nacteni souboru do pole mystring
	while (fgets(mystring, 50, pFile) != NULL) {
		//parsovani pomoci strtok v ukazateli pch vzdy cast mezi oddelovacem
		pch = strtok(mystring, ODDELOVACE); 
		//dokud neni ukazatel prazdny (konec souboru) -> zapisuje do jednotivych promennych udaje
		while (pch != NULL) { 
			switch (atribut)
			{
			case 0:
				strcpy(jmenoHrace, pch);
				break;
			case 1:
				titul = *pch;
				break;
			case 2:
				progres = atoi(pch); //prevod retezce na int
				break;
			case 3:
				spatne = atoi(pch);
				break;
			}
			atribut++; //posunuti na dalsi atribut
			pch = strtok(NULL, ODDELOVACE); //vyprazdenini ukazatele
		}
	}
	fclose(pFile); //uzavreni souboru
	system("cls");
	startHry(jmenoHrace, titul, progres, spatne);
}

/*pokud uzivatel zvoli moznost nova hra, bude vyzvan k zadani jmena a vyberu titulu.
nasledne bude zavolana funkce startHRy z vlastniho modulu otazkyZeSouboru s parametry
(hrac(hodnota zadana uzivatelem),titul(vybrano pomoci _getch()), 0 jako progres ->
-> start titulu od zacatku, 0 -> pocet spatnych odpoved -> hodnota 0 (hra probiha
od zacatku uzivatel nema zadne zaznamenane odpovedi))*/
void newGame() {
	char jmenoHrace[50];
	char titul;
	printf("\n\n\n\n\n\n\n\n\n %40c ZADEJ JMENO HRACE: ", ' ');
	scanf_s("%s", jmenoHrace,50);
	system("cls");
	printf("\n\n\n\n\n\n\n\%40c DOSTUPNE TITULY\n", ' ');
	printf("\033[1;31m");
	printf("%43d) Sileny matematik\n", 1);
	printf("%43d) Elektrotechnika hrou\n", 2);
	printf("\033[0m");

	titul = _getch();
	switch (titul) {
	case '1':
		system("cls");
		startHry(jmenoHrace, 'm', 0, 0);
		break;
	case '2':
		system("cls");
		startHry(jmenoHrace, 'e', 0, 0);
		break;
	}
}

/*hlavni smycka - hlavni menu -> vyber pomoci _getch() <- (stisk klavesy) -> switch
podle zaznamenane klavesy se zavola dana funkce bud (newGame, continueGame, showLeaderboard,about)
nebo se hra ukonci*/
int main()
{
	system("mode 110,21"); //zmena velikosti okna
	hidecursor();
    intro();
	system("cls");

	char volba;

	do {
		system("mode 110,21");
		system("cls");
		printf("\n\n\n\n\n\n%45d) Nova hra\n", 1);
		printf("%45d) Pokracovat ve hre\n", 2);
		printf("%45d) Vysledkova listina\n", 3);
		printf("%45d) O hre\n", 4);
		printf("%45d) KONEC\n", 5);

		volba = _getch();

		switch (volba) {
		case '1':
			system("cls");
			newGame();
			break;
		case '2':
			system("cls");
			continueGame();
			break;
		case '3':
			showLeaderboard();
			break;
		case '4':
			about();
			break;
		case '5':
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n%50c KONEC",' ');
			Sleep(2000);
			system("cls");
			system("exit");
			break;
		}
	} while (volba != '5');
}

