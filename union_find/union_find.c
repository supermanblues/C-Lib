/**
 * @author: wangxiaoqiang
 * @version: 0.0.4
 * @create-date: 2022-04-25
 * @modify-date: 2022-05-23
 * @description: UnionFind Implementation File
 */
#include <stdio.h>
#include <stdlib.h>

#include "union_find.h"
#include <array.h>

size_t uf_size(struct UnionFind *);
int uf_find(struct UnionFind *, int);
int uf_unite(struct UnionFind *, int, int);
int uf_connected(struct UnionFind *, int, int);

struct UnionFind * uf_create(int initsize)
{
  int i;
  struct UnionFind *ptr = NULL;
  struct ARRAY *parents = NULL;

  if (initsize <= 0)
    return NULL; 

  ptr = (struct UnionFind *) malloc(sizeof *ptr);
  if (ptr == NULL)
    return NULL;

  parents = arr_create(initsize + 1, sizeof(int));
  if (parents == NULL)
    return NULL;

  // init union_find
  for (i = 0; i <= initsize; ++i)
    parents->push_back(parents, &i);

  ptr->count     = initsize;
  ptr->parents   = parents;

  /* =============== Operations =============== */
  ptr->size      = uf_size;
  ptr->find      = uf_find;
  ptr->unite     = uf_unite;
  ptr->connected = uf_connected;

  return ptr;
}

size_t uf_size(struct UnionFind *ptr)
{
  return ptr->count;
}

int uf_find(struct UnionFind *ptr, int x)
{
  int *pi = NULL;
  struct ARRAY *parents = NULL;

  parents = ptr->parents;
  pi = parents->get(parents, x);

  if (*pi ^ x)
    *pi = uf_find(ptr, *pi);
  
  return *pi;
}

int uf_unite(struct UnionFind *ptr, int u, int v)
{

  struct ARRAY *parents = NULL;

  u = uf_find(ptr, u), v = uf_find(ptr, v);
  if (u == v)
    return 0;

  parents = ptr->parents;
  *(int *) parents->get(parents, u) = v;
  --ptr->count;

  return 1;
}

int uf_connected(struct UnionFind *ptr, int u, int v)
{
  return (uf_find(ptr, u) == uf_find(ptr, v));
}

void uf_destroy(struct UnionFind *ptr) {
  arr_destroy(ptr->parents);
  free(ptr);
}