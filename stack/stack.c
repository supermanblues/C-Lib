#include <stdlib.h>
#include <string.h>

#include "stack.h"

struct SqStack *
CreateSqStack(const int capacity, const int datasize)
{
  struct SqStack *ptr = NULL;

  ptr = (struct SqStack *) malloc(sizeof *ptr);
  if (ptr == NULL)
    return NULL;

  ptr->base = malloc(capacity * datasize);
  if (!ptr->base) // 内存分配失败
    return NULL;

  ptr->top      = ptr->base;
  ptr->capacity = capacity;
  ptr->datasize = datasize;

  /* =============== Operations ============== */
  ptr->empty   = StackEmpty;
  ptr->full    = StackFull;
  ptr->size    = StackLength;
  ptr->push    = Push;
  ptr->pop     = Pop;
  ptr->get_top = GetTop;

  return ptr;
}

int StackEmpty(struct SqStack *ptr)
{
  return (ptr->top == ptr->base);
}

int StackFull(struct SqStack *ptr)
{
  return (ptr->top - ptr->base == ptr->capacity * ptr->datasize);
}

size_t StackLength(struct SqStack *ptr)
{
  return (ptr->top - ptr->base) / ptr->datasize;
}

static inline int large_(SqStack* ptr, float factor)
{
  void *new_base = NULL;

  new_base = realloc(ptr->base, ptr->capacity * factor * ptr->datasize);
  if (new_base == NULL)
    return -1;

  // void *new_base = malloc(ptr->capacity * factor * ptr->datasize);
  // if (!new_base)
  //   return -1;

  // memcpy(new_base, ptr->base, ptr->capacity * ptr->datasize); // copy data
  // free(ptr->base);  /* release old memory spaces! */

  ptr->base = new_base;
  ptr->top = ptr->base + ptr->capacity * ptr->datasize;
  ptr->capacity *= factor;

  return 0;
}

int Push(struct SqStack *ptr, const void *data)
{
  if (StackFull(ptr))
    large_(ptr, STACK_LARGE_FACTOR);

  memcpy(ptr->top, data, ptr->datasize);
  ptr->top += ptr->datasize; /* 栈顶指针向后移动一个位置 */ 
  return 0;
}

int Pop(struct SqStack *ptr, void *data)
{
  if (StackEmpty(ptr))
    return -1;

  ptr->top -= ptr->datasize; /* 栈顶指针向前移动一个位置 */
  if (data != NULL)
    memcpy(data, ptr->top, ptr->datasize); /* 回填数据 */

  return 0;
}

const void * GetTop(struct SqStack *ptr)
{
  if (StackEmpty(ptr))
    return NULL;

  return (ptr->top - ptr->datasize);
}

void DestroyStack(struct SqStack *ptr) 
{
  free(ptr->base);
  free(ptr);
}
