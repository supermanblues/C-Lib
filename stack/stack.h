/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-14
 * @version: 0.1.0
 * @description: SqStack Header File
 */
/* ========================= SqStack Start ========================= */
#ifndef __STACK_H__
#define __STACK_H__

#define st_create(datasize) CreateSqStack(datasize)
#define st_destroy(ptr) DestroyStack(ptr);

typedef struct SqStack
{
  struct ARRAY *arr;

  /** 判断栈是否为空 */
  int (*empty) (struct SqStack *);
  
  /** 返回栈中元素的个数 */
  size_t (*size) (struct SqStack *);

  /** 压栈一个元素 */
  int (*push) (struct SqStack *, const void *);

  /** 从栈中弹出一个元素 */
  int (*pop) (struct SqStack *, void *);

  /** 获取栈顶元素的内存地址 */
  const void * (*top) (struct SqStack *);

  /** 同上 */
  const void * (*peek) (struct SqStack *);

} SqStack;

struct SqStack * CreateSqStack(int datasize);

void DestroyStack(struct SqStack *);

#endif
/* ========================= SqStack End ========================= */