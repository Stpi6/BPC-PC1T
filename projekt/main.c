#include <stdio.h>
#include <stdlib.h>
#include "zapis/zapis.h"
#include "heslo/heslo.h"
#include "pomocne/pomocne.h"
#include "vypis/vypis.h"
#include "uprava/uprava.h"
#include "mazani/mazani.h"

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
