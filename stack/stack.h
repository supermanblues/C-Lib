/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-07
 * @version: 0.0.8
 * @description: SqStack Header File
 */
/* ========================= SqStack Start ========================= */
#ifndef __STACK_H__
#define __STACK_H__

#define STACK_LARGE_FACTOR    2

typedef struct SqStack
{
  void *base;    /* 顺序栈的基地址 */
  void *top;     /* 栈顶指针 */
  int capacity;  /* 顺序栈的最大容量 （支持动态扩容） */
  int datasize;  /* 元素数据块大小 */

  /* 是否栈空 */
  int (*empty) (struct SqStack *);
  
  /* 是否栈满 */
  int (*full) (struct SqStack *);
  
  /* 返回栈中元素数量 */
  size_t (*size) (struct SqStack *);

  /* 元素入栈 */
  int (*push) (struct SqStack *, const void *);

  /* 弹出栈顶元素 */
  int (*pop) (struct SqStack *, void *);

  /* 查看栈顶元素 */
  const void * (*get_top) (struct SqStack *);

} SqStack;

struct SqStack * 
CreateSqStack(const int capacity, const int datasize);

int StackEmpty(struct SqStack *);

int StackFull(struct SqStack *);

size_t StackLength(struct SqStack *);

int Push(struct SqStack *, const void *);

int Pop(struct SqStack *, void *);

const void * GetTop(struct SqStack *);

void DestroyStack(SqStack *);

#endif
/* ========================= SqStack End ========================= */