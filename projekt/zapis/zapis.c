#include <stdio.h>
#include "zapis.h"

// Nacte od uzivatele udaje o nove jizde
void novy_zapis(struct zapis* f)
{
      
        //  DATUM
        printf("\r\nZadejte cislo aktualniho/dnesniho dne v mesici:  ");

        scanf("%d", &f->datum.den);

        printf("\r\nZadejte cislo aktualniho/dnesniho mesice:  ");

        scanf("%d", &f->datum.mesic);

        printf("\r\nZadejte cislo aktualniho/dnesniho roku:  ");

        scanf("%d", &f->datum.rok);



        //  RIDIC
        printf("\r\nZadejte sve jmeno:  ");
        
        scanf("%s", &f->ridic.jmeno);

        printf("\r\nZadejte sve prijmeni:  ");

        scanf("%s", &f->ridic.prijmeni);

        printf("\r\nZadejte sve ID:  ");

        scanf("%s", &f->ridic.id);



        //  AUTO INFO
        printf("\r\nZadejte SPZ vami pouziteho auta pro zapisovanou jizdu:  ");

        scanf("%s", &f->autoo.auto_spz);

        printf("\r\nZadejte pocet ujetych kolimetru se zapsanym autem za zapisovanou jizdu:  ");
        
        scanf("%d", &f->autoo.najezd);



        //  DOBA LETU..
        printf("\r\nZadejte priblizny zacatek zapisovane jizdy ve formatu XX:XX:  ");

        scanf("%s", &f->doba.zacatek);

        printf("\r\nZadejte priblizny konec zapisovane jizdy ve formatu XX:XX :  ");

        scanf("%s", &f->doba.konec);


        printf("Dekujeme, Vase jizda byla uspesne zapsana a uložena.");


}

// Prida jeden zaznam o jizde na konec souboru data/jizdy.csv
void uloz_zapis_do_csv(struct zapis *f)
{
    FILE *kontrola;
    FILE *soubor;
    int prazdny = 1;

    // otevre soubor pro cteni, aby zjistil, jestli uz existuje a neni prazdny
    kontrola = fopen("data/jizdy.csv", "r");

    if(kontrola != NULL)
    {
        fseek(kontrola, 0, SEEK_END);   // presune na konec souboru

        if(ftell(kontrola) != 0)        // zjisti velikost souboru; kdyz neni 0, hlavicka uz v nem je
        {
            prazdny = 0;
        }

        fclose(kontrola);
    }

    // otevre soubor v rezimu "a" (pridani na konec)
    soubor = fopen("data/jizdy.csv", "a");

    if(soubor == NULL)
    {
        printf("\r\nZapis se nepodarilo ulozit do souboru data/jizdy.csv.\r\n");

        return;
    }

    // u noveho nebo prazdneho souboru zapise nejdriv hlavicku sloupcu
    if(prazdny == 1)
    {
        fprintf(soubor, "den,mesic,rok,jmeno,prijmeni,id,spz,najezd,zacatek,konec\n");
    }

    // zapise vsechny udaje jizdy jako jeden novy radek CSV
    fprintf(soubor, "%d,%d,%d,%s,%s,%s,%s,%d,%s,%s\n", f->datum.den, f->datum.mesic, f->datum.rok, f->ridic.jmeno, f->ridic.prijmeni, f->ridic.id, f->autoo.auto_spz, f->autoo.najezd, f->doba.zacatek, f->doba.konec);

    fclose(soubor); // uzavre soubor
}

// Nacte vsechny ulozene jizdy ze souboru data/jizdy.csv do pole a vrati jejich pocet
int nacti_zapisy_z_csv(struct zapis pole[])
{
    FILE *soubor;
    int pocet = 0;

    // otevre soubor pro cteni
    soubor = fopen("data/jizdy.csv", "r");

    // pokud soubor jeste neexistuje, vrati 0 nactenych zapisu
    if(soubor == NULL)
    {
        return 0;
    }

    // precte a zahodi prvni radek s hlavickou CSV
    fscanf(soubor, "%*s");

    // cte zaznamy ze souboru az do jeho konce
    while(!feof(soubor))
    {
        // %[^,] cte text az po carku; kdyz se nacte vsech 10 hodnot, ulozi se do pole a zvysi se pocet
        if(fscanf(soubor, "%d,%d,%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%s",
                  &pole[pocet].datum.den,
                  &pole[pocet].datum.mesic,
                  &pole[pocet].datum.rok,
                  pole[pocet].ridic.jmeno,
                  pole[pocet].ridic.prijmeni,
                  pole[pocet].ridic.id,
                  pole[pocet].autoo.auto_spz,
                  &pole[pocet].autoo.najezd,
                  pole[pocet].doba.zacatek,
                  pole[pocet].doba.konec) == 10)
        {
            pocet++;
        }
    }

    fclose(soubor); // uzavre soubor

    return pocet;
}
