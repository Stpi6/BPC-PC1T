#include <stdio.h>
#include "vypis.h"

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
