#include "attaque.h"

char nb[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

char *dec_to_hex(int num, char *numhex)     //conersion decimal en hexadecimal
{
    int i = 0;
    int j = 0;
    int *tmp = calloc(sizeof(int), 6);
    for (i = 5; num > 0; i--)
    {
        tmp[i] = num % 16;
        //printf("tmp %d\n", tmp[i]);
        num = num / 16;
    }

    for (j = 0; j < 6; j++)
    {
        if (tmp[j] < 10)
        {
            char *c = calloc(2, sizeof(char));
            //printf("tmp: %hd\n", tmp[j]);
            sprintf(c, "%hd", tmp[j]);
            strcpy(&numhex[j], c);
            free(c);
        }
        else
        {
            switch (tmp[j])
            {
            case 10:
                strcpy(&numhex[j], "a");
                break;
            case 11:
                strcpy(&numhex[j], "b");
                break;
            case 12:
                strcpy(&numhex[j], "c");
                break;
            case 13:
                strcpy(&numhex[j], "d");
                break;
            case 14:
                strcpy(&numhex[j], "e");
                break;
            case 15:
                strcpy(&numhex[j], "f");
                break;
            default:
                fprintf(stderr, "Unknown value.\n");
                break;
            }
        }
    }
    free(tmp);
    //printf("fin: %s\n", numhex);

    return numhex;
}

KEYLIST *create_tabs(KEYLIST *key_tab)      //creation de la liste de clé-message
{
    key_tab = malloc(sizeof(KEYLIST));
    if (key_tab == NULL)
        exit(0);

    key_tab->key = malloc(sizeof(char) * 7);
    key_tab->res = malloc(sizeof(char) * 7);
    key_tab->suiv = NULL;
    return key_tab;
}

KEYLIST *key_generator(int size, KEYLIST *key_tab)      //générateur de combinaison de clé héxadécimal
{
    key_tab = create_tabs(key_tab);

    KEYLIST *new_key = create_tabs(new_key);
    dec_to_hex(size, key_tab->key); 
    //printf("key_tab %d: %s\n", size, key_tab->key);
    key_tab->suiv = new_key;
    if (size == 0)
    {
        return NULL;
    }
    key_generator(size - 1, key_tab->suiv);
    return key_tab;
}

void comparaison(int size, KEYLIST *key_tab_m1, KEYLIST *key_tab_c1, int fd) //comparaison des messages obtenus après les chiffrements et déchiffrements
{
    int i = 0;
    int j = 0;
    while (i < size)
    {
        while (j < size)
        {
            if (strcmp(key_tab_c1->res, key_tab_m1->res) == 0)
            {
                printf("écrit.\n");
                char * buf = malloc(sizeof(key_tab_c1->key)*2 +2);
                sprintf(buf, "%s - %s\n", key_tab_m1->key, key_tab_c1->key);
                write(fd, buf, strlen(buf));
                free(buf);
                
            }
            key_tab_c1 = key_tab_c1->suiv;
            j++;

        }
        key_tab_m1 = key_tab_m1->suiv;
        i++;
    }
}

void attaque(int size, KEYLIST *key_tab_m1, KEYLIST *key_tab_c1, char *m1, char *c1)
{
    int fd = open("clairchiff1.txt", O_CREAT, S_IRWXU);
    key_tab_m1 = key_generator(size, key_tab_m1);
    key_tab_c1 = key_generator(size, key_tab_c1);
    //printf("key tab: %s\n", key_tab->suiv->key);
    printf("generator done\n");
    char *mess_bi = calloc(sizeof(char), 25);
    if (strlen(mess_bi) != 0)
    {
        strcpy(mess_bi, "");
    }
    hex_to_bi(m1, mess_bi);

    char *chiff_bi = calloc(sizeof(char), 25);
    if (strlen(chiff_bi) != 0)
    {
        strcpy(chiff_bi, "");
    }
    hex_to_bi(c1, chiff_bi);

    for (int i = 0; i < size; i++)
    {
        char *key_bi = calloc(sizeof(char), 80);
        if (strlen(key_bi) != 0)
        {
            strcpy(key_bi, "");
        }
        hex_to_bi(key_tab_m1->key, key_bi);             //stockage de la clé traité dans les listes
        hex_to_bi(key_tab_c1->key, key_bi);
        if (strlen(key_bi) < 80)
        {
            padding(key_bi);
        }

        mess_bi = chiffrement(mess_bi, key_bi);         //fonction de chiffrement

        bi_to_hex(mess_bi, key_tab_m1->res);

        printf("key_tab_m1->res: %s--> %ld\n", key_tab_m1->res, strlen(key_tab_m1->res));


        printf("chiff_bi: %s--> %ld\n", chiff_bi, strlen(chiff_bi));
        strcat(chiff_bi, "\0");

        chiff_bi = dechiffrement(chiff_bi, key_bi);        //fonction de déchiffrement
        printf("Dech_chiff_bi: %s--> %ld\n", chiff_bi, strlen(chiff_bi));

        bi_to_hex(chiff_bi, key_tab_c1->res);
        printf("key_tab->resCh: %s--> %ld\n", key_tab_c1->res, strlen(key_tab_c1->res));

        key_tab_m1 = key_tab_m1->suiv;                      //changement de clé
        key_tab_c1 = key_tab_c1->suiv;
        free(key_bi);
    }
    //comparaison(size, key_tab_m1, key_tab_c1, fd);
    free(mess_bi);
    free(chiff_bi);
    close(fd);
}