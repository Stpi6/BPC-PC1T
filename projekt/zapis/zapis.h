#pragma once

//POLE STRUKTUR A FOR PRISTUP PRES GLOBAL I SKRZE POINTER
struct zapis
{

    struct driver
    {

        char jmeno[33];

        char prijmeni[33];

        char id[7];

    } ridic;

    
    struct car
    {
        char auto_spz[9];

        int najezd;

    } autoo;
    

    struct time
    {

        char zacatek[6];

        char konec[6];

    } doba;

   

     struct date
    {
            int den;

            int mesic;

            int rok;

    } datum;

};

void novy_zapis(struct zapis* f);
// nacte od uzivatele udaje o jedne jizde do struktury

void uloz_zapis_do_csv(struct zapis *f);
// prida jeden zapis na konec souboru data/jizdy.csv

void uloz_upraveny_zapis_do_csv(struct zapis f[], int celkem_radku, int idpr[]);
// Prepise cely soubor i se zmenou

int nacti_zapisy_z_csv(struct zapis pole[]);
// nacte ulozene jizdy ze souboru data/jizdy.csv do pole a vrati jejich pocet
