//
// Created by MStefan99 on 9.9.2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    char title[32];
    char data[32];
} content;


typedef struct node_ {
    void *content;
    struct node_ *next;
    struct node_ *prev;
} element;


typedef struct list_ {
    element *first;
    element *last;
    int e_count;
} list;


list new_list();
element *alloc_element(element *prev, element *next, const void *content, size_t size);

int append(list *l, const void *content, size_t size);
int appendLeft(list *l, const void *content, size_t size);
int pop(list *l, void *content, size_t size);
int popLeft(list *l,  void *content, size_t size);
void wipe(list *l);

int get_size(list l);
void print_all(list l, void (*print_element)(const void *element));
void print_element(const void *element);

void ui();

int main() {
    //ui();

    content c1 = {"Test", "Hello world"};
    content c2 = {"Log", "Some test data"};
    list l = new_list();
    append(&l, (void *)&c1, sizeof(content));
    append(&l, (void *)&c1, sizeof(content));
    append(&l, (void *)&c1, sizeof(content));
    append(&l, (void *)&c2, sizeof(content));
    print_all(l, print_element);
    wipe(&l);
}


list new_list() {
    element *first = NULL;
    element *last = NULL;

    list list = {first, last, 0};
    return list;
}


element *alloc_element(element *prev, element *next, const void *content, size_t size) {
    element *e = malloc(sizeof(element));
    void *c = malloc(size);
    if (!e) {
        return NULL;
    }

    if (prev) {
        e->prev = prev;
    } else {
        e->prev = NULL;
    }
    if (next) {
        e->next = next;
    } else {
        e->next = NULL;
    }

    memcpy(c, content, size);
    e->content = c;
    return e;
}


int append(list *l, const void *content, size_t size) {
    element *e = alloc_element(l->last, NULL, content, size);
    if (!e) {
        return 1;
    }

    if (!l->first) {
        l->first = e;
    }

    if (l->last) {
        l->last->next = e;
    }

    l->last = e;
    ++l->e_count;
    return 0;
}


int appendLeft(list *l, const void *content, size_t size) {
    element *e = alloc_element(NULL, l->first, content, size);
    if (!e) {
        return 1;
    }

    if (!l->last) {
        l->last = e;
    }

    if (l->first) {
        l->first->prev = e;
    }

    l->first = e;
    ++l->e_count;
    return 0;
}


int pop(list *l, void *content, size_t size) {
    element *e = l->last;
    if (e) {
        memcpy(content, e->content, size);

        if (e->prev) {
            e->prev->next = NULL;
        } else {
            l->first = NULL;
        }
        l->last = e->prev;

        --l->e_count;
        free(e->content);
        free(e);
        return 0;
    } else {
        return 1;
    }
}


int popLeft(list *l, void *content, size_t size) {
    element *e = l->first;
    if (e) {
        memcpy(content, e->content, size);

        if (e->next) {
            e->next->prev = NULL;
        } else {
            l->last = NULL;
        }

        l->first = e->next;

        --l->e_count;
        free(e->content);
        free(e);
        return 0;
    } else {
        return 1;
    }
}


void wipe(list *l) {
    element *p = l->first;
    element *t;

    while (p) {
        t = p;
        p = p->next;
        free(t->content);
        free(t);
    }

    l->first = NULL;
    l->last = NULL;
    l->e_count = 0;
}


int get_size(list l) {
    return l.e_count;
}


void print_all(list l, void (*print_element)(const void *)) {
    int i = 0;
    if (!l.first) {
        printf("list empty\n");
    } else {
        printf("list elements:\n");
        for (element *p = l.first; p; p = p->next, i++) {
            printf("element %i: {\n", i + 1);
            print_element(p->content);
            printf("}\n");
        }
        printf("\n");
    }
}


void print_element(const void *element) {
    printf("Title: \"%s\"\nData: \"%s\"\n", ((content *)element)->title, ((content *)element)->data);
}


void ui() {
    int action;
    char str[32];
    list l = new_list();

    printf("Available actions:\n"
           "1 - Append string\n"
           "2 - Append string to the left\n"
           "3 - Pop string\n"
           "4 - Pop left string\n"
           "5 - Print all strings\n"
           "6 - Get list size\n"
           "7 - Clear list\n"
           "8 - Exit\n");
    do {
        printf("Select action:\n");
        scanf("%i", &action);

        switch (action) {
            case 1:
                printf("Enter the element: ");
                scanf("%s", str);

                if (!append(&l, str, sizeof(str))) {
                    printf("Inserted element %s\n", str);
                } else {
                    printf("Could not insert!\n");
                }
                break;

            case 2:
                printf("Enter the element: ");
                scanf("%s", str);

                if (!appendLeft(&l, str, sizeof(str))) {
                    printf("Inserted element %s at the left\n", str);
                } else {
                    printf("Could not insert!\n");
                }
                break;

            case 3:
                if (!pop(&l, str, sizeof(str))) {
                    printf("Popped element %s\n", str);
                } else {
                    printf("Could not pop!\n");
                }
                break;

            case 4:
                if (!popLeft(&l, str, sizeof(str))) {
                    printf("Popped element %s from the left\n", str);
                } else {
                    printf("Could not pop!\n");
                }
                break;

            case 5:
                print_all(l, print_element);
                break;

            case 6:
                printf("list now contains %i elements.\n", get_size(l));
                break;

            case 7:
                wipe(&l);
                printf("list cleared!\n");
                break;

            case 8:
                wipe(&l);
                printf("Closing program.\n");
                break;

            default:
                printf("No such action!\n");
                break;
        }
    } while (action != 8);
}