/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-19
 * @modify-date: 2020-05-23
 * @version: 0.0.2
 * @description: Set Header File
 */
/* ========================== Set Start ========================= */
#ifndef __SET_H__
#define __SET_H__

#if __clang__
typedef int (^compar)(const void *, const void *);
#else
typedef int compar(const void *, const void *);
#endif

typedef struct SET
{
  struct BST *bst;

  int (*empty) (struct SET *);
  size_t (*size) (struct SET *);

  int (*add) (struct SET *, const void *key, const void *data);
  int (*contains) (struct SET *, const void *key);
  int (*remove) (struct SET *, const void *key);

} SET;

#if __clang__
struct SET * set_create(int datasize, compar);
#else
struct SET * set_create(int datasize, compar *);
#endif

void set_destroy(struct SET *);
#endif
/* ========================== Set End ========================= */