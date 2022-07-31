#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/**
 * @file c-mem-entity-d-array.h
 * @author Vasily Davydov
 * @version 0.1
 * @date 2022-07-31
 *
 * @copyright Copyright (c) 2022
 *
 */

/*  */
typedef struct Rame {
    void* data;
    struct Rame* next;
}Rame;

static Rame* make_rame(){
    return (Rame*) malloc(sizeof(Rame));
}

static void* make_cherry(size_t _cherry_size){
    return malloc(_cherry_size);
}

void grow_cherry_at_beginning(Rame* beginning, void* cherry, size_t cherry_size){
    /* Assertion of the rame being initialized or not. */
    assert(beginning);

    Rame* new = make_rame();

    void* _cherry_loc = make_cherry(cherry_size);
    memcpy(_cherry_loc, cherry, cherry_size);

    new->data = _cherry_loc;
    new->next = beginning;
    beginning = new;
}

void grow_cherry_after_cherry(Rame* cherry_on_rame, void* cherry, size_t cherry_size) {
    /* Assertion of the rame being initialized or not. */
    assert(cherry_on_rame);

    Rame *new = make_rame();

    void* _cherry_loc = make_cherry(cherry_size);
    memcpy(_cherry_loc, cherry, cherry_size);

    new->data = _cherry_loc;
    new->next = cherry_on_rame->next;
    cherry_on_rame->next = new;
}

static size_t if_delete_cb(){
}

void* for_each_cherry(Rame* beginning, size_t (*cherry_callback)(void*)){
    /* Assertion of the rame being initialized or not. */
    assert(beginning);

    for(Rame* temp = beginning;temp;temp = temp->next) {
        cherry_callback(temp->data);
    }
}

Rame* find_rame(Rame* beginning, size_t (*cherry_callback)(void*)){
    /* Assertion of the rame being initialized or not. */
    assert(beginning);

    for(Rame* temp = beginning;temp;temp = temp->next) {
        if(cherry_callback(temp->data)){
            return temp;
        }
    }
    return NULL;
}

void pick_cherry(Rame* beginning, size_t (*cherry_callback)(void*)){
    Rame* to_delete = find_rame(beginning, cherry_callback);
    assert(to_delete);

    free(to_delete->data);

    Rame* prev = to_delete->next;
}



