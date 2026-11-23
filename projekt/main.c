#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include "zapis/zapis.h"
#include "heslo/heslo.h"

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

void vypis_zaznamy(int id_radku, struct zapis jizda[], int id_prazdnych_radku[])
{

    int i = 0;

    for(int x = 0; x < id_radku; x++)
    {

        if(x + 1 == id_prazdnych_radku[i])
        {
            i++;
            printf("%d. - ZAPIS SMAZAN/POSKOZEN\r\n", x+1);
        }
                    
        else
        printf("%d. - %s %s, datum: %d.%d.%d\r\n", x+1, jizda[x].ridic.jmeno, jizda[x].ridic.prijmeni, jizda[x].datum.den, jizda[x].datum.mesic, jizda[x].datum.rok);
    }

}
//  Vypise vsechny zaznamy ze struktury zapis, u prazdnych radku vypise informaci ze zaznam byl smazan/poskozen

void smazani_zapisu(struct zapis f[], int celkem_radku, int idpr[], int smazany_radek, int pocet_prazdnych_radku)
{
    FILE *soubor;

    soubor = fopen("data/jizdy.csv", "w");

    if (soubor == NULL) printf("\r\nZapis se nepodarilo ulozit do souboru data/jizdy.csv.\r\n");

    else
    {

    idpr[pocet_prazdnych_radku] = smazany_radek;

    idpr[pocet_prazdnych_radku + 1] = 0;

    while(idpr[pocet_prazdnych_radku] < idpr[pocet_prazdnych_radku - 1] && pocet_prazdnych_radku > 0)
    {

        idpr[pocet_prazdnych_radku - 1] = idpr[pocet_prazdnych_radku] + idpr[pocet_prazdnych_radku - 1];

        idpr[pocet_prazdnych_radku] = idpr[pocet_prazdnych_radku - 1] - idpr[pocet_prazdnych_radku];

        idpr[pocet_prazdnych_radku -1] = idpr[pocet_prazdnych_radku - 1] - idpr[pocet_prazdnych_radku];

        pocet_prazdnych_radku--;

    }

    fprintf(soubor, "den,mesic,rok,jmeno,prijmeni,id,spz,najezd,zacatek,konec\n");

    int e = 0;

    for (int u = 0; u < celkem_radku; u++)
    { 
        if (u + 1 == idpr[e])
        {
            fprintf(soubor, "\t%d,%d,%d,%s,%s,%s,%s,%d,%s,%s\n", f[u].datum.den, f[u].datum.mesic, f[u].datum.rok, f[u].ridic.jmeno, f[u].ridic.prijmeni, f[u].ridic.id, f[u].autoo.auto_spz, f[u].autoo.najezd, f[u].doba.zacatek, f[u].doba.konec);
            
            e++;
        }
        

         else   fprintf(soubor, "%d,%d,%d,%s,%s,%s,%s,%d,%s,%s\n", f[u].datum.den, f[u].datum.mesic, f[u].datum.rok, f[u].ridic.jmeno, f[u].ridic.prijmeni, f[u].ridic.id, f[u].autoo.auto_spz, f[u].autoo.najezd, f[u].doba.zacatek, f[u].doba.konec);

                
    }
    }

    fclose(soubor);


    
}

void upraveni_zaznamu(struct zapis* f)
{
    printf("Zadejte cislo podle toho, jakou kategorii zapisu chcete upravit: \r\n1 - Datum\r\n2 - Cas\r\n3 - Ridic\r\n4 -Auto\r\n\n     ");

    int l;

    scanf("%d", &l);

    switch (l)
    {
        // Upravit datum
        case 1:

            printf("\r\nZadejte cislo aktualniho/dnesniho dne v mesici:  ");

            scanf("%d", &f->datum.den);

            printf("\r\nZadejte cislo aktualniho/dnesniho mesice:  ");

            scanf("%d", &f->datum.mesic);

            printf("\r\nZadejte cislo aktualniho/dnesniho roku:  ");

            scanf("%d", &f->datum.rok);

        break;

         // Upravit čas
        case 2:
                   
            printf("\r\nZadejte priblizny zacatek zapisovane jizdy ve formatu XX:XX:  ");

            scanf("%5s", &f->doba.zacatek);

            printf("\r\nZadejte priblizny konec zapisovane jizdy ve formatu XX:XX :  ");

            scanf("%5s", &f->doba.konec);

        break;

        // Upravit řidiče
        case 3:

            printf("\r\nZadejte sve jmeno:  ");
        
            scanf("%32s", &f->ridic.jmeno);

            printf("\r\nZadejte sve prijmeni:  ");

            scanf("%32s", &f->ridic.prijmeni);

            printf("\r\nZadejte sve ID:  ");

            scanf("%6s", &f->ridic.id);    
                    
        break;

        // Upravit auto
        case 4:

            printf("\r\nZadejte SPZ vami pouziteho auta pro zapisovanou jizdu:  ");

            scanf("%8s", &f->autoo.auto_spz);

            printf("\r\nZadejte pocet ujetych kolimetru se zapsanym autem za zapisovanou jizdu:  ");
        
            scanf("%d", &f->autoo.najezd);            
            
        break;
                    
        default:
                        printf("Nejedna se o platnou volbu. Budete presmerovani zpet do menu.\r\n");

        break;
    }

    printf("Dekujeme, Vase zmena byla uspesne ulozena.");
}
// Upravi konkretni data vybraneho zaznamu


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




enum menu { NOVY_ZAPIS = 1, UPRAVIT_ZAPIS, SMAZAT_ZAPIS, VYPSAT_ZAPISY, NASTAVIT_HESLO, KONEC };

int main()
{

    //MAZANI TERMINALU FCE????

    //Zjistit pokud heslo existuje a zavolat prihlaseni if kontrola_pozadavku_hesla 

    char heslo[33];

    char ulozene_heslo[33];

    enum menu vybrano;

    int i = 0; //   NEMAM TUSENI CO TU DELA

    int id_struct_pole;

    long zacatek_dat = 0;

    int id_prazdnych_radku[100] = {-1};

    int pocet_prazdnych_radku;

    struct zapis jizda[100];

    if(nacti_heslo_ze_souboru(ulozene_heslo) == 1)
    {
        if(prihlaseni(ulozene_heslo) == 0) return 0;
    }

    spocitej_radky(&pocet_prazdnych_radku,&id_struct_pole,id_prazdnych_radku,&zacatek_dat);

    if (id_struct_pole == -3)
    {
        printf("\r\nNeco se pokazilo :( Data ze souboru se nepodarilo nacist. Zadejte cokoliv a stisknet ENTER pro ukonceni programu\r\n\n");
        scanf("%32s", jizda->ridic.jmeno);
        return 300;
    }
    else
    {

        nacteni_zaznamu(jizda, id_struct_pole, zacatek_dat, id_prazdnych_radku);


    }

        //id_struct_pole = nacti_zapisy_z_csv(jizda); ZMENA CO SE ZRUSILA MERGENUTIM
    

    while(1)
    {
        
        printf("\r\nMENU\r\n\n1 - Novy zapis\r\n2 - Upravit stavajici zapis\r\n3 - Smazat zapis\r\n4 - Vypsat zapis/y\r\n5 - Nastavit heslo\r\n6 - Konec\r\n\n");

        scanf("%d",&vybrano);

        //if(isdigit(vybrano_menu) > 0)
        //{ ZJISTIT KDE JE CHYBA
        
        // CHYBA PRI ZADANI CISEL MISTO PISMEN
        
            switch (vybrano) {

        //Novy zapis - prepsat tak aby i po smazani zapisu uprostred se novy zapis zapsal do prvni volne bunky a pak aby pokracoval v zapisovani postupne
            case NOVY_ZAPIS:
                system("cls");
                novy_zapis(&jizda[id_struct_pole]);
                uloz_zapis_do_csv(&jizda[id_struct_pole]);

                // printf("\r\nDatum: %d.%d.%d\r\nJmeno ridice: %s\r\nPrijmeni ridice: %s\r\nID ridice: %s\r\nSPZ auta: %s\r\nNajezd auta: %d\r\nDoba jizdy: %s - %s", jizda[id_struct_pole].datum.den, jizda[id_struct_pole].datum.mesic, jizda[id_struct_pole].datum.rok, jizda[id_struct_pole].ridic.jmeno, jizda[id_struct_pole].ridic.prijmeni, jizda[id_struct_pole].ridic.id, jizda[id_struct_pole].autoo.auto_spz, jizda[id_struct_pole].autoo.najezd, jizda[id_struct_pole].doba.zacatek, jizda[id_struct_pole].doba.konec);

                id_struct_pole++;

            break;


        //Upravit stavajici zapis - bud podle ciselzapisu nebo vypsat ke kazdemu zapisu ktery jde upravit prijmeni  a datum pro lepsi orientaci
            case UPRAVIT_ZAPIS:
                system("cls");

                printf("Upravit je mozne nasledujici zapisy: \r\n");
                
                spocitej_radky(&pocet_prazdnych_radku,&id_struct_pole,id_prazdnych_radku,&zacatek_dat);

                nacteni_zaznamu(jizda, id_struct_pole, zacatek_dat, id_prazdnych_radku);

                vypis_zaznamy(id_struct_pole, jizda, id_prazdnych_radku);

                printf("\r\nZadejte cislo zapisu, ktery chcete upravit: \r\n");

                scanf("%d", &i);

                if(kontrola_obsahu_zapisu(pocet_prazdnych_radku, i, id_prazdnych_radku) == 1)
                {
                    i = i - 1;
                    upraveni_zaznamu(&jizda[i]);
                    uloz_upraveny_zapis_do_csv(jizda, id_struct_pole, id_prazdnych_radku);
                }
                else
                {
                    novy_zapis(&jizda[i]);
                    uloz_upraveny_zapis_do_csv(jizda, id_struct_pole, id_prazdnych_radku);
                }
                

                i = 0;
            break;


        //Smazat zapis - bud podle ciselzapisu nebo vypsat ke kazdemu zapisu ktery jde upravit prijmeni a datum pro lepsi orientaci
            case SMAZAT_ZAPIS:
                system("cls");

                printf("Smazat je mozne nasledujici zapisy: \r\n");

                spocitej_radky(&pocet_prazdnych_radku,&id_struct_pole,id_prazdnych_radku,&zacatek_dat);

                nacteni_zaznamu(jizda, id_struct_pole, zacatek_dat, id_prazdnych_radku);

                vypis_zaznamy(id_struct_pole, jizda, id_prazdnych_radku);

                printf("Zadejte cislo zapisu, ktery chcete smazat:  ");

                scanf("%d", &i);

                smazani_zapisu(jizda, id_struct_pole, id_prazdnych_radku, i, pocet_prazdnych_radku);

                i = 0;
            break;


        //Vypsat zapis/y - orientovat se podle id_struct_pole a podle toho nabidnout pocet zapisu k dispozici - scanf do promenne a podle toho vypsat strukturu
            case VYPSAT_ZAPISY:
                system("cls");

                spocitej_radky(&pocet_prazdnych_radku,&id_struct_pole,id_prazdnych_radku,&zacatek_dat);

                nacteni_zaznamu(jizda, id_struct_pole, zacatek_dat, id_prazdnych_radku);

                vypis_zaznamy(id_struct_pole, jizda, id_prazdnych_radku);

                printf("\r\nChcete blizsi informace o nejakem ze zapisu?\r\nANO - 1\r\nNE - 0\r\n\n     ");

                scanf("%d", &i);

                if(i == 1)
                {
                    printf("\r\nVyberte cislo zaznamu:  ");

                    scanf("%d", &i);

                    if(i > id_struct_pole)
                    {

                        printf("\r\nNevybrali jste spravnou moznost. Budete presmerovani do menu.\r\n");

                    }

                    else if (kontrola_obsahu_zapisu(pocet_prazdnych_radku, i, id_prazdnych_radku) == 1)
                    {
                        i = i - 1;

                        printf("\r\nDetail zaznamu cislo: %d\r\n\nDatum - %d.%d.%d\r\nCas - od %s do %s\r\nRidic - %s %s\r\nAuto - SPZ: %s\r\n     - Najezd: %d\r\n", i + 1, jizda[i].datum.den, jizda[i].datum.mesic, jizda[i].datum.rok, jizda[i].doba.zacatek, jizda[i].doba.konec, jizda[i].ridic.jmeno, jizda[i].ridic.prijmeni, jizda[i].autoo.auto_spz, jizda[i].autoo.najezd);
                    }
                    
                }

                

                i = 0;

            break;


        //Nastavit Heslo
            case NASTAVIT_HESLO:
            system("cls");
            while (1)
            {
        
            //smazani terminalu

                printf("Zadejte silne heslo - pozadavky: \r\nminimalne 8 a maximalne 32 znaku\r\nminimalne 1 velke pismeno\r\nminimalne 1 cislo\r\nminimalne 1 specialni znak\r\n(Pro navrat zpet do MENU zadejte 6)\r\n\nMoje heslo: ");

                scanf("%s", &heslo);
            
                if(zkouska_delky(heslo) == 0 && heslo[0] == '6' && heslo[1] == '\0') break;
            
                else if(zkouska_delky(heslo) == 0) printf("\r\nHeslo je moc kratke.\r\n");            

                else
                {
                    if(kontrola_pozadavku_hesla(heslo) == 1) 
                    {
                        printf("\r\nHeslo bylo nastaveno a ulozeno\r\n");

                        ulozeni_hesla(heslo, ulozene_heslo);

                        uloz_heslo_do_souboru(ulozene_heslo);

                        //printf("\r\n%s\r\n", ulozene_heslo); PRO KONTROLU 

                        break;
                    }
                    else printf("\r\nHeslo nesplnuje pozadavky.\r\n");

                }

            }
            break;


        //Konec
            case KONEC:
            
            return 6;

            default:

            printf("Vyberte jednu z nabizenych moznosti  %d", vybrano);            

            break;
            

        }
    
    //}

    //else printf("Vyberte jednu z nabizenych moznosti  %s", vybrano_menu);

        
    }

   return 0;
}
