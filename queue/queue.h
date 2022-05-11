/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-25
 * @modify-date: 2020-05-05
 * @version: 0.0.3
 * @description: SqQueue Header File
 */
/* ========================== SqQueue Start ========================= */
#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct SqQueue
{
  void *base;      /* 存储空间的基地址 */
  int datasize;    /* 元素数据块大小 */
  size_t front;    /* 队头指针 */
  size_t rear;     /* 队尾指针 */
  size_t capacity; /* 队列中存储元素数量的上限 */

  /* 队列是否为空 */
  int (*empty) (struct SqQueue *);

  /* 队列是否已经满了 */
  int (*full) (struct SqQueue *);
  
  /* 获取队列中的元素数量  */
  size_t (*size) (struct SqQueue *);
  
  /* 查看队头元素 */
  const void * (*get_front) (struct SqQueue *);

  /* 查看队尾元素 */
  const void * (*get_rear) (struct SqQueue *);

  /* 入队元素 */
  int (*push) (struct SqQueue *, const void *);

  /* 出队元素 */
  int (*pop) (struct SqQueue *, void *);

  /* 清空队列 */
  int (*clear) (struct SqQueue *);

} SqQueue;

struct SqQueue * CreateSqQueue(const int datasize, const size_t capacity);

void DestroyQueue(SqQueue *);
/* ========================== SqQueue End ========================= */
#endif