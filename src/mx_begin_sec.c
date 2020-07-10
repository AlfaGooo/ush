#include "ush.h"

static bool check_if_env_have(char *name, t_list **var_tree) {
    t_list *var_tree_check = *var_tree;

    while (var_tree_check) {
        if (mx_strcmp(((t_variable *)var_tree_check->data)->name, name) == 0)
            return false;
        else
            var_tree_check = var_tree_check->next;
    }
    return true;
}

static void check_env(t_list **var_tree) {
    char *temp = 0;

    if (check_if_env_have("PWD", var_tree)) {
        temp = getcwd(NULL, 0);;
        mx_add_env_s(var_tree, mx_strdup("PWD"),
                    temp, mx_strjoin("PWD=", temp));
    }
    if (check_if_env_have("OLDPWD", var_tree)) {
        temp = getcwd(NULL, 0);
        mx_add_env_s(var_tree, mx_strdup("OLDPWD"), temp,
                    mx_strjoin("OLDPWD=", temp));
    }
    if (check_if_env_have("SHLVL", var_tree)) {
        temp = mx_strdup("1");
        mx_add_env_s(var_tree, mx_strdup("SHLVL"), temp,
                    mx_strjoin("SHLVL=", temp));
    }
}

void mx_begin_sec(t_list **var_tree, char **env) {
    int i = -1;
    char **envvar = 0;
    char *temp = 0;
    t_variable *var = 0;

    while (env[++i]) {
        var = (t_variable *)malloc(sizeof(t_variable));
        envvar = mx_strsplit(env[i], '=');
        var->name = envvar[0];
        var->value = mx_strdup(&env[i][mx_strlen(var->name) + 1]);
        temp = mx_create_mem(envvar[0], &envvar[1], env[i], &(var->value));
        var->is_env = true;
        var->mem = temp;
        putenv(temp);
        mx_push_back(var_tree, var);
        free(envvar[1]);
        free(envvar);
    }
    check_env(var_tree);
}
