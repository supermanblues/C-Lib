/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-02
 * @modify-date: 2020-05-15
 * @version: 0.0.1
 * @description: Singly-Linked List Header File
 */
/* ========================== Singly Linked List Start ========================= */
#ifndef __SLIST_H__
#define __SLIST_H__

#ifndef __COPY_DATA_
#define __COPY_DATA_(dst, src, size) memcpy(dst, src, size)
#endif

typedef void visit(const void *);

typedef struct SListNode
{
  struct SListNode *next;
  char data[];
} SListNode;

// forward-list
typedef struct SLIST
{
  int datasize;
  size_t length;
  struct SListNode *head;
  struct SListNode *tail;

  int (*empty) (struct SLIST *);
  size_t (*size) (struct SLIST *);

  const void * (*front) (struct SLIST *);
  const void * (*back) (struct SLIST *);
  const void * (*rear) (struct SLIST *);

  int (*push_front) (struct SLIST *, const void *);
  int (*push_back) (struct SLIST *, const void *);
  int (*pop_front) (struct SLIST *, void *);

  void (*travel) (struct SLIST *, visit *);
  void (*reverse) (struct SLIST *);
  void (*sort) (struct SLIST *);

} SLIST;

struct SLIST * slist_create(int datasize);

void slist_destroy(struct SLIST *);

#endif
/* ========================== Singly Linked List End   ========================= */