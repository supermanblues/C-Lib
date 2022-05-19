/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-14
 * @version: 0.1.0
 * @description: SqStack Implementation File
 */
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "../array/array.h"

int st_empty(struct SqStack *);
size_t st_size(struct SqStack *);

int st_push(struct SqStack *, const void *);
int st_pop(struct SqStack *, void *);

const void * st_top(struct SqStack *);

struct SqStack * CreateSqStack(int datasize)
{
  struct SqStack *ptr = NULL;

  if (datasize <= 0)
    return NULL;

  ptr = (struct SqStack *) malloc(sizeof *ptr);
  if (ptr == NULL)
    return NULL;

  ptr->arr = Create_Array(datasize);
  if (ptr->arr == NULL)
    return NULL;

  /* =============== Operations ============== */
  ptr->empty = st_empty;
  ptr->size  = st_size;
  ptr->push  = st_push;
  ptr->pop   = st_pop;
  ptr->top   = st_top;
  ptr->peek  = st_top;

  return ptr;
}

int st_empty(struct SqStack *ptr)
{
  struct ARRAY *arr = ptr->arr;

  return arr->empty(arr);
}

size_t st_size(struct SqStack *ptr)
{
  struct ARRAY *arr = ptr->arr;

  return arr->size(arr);
}

int st_push(struct SqStack *ptr, const void *data)
{
  struct ARRAY *arr = ptr->arr;

  return arr->push_back(arr, data);
}

int st_pop(struct SqStack *ptr, void *data)
{
  struct ARRAY *arr = ptr->arr;

  if (arr->empty(arr))
    return -1;
  
  if (data != NULL) // 回填数据
    __COPY_DATA_(data, arr->back(arr), arr->datasize);

  return arr->pop_back(arr);
}

const void * st_top(struct SqStack *ptr)
{
  struct ARRAY *arr = ptr->arr;

  return arr->back(arr);
}

void DestroyStack(struct SqStack *ptr) 
{
  arr_destroy(ptr->arr);
  free(ptr);
}