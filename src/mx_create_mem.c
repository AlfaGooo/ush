#include "ush.h"

char *mx_create_mem(char *str1, char **str2, char *str3, char **value) {
    char *mem = 0;

    if (mx_strcmp(str1, "SHLVL") == 0) {
        mx_shlvl_new(str2);
        mx_strdel(value);
        *value = mx_strdup(*str2);
        mem = mx_strjoin("SHLVL=", *str2);
    }
    else if (mx_strcmp(str1, "PWD") == 0) {
        mx_strdel(str2);
        *str2 = getcwd(NULL, 0);
        mem = mx_strjoin("PWD=", *str2);
    }
    else if (mx_strcmp(str1, "OLDPWD") == 0) {
        mx_strdel(str2);
        *str2 = getcwd(NULL, 0);
        mem = mx_strjoin("OLDPWD=", *str2);
    }
    else
        mem = mx_strdup(str3);
    return mem;
}
