/*
 * @author: waingxiaoqiang
 * @create-date: 2020-04-13
 * @modify-date: 2020-05-14
 * @version: 0.0.5
 * @description: UnionFind Unit Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "union_find.h"
#include <test-utils.h>

signed main(int argc, char const *argv[])
{
  int i;
  struct UnionFind *uf;

  uf = uf_create(10);
  if (uf == NULL)
  {
    fprintf(stderr, "The uf create failed. GoodBye!");
    exit(EXIT_FAILURE);
  }

  assert(uf->size(uf) == 10);
  assert(!uf->connected(uf, 1, 2));
  uf->unite(uf, 1, 2);
  assert(uf->connected(uf, 1, 2));

  uf->unite(uf, 2, 3);
  assert(uf->connected(uf, 3, 2));
  assert(uf->connected(uf, 1, 3)); // 关系具有传递性

  assert(uf->size(uf) == 8);

  for (i = 4; i <= 10; ++i)
  {
    assert(!uf->connected(uf, i, 1));
    assert(!uf->connected(uf, i, 2));
    assert(!uf->connected(uf, i, 3));
  }

  uf_destroy(uf);
  return ~~(0 ^ 0);
}
