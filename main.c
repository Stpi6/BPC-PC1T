#include <stdio.h>
#include <ctype.h>

int zjisteni_delky(char text[])
{
    int x = 0;

    while(text[x] =! '\0')
    {
        x++;

    }

    return x;

}


int kontrola_nas_hesla(char kon_nas_heslo[])
{

    if(zjisteni_delky(kon_nas_heslo) < 8) 
    {
        printf("Zadejte heslo ve správném tvaru.");

        return 0;
    }

    else{

        int cislo = 0;

        int velke_pismeno = 0;

        int specialni_znak = 0;

        for(int i = 0; i <= zjisteni_delky(kon_nas_heslo); i++)
        {
            if(specialni_znak =! 1 &&((kon_nas_heslo[i] >= '!' && kon_nas_heslo[i] <= '/') || (kon_nas_heslo[i] >= ':' && kon_nas_heslo[i] <= '@') || (kon_nas_heslo[i] >= '[' && kon_nas_heslo[i] <= 96) || (kon_nas_heslo[i] >= 123 && kon_nas_heslo[i] <= 126)))
            {
                specialni_znak = 1;
            }

            if(cislo =! 1 && isdigit(kon_nas_heslo[i]) > 0)
            {
                cislo = 1;
            }

            if(velke_pismeno =! 1 && (kon_nas_heslo[i] >= 'A' && kon_nas_heslo[i] <= 'Z'))
            {
                velke_pismeno = 1;
            }


        }

        if(specialni_znak > 0 && cislo > 0 && velke_pismeno > 0) 
        {
            printf("Heslo bylo nastaveno a uloženo");

            return 1;
        }
    }

}

int nastaveni_hesla(char nas_heslo[])
{

    if(kontrola_nas_hesla(nas_heslo) == 1) 
    {
        return 1;

    }    
    else if (nas_heslo[0] == 6 && nas_heslo[1] == '\0')
    {
        return 6;

    }
    
    
}





int main()
{

    //MAZANI TERMINALU FCE????

    //Zjistit pokud heslo existuje a zavolat prihlaseni

    char heslo[20] = {0, '\0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int vybrano_menu;

    int i = 0;

    while(1)
    {

        printf("\r\nMENU\r\n\n1 - Novy zapis\r\n2 - Upravit stavajici zapis\r\n3 - Smazat zapis\r\n4 - Vypsat zapis/y\r\n5 - Nastavit heslo\r\n6 - konec\r\n\n");

        



        scanf("%d",&vybrano_menu);

        switch (vybrano_menu) {

        //Novy zapis
        case 1:
             

            i = 0;
        break;


        //Upravit stavajici zapis
        case 2:
            printf("B");

            i = 0;
        break;


        //Smazat zapis
        case 3:
            printf("C");

            i = 0;
        break;


        //Vypsat zapis/y
        case 4:
            printf("D");

            i = 0;
        break;


        //Nastavit Heslo
        case 5:
            
        while (1)
        {
        
            //smazani terminalu

            printf("Zadejte silne heslo(minimalni pozadavky: \r\n8 znaku\r\n1 velke pismeno\r\n1 cislo\r\n1 specialni znak)\r\n\nMoje heslo: ");

            scanf("%s", &heslo);

            if (nastaveni_hesla(heslo) == 1)
            {
                break;
            }
            
            else if (nastaveni_hesla(heslo) == 6)
            {
                break;
            }

            if (kontrola_nas_hesla(heslo) == 0)
            {
                kontrola_nas_hesla(heslo);
            }
            
            
        }
        break;


        //Konec
        case 6:
            printf("F");
        break;

        default:
            printf("Vyberte platnou moznost");
            i++;
        break;
        }

        if (i == 3) break;

    
    }

    printf("\r\nKonec\r\n");

    

    return 0;
}