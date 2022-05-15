/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-02
 * @modify-date: 2020-05-10
 * @version: 0.0.6
 * @description: LinkStack Implementation File (llist-based)
 */
#include <stdlib.h>

#include "linkstack.h"
#include "../llist/slist.h"

int lstk_empty(struct LinkStack *);
size_t lstk_size(struct LinkStack *);

const void * lstk_top(struct LinkStack *);
const void * lstk_peek(struct LinkStack *);

int lstk_push(struct LinkStack *, const void *);
int lstk_pop(struct LinkStack *, void *);

struct LinkStack * CreateLinkStack(int datasize)
{
  struct LinkStack *ptr = NULL;

  if (datasize <= 0)
    return NULL;

  ptr = (struct LinkStack *) malloc(sizeof *ptr);
  if (ptr == NULL)
    return NULL;

  ptr->lst = slist_create(datasize);
  if (ptr->lst == NULL)
    return NULL;

  /* ================ Operations =============== */
  ptr->empty = lstk_empty;
  ptr->size  = lstk_size;
  ptr->top   = lstk_top;
  ptr->peek  = lstk_top;
  ptr->push  = lstk_push;
  ptr->pop   = lstk_pop;

  return ptr;
}

int lstk_empty(struct LinkStack *ptr)
{
  struct SLIST *lst = ptr->lst;

  return lst->empty(lst);
}

size_t lstk_size(struct LinkStack *ptr)
{
  struct SLIST *lst = ptr->lst;

  return lst->size(lst);
}

const void * lstk_top(struct LinkStack *ptr)
{
  struct SLIST *lst = ptr->lst;

  return lst->front(lst);
}

int lstk_push(struct LinkStack *ptr, const void *data)
{
  struct SLIST *lst = ptr->lst;

  return lst->push_front(lst, data);
}

int lstk_pop(struct LinkStack *ptr, void *data)
{
  struct SLIST *lst = ptr->lst;

  return lst->pop_front(lst, data);
}

void DestroyLinkStack(struct LinkStack *ptr)
{
  slist_destroy(ptr->lst);  
  free(ptr);
}
