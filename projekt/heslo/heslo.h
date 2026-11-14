#pragma once

int zkouska_delky(char zk[]);
// return x - splnuje           return 0 - nesplnuje

int kontrola_pozadavku_hesla(char kon_heslo[]);
// return 1 - splnuje           return 0 - nesplnuje

void ulozeni_hesla(char zapsane[], char ulozene[]);
// ulozi napsane heslo do ulozene_heslo[]

void uloz_heslo_do_souboru(char ulozene[]);

int nacti_heslo_ze_souboru(char ulozene[]);

int prihlaseni(char ulozene[]);
