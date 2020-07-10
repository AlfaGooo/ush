#include "ush.h"

void mx_del_leaks(t_info *info) {
    if (!info->processes)
        return;
    mx_del_strarr(&((t_process*)info->processes->data)->name);
    mx_pop_front(&info->processes);
}
