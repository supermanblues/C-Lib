/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-02
 * @modify-date: 2020-05-16
 * @version: 0.0.2
 * @description: Singly-Linked List Header File
 */
/* ========================== Singly Linked List Start ========================= */
#ifndef __SLIST_H__
#define __SLIST_H__

#define __SLIST_FOR_EACH_(pos, head) \
    for (pos = head; pos != NULL; pos = pos->next)

#ifndef __COPY_DATA_
#define __COPY_DATA_(dst, src, size) memcpy(dst, src, size)
#endif

typedef int compar(const void *, const void *);
typedef void (^visit)(const void *);

typedef struct SListNode
{
  struct SListNode *next; /** 指向其直接后继节点的指针域 */
  char data[];            /** 数据域 */
} SListNode;

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

  void (*travel) (struct SLIST *, visit);
  void (*reverse) (struct SLIST *);
  void (*sort) (struct SLIST *, compar *);

} SLIST;

struct SLIST * slist_create(int datasize);

void slist_destroy(struct SLIST *);

#endif
/* ========================== Singly Linked List End   ========================= */