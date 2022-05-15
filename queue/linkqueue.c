/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-02
 * @modify-date: 2020-05-10
 * @version: 0.0.6
 * @description: LinkQueue Implementation File (llist-based)
 */
#include <stdlib.h>

#include "linkqueue.h"
#include "../llist/slist.h"

int lqu_empty(struct LinkQueue *);
size_t lqu_size(struct LinkQueue *);

const void * lqu_front(struct LinkQueue *);
const void * lqu_back(struct LinkQueue *);

int lqu_push(struct LinkQueue *, const void *);
int lqu_pop(struct LinkQueue *, void *);

struct LinkQueue * CreateLinkQueue(int datasize)
{
  struct LinkQueue *ptr = NULL;

  if (datasize <= 0)
    return NULL;

  ptr = (struct LinkQueue *) malloc(sizeof *ptr);
  if (ptr == NULL)
    return NULL;

  ptr->lst = slist_create(datasize);
  if (ptr->lst == NULL)
    return NULL;

  /* ============== Operations ============== */
  ptr->empty = lqu_empty;
  ptr->size  = lqu_size;

  ptr->front = lqu_front;
  ptr->peek  = lqu_front;
  
  ptr->back  = lqu_back;
  ptr->rear  = lqu_back;
  
  ptr->push  = lqu_push;
  ptr->pop   = lqu_pop;

  return ptr;
}

int lqu_empty(struct LinkQueue *ptr)
{
  struct SLIST *lst = ptr->lst;

  return lst->empty(lst);
}

size_t lqu_size(struct LinkQueue *ptr)
{
  struct SLIST *lst = ptr->lst;

  return lst->size(lst);
}

const void * lqu_front(struct LinkQueue *ptr)
{
  struct SLIST *lst = ptr->lst;

  return lst->front(lst);
}

const void * lqu_back(struct LinkQueue *ptr)
{
  struct SLIST *lst = ptr->lst;

  return lst->back(lst);
}

int lqu_push(struct LinkQueue *ptr, const void *data)
{
  struct SLIST *lst = ptr->lst;

  return lst->push_back(lst, data);
}

int lqu_pop(struct LinkQueue *ptr, void *data)
{
  struct SLIST *lst = ptr->lst;

  return lst->pop_front(lst, data);
}

void DestroyLinkQueue(struct LinkQueue *ptr)
{
  slist_destroy(ptr->lst);  
  free(ptr);
}
