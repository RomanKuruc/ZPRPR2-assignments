#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//tutok nacitame zo suboru jeden riadok
void citanie(FILE **file, int riadek){
	int j = 1;
	char znak;

	//nastavim sa na zaciatok suboru
	rewind(*file);

   	//nacitavam si znaky zo suboru
    while(fscanf(*file, "%c", &znak) != EOF) {

		//tuto nam najde riadok
        if(j == (riadek) ){
            //ak sa pozicia rovna znaku, tak ho zapiseme do pola "pozicia"
			printf("%c",znak);
  		}
		//ked sa dostanem na koniec riadku, tak
        if(znak == '\n') {
           	j++;
    	}
    }
}

//toto je funkcia V
void zaznamy(FILE **file, char **prispevok, char **autor, char **prezentovanie, char **den, char **cas, int *pocet_zaznamov) {

	//ak sa subor nebol otvoreny, otvorime  ho
    char znak;
    int pocet_riadokov = 1, i = 0, j, pozicia;

    *file = fopen("OrganizacnePodujatia.txt", "r");

	if (*file == NULL) {
        printf("Neotvoreny subor.\n");
    }
        //v pripade, ze bol otvoreny, tak pokracujem v kode
    else {
        //tutok si prejdem cely subor a naplnim si pocet_riadkov
        while(fscanf(*file, "%c", &znak) != EOF) {
            if(znak == '\n') {
               pocet_riadokov++;
            }
        }

        //kazdy zaznam ma 6 riadkov, tak staci vydelit 6mi
        *pocet_zaznamov = pocet_riadokov / 6;


        //ak nebolo vytvorene pole, tak mi to  spravi vypis zo suboru
        if (autor == NULL) {

            //nacitavam zaznamy zo suboru
		   for (i = 0; i < *pocet_zaznamov; i++){

  	  	   	   printf("Nazov prispevku: ");
  	  	   	   citanie(file, (6*i + 1));

  	  	   	   printf("Mena autorov: ");
  	  	   	   citanie(file, (6*i + 2));

  	  	   	   printf("Typ prezentovania: ");
  	  	   	   citanie(file, (6*i + 3));

			   printf("Cas prezentovania: ");
  	  	   	   citanie(file, (6*i + 4));

  	  	   	   printf("Datum: ");
  	  	   	   citanie(file, (6*i + 5));

  	  	   	   printf("\n");

		   }

   		}

   		else {

			for (i = 0; i < *pocet_zaznamov; i++){

  	  	   	   printf("Nazov prispevku: %s\n", prispevok[i]);
  	  	   	   printf("Mena autorov: %s\n", autor[i]);
 			   printf("Typ prezentovania: %s\n", prezentovanie[i]);
  	  	   	   printf("Cas prezentovania: %s\n", den[i]);
  	  	   	   printf("Datum: %s\n", cas[i]);
  	  	   	   printf("\n");

		   }

		}
    }
}

//toto je funkcia N
void nacitanie(FILE **file, char ***prispevok, char ***autor, char ***prezentovanie, char ***den, char ***cas, int pocet_zaznamov) {

	int i;
    //j je pozicia riadku
    int j = 1;
    char znak;
	int pozicia = 0;

    //toto mi zada poziciu  suboru an zaciatok
    rewind(*file);

	if (*file == NULL) {
       printf("Neotvoreny subor\n");
    }

    else {
        //tutok si alokujem pole pre prispevky
        (*prispevok) = (char**)malloc(pocet_zaznamov*(sizeof(char*)));

        for(i = 0; i < pocet_zaznamov; i++) {
            //vytvorim si pole i o pocte 150 pismenok
            (*prispevok)[i] = (char*)malloc(150*(sizeof(char)));
            j = 1;
            pozicia = 0;

            //nastavim si poziciu an zaciatok suboru
			rewind(*file);

            //tutok si nacitavam znaky zo suboru
            while(fscanf(*file, "%c", &znak) != EOF) {

                //tuto nam najde riadok
                if(j == ((i * 6)+1)) {
                    //ak sa pozicia rovna znaku, tak ho zapiseme do pola "pozicia"

					if (znak != '\n') {
					   (*prispevok)[i][pozicia] = znak;
                       pozicia++;
                	}

					if (znak == '\n') {
                        (*prispevok)[i][pozicia] = '\0';
                    }
                }
                //ked sa dostanem na koniec riadku, tak
                if(znak == '\n') {
                    j++;
                }
            }
        }

        //tutok si alokujem pole pre autora
        (*autor) = (char**)malloc(pocet_zaznamov*(sizeof(char*)));
        for(i = 0; i < pocet_zaznamov; i++) {
            //vytvorim si pole i o pocte 150 pismenok
            (*autor)[i] = (char*)malloc(150*(sizeof(char)));
            j = 1;
            pozicia = 0;

			rewind(*file);

            //tutok si nacitavam znaky zo suboru
            while(fscanf(*file, "%c", &znak) != EOF) {

                //tuto nam najde riadok
                if(j == ((i * 6)+2)) {
                    //ak sa pozicia rovna znaku, tak ho zapiseme do pola "pozicia"

					if (znak != '\n') {
					   (*autor)[i][pozicia] = znak;
                       pozicia++;
                	}

					if (znak == '\n') {
                        (*autor)[i][pozicia] = '\0';
                    }
                }
                //ked sa dostanem na koniec riadku, tak
                if(znak == '\n') {
                    j++;
                }
            }
        }

        //tutok si alokujem pole pre prezentovanie
        (*prezentovanie) = (char**)malloc(pocet_zaznamov*(sizeof(char*)));
        for(i = 0; i < pocet_zaznamov; i++) {
            //vytvorim si pole i o pocte 150 pismenok
            (*prezentovanie)[i] = (char*)malloc(150*(sizeof(char)));
            j = 1;
            pozicia = 0;

			rewind(*file);

            //tutok si nacitavam znaky zo suboru
            while(fscanf(*file, "%c", &znak) != EOF) {

                //tuto nam najde riadok
                if(j == ((i * 6)+3)) {
                    //ak sa pozicia rovna znaku, tak ho zapiseme do pola "pozicia"

					if (znak != '\n') {
					   (*prezentovanie)[i][pozicia] = znak;
                       pozicia++;
                	}

					if (znak == '\n') {
                        (*prezentovanie)[i][pozicia] = '\0';
                    }
                }
                //ked sa dostanem na koniec riadku, tak
                if(znak == '\n') {
                    j++;
                }
            }
        }

        //tutok si alokujem pole pre den
        (*den) = (char**)malloc(pocet_zaznamov*(sizeof(char*)));
        for(i = 0; i < pocet_zaznamov; i++) {
            //vytvorim si pole i o pocte 150 pismenok
            (*den)[i] = (char*)malloc(150*(sizeof(char)));
            j = 1;
            pozicia = 0;

			rewind(*file);

            //tutok si nacitavam znaky zo suboru
            while(fscanf(*file, "%c", &znak) != EOF) {

                //tuto nam najde riadok
                if(j == ((i * 6)+4)) {
                    //ak sa pozicia rovna znaku, tak ho zapiseme do pola "pozicia"

					if (znak != '\n') {
					   (*den)[i][pozicia] = znak;
                       pozicia++;
                	}

					if (znak == '\n') {
                        (*den)[i][pozicia] = '\0';
                    }
                }
                //ked sa dostanem na koniec riadku, tak
                if(znak == '\n') {
                    j++;
                }
            }
        }
        //tutok si alokujem pole pre cas
        (*cas) = (char**)malloc(pocet_zaznamov*(sizeof(char*)));
        for(i = 0; i < pocet_zaznamov; i++) {
            //vytvorim si pole i o pocte 150 pismenok
            (*cas)[i] = (char*)malloc(150*(sizeof(char)));
            j = 1;
            pozicia = 0;


            //nastavim si poziciu na zaciatok suboru
			rewind(*file);

            //tutok si nacitavam znaky zo suboru
            while(fscanf(*file, "%c", &znak) != EOF) {

                //tuto nam najde riadok
                if(j == ((i * 6)+5)) {
                    //ak sa pozicia rovna znaku, tak ho zapiseme do pola "pozicia"

					if (znak != '\n') {
					   (*cas)[i][pozicia] = znak;
                       pozicia++;
                	}

					if (znak == '\n') {
                        (*cas)[i][pozicia] = '\0';
                    }
                }
                //ked sa dostanem na koniec riadku, tak
                if(znak == '\n') {
                    j++;
                }
            }
        }
    }
    //ak sa vsetko splnilo, tak mi to spravi tento vypis
    printf("Nacitane data.\n");
}

//FUNKCIA S
void funckia_s(char **prispevok, char **autor, char **prezentovanie, char **den, char **cas, int pocet_zaznamov) {

	//PREMENNE
    char datum[8];
    char TypPrezentovania[2];
    int i;

    //VSTUP
    printf("Zadaj datum vo formate rrrrmmdd a typ prezentovania (PD, UD, PP, UP):  \n");
    scanf("%s %s", &datum, &TypPrezentovania);

    //tutok kontrolujem, ci su vytvorene polia
    if (autor == NULL) {
        printf("Polia nie su vytvorene\n");
        return;
    }


    if(strcmp(TypPrezentovania, "PD") == 0 || strcmp(TypPrezentovania, "PP") == 0 || strcmp(TypPrezentovania, "UP") == 0 || strcmp(TypPrezentovania, "UD") == 0 ) {

        for(i = 0; i < pocet_zaznamov; i++) {
            //tuto si kontrolujem ci sa zadany cas a prezentovanie rovna s tym, co je v poli
			if(strcmp(cas[i], datum) == 0 && strcmp(prezentovanie[i], TypPrezentovania) == 0) {
                printf("%s		%20s	%30s\n", den[i], autor[i], prispevok[i]);
            }
        }
    }

    else {
        printf("Pre dany vstup neexistuju zaznamy\n");
    }
}

//FUNKCIA H
void histogram(FILE **file, char **prispevok, char **autor, char **prezentovanie, char **den, char **cas, int *pocet_zaznamov) {

    int UD = 0;
    int UP = 0;
    int PD = 0;
    int PP = 0;
    int i, novy_cas;

    int tento_cas, min, max;

    int a;

    //tuto skontrolujem ci bolo vytvorene pole
     if (autor  == NULL){

         printf("Polia nie su vytvorene.\n");
         return;
     }

     //vrchny vypis histogramu
     printf("   hodina          UP   UD   PP   PD\n");

     //ak sa nas novy cas rovna 8, ale je mensi ako  18, tak zvisime jeho hodnotu  o 2
     for (novy_cas = 0; novy_cas < 6; novy_cas++){

     //znovu si nastavím moje premenne na 0
          UP = 0;
          UD = 0;
          PP = 0;
          PD = 0;

        //vypis dautom
        printf("%02d:00 - %02d:59 :", 8+ (novy_cas*2), 8+ (novy_cas*2)+1);

         for (i = 0; i < pocet_zaznamov; i++){

             //tutok zmenim text na cislo
             tento_cas = atoi(den[i]);

             //tutok si vypocitam rozsah hodnot od min do max
             //800 mi predstavuje 8 hodin
             //200 mi predstavuje 2 hodiny
             min = 800+(novy_cas*200);
             max = 800+((novy_cas+2)*200);

             //najskor si prekonvertujem string na integer a ak sa
             if (tento_cas >= min && tento_cas < max){
                 //potom skontrolujem comu sa to rovna a zvysim hodnotu o 1
                if (strcmp("UD", prezentovanie[i]) == 0){
                    UD++;
                   }
                if (strcmp("UP", prezentovanie[i]) == 0){
                   UP++;
                }
                if (strcmp("PP", prezentovanie[i]) == 0){
                   PP++;
                }
                if (strcmp("PP", prezentovanie[i]) == 0){
                   PD++;
                }
              }
         }
         //tuto vypisujem histogram
         printf("     %d    %d    %d    %d\n", UP, UD, PP, PD);
    }
    //novy riadok
    printf("\n");
}


int main() {
    //tento input sluzi pri  zadavani klavesy na klavesnici
    char input;
    int pocet_zaznamov;

    //toto su premenne pre naplnenie 2d polia
    char **prispevok = NULL, **autor = NULL, **prezentovanie = NULL, **den = NULL, **cas = NULL;
    FILE *file;

    char datum;
    char TypPrezentovania;

    int a;

    char **retazec_pole;

    //vypis funkcii
    printf("| v - program bud vypise data zo suboru, alebo pola\n");
    printf("| n - program na dynamicky alokuje  polia\n");
    printf("| o - program nam porovna zadany vstup s casom a spravy vypis  -  NEFUNGUJE\n");
    printf("| s - program nacita datum a typ prezentovania\n");
    printf("| h - program nam vypise histogram\n");
    printf("| z - program nam nacita vstup a vymaze  -  NEFUNGUJE\n");
    printf("| p - program nam nacita vstup a ulozi ho do array   -  NEFUNGUJE\n");
    printf("| k - dealokuje nam pamat a ukonci program\n");


    //tutok mam ovladanie pomocou case
    while(1) {
            scanf("%c", &input);
            switch(input) {
        case 'v':
            zaznamy(&file, prispevok, autor, prezentovanie, den, cas, &pocet_zaznamov);
            break;
        case 'n':
            nacitanie(&file, &prispevok, &autor, &prezentovanie, &den, &cas, pocet_zaznamov);
            break;
        case 's':
            funckia_s(prispevok, autor, prezentovanie, den, cas, pocet_zaznamov);
            break;
        case 'h':
            histogram(file, prispevok, autor, prezentovanie, den, cas, pocet_zaznamov);
            break;
        case 'k':
                free(*prispevok = NULL);
                *prispevok = NULL;
                free(*autor);
                *autor = NULL;
                free(*prezentovanie);
                *prezentovanie = NULL;
                free(*den);
                *den = NULL;
                free(*cas);
                *cas = NULL;
                exit(0);
        }
    }
    return 0;
}

