#include "dechiffrement.h"

 typedef struct keylist
{
    char *key;
    char *res;
    struct keylist *suiv;

} KEYLIST;

void create_keytab(int size, KEYLIST *tab);

void combine(char *nb, char *tmp, int len, int ind);

void keys_generator(int size, KEYLIST *tab);

void copy_key_tab(int size, KEYLIST *rempli, KEYLIST *vide);

void comparison_tabs(KEYLIST *tab);

void attaque(int size, KEYLIST *tab1, KEYLIST *tab2, char *mess, char * chif);
