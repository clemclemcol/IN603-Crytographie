#include "attaque.h"

char nb[] = "0123456789abcdef";

void create_keytab(int size, KEYLIST *tab)
{
    int i;
    tab = malloc(size+1 * sizeof(KEYLIST) );
    if (tab == NULL)
    {
        fprintf(stderr, "Error malloc.\n");
    }
    for (i = 0; i < size; i++)
    {

        tab->key = malloc(6* sizeof(char));
        tab->res = malloc(6*sizeof(char));
        tab->suiv = malloc(sizeof(KEYLIST));
        tab = tab->suiv;

    }
}

void keys_generator(int size, KEYLIST *tab)
{
    char *tmp = malloc(sizeof(char)+1);
    for (int z = 0; z < size; z++)
    {
        for (int i = 0; i < 16; i++)
        {printf("ge 0 %c\n", nb[i]);

            sprintf(tmp, "%c", nb[i]); 
            printf("tmp: %s\n", tmp);

            strncpy(tab->key, tmp, 1);
            printf("i:%d\n", i);
            strcpy(tmp, "");
            printf("generer cle\n");
            for (int j = 0; j < 16; j++)
            {
                sprintf(tmp, "%c", nb[j]);
                strncat(tab->key, tmp, 1);
                strcpy(tmp, "");

                for (int k = 0; k < 16; k++)
                {
                    sprintf(tmp, "%c", nb[k]);
                    strncat(tab->key, tmp, 1);
                    strcpy(tmp, "");

                    for (int l = 0; l < 16; l++)
                    {
                        sprintf(tmp, "%c", nb[l]);
                        strncat(tab->key, tmp, 1);
                        strcpy(tmp, "");

                        for (int m = 0; m < 16; m++)
                        {
                            sprintf(tmp, "%c", nb[m]);
                            strncat(tab->key, tmp, 1);
                            strcpy(tmp, "");

                            for (int n = 0; n < 16; n++)
                            {
                                sprintf(tmp, "%c", nb[n]);
                                strncat(tab->key, tmp, 1);
                                strcpy(tmp, "");
                            }
                        }
                    }
                }
            }
        }
        tab = tab->suiv;
        printf("suiv\n");
    }
    free(tmp);
}

void copy_key_tab(int size, KEYLIST *rempli, KEYLIST *vide)
{
    for (int i = 0; i < size; i++)
    {
        strcpy(vide[i].key, rempli[i].key);
    }
    printf("copy fait\n");
}

void comparison_tabs(KEYLIST *tab) {}

void attaque(int size, KEYLIST *tab1, KEYLIST *tab2, char *mess, char *chif)
{
    printf("ici\n");
    create_keytab(size, tab1);
    create_keytab(size, tab2);
    printf("tchuss\n");
    keys_generator(size, tab1);
    printf("coucou\n");
    copy_key_tab(size, tab1, tab2);
    printf("polaire\n");

    char *mess_bi = malloc(24 * sizeof(char));
    char *chif_bi = malloc(24 * sizeof(char));
    char *key_bi = malloc(24 * sizeof(char));
    printf("grise\n");

    hex_to_bi(mess, mess_bi);
    printf("panpan\n");

    hex_to_bi(chif, chif_bi);

    for (int i = 0; i < size; i++)
    {
        hex_to_bi(tab1[i].key, key_bi);
        tab1[i].res = chiffrement(mess_bi, key_bi);
        tab2[i].res = dechiffrement(chif_bi, tab2[i].key);
    }

    free(mess_bi);
    free(chif_bi);
    free(key_bi);
}
