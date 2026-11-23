#include <stdio.h>
#include <ctype.h>
#include "pomocne.h"

void spocitej_radky(int *prazdne_radky, int *celkem_radku, int idpr[], long *zacatek_dat)
{
    FILE *soubor;

    soubor = fopen("data/jizdy.csv", "r");

    *prazdne_radky = 0;

    *celkem_radku = 0;

    int aktualni_znak;

    int predesli_znak = 0;

    if (soubor == NULL)
    {
        *celkem_radku = -3;
    }
    else 
    {

        while ((aktualni_znak = fgetc(soubor)) != '\n' && aktualni_znak != EOF); // Preskoci hlavicku souboru

        *zacatek_dat = ftell(soubor); // Zjisti pozici v souboru, kde zacina prvni zaznam - zatím NENI pouzivano

        predesli_znak = '\n'; // Nastaveno aby i prvni radek mohl byt pocitan jako prazdny radek
        
        
        while((aktualni_znak = fgetc(soubor)) != EOF) // Dokud neni konec souboru, cte po jednitlivych znaacich 
        {

            if(predesli_znak == '\n' && isspace(aktualni_znak) == 0) // Kdyz je predesl znak novy radek a aktualni znak je nejaky znak/cislo , tak se inkrementuje pocet radku
            {
                (*celkem_radku)++;
            }

            if(predesli_znak == '\n' && isspace(aktualni_znak) != 0) // Kdyz je predesl znak novy radek a aktualni znak je bílý znak, tak se inkrementuje pocet prazdnych radku a cislo radku se ulozi do pole idpr
            {

                    (*celkem_radku)++;

                    idpr[*prazdne_radky] = *celkem_radku;

                    (*prazdne_radky)++;

            }
                    
            predesli_znak = aktualni_znak;
        }

        idpr[*prazdne_radky] = 0; // na konec se ulozi do pole 0 aby se nemohlo stat ze se hodnota v pameti bude nahodou rovnat cislu nacitaneho radku ve funkci nacteni_zaznamu a preskoci se zaznam, ktery by se nemel preskocit

        fclose(soubor);
    }
    
}
//  Spocita vsechny radky v souboru - prekpoklad je ze prvni radek je zahlavi tabulky
// Vrati v longu zacatek_dat pozici v souboru, kde zacina prvni zaznam

int nacteni_zaznamu(struct zapis f[], int id_struct_pole, long offset, int idpr[])

{
    FILE *soubor;

    int o = 0;

    int c;

    soubor = fopen("data/jizdy.csv", "r");

    if(soubor == NULL) return 0;

    while ((c = fgetc(soubor)) != '\n' && c != EOF); // Preskoci hlavicku souboru

    for(int u = 0; u < id_struct_pole; u++) 
    {
        if ((u + 1) == idpr[o]) // Pokud se vypisovany zaznam rovna id prazdneho radku, preskoci ho a inkrementuje o
        {
            o++;
        }
        else // Jinak nacita zaznamy do struktury zapis
        {

            fscanf(soubor, "%d,%d,%d,%32[^,],%32[^,],%6[^,],%8[^,],%d,%5[^,],%5[^\n]", &f[u].datum.den, &f[u].datum.mesic, &f[u].datum.rok, f[u].ridic.jmeno, f[u].ridic.prijmeni, f[u].ridic.id, f[u].autoo.auto_spz, &f[u].autoo.najezd, f[u].doba.zacatek, f[u].doba.konec);
        
        }

        while ((c = fgetc(soubor)) != '\n' && c != EOF); // Dojede nakonec radku a preskoci ho, aby se nacitalo od zacatku dalsiho radku
    }

    fclose(soubor);

    return 1;
}
//  Nacte vsechny zaznamy ze souboru data/jizdy.csv do struktury zapis, preskoci prazdne radky a vrati 1 pokud se vse podarilo nactit, jinak 0

int kontrola_obsahu_zapisu(int pocet_prazdnych_radku, int i, int idpr[])
{
    for(int n = 0; n < pocet_prazdnych_radku; n++)
    {
        if(i == idpr[n])
        {
            printf("\r\nZadany zapis je smazany/poskozen a nelze ho upravit.\r\n");
            i = -1;
            return 0;
        }
        else return 1;

    }


   
}
//  Zkontroluje jesli zaznam, ktery se ma upravit neni smazany/poskozen a vrati 0 pokud je smazany/poskozen a 1 pokud je v poradku
