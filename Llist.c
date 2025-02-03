#include "Llist.h"

static inline void __llist_remove(llistLink* node) {
    node->left->right = node->right;
    node->right->left = node->left;
}

static inline void __llist_splice(llistLink* old_left, llistLink* old_right,
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

inline void Llist_init(Llist *self){
    self->left = self;
    self->right = self;
}

inline llistLink* llist_peek(enum Llist_dir dir, Llist* self){
    return (dir==left) ? self->right : self->left;
}

llistLink* llist_pop(enum Llist_dir dir, Llist *self) {
    llistLink* head = llist_peek(dir,self);    
    __llist_remove(head);
    return head;
}

inline Llist_Cursor cursor_new(enum Llist_dir dir, Llist* list){ return list; }

inline void move_cursor(enum Llist_dir dir, Llist_Cursor* self){
    *self = (dir==left) ? (*self)->left : (*self)->right;
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

void cursor_push(enum Llist_dir dir, Llist_Cursor self, Llist* new_node) {
    llistLink* left_node = (dir == left) ? self : self->left;
    llistLink* right_node = (dir == right) ? self : self->right;

    __llist_splice(left_node,right_node,new_node,new_node);
}

inline Llist_Cursor make_cursor(enum Llist_dir dir, Llist_Cursor self){
    return (dir==left) ? self->left : self->right;
}

inline int is_valid_pos(Llist_Cursor self, Llist* origin) {
    return self != origin;
}
