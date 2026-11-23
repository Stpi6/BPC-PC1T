#pragma once
#include "../zapis/zapis.h"

void spocitej_radky(int *prazdne_radky, int *celkem_radku, int idpr[], long *zacatek_dat);
// Spocita vsechny radky v souboru - predpoklad je ze prvni radek je zahlavi tabulky

int nacteni_zaznamu(struct zapis f[], int id_struct_pole, long offset, int idpr[]);
// Nacte vsechny zaznamy ze souboru data/jizdy.csv do struktury zapis

int kontrola_obsahu_zapisu(int pocet_prazdnych_radku, int i, int idpr[]);
// Zkontroluje jestli zaznam neni smazany/poskozen (1 = v poradku, 0 = smazany/poskozen)
