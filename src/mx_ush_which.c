#include "ush.h"

static int get_flags(int *i, char **argv) {
    int flags = 0;

    while(argv[++(*i)])
        if (argv[*i][0] == '-') {
            for(int j = 1; j < mx_strlen(argv[*i]); j++)
                if (argv[*i][j] == 'a')
                    flags |= 1;
                else if(argv[*i][j] == 's')
                    flags |= 2;
                else {
                    mx_printerr("which: bad option: -");
                    write(2, &argv[*i][j], 1);
                    write(2, "\n", 1);
                    return -1;
                }
        }
        else
            return flags;
    return flags;
}

static int check_build_in(char *command, int flags, bool *finded) {
    if (mx_check_buildin(command)) {
        if ((flags & 2) == 2)
            return 1;
        printf("%s: shell built-in command\n", command);
        *finded = true;
        if ((flags & 1) == 0)
            return 1;
    }
    return 0;
}

static bool check_command(char *command, char **pathes, int flags) {
    char *fullname = 0;
    bool finded = false;

    if (check_build_in(command, flags, &finded) == 1)
        return true;
    if (command[0] == '/') {
        if (mx_check_command(mx_strdup(command), flags))
                return true;
    }
    else {
        for(int i = 0; pathes[i]; i++) {
            fullname = mx_strjoin2(mx_strjoin(pathes[i], "/"), command);
            if (mx_check_command(fullname, flags)) {
                if ((flags & 1) == 0)
                    return true;
                finded = true;
            }
        }
    }
    return finded;
}

static bool check_commands(char **commands, char** pathes, int start_index,
                           int flags) {
    int i = start_index - 1;
    bool finded = false;

    while(commands[++i] != 0) {
        finded = check_command(commands[i], pathes, flags);
        if ((finded == false) && ((flags & 2) == 2))
            return false;
        if (finded == false) 
            printf("%s not found\n", commands[i]);
        if (finded && ((flags & 1) == 0 || (flags & 2) == 2))
            return true;
    }
    return finded;
}

void mx_ush_which(char **argv, t_info *info) {
    char *path = mx_get_value_new("PATH", &(info->var_tree));
    char **pathes = mx_strsplit(path, ':');
    int i_args = 0;
    int flags = get_flags(&i_args, argv);
    int finded = false;
    
    if (flags == -1) {
        mx_del_strarr(&pathes);
        info->last_status = 1;
        return;
    }
    finded = check_commands(argv, pathes, i_args, flags);
    finded ? (info->last_status = 0) : (info->last_status = 1);
    mx_del_strarr(&pathes);
}
