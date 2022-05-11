/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-02
 * @modify-date: 2020-05-11
 * @version: 0.0.4
 * @description: Doubly-Linked Circular List Implementation File
 */
#include <stdlib.h>
#include <string.h>

#include "llist.h"

int llist_empty(struct LLIST *);

size_t llist_size(struct LLIST *);

const void * llist_front(struct LLIST *);

const void * llist_rear(struct LLIST *);

int push_front(struct LLIST *, const void *);

int push_back(struct LLIST *, const void *);

int pop_front(struct LLIST *, void *);

int pop_back(struct LLIST *, void *);

struct LLIST * llist_create(const int datasize)
{
  struct LLIST *ptr = NULL;

  ptr = (struct LLIST *) malloc(sizeof *ptr);
  if (ptr == NULL)
    return NULL;

  LLIST_HEAD_INIT(ptr->head);

  ptr->length     = 0;
  ptr->datasize   = datasize;

  /* =============== Operations =============== */
  ptr->empty = llist_empty;
  ptr->size  = llist_size;
  ptr->front = llist_front;
  ptr->rear  = llist_rear;

  ptr->push_front = push_front;
  ptr->push_back  = push_back;
  ptr->pop_front  = pop_front;
  ptr->pop_back   = pop_back;

  return ptr;
}

DEQUE* CreateDeque(const int datasize)
{
  return llist_create(datasize);
}

int llist_empty(struct LLIST *ptr)
{
  return (ptr->length == 0);
}

size_t llist_size(struct LLIST *ptr)
{
  return ptr->length;
}

const void * llist_front(struct LLIST *ptr)
{
  if (llist_empty(ptr))
    return NULL;

  return ptr->head.next->data;
}

const void * llist_rear(struct LLIST *ptr)
{
  if (llist_empty(ptr))
    return NULL;

  return ptr->head.prev->data;
}

static inline
int llist_insert_(struct DuLNode *prev, struct DuLNode *next, const void *data, const int datasize)
{
  struct DuLNode *new_node = NULL;

  new_node = (struct DuLNode *) malloc((sizeof *new_node) + datasize);
  if (new_node == NULL)
    return -2; // failed to allocate the heap memory!

  memcpy(new_node->data, data, datasize);

  prev->next = new_node;
  next->prev = new_node;
  new_node->prev = prev;
  new_node->next = next;

  return 0;
}

static int llist_insert(struct LLIST *ptr, const void *data, LLIST_OPER_MODE mode)
{
  int ret;
  switch (mode)
  {
    case LLIST_FORWARD:
      ret = llist_insert_(&ptr->head, ptr->head.next, data, ptr->datasize);
      break;
    case LLIST_BACKWARD:
      ret = llist_insert_(ptr->head.prev, &ptr->head, data, ptr->datasize);
      break;
    default:
      return -1; // illegal argument!
  }

  if (ret == 0) // insertion successfully!
    ++ptr->length;

  return ret;
}

static inline
int llist_delete_(struct DuLNode *ptr, void *data, const int datasize)
{
  if (data != NULL)
    memcpy(data, ptr->data, datasize);

  /* 脱链操作 */
  ptr->prev->next = ptr->next;
  ptr->next->prev = ptr->prev;

  free(ptr);
  return 0;
}

static int llist_delete(struct LLIST *ptr, void *data, LLIST_OPER_MODE mode)
{
  if (llist_empty(ptr))
    return -1;

  int ret;
  switch (mode)
  {
    case LLIST_FORWARD:
      ret = llist_delete_(ptr->head.next, data, ptr->datasize);
      break;
    case LLIST_BACKWARD:
      ret = llist_delete_(ptr->head.prev, data, ptr->datasize);
      break;
    default:
      return -1; // illegal argument!
  }

  if (ret == 0) // deletion successfully!
    --ptr->length;

  return ret;
}

int push_front(struct LLIST *ptr, const void *data)
{
  return llist_insert(ptr, data, LLIST_FORWARD);
}

int push_back(struct LLIST *ptr, const void *data)
{
  return llist_insert(ptr, data, LLIST_BACKWARD);
}

int pop_front(struct LLIST *ptr, void *data)
{
  return llist_delete(ptr, data, LLIST_FORWARD);
}

int pop_back(struct LLIST *ptr, void *data)
{
  return llist_delete(ptr, data, LLIST_BACKWARD);
}

void llist_destroy(struct LLIST *ptr)
{
  struct DuLNode *cur, *nxt;
  for (cur = ptr->head.next; cur != &ptr->head; cur = nxt)
  {
    nxt = cur->next;
    free(cur);
  }
  free(ptr);
}

void DestroyDeque(DEQUE *ptr)
{
  llist_destroy(ptr);
}