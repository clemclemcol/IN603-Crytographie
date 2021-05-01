#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char sub_tab[] = "c 5 6 b 9 0 a d 3 e f 8 4 7 1 2";

int per_tab[24] = {0, 6, 12, 18, 1, 7, 13, 19, 2, 8, 14, 20,
                   3, 9, 15, 21, 4, 10, 16, 22, 5, 11, 17, 23};

//int hexConstant[] = {0, 1, 10, 11, 100, 101, 110, 111, 1000,
//                     1001, 1010, 1011, 1100, 1101, 1110, 1111};

int padding(char *key_bi)
{

    while (strlen(key_bi) != 80)
    {
        strcat(key_bi, "0");
    }

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
    fprintf(stdout, "conversion...\n");
    //fprintf(stdout, "bibi %s--> %ld\n", bi, strlen(bi));

    for (int i = 0; i < 80; i = i + 4)
    {
        char *tmp = malloc(4 * sizeof(char));
        int j;
        for (j = i; j < i + 4; j++)
        {
            strncat(tmp, &bi[j], 1);
            //fprintf(stdout, "bibi %d %d %c\n", i, j, bi[j]);
        }
        //fprintf(stdout, "tmp : %s\n", tmp);
        for (int w = 0; w < 16; w++)
        {
            char *wS = malloc(sizeof(char));

            int value = strtoul(tmp, NULL, 2);
            //fprintf(stdout, "val: %d\n", value);

            if (value > 9)
            {
                switch (value)
                {
                case 10:
                    strcat(hex, "A");
                    break;
                case 11:
                    strcat(hex, "B");
                    break;

                case 12:
                    strcat(hex, "C");
                    break;

                case 13:
                    strcat(hex, "D");
                    break;

                case 14:
                    strcat(hex, "E");
                    break;

                case 15:
                    strcat(hex, "F");
                    fprintf(stdout, "hex: %s\n", hex);
                    break;
                default: 
                    fprintf(stderr, "Unknown value.\n");
                    break;
                }
                break;
            }
            else {
                sprintf(wS, "%d", w);
                strncat(hex, wS, 1);
                break;
            }
            free(wS);
        }
        //fprintf(stdout, "in comming hex : %s\n", hex);
        free(tmp);
        j = 0;
    }
    //fprintf(stdout, " %s --> %ld\n", hex, strlen(hex));
    return 0;
}

int get_ki(char *key_bi, char *ki)
{
    int i;

    for (i = 16; i < 40; i++)
    {
        strncat(ki, &key_bi[i], 1);
    }

    return 0;
}

int pivot(char *key_bi, int n)
{
    for (int j = 0; j < 61; j++)
    {
        char temp = key_bi[0];
        for (int i = 0; i < n - 1; i++)
        {
            key_bi[i] = key_bi[i + 1];
        }
        key_bi[n - 1] = temp;
    }
}

char * xor (char *state, char *ki) {
    int stateI = atoi(state);
    fprintf(stdout, "state xor : %s\n", state);
    fprintf(stdout, "ki xor : %s\n", ki);

    int kiI = atoi(ki);

    fprintf(stdout, "stateI xor : %d\n", stateI);
    fprintf(stdout, "kiI xor : %d\n", kiI);

    stateI = stateI ^ kiI;

    sprintf(state, "%d", stateI);
    fprintf(stdout, "post xor : %s\n", state);
    return state;
}

    int substitution(char *state, int nb)
{ //PBM SUB
    char hex[80];
    int i;
    int j = 0;

    bi_to_hex(state, hex);

    printf("key hex : %s --> %ld\n", hex, strlen(hex));
    i = 0;
    while (hex[i] != '\0')
    {
        for (int j = 0; j < 11; j++)
        {
            if (j == hex[i])
            {
                hex[i] = sub_tab[j];
            }
            else if (strcmp(&hex[i], "A") == 0)
            {
                strcpy(&hex[i], &sub_tab[11]);
            }
            else if (strcmp(&hex[i], "B") == 0)
            {
                strcpy(&hex[i], &sub_tab[12]);
            }
            else if (strcmp(&hex[i], "C") == 0)
            {
                strcpy(&hex[i], &sub_tab[13]);
            }
            else if (strcmp(&hex[i], "D") == 0)
            {
                strcpy(&hex[i], &sub_tab[14]);
            }
            else if (strcmp(&hex[i], "E") == 0)
            {
                strcpy(&hex[i], &sub_tab[15]);
            }
            else if (strcmp(&hex[i], "F") == 0)
            {
                strcpy(&hex[i], &sub_tab[16]);
            }
        }
    }

    hex_to_bi(hex, state);
    fprintf(stdout, "post sub: %s\n", state);
    return 0;
}

int key_xor(char *key_bi, int I)
{ //PBM XOR
    char to_xor[5] = "";
    int w = 0;
    for (int x = 61; x < 66; x++)
    {
        strcpy(&to_xor[w], &key_bi[x]);
        w++;
    }
    fprintf(stdout, "to_xor : %ld\n", strlen(to_xor));

    char *tmp;
    char *char_I;
    char It[25] = "0";
    sprintf(char_I, "%d", I);
    hex_to_bi(char_I, tmp);
    strcat(It, tmp);
    strcpy(to_xor, xor(to_xor, It));

    int y;
    for (int x = 61; x < 66; x++)
    {
        y = x % 61;
        strcpy(&key_bi[x], &to_xor[y]);
    }
}

/*char * permutation(char *state){
    char * tmp = malloc (sizeof(char));
    if (tmp == NULL){
        fprintf(stderr, "Error malloc.\n");
    }
    int i, j = 0;
    int compt = 0;
    while (compt < 24){
        j = per_tab[i];
        if (j != i){
            strcpy(tmp, &state[j]);
            state[j] = state[i];  
            i = j;          
        }
        else {
            i ++;
        }
        compt ++;
        
    }
    free(tmp);
    printf("post perm: %s\n", state);
    return state;
}*/

int key_schedule(char *key_bi, char *ki, int I)
{ //algorithme cadencement de clé
    int n = strlen(key_bi);

    get_ki(key_bi, ki); // récupération ki
    fprintf(stdout, "Sous clé : %s --> %ld\n", ki, strlen(ki));

    pivot(key_bi, n); // décalage des bits de la clé maître
    fprintf(stdout, "K pivot: %s --> %ld\n", key_bi, strlen(key_bi));

    //PBM
    substitution(key_bi, 4); //substitution des 4 premiers bits
    fprintf(stdout, "K sub: %s\n", key_bi);

    //key_xor(key_bi, I);                     //XOR avec le nombre de tour

    fprintf(stdout, "K : %s\n", key_bi);
    return 0;
}

char *chiffrement(char *state_bi, char *key_bi)
{
    int i = 1;
    char ki[24] = "";

    //for (int i = 1; i < 11; i ++){

    key_schedule(key_bi, ki, i); // algo de cadencement de clé

    //strcpy(state, xor(state, key));//XOR
    //substitution(state, strlen(state));//substitution
    //permutation(state);//permutation
    //}
    //strcpy(state, xor(state, key));//XOR

    return state_bi;
}

int main(int argc, char *argv[])
{ //entrée valeur hexadecimales

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
    char mess_bi[25] = "";

    char *key = malloc(sizeof(24));
    if (key == NULL)
    {
        fprintf(stderr, "Error malloc key.\n");
    }
    key = argv[2];
    char key_bi[80] = "";
    char hex[80] = "";

    hex_to_bi(mess, mess_bi); // message en binaire
    printf("Mess en bi : %s --> %ld\n", mess_bi, strlen(mess_bi));
    hex_to_bi(key, key_bi); // clé en binaire
    if (strlen(key_bi) < 80)
    {
        padding(key_bi); // clé maître de 80 bits
    }
    printf("Key en bi : %s --> %ld \n", key_bi, strlen(key_bi));

    fprintf(stdout, "next step\n");
    chiffrement(mess_bi, key_bi);

    free(mess);
    free(key);
    return 0;
}