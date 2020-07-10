#include "ush.h"

void mx_del_if_noch(t_tnode **root, void *data,
                            int (*cmp)(void*, void*),
                            void (*free_tnode)(t_tnode *tnode)) {
    t_tnode *root_ = *root;
    int result = cmp(root_->data, data);

    if (result == 0) {
        free_tnode(*root);
        *root = 0;
    }
    else if (result > 0) {
       mx_del_if_noch(&((*root)->left), data, cmp, free_tnode);
    }
    else {
        mx_del_if_noch(&((*root)->right), data, cmp, free_tnode);
    }
}
