#include "ush.h"

void mx_del_node(t_tnode **root, void *data, int (*cmp)(void*, void*),
                     void (*free_tnode)(t_tnode *tnode)) {
    t_tnode *finded = mx_select_tree_node(*root, data,  cmp);

    if (finded == 0)
        return;
    if (finded == *root) {
        printf("ROOTTT\n");
        free_tnode(finded);
    }
    if (finded == 0)
        return;
    if ((finded->left == 0) && (finded->right == 0))
        mx_del_if_noch(root, data, cmp, free_tnode);
    else if ((finded->left == 0) && (finded->right != 0))
        mx_delete_tnodeb(root, data, cmp, free_tnode);
    else if ((finded->left != 0) && (finded->right == 0))
        mx_delete_tnodeb(root, data, cmp, free_tnode);
    else if ((finded->right != 0) && (finded->left !=0))
        mx_delete_tnodea(root, cmp, finded, free_tnode);
}
