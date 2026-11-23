#include <stdio.h>
#include "mazani.h"

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
