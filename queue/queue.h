/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-25
 * @modify-date: 2020-05-15
 * @version: 0.0.5
 * @description: Sequence Queue Header File
 */
/* ========================== SqQueue Start ========================= */
#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct SqQueue
{
  void *base;      /* 存储空间的基地址 */
  int datasize;    /* 元素数据块大小 */
  size_t front;    /* 指向队头元素的指针 */
  size_t rear;     /* 指向队尾元素的指针 */
  size_t capacity; /* 队列中存储元素数量的上限 */

  /** 判断队列是否为空 */
  int (*empty) (struct SqQueue *);

  /** 判断队列是否为满 */
  int (*full) (struct SqQueue *);
  
  /** 返回队列中的元素的个数  */
  size_t (*size) (struct SqQueue *);
  
  /** 返回队头元素的内存地址 */
  const void * (*get_front) (struct SqQueue *);

  /** 返回队尾元素的内存地址 */
  const void * (*get_rear) (struct SqQueue *);

  /** 入队 EnQueue */
  int (*push) (struct SqQueue *, const void *);

  /** 出队 DeQueue */
  int (*pop) (struct SqQueue *, void *);

  /** 清空队列 */
  int (*clear) (struct SqQueue *);

} SqQueue;

struct SqQueue * CreateSqQueue(const int datasize, const size_t capacity);

void DestroyQueue(struct SqQueue *);
/* ========================== SqQueue End ========================= */
#endif