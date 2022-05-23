/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-19
 * @modify-date: 2020-05-19
 * @version: 0.0.1
 * @description: Set Implementation File
 */
#include <stdlib.h>

#include "set.h"
#include <bst.h>

int set_empty(struct SET *);
size_t set_size(struct SET *);

int set_add(struct SET *, const void *, const void *);
int set_contains(struct SET *, const void *);
int set_remove(struct SET *, const void *);

struct SET * set_create(int datasize,
                      #if __clang__
                        compar compar)
                      #else
                        compar *compar)
                      #endif
{
  struct SET *ptr = NULL;

  if (datasize <= 0)
    return NULL;

  ptr = (struct SET *) malloc(sizeof *ptr);
  if (ptr == NULL)
    return NULL;

  ptr->bst = bst_create(datasize, compar, NULL);
  if (ptr->bst == NULL)
    return NULL;

  /* =============== Operations =============== */
  ptr->empty    = set_empty;
  ptr->size     = set_size;
  ptr->add      = set_add;
  ptr->contains = set_contains;
  ptr->remove   = set_remove;

  return ptr;
}

int set_empty(struct SET *ptr)
{
  struct BST *bst = ptr->bst;

  return bst->empty(bst);
}

size_t set_size(struct SET *ptr)
{
  struct BST *bst = ptr->bst;

  return bst->size(bst);
}

int set_add(struct SET *ptr, const void *key, const void *data)
{
  struct BST *bst = ptr->bst;
  
  return bst->insert(bst, key, data);
}

int set_contains(struct SET *ptr, const void *key)
{
  struct BST *bst = ptr->bst;
  
  return (bst->search(bst, key) != NULL);
}

int set_remove(struct SET *ptr, const void *key)
{
  struct BST *bst = ptr->bst;
  
  return bst->delete(bst, key);
}

void set_destroy(struct SET *ptr)
{
  bst_destroy(ptr->bst);
  free(ptr);
}