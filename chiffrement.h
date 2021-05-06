#include "common.h"

int c_get_ki(char *key_bi, char *ki);

char * c_key_substitution(char *state, int nb);

char* c_mess_substitution(char *state, int nb);

char * c_permutation(char *state);

void c_key_schedule(char *key_bi, int I);

char *chiffrement(char *state_bi, char *key_bi);