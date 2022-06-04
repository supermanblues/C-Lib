/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-02
 * @modify-date: 2020-05-15
 * @version: 0.0.7
 * @description: LinkStack Header File (slist-based)
 */
/* ========================== LinkStack Start ========================= */
#ifndef __LINKSTACK_H__
#define __LINKSTACK_H__

#include <stdio.h>

typedef struct LinkStack
{
  struct SLIST *lst;

  int (*empty) (struct LinkStack *);
  size_t (*size) (struct LinkStack *);

  const void * (*top) (struct LinkStack *);
  const void * (*peek) (struct LinkStack *);

  int (*push) (struct LinkStack *, const void *);
  int (*pop) (struct LinkStack *, void *);

} LinkStack;

struct LinkStack * CreateLinkStack(int datasize);

void DestroyLinkStack(struct LinkStack *);

#endif
/* ========================== LinkStack End ========================= */
