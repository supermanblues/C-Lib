/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-10
 * @modify-date: 2020-05-11
 * @version: 0.0.7
 * @description: Unit Test Hepler Functions Implementation File
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test-utils.h"

int cmp_int(const void *a, const void *b)
{
  return *(int*) a - *(int*) b;
}

int cmp_stud(const void *a, const void *b)
{
  const struct Student *s1 = (struct Student *) a;
  const struct Student *s2 = (struct Student *) b;

  /* 按数学成绩从高到低排序 */
  if (s1->math != s2->math)
    return s2->math - s1->math;

  /* 按学号从小到大排序 */
  return (s1->id - s2->id);
}

void print_int(const void *r)
{
  if (r == NULL)
    return;

  printf("%d ", *(int *) r);
}

void print_s(const void *r)
{
  if (r == NULL)
    return;

  const struct Student *s = (struct Student *) r;
  printf("id: %d\tname: %s\tmath: %d\tchinese: %d\n", s->id, s->name, s->math, s->chinese);
}

void reverse(void *arr, const size_t num, const size_t size)
{
  int i;
  void *tmp = NULL;

  tmp = malloc(size);
  if (tmp == NULL)
    return;

  for (i = 0; i < num >> 1; ++i)
  {
    __COPY_DATA_(tmp, arr + i * size, size);
    __COPY_DATA_(arr + i * size, arr + (num - 1 - i) * size, size);
    __COPY_DATA_(arr + (num - 1 - i) * size, tmp, size);
  }

  free(tmp);
}

int is_sorted(const void *data,
              const size_t num,
              const size_t size,
              int (*compar) (const void *, const void *))
{
  const void *p;

  for (p = data; p < data + (num - 1) * size; p += size)
    if (compar(p, p + size) > 0)
      return 0;

  return 1;
}