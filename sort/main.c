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
#include <test-utils.h>

/* 面向切面（AOP）的编程思想 --- 小型的测试框架 */
void test_sort(struct MySort *ps, SORT_MODE mode)
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

  int (^int_asc)(const void *, const void *) = ^(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
  };

  int (^cmp_stud)(const void *, const void *) = ^(const void *a, const void *b) {
    const struct Student *s1 = (struct Student *) a;
    const struct Student *s2 = (struct Student *) b;

    /* 按数学成绩从高到低排序 */
    if (s1->math != s2->math)
      return s2->math - s1->math;

    /* 按学号从小到大排序 */
    return (s1->id - s2->id);
  };

  ps->sort(ints, num, sizeof(*ints), int_asc, mode);
  assert( is_sorted(ints, num, sizeof(*ints), int_asc) );

  num = sizeof(studs) / sizeof(*studs);
  ps->sort(studs, num, sizeof(*studs), cmp_stud, mode);
  assert( is_sorted(studs, num, sizeof(*studs), cmp_stud) );
}

signed main(int argc, char const *argv[])
{ 
  struct MySort *ps = NULL;

  ps = mysort_create();
  if (ps == NULL)
  {
    fprintf(stderr, "The ps create failed, GoodBye!");
    exit(EXIT_FAILURE);
  }

  test_sort(ps, BUBBLE_SORT);
  test_sort(ps, SELECTION_SORT);
  test_sort(ps, INSERTION_SORT);
  test_sort(ps, QUICK_SORT);

  mysort_destroy(ps);
  return ~~(0 ^ 0);
}