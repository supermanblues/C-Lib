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

void slist_travel(struct SLIST *, visit);
void slist_reverse(struct SLIST *);
void slist_sort(struct SLIST *, compar *);

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
  ptr->sort    = slist_sort;

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

void slist_travel(struct SLIST *ptr, visit visit)
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

static inline SListNode * slist_merge(struct SListNode *l1, struct SListNode *l2, compar *cmp, struct SListNode **tail)
{
  struct SListNode dummy, *p = &dummy;

  if (l1 == NULL || l2 == NULL)
    return l1 != NULL ? l1 : l2;

  while (l1 != NULL && l2 != NULL)
  {
    if (cmp(l1->data, l2->data) < 0)
    {
      p = p->next = l1;
      l1 = l1->next;
    } 
    else
    {
      p = p->next = l2;
      l2 = l2->next;
    }
  }

  p->next = l1 ? l1 : l2;
  while (p->next != NULL)
    p = p->next;

  *tail = p;
  return dummy.next;
}

static struct SListNode * slist_sort_(struct SListNode *head, compar *cmp, struct SListNode **tail)
{
  struct SListNode *slow  = NULL;
  struct SListNode *fast  = NULL;
  struct SListNode *head2 = NULL;

  if (head == NULL || head->next == NULL)
    return head;

  slow = head, fast = head->next;
  while (fast != NULL && fast->next != NULL)
  {
    slow = slow->next;
    fast = fast->next->next;
  }

  head2 = slow->next;
  slow->next = NULL;

  return slist_merge(slist_sort_(head, cmp, tail), slist_sort_(head2, cmp, tail), cmp, tail);
}

void slist_sort(struct SLIST *ptr, compar *cmp)
{
  ptr->head = slist_sort_(ptr->head, cmp, &ptr->tail);
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

