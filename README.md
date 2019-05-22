# list
C实现的List 双向列表

这个List是从pjsip中剥离的双向list，使用C语言实现
在定义结构体时，请必须把列表声明放在结构体的开始位置，否则会有问题，如：
struct my_node
{
    // This must be the first member declared in the struct!
    DECL_LIST_MEMBER(struct my_node);
    int value;
};


主要接口如下：
/**
 * Initialize the list.
 * Initially, the list will have no member, and function list_empty() will
 * always return nonzero (which indicates TRUE) for the newly initialized 
 * list.
 *
 * @param node The list head.
 */
 
void list_init(list_type * node);


/**
 * Check that the list is empty.
 *
 * @param node  The list head.
 *
 * @return Non-zero if the list is empty, or zero if it is not empty.
 *
 */
 
int list_empty(const list_type * node);


/**
 * Insert the node to the list before the specified element position.
 *
 * @param pos   The element to which the node will be inserted before. 
 * @param node  The element to be inserted.
 *
 * @return void.
 */
 
void  list_insert_before(list_type *pos, list_type *node);


/**
 * Insert the node to the back of the list. This is just an alias for
 * #list_insert_before().
 *
 * @param list  The list. 
 * @param node  The element to be inserted.
 */
 
void list_push_back(list_type *list, list_type *node);


/**
 * Inserts all nodes in \a nodes to the target list.
 *
 * @param lst       The target list.
 * @param nodes     Nodes list.
 */
 
void list_insert_nodes_before(list_type *lst,
                                           list_type *nodes);

/**
 * Insert a node to the list after the specified element position.
 *
 * @param pos       The element in the list which will precede the inserted 
 *                  element.
 * @param node      The element to be inserted after the position element.
 *
 * @return void.
 */
 
void list_insert_after(list_type *pos, list_type *node);


/**
 * Insert the node to the front of the list. This is just an alias for
 * #pj_list_insert_after().
 *
 * @param list  The list. 
 * @param node  The element to be inserted.
 */
 
void list_push_front(list_type *list, list_type *node);


/**
 * Insert all nodes in \a nodes to the target list.
 *
 * @param lst       The target list.
 * @param nodes     Nodes list.
 */
 
void list_insert_nodes_after(list_type *lst,
                                          list_type *nodes);


/**
 * Remove elements from the source list, and insert them to the destination
 * list. The elements of the source list will occupy the
 * front elements of the target list. Note that the node pointed by \a list2
 * itself is not considered as a node, but rather as the list descriptor, so
 * it will not be inserted to the \a list1. The elements to be inserted starts
 * at \a list2->next. If \a list2 is to be included in the operation, use
 * \a pj_list_insert_nodes_before.
 *
 * @param list1 The destination list.
 * @param list2 The source list.
 *
 * @return void.
 */
 
void list_merge_first(list_type *list1, list_type *list2);


/**
 * Remove elements from the second list argument, and insert them to the list 
 * in the first argument. The elements from the second list will be appended
 * to the first list. Note that the node pointed by \a list2
 * itself is not considered as a node, but rather as the list descriptor, so
 * it will not be inserted to the \a list1. The elements to be inserted starts
 * at \a list2->next. If \a list2 is to be included in the operation, use
 * \a pj_list_insert_nodes_before.
 *
 * @param list1     The element in the list which will precede the inserted 
 *                  element.
 * @param list2     The element in the list to be inserted.
 *
 * @return void.
 */
 
void list_merge_last(list_type *list1, list_type *list2);


/**
 * Erase the node from the list it currently belongs.
 *
 * @param node      The element to be erased.
 */
 
void list_erase(list_type *node);


/**
 * Find node in the list.
 *
 * @param list      The list head.
 * @param node      The node element to be searched.
 *
 * @return The node itself if it is found in the list, or NULL if it is not 
 *         found in the list.
 */
 
list_type* list_find_node(list_type *list, 
                                          list_type *node);


/**
 * Search the list for the specified value, using the specified comparison
 * function. This function iterates on nodes in the list, started with the
 * first node, and call the user supplied comparison function until the
 * comparison function returns ZERO.
 *
 * @param list      The list head.
 * @param value     The user defined value to be passed in the comparison 
 *                  function
 * @param comp      The comparison function, which should return ZERO to 
 *                  indicate that the searched value is found.
 *
 * @return The first node that matched, or NULL if it is not found.
 */
 
list_type* list_search(list_type *list, void *value,
                                       int (*comp)(void *value, 
                                                   const list_type *node)
                                       );


/**
 * Traverse the list to get the number of elements in the list.
 *
 * @param list      The list head.
 *
 * @return          Number of elements.
 */
size_t list_size(const list_type *list);
