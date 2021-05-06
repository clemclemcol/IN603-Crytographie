#include "chiffrement.h"

int d_get_ki(char *key_bi, char **ki, int T);

char *d_key_substitution(char *state, int nb);

char *d_mess_substitution(char *state, int nb);

char *d_permutation(char *state);

void d_key_schedule(char *key_bi, int I);

char *dechiffrement(char *state_bi, char *key_bi);

