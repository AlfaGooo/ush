#include "ush.h"

static int get_start_index(char *str) {
    int i = 0;

    while(str[i]) {
        if (str[i] != ' ') {
            return i;
        }
        i++;
    }
    return i;
}

static int pos_parametr(char *str, int *start) {
    int i = *start;

    while (str[i] != '=') {
        i++;
    }
    if (str[i] == '=') {
        return i;
    }
    else 
        return 0;
}

static void create_parameter(char *str, int *start, int end, t_info *processes) {
    int pos = pos_parametr(str, start);
    char *name = mx_strndup(&str[*start], pos - *start);
    char *value = NULL;
    char *temp = NULL;

    *start = ++pos;
    mx_ex_with_flag(str, &pos, end, ' ');
    temp = mx_strndup(&str[*start], pos - *start);
    *start = pos;
    value = mx_check_str(temp, processes, 0);
    mx_strdel(&temp);
    mx_subs(&value);
    mx_find_list(&(processes->var_tree), name, value);
    pos = get_start_index(&str[*start]);
    if (pos != -1) 
        *start += pos;
    mx_is_param_new(str, start, end, processes);
}

static bool is_not_operator(char c) {
    if (c == '|' || c == '&' || c == '>' || c == '<'|| c == '$' || c == ' ')
        return false;
    if (c == '='|| c == 92 || c == 34 || c == 39 || c== 96 || c == 0)
        return false;
    return true;
}

void mx_is_param_new(char *str, int *start, int end, t_info *processes) {
    int check_start = *start;

    while (is_not_operator(str[check_start]))
        check_start++;
    if (str[check_start] == '=') {
        create_parameter(str, start, end, processes);
    }
}

