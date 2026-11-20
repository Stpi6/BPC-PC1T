#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include "zapis/zapis.h"
#include "heslo/heslo.h"

void spocitej_radky(uint8_t *prazdne_radky, int *celkem_radku, uint8_t idpr[], long *zacatek_dat)
{
    FILE *soubor;

    soubor = fopen("data/jizdy.csv", "r");

    *prazdne_radky = 0;

    *celkem_radku = -1;

    int aktualni_znak;

    int predesli_znak = 0;

    if (soubor == NULL)
    {
        *celkem_radku = -3;
    }
    else 
    {
        while((aktualni_znak = fgetc(soubor)) != 'E0F')
        {

            if(aktualni_znak == '\n') *celkem_radku++;

            if(predesli_znak == '\n' && (isspace(aktualni_znak) != 0 || aktualni_znak == '\n')) 
            {
                if(isspace(aktualni_znak) != 0)
                {
                    
                    idpr[*prazdne_radky] = celkem_radku + 1;

                    *prazdne_radky++;

                }
                else
                {

                    idpr[*prazdne_radky] = celkem_radku;

                    *prazdne_radky++;

                }

            }
            else if(predesli_znak == '\n' && celkem_radku == 0)
            {

                *zacatek_dat = ftell(soubor);

            }
            predesli_znak = aktualni_znak;
        }

        fclose(soubor);
    }
    
}
//  Spocita vsechny radky v souboru - prekpoklad je ze prvni radek je zahlavi tabulky - PREPSAT ABY SE RADKY PRICITALI PODLE TOHO JESTLI JE PRVNI ZNAK NA NOVEM RADKU PISMENO ABY NEDOCHAZELO K TOMU ZE SE NEZAPISE POSLEDNI ZNAK A TAK SE RADEK NEPRIPOCETL
//  Vraci taky pocet v longu pocet bajtu ktere se pouziji pro offset ve funkci nacteni_zaznamu

int nacteni_zaznamu(struct zapis f[], int id_struct_pole)
{
    FILE *soubor;

    int u = 0;

    _mkdir("data");

    soubor = fopen("data/zaznamy.csv", "r");

    if(soubor == NULL) return 0;

    for(u = 0; u < id_struct_pole; u++) //  id_struct_pole bude 0 - musí byt system kde do nej nejdriv ulozim pocet radku
    {
        fscanf(soubor, "%d,%d,%d,%32[^,],%32[^,],%6[^,],%8[^,],%d,%5[^,],%5[^\n]\n", &f[u].datum.den, &f[u].datum.mesic, &f[u].datum.rok, f[u].ridic.jmeno, f[u].ridic.prijmeni, f[u].ridic.id, f[u].autoo.auto_spz, &f[u].autoo.najezd, f[u].doba.zacatek, f[u].doba.konec);
    }

    fclose(soubor);

    return 1;
}
//  DOPSAT


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

    uint8_t id_prazdnych_radku[100];

    uint8_t pocet_prazdnych_radku;

    struct zapis jizda[100];

    if(nacti_heslo_ze_souboru(ulozene_heslo) == 1)
    {
        if(prihlaseni(ulozene_heslo) == 0) return 0;
    }

    spocitej_radky(&pocet_prazdnych_radku,&id_struct_pole,id_prazdnych_radku[100],&zacatek_dat);


    if (id_struct_pole < -1)
    {
        printf("\r\nNeco se pokazilo :( Data ze souboru se nepodarilo nacist. Zadejte cokoliv a stisknet ENTER pro ukonceni programu\r\n\n");
        scanf("%32s", jizda->ridic.jmeno);
        return 300;
    }
    else
    {

        //nacteni_zaznamu();

    }


    

    while(1)
    {
        
        printf("\r\nMENU\r\n\n1 - Novy zapis\r\n2 - Upravit stavajici zapis\r\n3 - Smazat zapis\r\n4 - Vypsat zapis/y\r\n5 - Nastavit heslo\r\n6 - konec\r\n\n");

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
                printf("B");

                i = 0;
            break;


        //Smazat zapis - bud podle ciselzapisu nebo vypsat ke kazdemu zapisu ktery jde upravit prijmeni a datum pro lepsi orientaci
            case SMAZAT_ZAPIS:
                system("cls");

                printf("Smazat je mozne nasledujici zapisy: \r\n");

                while(i < id_struct_pole)
                {
                    printf("%d. - %s %s, datum: %d.%d.%d\r\n", i+1, jizda[i].ridic.jmeno, jizda[i].ridic.prijmeni, jizda[i].datum.den, jizda[i].datum.mesic, jizda[i].datum.rok);

                    i++;
                }

                scanf("%d", &i);

                i = 0;
            break;


        //Vypsat zapis/y - orientovat se podle id_struct_pole a podle toho nabidnout pocet zapisu k dispozici - scanf do promenne a podle toho vypsat strukturu
            case VYPSAT_ZAPISY:
                system("cls");
                
                for(int x = 0; x < id_struct_pole; x++)
                {
                    printf("%d. - %s %s, datum: %d.%d.%d\r\n", x+1, jizda[x].ridic.jmeno, jizda[x].ridic.prijmeni, jizda[x].datum.den, jizda[x].datum.mesic, jizda[x].datum.rok);
                }

                scanf("%d", &i);
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
