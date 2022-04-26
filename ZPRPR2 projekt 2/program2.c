#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MDEBUG

typedef struct autori {
    char meno [200];
    char priezvisko[200];
} meno;


typedef struct Node {
    int id_cislo;
    char nazov_pripsevku[150];
    meno *autori;
    int pocet_autorov;
    char typ_prezentovania[3];
    char cas_prezentovania[9];
    char datum[9];
    struct Node *next;
} node;

//touto funkciu si naplnim meno a priezvisko v mojom linked liste
void meno_cast(int meno, int cast_mena, char *vsetky_mena, char *uloz_to_sem){

    int dlzka = strlen(vsetky_mena);
    int a = 0; //medzery
    int b = 1; //ktore meno to je, ci prve ci jake
    int c = 0; //pozicia
    int i;

    for(i = 0; i < 200; i++){
        uloz_to_sem[i] = '\0';
    }

    char navrat[200];

    //tuto prejdeme cely string
    for (i = 0; i < dlzka; i++){

          if (b == meno && cast_mena == 1 && a == 0 && vsetky_mena[i] != '#'){
            uloz_to_sem[c] = vsetky_mena[i];
            c++;
        }

        if (b == meno && cast_mena == 2 && a > 0 && vsetky_mena[i] != '#'){
            uloz_to_sem[c] = vsetky_mena[i];
            c++;
        }

        //medzera
        if (vsetky_mena[i] == ' '){
            a++;
        }

        //koniec mena
        if (vsetky_mena[i] == '#'){
            a = 0;
            b++;
        }
    }
    return;

}

void funkciaN(FILE **file, node **zaciatok_zaznamu, int *pocet_zaznamov){

    int i = 0; //totok je chceny riadok
    int j = 0; //loop iba
    int n = 0;

    char *lineptr;

    *pocet_zaznamov = 0;

    node *pomocny2;

    char riadok[200]; //tuto citame riadok cely
    char cast_mena[200]; //menucko

    node *current;
    node *pomocny_pointer;

    *file = fopen("OrganizacnePodujatia2.txt", "r");

    if (*file == NULL) {
        printf("Zaznamy neboli nacitane!\n");
        return;
    }

    (*zaciatok_zaznamu) = malloc(sizeof(node));
    pomocny_pointer = (*zaciatok_zaznamu);

    while( fgets(riadok, 200, *file) != NULL) {

        if(i==1) {
            lineptr = strtok(riadok, "\n");
            pomocny_pointer->id_cislo = atoi(riadok);
        }

        else if(i==2) {
            lineptr = strtok(riadok, "\n");
            strcpy(pomocny_pointer->nazov_pripsevku, riadok);
        }

        else if(i==3) {

            for (j = 0; j < 200; j++){

                if (riadok[j] == '#'){
                    n++;
                }
            }

            n++;

            //kredit: matej stancik mi toto dajako vysvetlil
            pomocny_pointer->pocet_autorov = n;
            pomocny_pointer->autori = (meno*)malloc(n * sizeof(meno)); //vytvorime si dynamicke pole autorov

            for (j = 0; j < n; j++){
                meno_cast(j+1,1,riadok, cast_mena);
                strcpy(pomocny_pointer->autori[j].meno, cast_mena);

                meno_cast(j+1,2,riadok, cast_mena);
                strcpy(pomocny_pointer->autori[j].priezvisko, cast_mena);
            }
        }
        else if(i==4) {
            lineptr = strtok(riadok, "\n");
            strcpy(pomocny_pointer->typ_prezentovania, riadok);
        }
        else if(i==5) {
            lineptr = strtok(riadok, "\n");
            strcpy(pomocny_pointer->cas_prezentovania, riadok);
        }
        else if(i==6) {
            lineptr = strtok(riadok, "\n");
            strcpy(pomocny_pointer->datum, riadok);
            *pocet_zaznamov += 1;
            i=0;
            n=0;
            pomocny_pointer->next = malloc(sizeof(node));      //nastavim si pointer next a alokujem mu pamat
            pomocny2 = current;
            current = pomocny_pointer->next;                    //nastavim si pointer na dalsi zoznam
            pomocny_pointer=current;
            continue;
        }

        i++;

    }

    printf("Nacitalo sa %d zaznamov\n", (*pocet_zaznamov));

    current = pomocny2;
    current->next = NULL;
    free(pomocny_pointer);

}

void funkciaV(node **zaciatok_zaznamu){

     int b = 1,j;
     node *pomocny_pointer = (*zaciatok_zaznamu);

     if ( (*zaciatok_zaznamu) == NULL ){
        printf("Prazdny zoznam zaznamov!\n");
        return;
     }

     printf("\n");

    while(pomocny_pointer != NULL) {
        printf("%d.\n", b);
        printf("ID cislo: %d\n", pomocny_pointer->id_cislo);
        printf("Nazov prispevku: %s\n", pomocny_pointer->nazov_pripsevku);
        printf("Mena Autorov: \n");

        for (j = 0; j < pomocny_pointer->pocet_autorov; j++){
            printf("    %d: %s %s\n", j+1, pomocny_pointer->autori[j].meno,pomocny_pointer->autori[j].priezvisko);
        }
        printf("Typ prezentovania: %s\n", pomocny_pointer->typ_prezentovania);
        printf("Cas prezentovania: %s\n", pomocny_pointer->cas_prezentovania);
        printf("Datum: %s\n", pomocny_pointer->datum);
        printf("\n");
        pomocny_pointer=pomocny_pointer->next;
        b++;
    }

}

void funkciaH(FILE **file, node **zaciatok_zaznamu, int *pocet_zaznamov){
    char prezentovanie_vstup[3];

    node *pomocny_pointer = (*zaciatok_zaznamu);

    int i;
    int b = 1,j;

    //za zaciatok  skontrolujem ci este bol vytvoreny spajany zoznam, ak nie, tak program vypise spravu a ukonci funkciu
    if((*zaciatok_zaznamu) == NULL) {
        printf("este nebol vytvoreny Linked List.\n");
        return;
    }

    printf("Zadaj typ prezentovania UP, UD, PP, PD:\n");
    scanf("%s", prezentovanie_vstup);

    //tuto kontrolujem ci sa zadany vstup rovna jednemu z typov prezentovania
    if(strcmp(prezentovanie_vstup, "PD") == 0 || strcmp(prezentovanie_vstup, "PP") == 0 || strcmp(prezentovanie_vstup, "UP") == 0 || strcmp(prezentovanie_vstup, "UD") == 0) {

        while(pomocny_pointer != NULL){
            //tuto porovnavam ci sa zadany vstup rovna typu prezentovania, ak ano, tak to vypise zaznamy
            if(strcmp(prezentovanie_vstup, pomocny_pointer->typ_prezentovania) == 0) {
                printf("%d.\n", b);
                printf("ID cislo: %d\n", pomocny_pointer->id_cislo);
                printf("Nazov prispevku: %s\n", pomocny_pointer->nazov_pripsevku);

                printf("Mena Autorov: \n");

                for (j = 0; j < pomocny_pointer->pocet_autorov; j++){
                    printf("    %d: %s %s\n", j+1, pomocny_pointer->autori[j].meno,pomocny_pointer->autori[j].priezvisko);
                }

                printf("Typ prezentovania: %s\n", pomocny_pointer->typ_prezentovania);
                printf("Cas prezentovania: %s\n", pomocny_pointer->cas_prezentovania);
                printf("Datum: %s\n", pomocny_pointer->datum);
                printf("\n");
                b++;
            }
            pomocny_pointer=pomocny_pointer->next;
        }
    }
    else {
        //ak bol zadany zly typ prezentovania, program vypise nasledujucu spravu a ukonci funckiu
        printf("Pre typ: %s nie su ziadne zaznamy\n", prezentovanie_vstup);
        return;
    }
    printf("\n");
}

void funkciaA(FILE **file, node **zaciatok_zaznamu, int *pocet_zaznamov){

    char IDCislo_vstup[11];
    char prezentovanie_vstup[3];
    char IDkonvert[11];
    char ulozenaHodnota[3];
    node *pomocny_pointer = (*zaciatok_zaznamu);
    int i;
    int b = 1,j;

    //za zaciatok  skontrolujem ci este bol vytvoreny spajany zoznam, ak nie, tak program vypise spravu a ukonci funkciu
    if((*zaciatok_zaznamu) == NULL) {
        printf("este nebol vytvoreny Linked List.\n");
        return;
    }


    printf("zadaj ID cislo delitelne 15 a typ prezentovania: \n");
    for(;;) {

        scanf("%s %s", IDCislo_vstup, prezentovanie_vstup);

        //porovnam ci sa zadany vstup zhoduje s typmi prezentovania
        if (strcmp(prezentovanie_vstup, "PD") == 0 || strcmp(prezentovanie_vstup, "PP") == 0 || strcmp(prezentovanie_vstup, "UP") == 0 || strcmp(prezentovanie_vstup, "UD") == 0) {

            if ( atoi(IDCislo_vstup) % 15 == 0) {
                   break;
               }
        }

         printf("Zadane udaje nie su korektne, zadaj novy retazec: ");
    }


    while (pomocny_pointer->next != NULL){

            //prekonvertujem si z integeru na string
            itoa(pomocny_pointer->id_cislo, IDkonvert,10);
          //najskor porovnam ci sa zhoduju IDcka
          if (strcmp(IDCislo_vstup, IDkonvert) == 0){

              //ulozim si typ prezentovania do pomocnej premennej, aby som ju potom mohol vypisat
              strcpy(ulozenaHodnota, pomocny_pointer->typ_prezentovania);

              //prekopirujem zadany typ prezentovania do typu prezentovania v LL.
              strcpy(pomocny_pointer->typ_prezentovania, prezentovanie_vstup);

              //vypisem text
              printf("Prispevok s nazvom %s sa bude prezentovat %s [%s]\n", pomocny_pointer->nazov_pripsevku, pomocny_pointer->typ_prezentovania, ulozenaHodnota);

          }
        pomocny_pointer = pomocny_pointer->next;
    }

}

void funkciaR(FILE **file, node **zaciatok_zaznamu, int *pocet_zaznamov) {
    /*char IDCislo_vstup[11];
    char prezentovanie_vstup[3];
    char IDkonvert[11];
    char ulozenaHodnota[3];
    node *pomocny_pointer = (*zaciatok_zaznamu);
    int i;
    int b = 1,j;

    //za zaciatok  skontrolujem ci este bol vytvoreny spajany zoznam, ak nie, tak program vypise spravu a ukonci funkciu
    if((*zaciatok_zaznamu) == NULL) {
        printf("este nebol vytvoreny Linked List.\n");
        return;
    }*/
}

void funkciaP(FILE **file, node **zaciatok_zaznamu, int *pocet_zaznamov) {
    node *NovyNode;
    NovyNode = malloc(sizeof(node));

    int pozicia;
    char array[150];

    char NoveMeno[200];
    char cast_mena[200];

    node *pomoc1;
    node *pomoc2;

    char NovePriezvisko[150];

    int i,j;
    int n=0;



    printf("Zadajte poziciu: ");
    scanf("%d", &pozicia);

    printf("Zadaj id cislo: ");
    scanf("%d", &(NovyNode->id_cislo));

    //tuto vycistim buffer
    fflush(stdin);
    printf("Zadaj nazov prispevku: ");
    gets(NovyNode->nazov_pripsevku);

    NovyNode->autori = malloc(sizeof(meno));
    printf("Zadaj meno autora/ov: ");
    gets(NoveMeno);

    for (j = 0; j < 200; j++){

        if (NoveMeno[j] == '#'){

            n++;
        }

        //znak konca stringu
        if(NoveMeno[j] == '\0') {
            break;
        }
    }
    n++;
    NovyNode->pocet_autorov = n;
    NovyNode->autori = (meno*)malloc(n * sizeof(meno)); //vytvorime si dynamicke pole autorov

    for (j = 0; j < n; j++){
        //rozdelenie mena
        meno_cast(j+1,1,NoveMeno, cast_mena);
        strcpy(NovyNode->autori[j].meno, cast_mena);

        //rozdelenie priezviska
        meno_cast(j+1,2,NoveMeno, cast_mena);
        strcpy(NovyNode->autori[j].priezvisko, cast_mena);
    }

    printf("zadaj typ prezentovania (UP, UD, PD, PP): " );
    scanf("%s", NovyNode->typ_prezentovania);

    printf("Zadaj cas prezentovania vo formate: ");
    scanf("%s", NovyNode->cas_prezentovania);

    printf("Zadaj datum prezentovania vo formate rrrrmmdd: ");
    scanf("%s", NovyNode->datum);

    //ak neboli vytvorene zaznamy
    int k=1;


    if(*pocet_zaznamov == 0) {
        *zaciatok_zaznamu = NovyNode;
        (*zaciatok_zaznamu)->next = NULL;
    }
    else {
        pomoc1 = *zaciatok_zaznamu;
        while(pomoc1 != NULL) {
            //pre prvu poziciu
            if(1 == pozicia && k==1) {
                NovyNode->next = *zaciatok_zaznamu;
                *zaciatok_zaznamu = NovyNode;
                break;
            }
            //pre poslednu poziciu
            else if(pomoc1->next == NULL) {
                pomoc1->next = NovyNode;
                NovyNode->next = NULL;
                break;
            }
            //pre medzi a poslednou poziciou
            else {
                if(k == pozicia-1) {
                    pomoc2 = pomoc1->next;
                    pomoc1->next = NovyNode;
                    NovyNode->next = pomoc2;
                    break;
                }

            } k++;
            pomoc1 = pomoc1->next;
        }
    }
*pocet_zaznamov++;




return;
}

int main(){

    //input sluzi pri  zadavani klavesy na klavesnici
    char input;

    FILE *file = NULL;
    node *spajany_zoznam = NULL;
    int pocet_zaznamov = 0;

    node *temporary;

    // vypis funkcii
    printf("| n - prikaz nacita zaznamy zo zaznamov seminarov\n");
    printf("| v - vypis celeho spajaneho zoznamu\n");
    printf("| p - prikaz prida zaznam do spajaneho zoznamu - PRACUJE SA NA TOM \n");
    printf("| z - prikaz zmaze zaznam podla zadaneho mena - NEFUNGUJE\n");
    printf("| h - vyhlada a vypise vestky polozky zo zaznamu\n");
    printf("| a - aktualizuje (zmeni) typ prezentovania prispevku\n");
    printf("| r - prikaz prehodi dva zaznamy v spajanom zozname - NEFUNGUJE \n");
    printf("| k - ukonci program\n");

    // tutok mam ovladanie pomocou case
    while (1)
    {
        scanf("%c", &input);
        switch (input)
        {
        case 'v':
            funkciaV(&spajany_zoznam);
            break;
        case 'n':
            funkciaN(&file, &spajany_zoznam, &pocet_zaznamov);
            break;
        case 'p':
            funkciaP(&file, &spajany_zoznam, &pocet_zaznamov);
            break;
        /*case 'z':
            funkcia();
            break;*/
        case 'h':
            funkciaH(&file, &spajany_zoznam, &pocet_zaznamov);
            break;
        case 'a':
            funkciaA(&file, &spajany_zoznam, &pocet_zaznamov);
            break;
        /*case 'r':
            funkciaR(&file, &spajany_zoznam, &pocet_zaznamov);
            break;*/
        case 'k':
            if(pocet_zaznamov != 0) {
                temporary = spajany_zoznam;
                while(spajany_zoznam != NULL){
                    free(spajany_zoznam->autori);
                    temporary = spajany_zoznam->next;
                    free(spajany_zoznam);
                    spajany_zoznam = temporary;
                    printf("DEBUG: \n");
                }
                if(file != NULL) {
                    fclose(file);
                }
            }
            return 0;
        }
    }

    return 0;
}
