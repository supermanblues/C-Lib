/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-02
 * @modify-date: 2020-05-23
 * @version: 0.0.3
 * @description: Singly-Linked List Header File
 */
/* ========================== Singly Linked List Start ========================= */
#ifndef __SLIST_H__
#define __SLIST_H__

#include <stdio.h>

#define __SLIST_FOR_EACH_(pos, head) \
    for (pos = head; pos != NULL; pos = pos->next)

#ifndef __COPY_DATA_
#define __COPY_DATA_(dst, src, size) memcpy(dst, src, size)
#endif

#if __clang__
typedef void (^visit)(const void *);
typedef void (^callback)(int index, void *, const void *);
#else
typedef void visit(const void *);
typedef void callback(int index, void *, const void *);

#endif

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

  void (*reverse) (struct SLIST *);

#if __clang__
  void (*travel) (struct SLIST *, visit);
  
  void (*accumulate) (struct SLIST *, void *, callback);

#else
  void (*travel) (struct SLIST *, visit *);

  void (*accumulate) (struct SLIST *, void *, callback *);
#endif

} SLIST;

struct SLIST * slist_create(int datasize);

void slist_destroy(struct SLIST *);

#endif
/* ========================== Singly Linked List End   ========================= */
