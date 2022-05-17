/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-13
 * @modify-date: 2020-05-16
 * @version: 0.0.3
 * @description: Dynamic Array Implementation File
 */
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "../sort/sort.h"

int arr_empty(struct ARRAY *);
int arr_full(struct ARRAY *);
size_t arr_size(struct ARRAY *);

void * arr_get(struct ARRAY *, int index);
void * arr_front(struct ARRAY *);
void * arr_back(struct ARRAY *);

void * arr_find(struct ARRAY *, const void *key, match *);

int arr_insert(struct ARRAY *, int, const void *);
int arr_delete(struct ARRAY *, int);
int arr_delete_row(struct ARRAY *, int);

int arr_push_front(struct ARRAY *, const void *);
int arr_push_back(struct ARRAY *, const void *);
int arr_pop_front(struct ARRAY *);
int arr_pop_back(struct ARRAY *);

void arr_init(struct ARRAY *, const void *);
void arr_travel(struct ARRAY *, void (*visit) (const void *));
void arr_sort(struct ARRAY *, compar *, int);
void arr_reverse(struct ARRAY *);

struct ARRAY * CreateArray(size_t init_capacity, int datasize)
{
  struct ARRAY *ptr = NULL;

  if (init_capacity <= 0 || datasize <= 0)
    return NULL;

  ptr = (struct ARRAY *) malloc(sizeof *ptr);
  if (ptr == NULL)
    return NULL;

  ptr->base = malloc(init_capacity * datasize);
  if (ptr->base == NULL)
    return NULL;
  
  ptr->datasize = datasize;
  ptr->length   = 0;
  ptr->capacity = init_capacity;

  /* ================ Operations ================ */
  ptr->empty = arr_empty;
  ptr->full  = arr_full;
  ptr->size  = arr_size;

  ptr->get   = arr_get;
  ptr->front = arr_front;
  ptr->back  = arr_back;
  ptr->rear  = arr_back;

  ptr->find       = arr_find;
  ptr->insert     = arr_insert;
  ptr->delete     = arr_delete;
  ptr->delete_row = arr_delete_row;

  ptr->push_front = arr_push_front;
  ptr->push_back  = arr_push_back;
  ptr->pop_front  = arr_pop_front;
  ptr->pop_back   = arr_pop_back;

  ptr->init    = arr_init;
  ptr->travel  = arr_travel;
  ptr->sort    = arr_sort;
  ptr->reverse = arr_reverse;

  return ptr;
}

struct ARRAY * arr_create(size_t init_capacity, int datasize)
{
  return CreateArray(init_capacity, datasize);
}

struct ARRAY * arr_create2D(size_t init_capacity, int datasize)
{
  int i;
  struct ARRAY *row    = NULL;
  struct ARRAY *arr_2d = NULL;

  arr_2d = arr_create(init_capacity, sizeof(struct ARRAY *));
  if (arr_2d == NULL)
    return NULL;

  for (i = 0; i < init_capacity; ++i)
  {
    row = Create_Array(datasize);
    if (row == NULL)
      return NULL;

    arr_2d->push_back(arr_2d, &row);
  }

  return arr_2d;
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

void * arr_get(struct ARRAY *ptr, int index)
{
  if (index < 0 || index >= ptr->length)
    return NULL;

  return (ptr->base + index * ptr->datasize);
}

void * arr_front(struct ARRAY *ptr)
{
  return arr_get(ptr, 0);
}

void * arr_back(struct ARRAY *ptr)
{
  return arr_get(ptr, ptr->length - 1);
}

void * arr_find(struct ARRAY *ptr, const void *key, match *match)
{ // 循序查找法
  int i;
  void *p;

  for (i = 0, p = ptr->base;
       i < ptr->length;
       ++i, p += ptr->datasize)
  {
    if (match(key, p) == 0)
      return p;
  }

  return NULL;
}

static inline void large_(struct ARRAY *ptr)
{
  void *new_base = NULL;

  new_base = realloc(ptr->base, (ptr->capacity << 1) * ptr->datasize);
  if (new_base == NULL)
    return;

  ptr->base = new_base;
  ptr->capacity <<= 1;
}

int arr_insert(struct ARRAY *ptr, int index, const void *data)
{
  void *p;

  /* Be Careful：在数组中最后一个元素后面插入是合法的 */
  if (index < 0 || index > ptr->length)
    return -1;

  if (arr_full(ptr))
    large_(ptr);

  // Move Data
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
  int i;

  if (index < 0 || index >= ptr->length)
    return -1;

  // Move Data
  for (i = index + 1; i < ptr->length; ++i)
    __COPY_DATA_(ptr->base + (i - 1) * ptr->datasize, ptr->base + i * ptr->datasize, ptr->datasize);

  --ptr->length;
  return 0;
}

// 册除并释放内存
int arr_delete_row(struct ARRAY *ptr, int index)
{ 
  int i;
  struct ARRAY *row;

  if (index < 0 || index >= ptr->length)
    return -1;

  row = *(struct ARRAY **) ptr->get(ptr, index);
  arr_destroy(row);

  // Move Data
  for (i = index + 1; i < ptr->length; ++i)
    __COPY_DATA_(ptr->base + (i - 1) * ptr->datasize, ptr->base + i * ptr->datasize, ptr->datasize);

  --ptr->length;
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

void arr_init(struct ARRAY *ptr, const void *data)
{
  int i;

  for (i = 0; i < ptr->length; ++i)
    __COPY_DATA_(ptr->base + i * ptr->datasize, data, ptr->datasize);

  return;
}

void arr_travel(struct ARRAY *ptr, void (*visit) (const void *))
{
  int i = 0;
  void *p = ptr->base;

  for (; i < ptr->length; ++i, p += ptr->datasize)
    visit(p);

  return;
}

void arr_sort(struct ARRAY *ptr, compar *cmp, int mode)
{
  struct MySort *ps = NULL;

  ps = CreateMySort();
  if (ps == NULL)
    return;

  ps->sort(ptr->base, ptr->length, ptr->datasize, cmp, mode);

  DestroyMySort(ps);
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

  free(tmp);
}

void DestroyArray(struct ARRAY *ptr)
{
  free(ptr->base);
  free(ptr);
}

void arr_destroy(struct ARRAY *ptr)
{
  DestroyArray(ptr);
}

void arr_destroy2D(struct ARRAY *ptr)
{
  int i;
  struct ARRAY *row = NULL;

  for (i = 0; i < ptr->length; ++i)
  {
    row = *(struct ARRAY **) ptr->get(ptr, i);
    arr_destroy(row);
  }

  arr_destroy(ptr);
}