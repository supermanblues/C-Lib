/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-19
 * @modify-date: 2020-05-19
 * @version: 0.0.1
 * @description: Set Unit Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "set.h"
#include <test-utils.h>

signed main(int argc, char const *argv[])
{
  int i, x;
  struct SET *set = NULL;

  set = set_create(sizeof(int), cmp_int);
  if (set == NULL)
  {
    fprintf(stderr, "The set create failed. GoodBye!");
    exit(EXIT_FAILURE);
  }

  assert( set->empty(set));
  assert( set->size(set) == 0);

  for (i = 0; i < DATA_SIZE; ++i)
    set->add(set, DATA + i, DATA + i);

  assert( !set->empty(set) );
  assert( set->size(set) == DATA_SIZE);

  assert( set->contains(set, DATA) );
  x = 123, assert( !set->contains(set, &x) );
  set->add(set, &x, &x), assert( set->contains(set, &x) );

  assert( set->contains(set, DATA + DATA_SIZE - 1) );
  set->remove(set, DATA + DATA_SIZE - 1);
  assert( !set->contains(set, DATA + DATA_SIZE - 1) );

  set_destroy(set);
  return ~~(1 ^ 1);
}