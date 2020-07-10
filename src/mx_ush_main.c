#include "ush.h"

int main(int argc, char *argv[], char **envp) {
    int str = 1;
    t_info *info = 0;

    mx_take_term_width();
    mx_ush_start(&info, envp);
    if (isatty(0) == 0) 
        mx_not_stdin_terminal(info, argc, argv);
    else
        while (str != 0) {
            if (info->history && str == 1) {
                mx_ush_parser(info->history->data, info);
                mx_check_new_line_need();
            }
            if (info->is_exit)
                break;
            str = mx_input_status(info);
            info->if_ctrl_c = 1;
        }
    mx_ush_end(info);
    return info->exit_status;
}
