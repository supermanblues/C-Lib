/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-19
 * @modify-date: 2020-05-19
 * @version: 0.0.1
 * @description: Set Header File
 */
/* ========================== Set Start ========================= */
#ifndef __SET_H__
#define __SET_H__

typedef int compar(const void *, const void *);

typedef struct SET
{
  struct BST *bst;

  int (*empty) (struct SET *);
  size_t (*size) (struct SET *);

  int (*add) (struct SET *, const void *key, const void *data);
  int (*contains) (struct SET *, const void *key);
  int (*remove) (struct SET *, const void *key);

} SET;

struct SET * set_create(int datasize, compar *);

void set_destroy(struct SET *);
#endif
/* ========================== Set End ========================= */