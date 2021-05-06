#include "dechiffrement.h"

char d_sub_tab[] = "c56b90ad3ef84712";

char d_sub_tab_inv[] = "5ef8c12db463079a";

int d_per_tab[24] = {0, 6, 12, 18, 1, 7, 13, 19, 2, 8, 14, 20, 3, 9, 15, 21, 4, 10, 16, 22, 5, 11, 17, 23};

int d_get_ki(char *key_bi, char **ki, int T)
{
    char *tmp = malloc(sizeof(char));
    if (tmp == NULL)
    {
        fprintf(stderr, "ERR malloc.\n");
        return 1;
    }
    for (int i = 40; i < 64; i++)
    {
        sprintf(tmp, "%c", key_bi[i]);
        strcat(ki[T], tmp);
        strcpy(tmp, "");
    }
    free(tmp);
    return 0;
}

char *d_key_substitution(char *state, int nb)
{
   char *sub_hex = malloc(80 * sizeof(char));
    int i = 0;
    bi_to_hex(state, sub_hex);

    //printf("hex : %s --> %ld\n", sub_hex, strlen(sub_hex));
    int value;
    for (int i = 0; i < 1; i++)
    {
        //fprintf(stdout, "hex i: %c \n", sub_hex[i]);
        switch (sub_hex[i])
        {
        case '0':
            strncpy(&sub_hex[i], &d_sub_tab[0], 1);
            break;
        case '1':
            strncpy(&sub_hex[i], &d_sub_tab[1], 1);
            break;
        case '2':
            strncpy(&sub_hex[i], &d_sub_tab[2], 1);
            break;
        case '3':
            strncpy(&sub_hex[i], &d_sub_tab[3], 1);
            break;
        case '4':
            strncpy(&sub_hex[i], &d_sub_tab[4], 1);
            break;
        case '5':
            strncpy(&sub_hex[i], &d_sub_tab[5], 1);
            break;
        case '6':
            strncpy(&sub_hex[i], &d_sub_tab[6], 1);
            break;
        case '7':
            strncpy(&sub_hex[i], &d_sub_tab[7], 1);
            break;
        case '8':
            strncpy(&sub_hex[i], &d_sub_tab[8], 1);
            break;
        case '9':
            strncpy(&sub_hex[i], &d_sub_tab[9], 1);
            break;
        case 'A':
        case 'a':
            strncpy(&sub_hex[i], &d_sub_tab[10], 1);
            break;
        case 'B':
        case 'b':
            strncpy(&sub_hex[i], &d_sub_tab[11], 1);
            break;
        case 'C':
        case 'c':
            strncpy(&sub_hex[i], &d_sub_tab[12], 1);
            break;
        case 'D':
        case 'd':
            strncpy(&sub_hex[i], &d_sub_tab[13], 1);
            break;
        case 'E':
        case 'e':
            strncpy(&sub_hex[i], &d_sub_tab[14], 1);
            break;
        case 'F':
        case 'f':
            strncpy(&sub_hex[i], &d_sub_tab[15], 1);
            break;
        default:
            fprintf(stderr, "Unkown value.\n");
        }
    }
    empty(state);
    
    hex_to_bi(sub_hex, state);
    return state;
}

char *d_mess_substitution(char *state, int nb)
{
    char *sub_hex = malloc(80 * sizeof(char));
    char *sub_h = malloc(80 * sizeof(char));
    char *tmp = malloc(sizeof(char));
    int i = 0;
    bi_to_hex(state, sub_hex);

    int value;
    while (sub_hex[i] != '\0')
    {
        sprintf(tmp, "%c", sub_hex[i]);        
        switch (*tmp)
        {
        case '0':
            strncat(sub_h, &d_sub_tab_inv[0], 1);
            i++;
            break;
        case '1':
            strncat(sub_h, &d_sub_tab_inv[1], 1);
            i++;
            break;
        case '2':
            strncat(sub_h, &d_sub_tab_inv[2], 1);
            i++;
            break;
        case '3':
            strncat(sub_h, &d_sub_tab_inv[3], 1);
            i++;
            break;
        case '4':
            strncat(sub_h, &d_sub_tab_inv[4], 1);
            i++;
            break;
        case '5':
            strncat(sub_h, &d_sub_tab_inv[5], 1);
            i++;
            break;
        case '6':
            strncat(sub_h, &d_sub_tab_inv[6], 1);
            i++;
            break;
        case '7':
            strncat(sub_h, &d_sub_tab_inv[7], 1);
            i++;
            break;
        case '8':
            strncat(sub_h, &d_sub_tab_inv[8], 1);
            i++;
            break;
        case '9':
            strncat(sub_h, &d_sub_tab_inv[9], 1);
            i++;
            break;
        case 'a':
        case 'A':
            strncat(sub_h, &d_sub_tab_inv[10], 1);
            i++;
            break;
        case 'b':
        case 'B':
            strncat(sub_h, &d_sub_tab_inv[11], 1);
            i++;
            break;
        case 'c':
        case 'C':
            strncat(sub_h, &d_sub_tab_inv[12], 1);
            i++;
            break;
        case 'd':
        case 'D':
            strncat(sub_h, &d_sub_tab_inv[13], 1);
            i++;
            break;
        case 'e':
        case 'E':
            strncat(sub_h, &d_sub_tab_inv[14], 1);
            i++;
            break;
        case 'f':
        case 'F':
            strncat(sub_h, &d_sub_tab_inv[15], 1);
            i++;
            break;
        default:
            fprintf(stderr, "Unkown value.\n");
        }
    }
    strcpy(tmp, "");
    empty(state);
    
    hex_to_bi(sub_h, state);
    free(sub_h);
    return state;
}

char *d_permutation(char *state)
{
    char *tmp = malloc(24 * sizeof(char));
    if (tmp == NULL)
    {
        fprintf(stderr, "Error malloc.\n");
    }
    int i, j;
    for (i = 0; i < 24; i++)
    {
        for (j = 0; j < 24; j++)
        {
            if (i == d_per_tab[j])
            {
                strncpy(&tmp[j], &state[i], 1);
            }
        }
    }

    empty(state);
    for (i = 0; i < 24; i++)
    {
        strncpy(&state[i], &tmp[i], 1);
    }
    
    free(tmp);
    return state;
}

void d_key_schedule(char *key_bi, int I) 
{
    key_bi = pivot(key_bi); 

    key_bi = d_key_substitution(key_bi, 4); 
    
    key_bi = key_xor(key_bi, I); 
}

char *dechiffrement(char *state_bi, char *key_bi)
{

    char **ki = malloc(12 * sizeof(char *));
    for (int a = 0; a < 12; a++)
    {
        ki[a] = malloc(25 * sizeof(char));
    }
    if (ki == NULL)
    {
        fprintf(stderr, "ERR malloc.\n");
        exit(2);
    }
    int i = 1;
    for (i = 1; i < 12; i++)
    {
        d_get_ki(key_bi, ki, i);

        d_key_schedule(key_bi, i); 
    }

    fprintf(stdout, "\nDECHIFFREMENT\n");
    state_bi = mess_xor(state_bi, ki[11]); 
    fprintf(stdout, "[ TOUR 11 ] state : %s --> ki 11: %s \n", state_bi, ki[11]);
    
    for (i = 10; i > 0; i--)
    {
        char *keyhex = malloc(24 * sizeof(char));
        char *messhex = malloc(24 * sizeof(char));
        if (strlen(messhex) != 0 || strlen(keyhex) != 0)
        {
            strcpy(messhex, "");
            strcpy(keyhex, "");
        }
        state_bi = d_permutation(state_bi); 
        //fprintf(stdout, "state post perm: %s\n", state_bi);

        state_bi = d_mess_substitution(state_bi, strlen(state_bi)); 
        //fprintf(stdout, "state post sub: %s\n", state_bi);
       
        state_bi = mess_xor(state_bi, ki[i]); 
        //fprintf(stdout, "state post xor: %s\n", state_bi);
        bi_to_hex(state_bi, messhex); 
        //fprintf(stdout, "state post xor: %s\n", messhex);
        fprintf(stdout, "[ TOUR %d ] state : %s --> ki %d: %s ---> %ld //%ld\n", i, state_bi, i, ki[i], strlen(state_bi), strlen(ki[i]));
       

        free(messhex);
        free(keyhex);
    }
    return state_bi;
}

