#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Llist.h"

typedef struct Llist_node {
    llistLink _link;
    int data;
} Llist_node;

void test_push_pop(){
    Llist list;
    Llist_init(&list);
    for(int i=0;i<50;i++){
        Llist_node* node = malloc(sizeof(Llist_node));
        node->data = i;
        llist_push(left, &list, &node->_link);
    }
    for(int i=0;i<50;i++){
        Llist_node* node = (Llist_node*) llist_pop(right,&list);
        assert(node->data == i);
        fprintf(stderr,"%d\n",node->data);
        free(node);
    }
    assert( list.left == &list && list.right == &list);
    fprintf(stderr,"%p %p %p\n",&list,list.left,list.right);

    printf("Push/Pop tests passed\n");
}

int main(){
    test_push_pop();
}
