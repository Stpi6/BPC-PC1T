#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <direct.h>
#include "heslo.h"

int zkouska_delky(char zk[])
{
    int x = 0;

    while(zk[x] != '\0')
    {
        x++;

    }

    if(x < 8) return 0;

    else return x;
}
// return x - splnuje           return 0 - nesplnuje 

int kontrola_pozadavku_hesla(char kon_heslo[])
{
        int cislo = 0;

        int velke_pismeno = 0;

        int specialni_znak = 0;

        for(int i = 0; i <= zkouska_delky(kon_heslo); i++)
        {
            if(specialni_znak != 1 &&((kon_heslo[i] >= '!' && kon_heslo[i] <= '/') || (kon_heslo[i] >= ':' && kon_heslo[i] <= '@') || (kon_heslo[i] >= '[' && kon_heslo[i] <= 96) || (kon_heslo[i] >= 123 && kon_heslo[i] <= 126)))
            {
                specialni_znak = 1;
            }

            if(cislo != 1 && isdigit(kon_heslo[i]) > 0)
            {
                cislo = 1;
            }

            if(velke_pismeno != 1 && (kon_heslo[i] >= 'A' && kon_heslo[i] <= 'Z'))
            {
                velke_pismeno = 1;
            }


        }

        if(specialni_znak > 0 && cislo > 0 && velke_pismeno > 0) 
        {
            return 1;

        }
        else return 0;

}
// return 1 - splnuje           return 0 - nesplnuje

void ulozeni_hesla(char zapsane[], char ulozene[])
{

    int h = 0;

    while(h <= zkouska_delky(zapsane))
    {
        ulozene[h] = zapsane[h];

        h++;
    } 

}
// ulozi napsane heslo do ulozene_heslo[]

void uloz_heslo_do_souboru(char ulozene[])
{
    FILE *soubor;

    _mkdir("data");

    soubor = fopen("data/heslo.txt", "w");

    if(soubor == NULL)
    {
        printf("\r\nHeslo se nepodarilo ulozit do souboru data/heslo.txt.\r\n");

        return;
    }

    fprintf(soubor, "%s\n", ulozene);

    fclose(soubor);
}

int nacti_heslo_ze_souboru(char ulozene[])
{
    FILE *soubor;

    _mkdir("data");

    soubor = fopen("data/heslo.txt", "r");

    if(soubor == NULL) return 0;

    if(fscanf(soubor, "%32s", ulozene) != 1)
    {
        fclose(soubor);

        return 0;
    }

    fclose(soubor);

    return 1;
}

int prihlaseni(char ulozene[])
{
    char zadane[33];

    while(1)
    {
        printf("\r\nZadejte heslo (Pro konec zadejte 6): ");

        scanf("%32s", zadane);

        if(zadane[0] == '6' && zadane[1] == '\0') return 0;

        if(strcmp(zadane, ulozene) == 0) return 1;

        printf("\r\nNespravne heslo.\r\n");
    }
}
