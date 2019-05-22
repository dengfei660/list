#include <stddef.h>
#include <stdint.h>

#include "list.h"

/* Internal func*/
void link_node(list_type *prev, list_type *next)
{
    ((list_st*)prev)->next = next;
    ((list_st*)next)->prev = prev;
}

void list_init(list_type * node)
{
    ((list_st*)node)->next = ((list_st*)node)->prev = node;
}


int list_empty(const list_type * node)
{
    return ((list_st*)node)->next == node;
}

void list_push_back(list_type *list, list_type *node)
{
    list_insert_before(list, node);
}

void list_push_front(list_type *list, list_type *node)
{
    list_insert_after(list, node);
}

void list_insert_after(list_type *pos, list_type *node)
{
    ((list_st*)node)->prev = pos;
    ((list_st*)node)->next = ((list_st*)pos)->next;
    ((list_st*)((list_st*)pos)->next)->prev = node;
    ((list_st*)pos)->next = node;
}


void list_insert_before(list_type *pos, list_type *node)
{
    list_insert_after(((list_st*)pos)->prev, node);
}


void list_insert_nodes_after(list_type *pos, list_type *lst)
{
    list_st *lst_last = (list_st *) ((list_st*)lst)->prev;
    list_st *pos_next = (list_st *) ((list_st*)pos)->next;

    link_node(pos, lst);
    link_node(lst_last, pos_next);
}

void list_insert_nodes_before(list_type *pos, list_type *lst)
{
    list_insert_nodes_after(((list_st*)pos)->prev, lst);
}

void list_merge_last(list_type *lst1, list_type *lst2)
{
    if (!list_empty(lst2)) {
        link_node(((list_st*)lst1)->prev, ((list_st*)lst2)->next);
        link_node(((list_st*)lst2)->prev, lst1);
        list_init(lst2);
    }
}

void list_merge_first(list_type *lst1, list_type *lst2)
{
    if (!list_empty(lst2)) {
        link_node(((list_st*)lst2)->prev, ((list_st*)lst1)->next);
        link_node(((list_st*)lst1), ((list_st*)lst2)->next);
        list_init(lst2);
    }
}

void list_erase(list_type *node)
{
    link_node( ((list_st*)node)->prev, ((list_st*)node)->next);

    /* It'll be safer to init the next/prev fields to itself, to
     * prevent multiple erase() from corrupting the list. See
     * ticket #520 for one sample bug.
     */
    list_init(node);
}


list_type* list_find_node(list_type *list, list_type *node)
{
    list_st *p = (list_st *)((list_st*)list)->next;
    while (p != list && p != node) {
        p = (list_st *) p->next;
    }

    return p==node ? p : NULL;
}


list_type* list_search(list_type *list, void *value,
                        int (*comp)(void *value, const list_type *node))
{
    list_st *p = (list_st *) ((list_st*)list)->next;
    while (p != list && (*comp)(value, p) != 0) {
        p = (list_st *) p->next;
    }

    return p==list ? NULL : p;
}


size_t list_size(const list_type *list)
{
    const list_st *node = (const list_st*) ((const list_st*)list)->next;
    size_t count = 0;

    while (node != list) {
        ++count;
        node = (list_st*)node->next;
    }

    return count;
}