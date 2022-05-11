/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-02
 * @modify-date: 2020-05-10
 * @version: 0.0.6
 * @description: LinkStack Header File (llist-based)
 */
/* ========================== LinkStack Start ========================= */
#ifndef __LINKSTACK_H__
#define __LINKSTACK_H__

typedef struct LinkStack
{
  struct LLIST *lst;

  int (*empty) (struct LinkStack *);
  size_t (*size) (struct LinkStack *);

  const void * (*top) (struct LinkStack *);
  const void * (*peek) (struct LinkStack *);

  int (*push) (struct LinkStack *, const void *);
  int (*pop) (struct LinkStack *, void *);

} LinkStack;

struct LinkStack * CreateLinkStack(const int datasize);

void DestroyLinkStack(struct LinkStack *);

#endif
/* ========================== LinkStack End ========================= */