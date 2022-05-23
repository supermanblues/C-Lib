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

#if __clang__
int is_sorted(const void *data,
              const size_t num,
              const size_t size,
              int (^compar)(const void *, const void *))
{
  const void *p;

  for (p = data; p < data + (num - 1) * size; p += size)
    if (compar(p, p + size) > 0)
      return 0;

  return 1;
}
#endif

int is_sorted2(const void *data,
              const size_t num,
              const size_t size,
              int (*compar)(const void *, const void *))
{
  const void *p;

  for (p = data; p < data + (num - 1) * size; p += size)
    if (compar(p, p + size) > 0)
      return 0;

  return 1;
}