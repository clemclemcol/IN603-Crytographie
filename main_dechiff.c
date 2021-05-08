#include "dechiffrement.h"

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
    char *mess_bi = malloc(sizeof(char) * 25);

    char *key = malloc(sizeof(24));
    if (key == NULL)
    {
        fprintf(stderr, "Error malloc key.\n");
    }
    strcpy(key, argv[2]);
    char key_bi[80] = "";
    hex_to_bi(key, key_bi);    //converti la clé héxadécimale en binaire 
    hex_to_bi(mess, mess_bi); //converti le message héxadécimale en binaire
    printf("Message chiffré : %s \n", mess);
    if (strlen(key_bi) < 80)
    {
        padding(key_bi);  // ajout des 0 en bits de poids faible
    }

    mess_bi = dechiffrement(mess_bi, key_bi);   
    empty(mess);
    bi_to_hex(mess_bi, mess);

    printf("Message clair: %s \n", mess);

    free(mess);
    free(key);
    exit(EXIT_SUCCESS);
}