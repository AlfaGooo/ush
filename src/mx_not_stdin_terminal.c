#include "ush.h"

void mx_not_stdin_terminal(t_info *info, int argc, char *argv[]) {
    char *str = 0;
    char *temp = mx_strnew(1024);
    char *temp2 = 0;
    ssize_t check;
    int i = -1;

    info->if_ctrl_c = 1;
    while ((check = read(0, temp, 1024)) != 0) {
        temp2 = mx_strndup(temp, check);
        str = mx_strjoin3(str, temp2);
    }
    free(temp);
    while (str && str[++i] != 0)
        if (str[i] == '\n')
            str[i] = ';';
    mx_ush_parser(str, info);
    free(str);
    argv++;
    argc++;
}
