#include "list.h"

element *allocate_element_(element *prev, element *next, const void *content,
                           size_t size) {
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

list make_list() {
  element *first = NULL;
  element *last = NULL;

  list list = {first, last, 0};
  return list;
}

int list_push_back(list *l, const void *content, size_t size) {
  element *e = allocate_element_(l->last, NULL, content, size);
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

int list_push_front(list *l, const void *content, size_t size) {
  element *e = allocate_element_(NULL, l->first, content, size);
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

int list_pop_back(list *l, void *content, size_t size) {
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

int list_pop_front(list *l, void *content, size_t size) {
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

void list_clear(list *l) {
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

int list_size(list *l) { return l->e_count; }

void list_foreach(list *l, void (*cb)(void *)) {
  for (element *p = l->first; p; p = p->next) {
    cb(p->content);
  }
}

void *list_find(list *l, int (*predicate)(void *)) {
  for (element *p = l->first; p; p = p->next) {
    if (predicate(p->content)) {
      return p->content;
    }
  }
}

uint8_t list_is_null(list *l) {
  if (!l) {
    return 0;
  } else {
    return 1;
  }
}