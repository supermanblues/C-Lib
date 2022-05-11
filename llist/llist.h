/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-02
 * @modify-date: 2020-05-11
 * @version: 0.0.3
 * @description: Doubly-Linked Circular List Header File
 */
/* ========================== LLIST Start ========================= */
#ifndef __LLIST_H__
#define __LLIST_H__

#define LLIST_HEAD_INIT(name) \
    name = (struct DuLNode) { .prev = &(name), .next = &(name) }

typedef enum { LLIST_FORWARD, LLIST_BACKWARD } LLIST_OPER_MODE;

typedef struct DuLNode
{
  struct DuLNode *prev;  /* 指向直接前驱结点的指针 */
  struct DuLNode *next;  /* 指向直接后继结点的指针 */
  char data[];           /* data field */
} DuLNode;

typedef struct LLIST
{
  int (*empty) (struct LLIST *);
  size_t (*size) (struct LLIST *);

  const void * (*front) (struct LLIST *);
  const void * (*rear) (struct LLIST *);

  int (*push_front) (struct LLIST *, const void *);
  int (*push_back) (struct LLIST *, const void *);

  int (*pop_front) (struct LLIST *, void *);
  int (*pop_back) (struct LLIST *, void *);

  int datasize;
  size_t length;
  struct DuLNode head;

} LLIST, DEQUE;

struct LLIST * llist_create(const int dataisze);
DEQUE * CreateDeque(const int datasize);

void llist_destroy(struct LLIST *);
void DestroyDeque(DEQUE *);

#endif
/* ========================== LLIST End ========================= */