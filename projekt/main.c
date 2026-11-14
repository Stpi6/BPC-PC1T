#include <stdio.h>
#include <ctype.h>
#include "zapis/zapis.h"
#include "heslo/heslo.h"

int main()
{

    //MAZANI TERMINALU FCE????

    //Zjistit pokud heslo existuje a zavolat prihlaseni if kontrola_pozadavku_hesla 

    char heslo[33];

    char ulozene_heslo[33];

    int vybrano_menu;

    int i = 0; //   NEMAM TUSENI CO TU DELA

    int id_struct_pole = 0;

    struct zapis jizda[100];

    if(nacti_heslo_ze_souboru(ulozene_heslo) == 1)
    {
        if(prihlaseni(ulozene_heslo) == 0) return 0;
    }

    while(1)
    {
        
        printf("\r\nMENU\r\n\n1 - Novy zapis\r\n2 - Upravit stavajici zapis\r\n3 - Smazat zapis\r\n4 - Vypsat zapis/y\r\n5 - Nastavit heslo\r\n6 - konec\r\n\n");

        scanf("%d",&vybrano_menu);

        //if(isdigit(vybrano_menu) > 0)
        //{ ZJISTIT KDE JE CHYBA
        
        // CHYBA PRI ZADANI CISEL MISTO PISMEN
        
            switch (vybrano_menu) {

        //Novy zapis - prepsat tak aby i po smazani zapisu uprostred se novy zapis zapsal do prvni volne bunky a pak aby pokracoval v zapisovani postupne
            case 1:
                system("cls");
                novy_zapis(&jizda[id_struct_pole]);
                uloz_zapis_do_csv(&jizda[id_struct_pole]);

                printf("\r\nDatum: %d.%d.%d\r\nJmeno ridice: %s\r\nPrijmeni ridice: %s\r\nID ridice: %s\r\nSPZ auta: %s\r\nNajezd auta: %d\r\nDoba jizdy: %s - %s", jizda[id_struct_pole].datum.den, jizda[id_struct_pole].datum.mesic, jizda[id_struct_pole].datum.rok, jizda[id_struct_pole].ridic.jmeno, jizda[id_struct_pole].ridic.prijmeni, jizda[id_struct_pole].ridic.id, jizda[id_struct_pole].autoo.auto_spz, jizda[id_struct_pole].autoo.najezd, jizda[id_struct_pole].doba.zacatek, jizda[id_struct_pole].doba.konec);

                id_struct_pole++;

            break;


        //Upravit stavajici zapis - bud podle ciselzapisu nebo vypsat ke kazdemu zapisu ktery jde upravit prijmeni  a datum pro lepsi orientaci
            case 2:
                system("cls");
                printf("B");

                i = 0;
            break;


        //Smazat zapis - bud podle ciselzapisu nebo vypsat ke kazdemu zapisu ktery jde upravit prijmeni a datum pro lepsi orientaci
            case 3:
                system("cls");
                printf("C");

                i = 0;
            break;


        //Vypsat zapis/y - orientovat se podle id_struct_pole a podle toho nabidnout pocet zapisu k dispozici - scanf do promenne a podle toho vypsat strukturu
            case 4:
                system("cls");
                printf("D");

                i = 0;
            break;


        //Nastavit Heslo
            case 5:
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
            case 6:
            
            return 6;

            default:

            printf("Vyberte jednu z nabizenych moznosti  %d", vybrano_menu);            

            break;
            

        }
    
    //}

    //else printf("Vyberte jednu z nabizenych moznosti  %s", vybrano_menu);

        
    }

   return 0;
}
