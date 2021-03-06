#include "ush.h"

static int flang_string(char *str, int *position, int end, int flag) {
    while (*position < end) {
        if (mx_is_symbol_in_position(str, *position, 39))
            return 0;
        (*position)++;
    }
    mx_printerr("u$h: parse error near | \' |\n");
    return flag;
}

int mx_ex_with_flag(char *str, int *position, int end, int flag) {
    int check_flag = 0;

    if (flag == 39)
        check_flag = flang_string(str, position, end, flag);
    else
        check_flag = mx_command_flag(str, position, end, flag);
    (*position)++;
    return check_flag;
}
