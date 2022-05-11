#include <stdlib.h>

#include "union_find.h"

int find(struct UnionFind *, int);
int unite(struct UnionFind *, int, int);
int connected(struct UnionFind *, int, int);
int comp_size(struct UnionFind *);

struct UnionFind * CreateUnionFind(int initsize)
{
  // 守护
  if (initsize <= 0)
    return NULL;

  int i, *p = NULL;
  struct UnionFind *uf;

  uf = malloc(sizeof *uf);
  if (uf == NULL)
    return NULL;

  p = (int*) malloc((initsize + 1) * sizeof(int));
  if (p == NULL)
    return NULL;

  for (i = 0; i <= initsize; ++i)
    *(p + i) = i;

  uf->parents   = p;
  uf->count     = initsize;
  uf->find      = find;
  uf->unite     = unite;
  uf->connected = connected;
  uf->comp_size = comp_size;

  return uf;
}

int find(struct UnionFind *uf, int x)
{
  int *p = uf->parents;
  if (p[x] ^ x) p[x] = find(uf, p[x]);
  return p[x];
}

int unite(struct UnionFind *uf, int u, int v)
{
  u = find(uf, u), v = find(uf, v);
  if (u == v)
    return 0;

  uf->parents[u] = v;
  --uf->count;
  return 1;
}

int connected(struct UnionFind *uf, int u, int v)
{
  return (find(uf, u) == find(uf, v));
}

/**
 * 返回联通分量的数量 
 */
int comp_size(struct UnionFind *uf)
{
  return uf->count;
}

void DestroyUnionFind(struct UnionFind *uf) {
  free(uf->parents);
}