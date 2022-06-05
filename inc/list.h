//
// Created by MStefan99 on 9.9.2019.
//

#include <stdlib.h>
#include <string.h>

#ifndef LIST_H
#define LIST_H


typedef struct element_ {
	void* content;
	struct element_* next;
	struct element_* prev;
} element;


typedef struct {
	element* first;
	element* last;
	int e_count;
} list;

element* allocate_element_(element* prev, element* next, const void* content, size_t size);

/** Create a new list copy
 * 
 * @return list 
 */
list make_list();

/** Push element to the back of the list
 * @brief 
 * 
 * @param l - your list where element is pushed
 * @param content - your element
 * @param size - size of your element 
 * @return 0 if succeess 
 */
int list_push_back(list* l, const void* content, size_t size);

/** Push element to the front of the list
 * 
 * 
 * @param l - your list where element is pushed
 * @param content - your element
 * @param size - size of your element 
 * @return 0 if succeess 
 */
int list_push_front(list* l, const void* content, size_t size);

/***/
int list_pop_back(list* l, void* content, size_t size);

/***/
int list_pop_front(list* l, void* content, size_t size);

/***/
void list_clear(list* l);

/** Get list size
 * 
 * 
 * @param l - your list
 * @return size of your list
 */
int list_size(list* l);

/** List iterator 
 *  
 * 
 * @param l - your list entity
 * @param cb - callback function
 */
void list_foreach(list* l, void (*cb)(void*));
void* list_find(list* l, int (*predicate)(void*));
/** Check the initialization of a list
 * 
 * @param l - new list entity
 * @return true if list was declared. else false 
 */
uint8_t list_is_null(list* l);

/***/
void replace_by_address(void* addr, size_t size, char* file, size_t line);





#endif /*LIST_H*/
