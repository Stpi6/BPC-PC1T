#include <stdio.h>
#include "uprava.h"

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
