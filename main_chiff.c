#include "chiffrement.h"

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
    strcpy(mess, argv[1]);
    char *mess_bi = malloc(sizeof(char)*25);

    char *key = malloc(sizeof(24));
    if (key == NULL)
    {
        fprintf(stderr, "Error malloc key.\n");
    }
    strcpy(key, argv[2]);
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