#include "ush.h"

bool mx_ush_regular(char *str, char *regular) {
    regex_t regex;
    int result;

    regcomp(&regex, regular, REG_EXTENDED);
    result = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    return result == 0;
}
