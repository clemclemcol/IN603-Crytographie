#include "chiffrement.h"

char c_sub_tab[] = "c56b90ad3ef84712";

int c_per_tab[24] = {0, 6, 12, 18, 1, 7, 13, 19, 2, 8, 14, 20, 3, 9, 15, 21, 4, 10, 16, 22, 5, 11, 17, 23};

int c_get_ki(char *key_bi, char *ki)
{
    int i = 40;
    char * tmp = malloc(sizeof(char));
    for (i = 40; i < 64 ; i++)
    {
        sprintf(tmp, "%c", key_bi[i]);
        strncat(ki, tmp, 1);
        strcpy(tmp, "");
    }
    free(tmp);
    return 0;
}

char * c_key_substitution(char *state, int nb){
    char *sub_hex = malloc(80 * sizeof(char));
    if (strlen(sub_hex)!=0){
        strcpy(sub_hex, "");
    }
    int i = 0;
    bi_to_hex(state, sub_hex);
    printf("key sub %s\n",state);

    int value;
    for (int i = 0; i < 1; i++)
    {
        switch (sub_hex[i])
        {
        case '0':
            strncpy(&sub_hex[i], &c_sub_tab[0], 1);
            break;
        case '1':
            strncpy(&sub_hex[i], &c_sub_tab[1], 1);
            break;
        case '2':
            strncpy(&sub_hex[i], &c_sub_tab[2], 1);
            break;
        case '3':
            strncpy(&sub_hex[i], &c_sub_tab[3], 1);
            break;
        case '4':
            strncpy(&sub_hex[i], &c_sub_tab[4], 1);
            break;
        case '5':
            strncpy(&sub_hex[i], &c_sub_tab[5], 1);
            break;
        case '6':
            strncpy(&sub_hex[i], &c_sub_tab[6], 1);
            break;
        case '7':
            strncpy(&sub_hex[i], &c_sub_tab[7], 1);
            break;
        case '8':
            strncpy(&sub_hex[i], &c_sub_tab[8], 1);
            break;
        case '9':
            strncpy(&sub_hex[i], &c_sub_tab[9], 1);
            break;
        case 'A':
        case 'a':
            strncpy(&sub_hex[i], &c_sub_tab[10], 1);
            break;
        case 'B':
        case 'b':
            strncpy(&sub_hex[i], &c_sub_tab[11], 1);
            break;
        case 'C':
        case 'c':
            strncpy(&sub_hex[i], &c_sub_tab[12], 1);
            break;
        case 'D':
        case 'd':
            strncpy(&sub_hex[i], &c_sub_tab[13], 1);
            break;
        case 'E':
        case 'e':
            strncpy(&sub_hex[i], &c_sub_tab[14], 1);
            break;
        case 'F':
        case 'f':
            strncpy(&sub_hex[i], &c_sub_tab[15], 1);
            break;
        default:
            fprintf(stderr, "Unkown value key_sub %s.\n", &sub_hex[i]);
        }
    }
    empty(state);
    
    hex_to_bi(sub_hex, state);
    free(sub_hex);

    return state;
}

char* c_mess_substitution(char *state, int nb)
{
    char *sub_hex = malloc(80 * sizeof(char));
    if (strlen(sub_hex)!=0){
        strcpy(sub_hex, "");
    }
    int i = 0;
    bi_to_hex(state, sub_hex);

    while (sub_hex[i] != '\0')
    {
        switch (sub_hex[i])
        {
        case '0':
            strncpy(&sub_hex[i], &c_sub_tab[0], 1);
            i++;
            break;
        case '1':
            strncpy(&sub_hex[i], &c_sub_tab[1], 1);
            i++;
            break;
        case '2':
            strncpy(&sub_hex[i], &c_sub_tab[2], 1);
            i++;
            break;
        case '3':
            strncpy(&sub_hex[i], &c_sub_tab[3], 1);
            i++;
            break;
        case '4':
            strncpy(&sub_hex[i], &c_sub_tab[4], 1);
            i++;
            break;
        case '5':
            strncpy(&sub_hex[i], &c_sub_tab[5], 1);
            i++;
            break;
        case '6':
            strncpy(&sub_hex[i], &c_sub_tab[6], 1);
            i++;
            break;
        case '7':
            strncpy(&sub_hex[i], &c_sub_tab[7], 1);
            i++;
            break;
        case '8':
            strncpy(&sub_hex[i], &c_sub_tab[8], 1);
            i++;
            break;
        case '9':
            strncpy(&sub_hex[i], &c_sub_tab[9], 1);
            i++;
            break;
        case 'a':
        case 'A':
            strncpy(&sub_hex[i], &c_sub_tab[10], 1);
            i++;
            break;
        case 'b':
        case 'B':
            strncpy(&sub_hex[i], &c_sub_tab[11], 1);
            i++;
            break;
        case 'c':
        case 'C':
            strncpy(&sub_hex[i], &c_sub_tab[12], 1);
            i++;
            break;
        case 'd':
        case 'D':
            strncpy(&sub_hex[i], &c_sub_tab[13], 1);
            i++;
            break;
        case 'e':
        case 'E':
            strncpy(&sub_hex[i], &c_sub_tab[14], 1);
            i++;
            break;
        case 'f':
        case 'F':
            strncpy(&sub_hex[i], &c_sub_tab[15], 1);
            i++;
            break;
        default:
            fprintf(stderr, "Unkown value mess_sub.\n");
        }
    }

    empty(state);
    
    hex_to_bi(sub_hex, state);

    free(sub_hex);
    return state;
}

char * c_permutation(char *state){
    char * tmp = malloc (24*sizeof(char));
    if (tmp == NULL){
        fprintf(stderr, "Error malloc.\n");
    }
    int i, j;
    for (i = 0; i < 24; i ++){
        for (j = 0; j < 24; j++){
            if (i == j){
                strncpy(&tmp[c_per_tab[j]],&state[i], 1);
            }
        }
    }
    empty(state);
    for(i = 0; i < 24; i ++){
        strncpy(&state[i], &tmp[i], 1);
    }
    free(tmp);
    return state;
}

void c_key_schedule(char *key_bi, int I)
{ 
    //printf("kb: %s\n", key_bi);
    
    key_bi = pivot(key_bi); 
    //printf("kb piv: %s\n", key_bi);
    key_bi = c_key_substitution(key_bi, 4); 
    
    key_bi = key_xor(key_bi, I); 

}

char *chiffrement(char *state_bi, char *key_bi)
{
    int i ;
    for (i = 1; i < 11; i ++){
        char *ki = malloc(24* sizeof(char)); 
        char * keyhex = malloc(24* sizeof(char));
        char * messhex = malloc(24* sizeof(char));

        if (ki == NULL){
            fprintf(stderr, "ERR malloc.\n");
            exit(2);
        }
        if (strlen(ki)!=0){
            strcpy(ki,"");
        }

        c_get_ki(key_bi, ki);

        bi_to_hex(ki, keyhex);
        bi_to_hex(state_bi, messhex);
        //fprintf(stdout, "[ TOUR %d ] state : %s --> ki %d: %s \n",i, messhex, i, keyhex);
        c_key_schedule(key_bi, i); 
       
        state_bi = mess_xor(state_bi, ki);

        state_bi = c_mess_substitution(state_bi, strlen(state_bi));

        state_bi = c_permutation(state_bi);

        free(ki);

    }
    char *ki = malloc(24 * sizeof(char)); 
    char * messhexf = malloc(24*sizeof(char));
    char * kihexf = malloc(24*sizeof(char));
    if (ki == NULL){
        fprintf(stderr, "ERR malloc.\n");
        exit(2);
        }
    if (strlen(ki)!=0){
        strcpy(ki,"");
    }
    c_get_ki(key_bi, ki);
    state_bi = mess_xor(state_bi, ki);
    bi_to_hex(state_bi, messhexf);
    bi_to_hex(ki, kihexf);
    //fprintf(stdout, "[ TOUR %d ] state : %s --> ki %d: %s \n",i, messhexf, i, kihexf);

    free(ki);
    free(messhexf);
    free(kihexf);
    return state_bi;
}

