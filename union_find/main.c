#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "union_find.h"
#include "../common/test-utils.h"

signed main(int argc, char const *argv[]) {

  int i;

  struct UnionFind *uf;
  uf = CreateUnionFind(10);

  assert(uf->comp_size(uf) == 10);

  assert(!uf->connected(uf, 1, 2));
  uf->unite(uf, 1, 2);
  assert(uf->connected(uf, 1, 2));

  uf->unite(uf, 2, 3);
  assert(uf->connected(uf, 3, 2));
  assert(uf->connected(uf, 1, 3)); // 关系具有传递性

  assert(uf->comp_size(uf) == 8);
  for (i = 4; i <= 10; ++i)
  {
    assert(!uf->connected(uf, i, 1));
    assert(!uf->connected(uf, i, 2));
    assert(!uf->connected(uf, i, 3));
  }

  DestroyUnionFind(uf);
  return ~~(0 ^ 0);
}
