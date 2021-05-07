#include "common.h"

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

    for (j = 0; j < 5; j++)
    {
        if (tmp[j])
        {
            num_bi[j] = tmp[j];
        }
        else
        {
            num_bi[j] = 0;
        }
    }

    free(tmp);
    return 0;
}

int hex_to_bi(char *key, char *key_bi)
{
    char dix[3] = "10";
    char ze[2] = "\0";
    if (key == dix)
    {
        strcat(key_bi, "1010");
        return 0;
    }
    int i = 0;
    while (key[i])
    {
        switch (key[i])
        {
        case '0':
            strcat(key_bi, "0000");
            i++;
            break;
        case '1':
            strcat(key_bi, "0001");
            i++;
            break;
        case '2':
            strcat(key_bi, "0010");
            i++;
            break;
        case '3':
            strcat(key_bi, "0011");
            i++;
            break;
        case '4':
            strcat(key_bi, "0100");
            i++;
            break;
        case '5':
            strcat(key_bi, "0101");
            i++;
            break;
        case '6':
            strcat(key_bi, "0110");
            i++;
            break;
        case '7':
            strcat(key_bi, "0111");
            i++;
            break;
        case '8':
            strcat(key_bi, "1000");
            i++;
            break;
        case '9':
            strcat(key_bi, "1001");
            i++;
            break;
        case 'a':
        case 'A':
            strcat(key_bi, "1010");
            i++;
            break;
        case 'b':
        case 'B':
            strcat(key_bi, "1011");
            i++;
            break;
        case 'c':
        case 'C':
            strcat(key_bi, "1100");
            i++;
            break;
        case 'd':
        case 'D':
            strcat(key_bi, "1101");
            i++;
            break;
        case 'e':
        case 'E':
            strcat(key_bi, "1110");
            i++;
            break;
        case 'f':
        case 'F':
            strcat(key_bi, "1111");
            i++;
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
        if (tmp == NULL)
        {
            fprintf(stderr, "ERROR malloc.\n");
        }
        if (strlen(tmp) != 0)
        {
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
                fprintf(stderr, "Unknown value bi_to_hex.\n");
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

char *pivot(char *key_bi)
{
    char *tab_piv = malloc(80 * sizeof(char));
    for (int i = 79; i >= 0; --i)
    {
        if ((i - 61) >= 0)
        {
            strncpy(&tab_piv[i - 61], &key_bi[i], 1);
        }
        else if ((i - 61) < 0)
        {
            int j = (i - 61) + 80;
            strncpy(&tab_piv[j], &key_bi[i], 1);
        }
    }
    empty(key_bi);
    for (int i = 0; i < 80; i++)
    {
        strncpy(&key_bi[i], &tab_piv[i], 1);
    }
    free(tab_piv);
    return key_bi;
}

char *key_xor(char *key_bi, int I)
{
    //fprintf(stdout, "key : %s --> tour : %d\n", key_bi, I);
    char *to_xor = malloc(sizeof(char) * 5);
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

char *mess_xor(char *state, char *ki)
{
    printf("mess : %s --> %ld // key : %s --> %ld\n", state, strlen(state), ki, strlen(ki));

    if (strlen(ki) > 24)
    {
        strcpy(&ki[23], "\0");
        printf("la\n");
        //strlen(ki) = strlen(ki)-1;
    }

    if (strlen(ki) != strlen(state) )//&&strlen(ki) > strlen(state)+1
    {
        fprintf(stderr, "Error lenght arguments message and ki.\n");
        exit(1);
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
        char *tmp = malloc(sizeof(char));
        sprintf(tmp, "%d", stateI[i]);
        strncpy(&state[i], tmp, 1);
        free(tmp);
    }
    free(stateI);
    free(kiI);
    return state;
}
