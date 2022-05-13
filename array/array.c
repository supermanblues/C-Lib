/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-13
 * @modify-date: 2020-05-13
 * @version: 0.0.1
 * @description: Dynamic Array Implementation File
 */
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "../sort/sort.h"

int arr_empty(struct ARRAY *);
int arr_full(struct ARRAY *);
size_t arr_size(struct ARRAY *);

const void * arr_get(struct ARRAY *, int index);
const void * arr_front(struct ARRAY *);
const void * arr_back(struct ARRAY *);

void * arr_find(struct ARRAY *, const void *key, compar *);

int arr_insert(struct ARRAY *, int, const void *);
int arr_delete(struct ARRAY *, int);

int arr_push_front(struct ARRAY *, const void *);
int arr_push_back(struct ARRAY *, const void *);
int arr_pop_front(struct ARRAY *);
int arr_pop_back(struct ARRAY *);

void arr_travel(struct ARRAY *, void (*visit) (const void *));
void arr_sort(struct ARRAY *, compar *);
void arr_reverse(struct ARRAY *);

struct ARRAY * CreateArray(size_t capacity, int datasize)
{
  struct ARRAY *ptr = NULL;

  if (capacity <= 0 || datasize <= 0)
    return NULL;

  ptr = (struct ARRAY *) malloc(sizeof *ptr);
  if (ptr == NULL)
    return NULL;

  ptr->base = malloc(capacity * datasize);
  if (ptr->base == NULL)
    return NULL;

  ptr->length   = 0;
  ptr->datasize = datasize;
  ptr->capacity = capacity;

  /* ================ Operations ================ */
  ptr->empty  = arr_empty;
  ptr->full   = arr_full;
  ptr->size   = arr_size;

  ptr->get    = arr_get;
  ptr->front  = arr_front;
  ptr->back   = arr_back;
  ptr->rear   = arr_back;

  ptr->find   = arr_find;
  ptr->insert = arr_insert;
  ptr->delete = arr_delete;

  ptr->push_front = arr_push_front;
  ptr->push_back  = arr_push_back;
  ptr->pop_front  = arr_pop_front;
  ptr->pop_back   = arr_pop_back;

  ptr->travel  = arr_travel;
  ptr->sort    = arr_sort;
  ptr->reverse = arr_reverse;

  return ptr;
}

int arr_empty(struct ARRAY *ptr)
{
  return (ptr->length == 0);
}

int arr_full(struct ARRAY *ptr)
{
  return (ptr->length == ptr->capacity);
}

size_t arr_size(struct ARRAY *ptr)
{
  return ptr->length;
}

const void * arr_get(struct ARRAY *ptr, int index)
{
  if (index < 0 || index >= ptr->length)
    return NULL;

  return (ptr->base + index * ptr->datasize);
}

const void * arr_front(struct ARRAY *ptr)
{
  return arr_get(ptr, 0);
}

const void * arr_back(struct ARRAY *ptr)
{
  return arr_get(ptr, ptr->length - 1);
}

void * arr_find(struct ARRAY *ptr, const void *key, compar *cmp)
{ // 顺序查找法
  int i;
  void *p;

  for (i = 0, p = ptr->base;
       i < ptr->length;
       ++i, p += ptr->datasize)
  {
    if (cmp(key, p) == 0)
      return p;
  }

  return NULL;
}

int arr_insert(struct ARRAY *ptr, int index, const void *data)
{
  void *p;

  if (arr_full(ptr))
  { // TODO: large_(ptr);
    return -1;
  }

  /* Be Careful：在数组中最后一个元素后面插入是合法的 */
  if (index < 0 || index > ptr->length)
    return -2;

  // Move
  for (p = ptr->base + (ptr->length - 1) * ptr->datasize;
       p >= ptr->base + index * ptr->datasize;
       p -= ptr->datasize)
  {
    __COPY_DATA_(p + ptr->datasize, p, ptr->datasize);
  }

  __COPY_DATA_(ptr->base + index * ptr->datasize, data, ptr->datasize);

  ++ptr->length;
  return 0;
}

int arr_push_front(struct ARRAY *ptr, const void *data)
{
  return arr_insert(ptr, 0, data);
}

int arr_push_back(struct ARRAY *ptr, const void *data)
{
  return arr_insert(ptr, ptr->length, data);
}

int arr_delete(struct ARRAY *ptr, int index)
{
  return 0;
}

int arr_pop_front(struct ARRAY *ptr)
{
  return arr_delete(ptr, 0);
}

int arr_pop_back(struct ARRAY *ptr)
{
  return arr_delete(ptr, ptr->length - 1);
}

void arr_travel(struct ARRAY *ptr, void (*visit) (const void *))
{
  int i = 0;
  void *p = ptr->base;

  for (; i < ptr->length; ++i, p += ptr->datasize)
    visit(p);

  return;
}

void arr_sort(struct ARRAY *ptr, compar *cmp)
{
  // qsort(ptr->base, ptr->length, ptr->datasize, cmp);
  struct MySort *sort = NULL;

  sort = CreateMySort();
  if (sort == NULL)
    return;

  sort->quick_sort(ptr->base, ptr->length, ptr->datasize, cmp);

  DestroyMySort(sort);
}

void arr_reverse(struct ARRAY *ptr)
{
  int i;
  void *base = NULL, *tmp = NULL;
  int datasize, len;

  tmp = malloc(ptr->datasize);
  if (tmp == NULL)
    return;

  base = ptr->base;
  len = ptr->length;
  datasize = ptr->datasize;

  for (i = 0; i < len >> 1; ++i)
  {
    __COPY_DATA_(tmp, base + i * datasize, datasize);
    __COPY_DATA_(base + i * datasize,  base + (len - 1 - i) * datasize, datasize);
    __COPY_DATA_(base + (len - 1 - i) * datasize, tmp, datasize);
  }

  return;
}

void DestroyArray(struct ARRAY *ptr)
{
  free(ptr->base);
  free(ptr);
}