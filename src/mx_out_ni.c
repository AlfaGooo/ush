#include "ush.h"

void mx_out_ni(char **mas_name, int index) {
    char *name = mx_arrstr_to_str(mas_name);

    printf("[%d] + continued %s\n",index, name);
    free(name);
}
