/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-02
 * @modify-date: 2020-05-10
 * @version: 0.0.6
 * @description: LinkQueue Header File (llist-based)
 */
/* ========================== LinkQueue Start ========================= */
#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

typedef struct LinkQueue
{
  struct LLIST *lst;

  int (*empty) (struct LinkQueue *);
  size_t (*size) (struct LinkQueue *);

  const void * (*front) (struct LinkQueue *);
  const void * (*peek) (struct LinkQueue *);

  int (*push) (struct LinkQueue *, const void *);
  int (*pop) (struct LinkQueue *, void *);

} LinkQueue;

struct LinkQueue * CreateLinkQueue(const int dataisze);

void DestroyLinkQueue(struct LinkQueue *);

#endif
/* ========================== LinkQueue End ========================= */