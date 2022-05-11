/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-25
 * @modify-date: 2020-05-05
 * @version: 0.0.3
 * @description: SqQueue Implementation File
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

struct SqQueue * CreateSqQueue(const int datasize, const size_t capacity)
{
  struct SqQueue *qu = NULL;

  qu = (struct SqQueue *) malloc(sizeof *qu);
  if (qu == NULL)
    return NULL;

  qu->base = malloc((capacity + 1) * datasize);
  if (qu->base == NULL)
    return NULL;

  qu->front    = 0;
  qu->rear     = 0;
  qu->datasize = datasize;
  qu->capacity = capacity + 1;

  /* =============== Operations =============== */
  qu->empty = qu_empty;
  qu->full  = qu_full;
  qu->size  = qu_size;

  qu->get_front = qu_front;
  qu->get_rear  = qu_rear;

  qu->push  = qu_push;
  qu->pop   = qu_pop;
  qu->clear = qu_clear;

  return qu;
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

void DestroyQueue(struct SqQueue *ptr)
{
  free(ptr->base);
}