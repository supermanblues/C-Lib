/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-02
 * @modify-date: 2020-05-26
 * @version: 0.0.7
 * @description: LinkQueue Header File (slist-based)
 */
/* ========================== LinkQueue Start ========================= */
#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#include <stdio.h>

typedef struct LinkQueue
{
  struct SLIST *lst;

  /** 判断队列是否为空 */
  int (*empty) (struct LinkQueue *);

  /** 返回队列中元素的个数 */
  size_t (*size) (struct LinkQueue *);

  /** 返回队头元素的内存地址 */
  const void * (*front) (struct LinkQueue *);

  /** 同上 */
  const void * (*peek) (struct LinkQueue *);

  /** 返回队尾元素的内存地址 */
  const void * (*back) (struct LinkQueue *);

  /** 同上 */
  const void * (*rear) (struct LinkQueue *);

  /** 入队 EnQueue */
  int (*push) (struct LinkQueue *, const void *);
  
  /** 出队 DeQueue */
  int (*pop) (struct LinkQueue *, void *);

} LinkQueue;

struct LinkQueue * lqu_create(int datasize);

void lqu_destroy(struct LinkQueue *);

#endif
/* ========================== LinkQueue End ========================= */
