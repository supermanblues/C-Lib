/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-11
 * @version: 0.0.4
 * @description: Sorting Unit Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sort.h"
#include "../common/test-utils.h"

/* 面向切面（AOP）的编程思想 --- 小型的测试框架 */
void test_sort(sort *sort)
{
  int ints[] = { 49, 38, 65, 97, 76, 13, 27, 49, -2, 100, 229 };
  struct Student studs[] = {
      {5, "zhang", 44, 69},
      {2, "wang",  53, 71},
      {3, "liu",   98, 61},
      {1, "zhao",  53, 83},
      {4, "shun",  67, 92},
      {6, "gao",   98, 32},
  };

  size_t num = sizeof(ints) / sizeof(*ints);
  sort(ints, num, sizeof(*ints), cmp_int);
  // print_ints(ints, num);
  assert( is_sorted(ints, num, sizeof(*ints), cmp_int) );

  num = sizeof(studs) / sizeof(*studs);
  sort(studs, num, sizeof(*studs), cmp_stud);
  // print_studs(studs, num);
  assert( is_sorted(studs, num, sizeof(*studs), cmp_stud) );
}

signed main(int argc, char const *argv[])
{ 
  struct MySort *obj = NULL;

  obj = CreateMySort();
  if (obj == NULL)
  {
    fprintf(stderr, "The obj create failed, GoodBye!");
    exit(EXIT_FAILURE);
  }

  test_sort(obj->bubble_sort);
  test_sort(obj->select_sort);
  test_sort(obj->insert_sort);
  test_sort(obj->quick_sort);

  DestroyMySort(obj);
  return ~~(0 ^ 0);
}