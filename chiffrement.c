#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char sub_tab[] = "c56b90ad3ef84712";

int per_tab[24] = {0, 6, 12, 18, 1, 7, 13, 19, 2, 8, 14, 20, 3, 9, 15, 21, 4, 10, 16, 22, 5, 11, 17, 23};

int padding(char *key_bi)
{
    while (strlen(key_bi) < 80)
    {
        strcat(key_bi, "0");
    }
    return 0;
}

int empty(char *state)
{
    for (int i = 0; i < strlen(state); i++)
    {
        strcpy(&state[i], "");
    }
    return 0;
}

int dec_to_bi(int num, int *num_bi)
{
    int i = 0;
    int j = 0;
    int *tmp = malloc(5 * sizeof(int));
    num_bi[0] = 0;
    for (i = 4; num > 0; i--)
    {
        tmp[i] = num % 2;
        //printf("tmp %d\n", tmp[i]);

        num = num / 2;
    }
    
    for (j = 0; j < 5; j ++)
    {
        if (tmp[j]){
           num_bi[j] = tmp[j]; 
          
        }
        else {
            num_bi[j] = 0;
        }
        
    }
    
    free(tmp);
    return 0;
}

int hex_to_bi(char *key, char *key_bi)
{
    if (strcmp(key, "10") == 0)
    {
        strcat(key_bi, "1010");
        return 0;
    }
    for (int i = 0; key[i] != '\0'; i++)
    {
        switch (key[i])
        {
        case '0':
            strcat(key_bi, "0000");
            break;
        case '1':
            strcat(key_bi, "0001");
            break;
        case '2':
            strcat(key_bi, "0010");
            break;
        case '3':
            strcat(key_bi, "0011");
            break;
        case '4':
            strcat(key_bi, "0100");
            break;
        case '5':
            strcat(key_bi, "0101");
            break;
        case '6':
            strcat(key_bi, "0110");
            break;
        case '7':
            strcat(key_bi, "0111");
            break;
        case '8':
            strcat(key_bi, "1000");
            break;
        case '9':
            strcat(key_bi, "1001");
            break;
        case 'a':
        case 'A':
            strcat(key_bi, "1010");
            break;
        case 'b':
        case 'B':
            strcat(key_bi, "1011");
            break;
        case 'c':
        case 'C':
            strcat(key_bi, "1100");
            break;
        case 'd':
        case 'D':
            strcat(key_bi, "1101");
            break;
        case 'e':
        case 'E':
            strcat(key_bi, "1110");
            break;
        case 'f':
        case 'F':
            strcat(key_bi, "1111");
            break;
        default:
            fprintf(stderr, "Invalid hexadecimal input.\n");
            return 1;
        }
    }
    return 0;
}

int bi_to_hex(char *bi, char *hex)
{
    for (int i = 0; i < strlen(bi); i = i + 4)
    {
        char *tmp = malloc(4 * sizeof(char));
        if (tmp == NULL){
            fprintf(stderr, "ERROR malloc.\n");
        }
        if (strlen(tmp)!= 0){
            strcpy(tmp, "");
        }
      
        int j;
        for (j = i; j < i + 4; j++)
        {
            strncat(tmp, &bi[j], 1);
           
        }
        
        for (int w = 0; w < 16; w++)
        {
            char *wS = malloc(sizeof(char));
          
            int value = strtoul(tmp, NULL, 2);
           
            switch (value)
                {
                case 0:
                    strcat(hex, "0");
                    break;
                case 1:
                    strcat(hex, "1");
                    break;
                case 2:
                    strcat(hex, "2");
                    break;
                case 3:
                    strcat(hex, "3");
                    break;
                case 4:
                    strcat(hex, "4");
                    break;
                case 5:
                    strcat(hex, "5");
                    break;
                case 6:
                    strcat(hex, "6");
                    break;
                case 7:
                    strcat(hex, "7");
                    break;
                case 8:
                    strcat(hex, "8");
                    break;
                case 9:
                    strcat(hex, "9");
                    break;
                case 10:
                    strcat(hex, "a");
                    break;
                case 11:
                    strcat(hex, "b");
                    break;
                case 12:
                    strcat(hex, "c");
                    break;
                case 13:
                    strcat(hex, "d");
                    break;
                case 14:
                    strcat(hex, "e");
                    break;
                case 15:
                    strcat(hex, "f");
                    break;
                default:
                    fprintf(stderr, "Unknown value.\n");
                    break;
                }
                break;
            
            free(wS);
        }
        free(tmp);
        j = 0;
    }
    return 0;
}

int get_ki(char *key_bi, char *ki)
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

char* pivot(char *key_bi)
{
    char *tab_piv = malloc(80 * sizeof(char));
    for (int i = 79; i >= 0; --i){
        if ((i - 61) >= 0){
            strncpy(&tab_piv[i - 61], &key_bi[i],1);
        }
        else if ((i - 61) < 0){
            int j = (i - 61) + 80;
            strncpy(&tab_piv[j], &key_bi[i],1);
        }
    }
    empty(key_bi);
    for(int i = 0; i < 80; i++){
        strncpy(&key_bi[i], &tab_piv[i],1);
    }
    free(tab_piv);
    return key_bi;
}

char* key_xor(char *key_bi, int I)
{ 
    //fprintf(stdout, "key : %s --> tour : %d\n", key_bi, I);
    char* to_xor = malloc(sizeof(char)*5);
    int w = 0;
    for (int x = 60; x < 65; x++)
    {
        strncpy(&to_xor[w], &key_bi[x], 1);
        w++;
    }
    int *I_bi = malloc(5 * sizeof(int));
    dec_to_bi(I, I_bi);
    //fprintf(stdout, "to_xor : %s --> tour bi: %ls\n", to_xor, I_bi);

    for (int i = 0; i < 5; i++)
    {
        to_xor[i] = to_xor[i] ^ I_bi[i];
    }
    //fprintf(stdout, "res xor : %s --> tour bi: %d\n", to_xor, I);
    w = 0;
    for (int x = 60; x < 65; x++)
    {
        strncpy(&key_bi[x], &to_xor[w], 1);
        w++;
    }
    free(I_bi);
    free(to_xor);

    return key_bi;
}

char * mess_xor(char *state, char *ki){
    if (strlen(ki) != strlen(state)){
        fprintf(stderr, "Error lenght arguments message and ki.\n");
        exit (1);
    }

    int *stateI = malloc(24 * sizeof(int));
    int *kiI = malloc(24 * sizeof(int));
    for (int i = 0; i < strlen(state); i++)
    {
        char kTemp[24];
        char sTemp[24];
        sprintf(&kTemp[i], "%c", ki[i]);
        kiI[i] = atoi(&kTemp[i]);
        sprintf(&sTemp[i], "%c", state[i]);
        stateI[i] = atoi(&sTemp[i]);

    }
    
    for (int i = 0; i < strlen(state); i++)
    {
        stateI[i] = stateI[i] ^ kiI[i];
        
    }
    
    for (int i = 0; i < strlen(state); i++)
    {
        char * tmp = malloc(sizeof(char));
        sprintf(tmp, "%d", stateI[i]);
        strncpy(&state[i], tmp, 1);
        free(tmp);
    }
    free(stateI);
    free(kiI);
    return state;

}

char * key_substitution(char *state, int nb){
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
            strncpy(&sub_hex[i], &sub_tab[0], 1);
            break;
        case '1':
            strncpy(&sub_hex[i], &sub_tab[1], 1);
            break;
        case '2':
            strncpy(&sub_hex[i], &sub_tab[2], 1);
            break;
        case '3':
            strncpy(&sub_hex[i], &sub_tab[3], 1);
            break;
        case '4':
            strncpy(&sub_hex[i], &sub_tab[4], 1);
            break;
        case '5':
            strncpy(&sub_hex[i], &sub_tab[5], 1);
            break;
        case '6':
            strncpy(&sub_hex[i], &sub_tab[6], 1);
            break;
        case '7':
            strncpy(&sub_hex[i], &sub_tab[7], 1);
            break;
        case '8':
            strncpy(&sub_hex[i], &sub_tab[8], 1);
            break;
        case '9':
            strncpy(&sub_hex[i], &sub_tab[9], 1);
            break;
        case 'A':
        case 'a':
            strncpy(&sub_hex[i], &sub_tab[10], 1);
            break;
        case 'B':
        case 'b':
            strncpy(&sub_hex[i], &sub_tab[11], 1);
            break;
        case 'C':
        case 'c':
            strncpy(&sub_hex[i], &sub_tab[12], 1);
            break;
        case 'D':
        case 'd':
            strncpy(&sub_hex[i], &sub_tab[13], 1);
            break;
        case 'E':
        case 'e':
            strncpy(&sub_hex[i], &sub_tab[14], 1);
            break;
        case 'F':
        case 'f':
            strncpy(&sub_hex[i], &sub_tab[15], 1);
            break;
        default:
            fprintf(stderr, "Unkown value.\n");
        }
    }
    empty(state);
    
    hex_to_bi(sub_hex, state);
    return state;
}

char* mess_substitution(char *state, int nb)
{
    char *sub_hex = malloc(80 * sizeof(char));
    int i = 0;
    bi_to_hex(state, sub_hex);

    while (sub_hex[i] != '\0')
    {
        switch (sub_hex[i])
        {
        case '0':
            strncpy(&sub_hex[i], &sub_tab[0], 1);
            i++;
            break;
        case '1':
            strncpy(&sub_hex[i], &sub_tab[1], 1);
            i++;
            break;
        case '2':
            strncpy(&sub_hex[i], &sub_tab[2], 1);
            i++;
            break;
        case '3':
            strncpy(&sub_hex[i], &sub_tab[3], 1);
            i++;
            break;
        case '4':
            strncpy(&sub_hex[i], &sub_tab[4], 1);
            i++;
            break;
        case '5':
            strncpy(&sub_hex[i], &sub_tab[5], 1);
            i++;
            break;
        case '6':
            strncpy(&sub_hex[i], &sub_tab[6], 1);
            i++;
            break;
        case '7':
            strncpy(&sub_hex[i], &sub_tab[7], 1);
            i++;
            break;
        case '8':
            strncpy(&sub_hex[i], &sub_tab[8], 1);
            i++;
            break;
        case '9':
            strncpy(&sub_hex[i], &sub_tab[9], 1);
            i++;
            break;
        case 'a':
        case 'A':
            strncpy(&sub_hex[i], &sub_tab[10], 1);
            i++;
            break;
        case 'b':
        case 'B':
            strncpy(&sub_hex[i], &sub_tab[11], 1);
            i++;
            break;
        case 'c':
        case 'C':
            strncpy(&sub_hex[i], &sub_tab[12], 1);
            i++;
            break;
        case 'd':
        case 'D':
            strncpy(&sub_hex[i], &sub_tab[13], 1);
            i++;
            break;
        case 'e':
        case 'E':
            strncpy(&sub_hex[i], &sub_tab[14], 1);
            i++;
            break;
        case 'f':
        case 'F':
            strncpy(&sub_hex[i], &sub_tab[15], 1);
            i++;
            break;
        default:
            fprintf(stderr, "Unkown value.\n");
        }
    }

    empty(state);
    
    hex_to_bi(sub_hex, state);

    //free(sub_hex);
    return state;
}

char * permutation(char *state){
    char * tmp = malloc (24*sizeof(char));
    if (tmp == NULL){
        fprintf(stderr, "Error malloc.\n");
    }
    int i, j;
    for (i = 0; i < 24; i ++){
        for (j = 0; j < 24; j++){
            if (i == j){
                strncpy(&tmp[per_tab[j]],&state[i], 1);
            }
        }
    }
    //printf("tmp : %s\n", tmp);
    empty(state);
    for(i = 0; i < 24; i ++){
        strncpy(&state[i], &tmp[i], 1);
    }
    //printf("post perm: %s\n", state);
    free(tmp);
    return state;
}

void key_schedule(char *key_bi, int I)
{ 

    key_bi = pivot(key_bi); 

    key_bi = key_substitution(key_bi, 4); 
    
    key_bi = key_xor(key_bi, I); 

}

char *chiffrement(char *state_bi, char *key_bi)
{
    int i ;
    for (i = 1; i < 11; i ++){
        char *ki = malloc(24 * sizeof(char)); 
        char * keyhex = malloc(24*sizeof(char));
        char * messhex = malloc(24*sizeof(char));

        if (ki == NULL){
            fprintf(stderr, "ERR malloc.\n");
            exit(2);
        }
        if (strlen(ki)!=0){
            strcpy(ki,"");
        }

        get_ki(key_bi, ki);

        bi_to_hex(ki, keyhex);
        bi_to_hex(state_bi, messhex);
        fprintf(stdout, "[ TOUR %d ] state : %s --> ki %d: %s \n",i, messhex, i, ki);
        key_schedule(key_bi, i); 
       
        state_bi = mess_xor(state_bi, ki);

        state_bi = mess_substitution(state_bi, strlen(state_bi));

        state_bi = permutation(state_bi);

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
    get_ki(key_bi, ki);
    state_bi = mess_xor(state_bi, ki);
    bi_to_hex(state_bi, messhexf);
    bi_to_hex(ki, kihexf);
    fprintf(stdout, "[ TOUR %d ] state : %s --> ki %d: %s \n",i, messhexf, i, kihexf);

    free(ki);
    free(messhexf);
    free(kihexf);
    return state_bi;
}

int main(int argc, char *argv[])
{ 
    if (argc != 3)
    {
        fprintf(stderr,
                "[ERR] usage: %s message key\n", argv[0]);
    }
    char *mess = malloc(sizeof(24));
    if (mess == NULL)
    {
        fprintf(stderr, "Error malloc mess.\n");
    }
    mess = argv[1];
    char *mess_bi = malloc(sizeof(char)*25);

    char *key = malloc(sizeof(24));
    if (key == NULL)
    {
        fprintf(stderr, "Error malloc key.\n");
    }
    key = argv[2];
    char *key_bi = malloc(80*sizeof(char));

    hex_to_bi(mess, mess_bi); // message en binaire
    hex_to_bi(key, key_bi); // clé en binaire
    if (strlen(key_bi) < 80)
    {
        padding(key_bi); // clé maître de 80 bits
    }

    mess_bi = chiffrement(mess_bi, key_bi);
    empty(mess);
    bi_to_hex(mess_bi, mess);
    
    printf("Message chiffré: %s --> %ld \n", mess, strlen(mess_bi));

    free(mess);
    free(mess_bi);
    free(key);
    free(key_bi);
    exit(EXIT_SUCCESS) ;
}