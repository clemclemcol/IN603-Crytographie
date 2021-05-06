#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int padding(char *key_bi);

int empty(char *state);

int dec_to_bi(int num, int *num_bi);

int hex_to_bi(char *key, char *key_bi);

int bi_to_hex(char *bi, char *hex);

char *pivot(char *key_bi);

char* key_xor(char *key_bi, int I);

char * mess_xor(char *state, char *ki);
