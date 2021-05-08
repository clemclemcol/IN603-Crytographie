#include "attaque.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr,
                "[ERR] usage: %s message key\n", argv[0]);
    }

    char *m1 = malloc(24 * sizeof(char));
    if (m1 == NULL)
    {
        fprintf(stderr, "Error malloc mess.\n");
    }
    strcpy(m1, argv[1]);

    char *c1 = malloc(24 * sizeof(char));
    if (c1 == NULL)
    {
        fprintf(stderr, "Error malloc chiff.\n");
    }
    strcpy(c1, argv[2]);

    KEYLIST *key_tab_m1;
    KEYLIST *key_tab_c1;
    attaque(1677, key_tab_m1, key_tab_c1, m1, c1); //16777215 --> nombre de clés possibles
    
    free(m1);
    free(c1);
    exit(EXIT_SUCCESS);
}