#include "dechiffrement.h"

 typedef struct keylist
{
    char *key;
    char *resCh;
    char *resDch;

    struct keylist *suiv;

} KEYLIST;



char *dec_to_hex(int num, char *numhex);

KEYLIST* create_tabs(KEYLIST *key_tab);

KEYLIST* key_generator(int size, KEYLIST *key_tab);

void comparison_tabs(KEYLIST *tab);

void attaque(int size, KEYLIST *key_tab, char *m1, char *c1);