#include "ush.h"

void mx_shlvl_new(char **s) {
    int a = 0;
    char *temp = 0;
    int i = 0;
    int neg = 1;

    if (s[0][0] == '-') {
        i++;
        neg = -1;
    }
    for (; i < mx_strlen(s[0]); i++){
        a = a * 10 + (s[0][i] - '0');
    }
    a = a * neg;
    mx_strdel(s);
    temp = mx_itoa(++a);
    *s = temp;
}
