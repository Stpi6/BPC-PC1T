#include <stdio.h>
#include <ctype.h>

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
void smazani_zapisu(

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

                novy_zapis(&jizda[id_struct_pole]);    

                printf("\r\nDatum: %d.%d.%d\r\nJmeno ridice: %s\r\nPrijmeni ridice: %s\r\nID ridice: %s\r\nSPZ auta: %s\r\nNajezd auta: %d\r\nDoba jizdy: %s - %s", jizda[id_struct_pole].datum.den, jizda[id_struct_pole].datum.mesic, jizda[id_struct_pole].datum.rok, jizda[id_struct_pole].ridic.jmeno, jizda[id_struct_pole].ridic.prijmeni, jizda[id_struct_pole].ridic.id, jizda[id_struct_pole].autoo.auto_spz, jizda[id_struct_pole].autoo.najezd, jizda[id_struct_pole].doba.zacatek, jizda[id_struct_pole].doba.konec);

                id_struct_pole++;

            break;


        //Upravit stavajici zapis - bud podle ciselzapisu nebo vypsat ke kazdemu zapisu ktery jde upravit prijmeni  a datum pro lepsi orientaci
            case 2:
                printf("B");

                i = 0;
            break;


        //Smazat zapis - bud podle ciselzapisu nebo vypsat ke kazdemu zapisu ktery jde upravit prijmeni a datum pro lepsi orientaci
            case 3:
                printf("C");

                i = 0;
            break;


        //Vypsat zapis/y - orientovat se podle id_struct_pole a podle toho nabidnout pocet zapisu k dispozici - scanf do promee a podle toho vypsat strukturu
            case 4:
                printf("D");

                i = 0;
            break;


        //Nastavit Heslo
            case 5:
            
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
