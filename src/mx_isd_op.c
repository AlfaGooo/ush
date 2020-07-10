#include "ush.h"

bool mx_isd_op(t_list *tmp, bool *op) {
    if (((t_token *)tmp->data)->type == TYPE_OPERATOR) {
        if (*op) {
            mx_printerr("\033[1;31mu$h: Error near \'");
            mx_printerr(((t_token *)tmp->data)->value[0]);
            mx_printerr("\'\033[0m\n");
            return true;
        }
        *op = true;
    }
    else
        *op = false;
    if ((tmp->next == 0) && (*op)) {
        mx_printerr("\033[1;31mu$h: Error near \'");
        mx_printerr(((t_token *)tmp->data)->value[0]);
        mx_printerr("\'\033[0m\n");
        return false;
    }
    return false;
}
