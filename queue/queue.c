/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-25
 * @modify-date: 2020-05-27
 * @version: 1.0.0
 * @description: Sequence Queue Implementation File
 */
#include <stdlib.h>
#include <string.h>

#include "queue.h"

int qu_empty(struct SqQueue *);

int qu_full(struct SqQueue *);

size_t qu_size(struct SqQueue *);

const void * qu_front(struct SqQueue *);

const void * qu_rear(struct SqQueue *);

int qu_push(struct SqQueue *, const void *);

int qu_pop(struct SqQueue *, void *);

int qu_clear(struct SqQueue *);

struct SqQueue * qu_create(int datasize, size_t capacity)
{
  struct SqQueue *ptr = NULL;
  
  if (datasize <= 0 || capacity <= 0)
    return NULL;

  ptr = (struct SqQueue *) malloc(sizeof *ptr);
  if (ptr == NULL)
    return NULL;

  ptr->base = malloc((capacity + 1) * datasize);
  if (ptr->base == NULL)
    return NULL;

  ptr->front    = 0;
  ptr->rear     = 0;
  ptr->datasize = datasize;
  ptr->capacity = capacity + 1;

  /* =============== Operations =============== */
  ptr->empty = qu_empty;
  ptr->full  = qu_full;
  ptr->size  = qu_size;

  ptr->get_front = qu_front;
  ptr->get_rear  = qu_rear;

  ptr->push  = qu_push;
  ptr->pop   = qu_pop;
  ptr->clear = qu_clear;

  return ptr;
}

int qu_empty(struct SqQueue *ptr)
{
  return (ptr->front == ptr->rear);
}

int qu_full(struct SqQueue *ptr)
{
  return ((ptr->rear + 1) % ptr->capacity == ptr->front);
}

size_t qu_size(struct SqQueue *ptr)
{
  return (ptr->rear - ptr->front + ptr->capacity) % ptr->capacity;
}

const void * qu_front(struct SqQueue *ptr)
{
  if (qu_empty(ptr))
    return NULL;

  return (ptr->base + ptr->front * ptr->datasize);
}

const void * qu_rear(struct SqQueue *ptr)
{
  if (qu_empty(ptr))
    return NULL;

  int index = (ptr->rear - 1 + ptr->capacity) % ptr->capacity;

  return (ptr->base + index * ptr->datasize);
}

int qu_push(struct SqQueue *ptr, const void *data)
{
  if (qu_full(ptr))
    return -1;

  memcpy(ptr->base + ptr->rear * ptr->datasize, data, ptr->datasize);

  ptr->rear = (ptr->rear + 1) % ptr->capacity;

  return 0;
}

int qu_pop(struct SqQueue *ptr, void *data)
{
  if (qu_empty(ptr))
    return -1;
 
  if (data != NULL) /* 回填数据 */
    memcpy(data, ptr->base + ptr->front * ptr->datasize, ptr->datasize);

  ptr->front = (ptr->front + 1) % ptr->capacity;

  return 0;
}

int qu_clear(struct SqQueue *ptr)
{
  ptr->front = ptr->rear = 0;
  return 0;
}

void qu_destroy(struct SqQueue *ptr)
{
  free(ptr->base);
}