#include <stdio.h>
#include <direct.h>
#include "zapis.h"

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

void uloz_zapis_do_csv(struct zapis *f)
{
    FILE *kontrola;
    FILE *soubor;
    int prazdny = 1;

    _mkdir("data");

    kontrola = fopen("data/jizdy.csv", "r");

    if(kontrola != NULL)
    {
        fseek(kontrola, 0, SEEK_END);

        if(ftell(kontrola) != 0)
        {
            prazdny = 0;
        }

        fclose(kontrola);
    }

    soubor = fopen("data/jizdy.csv", "a");

    if(soubor == NULL)
    {
        printf("\r\nZapis se nepodarilo ulozit do souboru data/jizdy.csv.\r\n");

        return;
    }

    if(prazdny == 1)
    {
        fprintf(soubor, "den,mesic,rok,jmeno,prijmeni,id,spz,najezd,zacatek,konec\n");
    }

    fprintf(soubor, "%d,%d,%d,%s,%s,%s,%s,%d,%s,%s\n", f->datum.den, f->datum.mesic, f->datum.rok, f->ridic.jmeno, f->ridic.prijmeni, f->ridic.id, f->autoo.auto_spz, f->autoo.najezd, f->doba.zacatek, f->doba.konec);

    fclose(soubor);
}
