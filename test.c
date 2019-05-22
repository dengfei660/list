#include <assert.h>
#include <stdio.h>

#include "list.h"

struct my_node
{
    // This must be the first member declared in the struct!
    DECL_LIST_MEMBER(struct my_node);
    int value;
};


int main()
{
    struct my_node nodes[10];
    struct my_node list;
    struct my_node *it;
    int i;
    
    // Initialize the list as empty.
    list_init(&list);
    
    // Insert nodes.
    for (i=0; i<10; ++i) {
        nodes[i].value = i;
        list_insert_before(&list, &nodes[i]);
    }
    
    // Iterate list nodes.
    it = list.next;
    while (it != &list) {
        printf("value = %d\n", it->value);
        it = it->next;
    }
    
    // Erase all nodes.
    for (i=0; i<10; ++i) {
        list_erase(&nodes[i]);
    }
    
    // List must be empty by now.
    assert(list_empty(&list));
    
    return 0;
};
