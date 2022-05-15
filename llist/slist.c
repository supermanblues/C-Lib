/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-02
 * @modify-date: 2020-05-15
 * @version: 0.0.1
 * @description: Singly-Linked List Implementation File
 */
#include <stdlib.h>
#include <string.h>

#include "slist.h"

int slist_empty(struct SLIST *);
size_t slist_size(struct SLIST *);

const void * slist_front(struct SLIST *);
const void * slist_back(struct SLIST *);

int slist_push_front(struct SLIST *, const void *);
int slist_push_back(struct SLIST *, const void *);
int slist_pop_front(struct SLIST *, void *);

void slist_travel(struct SLIST *, visit *);
void slist_reverse(struct SLIST *);

struct SLIST * slist_create(int datasize)
{
  struct SLIST *ptr = NULL;

  ptr = (struct SLIST *) malloc(sizeof *ptr);
  if (ptr == NULL)
    return NULL;

  ptr->head     = NULL;
  ptr->tail     = NULL;
  ptr->length   = 0;
  ptr->datasize = datasize;

  /* =============== Operations =============== */
  ptr->empty = slist_empty;
  ptr->size  = slist_size;

  ptr->front = slist_front;
  ptr->back  = slist_back;
  ptr->rear  = slist_back;

  ptr->push_front = slist_push_front;
  ptr->push_back  = slist_push_back;
  ptr->pop_front  = slist_pop_front;

  ptr->travel  = slist_travel;
  ptr->reverse = slist_reverse;

  return ptr;
}

int slist_empty(struct SLIST *ptr)
{
  return (ptr->head == NULL);
}

size_t slist_size(struct SLIST *ptr)
{
  return ptr->length;
}

const void * slist_front(struct SLIST *ptr)
{
  if (slist_empty(ptr))
    return NULL;

  return ptr->head->data;
}

const void * slist_back(struct SLIST *ptr)
{
  if (slist_empty(ptr))
    return NULL;

  return ptr->tail->data;
}

int slist_push_front(struct SLIST *ptr, const void *data)
{
  struct SListNode *new_node;

  new_node = (struct SListNode *) malloc(sizeof(*new_node) + ptr->datasize);
  if (new_node == NULL)
    return -1;

  __COPY_DATA_(new_node->data, data, ptr->datasize);
  new_node->next = NULL;

  if (ptr->head == NULL)
  {
    ptr->head = new_node;
    ptr->tail = new_node;
  }
  else
  {
    new_node->next = ptr->head;
    ptr->head = new_node;
  }

  ++ptr->length;
  return 0;
}

int slist_push_back(struct SLIST *ptr, const void *data)
{
  struct SListNode *new_node;

  new_node = (struct SListNode *) malloc(sizeof(*new_node) + ptr->datasize);
  if (new_node == NULL)
    return -1;

  __COPY_DATA_(new_node->data, data, ptr->datasize);
  new_node->next = NULL;

  if (ptr->head == NULL)
  {
    ptr->head = new_node;
    ptr->tail = new_node;
  }
  else
  {
    ptr->tail->next = new_node;
    ptr->tail = new_node;
  }

  ++ptr->length;
  return 0;
}

int slist_pop_front(struct SLIST *ptr, void *data)
{
  struct SListNode *del_node = NULL;

  if (slist_empty(ptr))
    return -1;

  del_node = ptr->head;
  if (data != NULL)
    __COPY_DATA_(data, del_node->data, ptr->datasize);

  ptr->head = del_node->next;
  if (ptr->head == NULL)
    ptr->tail = NULL;

  --ptr->length;
  free(del_node);

  return 0;
}

void slist_travel(struct SLIST *ptr, visit *visit)
{
  struct SListNode *cur = NULL;

  __SLIST_FOR_EACH_(cur, ptr->head)
    visit(cur->data);

  return;
}

static SListNode * reverse_(struct SListNode *head)
{
  struct SListNode *new_head = NULL;

  if (head == NULL || head->next == NULL)
    return head;

  new_head = reverse_(head->next);
  head->next->next = head;
  head->next = NULL;

  return new_head;
}

void slist_reverse(struct SLIST *ptr)
{
  ptr->tail = ptr->head;
  ptr->head = reverse_(ptr->head);
}

void slist_destroy(struct SLIST *ptr)
{
  struct SListNode *cur = NULL;
  struct SListNode *nxt = NULL;

  for (cur = ptr->head; cur != NULL; cur = nxt)
  {
    nxt = cur->next;
    free(cur);
  }

  free(ptr);
}

