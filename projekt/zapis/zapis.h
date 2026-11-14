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

void uloz_zapis_do_csv(struct zapis *f);
