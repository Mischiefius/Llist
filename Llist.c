#include "Llist.h"

inline void __llist_remove(llistLink* node) {
    node->left->right = node->right;
    node->right->left = node->left;
}

inline void __llist_splice(llistLink* old_left, llistLink* old_right,
                           llistLink* new_left, llistLink* new_right) {
    old_left->right = new_left;
    old_right->left = new_right;
    new_left->left = old_left;
    new_right->right = old_right;
}

void llist_push(enum Llist_dir dir, Llist *self, llistLink *new_node) {
    llistLink* left_node = (dir == left) ? self : self->left;
    llistLink* right_node = (dir == right) ? self : self->right;

    __llist_splice(left_node,right_node,new_node,new_node);
}

llistLink* llist_pop(enum Llist_dir dir, Llist *self) {
    llistLink* head = llist_peek(dir,self);    
    __llist_remove(head);
    return head;
}

llistLink* delete_move(enum Llist_dir dir, Llist_Cursor* self) {
    llistLink* node = *self;
    move_cursor(dir,self);
    __llist_remove(node);
    return node;
}


void cursor_splice(enum Llist_dir dir, Llist_Cursor self, Llist* new_list) {
    llistLink* left_node = (dir == left) ? self : self->left;
    llistLink* right_node = (dir == right) ? self : self->right;

    llistLink* new_left = llist_peek(left,new_list);
    llistLink* new_right = llist_peek(right,new_list);
    
    __llist_splice(left_node,right_node,new_left,new_right);
}
