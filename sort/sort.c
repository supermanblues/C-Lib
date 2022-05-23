/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-14
 * @version: 0.0.5
 * @description: Various Sorting Algorithm Implementation File
 */
#include <stdlib.h>
#include <string.h>

#include "sort.h"

#if __clang__
void mysort_sort(void *, const size_t, const size_t, compar, int);
#else
void mysort_sort(void *, const size_t, const size_t, compar *, int);
#endif
 
struct MySort * mysort_create(void)
{
  struct MySort *ptr = NULL;

  ptr = (struct MySort *) malloc(sizeof *ptr);
  if (ptr == NULL)
    return NULL;

  ptr->sort = mysort_sort;
  return ptr;
}

static inline void swap(void *a, void *b, size_t size)
{
  int i;

  for (i = 0; i < size; ++i)
  {
    *(char *) (a + i) ^= *(char *) (b + i);
    *(char *) (b + i) ^= *(char *) (a + i);
    *(char *) (a + i) ^= *(char *) (b + i);
  }
}

static void bubble_sort(void *base,
                        const size_t num,
                        const size_t size,
                      #if __clang__ 
                        compar compar)
                      #else
                        compar *compar)
                      #endif
{
  int i, j;
  int exchange;

  for (i = 0; i < num - 1; ++i)
  {
    exchange = 0;
    for (j = 0; j < num - 1 - i; ++j)
    {
      if (compar(base + j * size, base + (j + 1) * size) > 0)
      {
        swap(base + j * size, base + (j + 1) * size, size);
        exchange = 1;
      }
    }

    if (!exchange)
      break;
  }
}

static void select_sort(void *base,
                        const size_t num,
                        const size_t size,
                      #if __clang__ 
                        compar compar)
                      #else
                        compar *compar)
                      #endif
{
  int i, j, k;

  for (i = 0; i < num - 1; ++i)
  {
    k = i;
    for (j = i + 1; j < num; ++j)
      if (compar(base + j * size, base + k * size) < 0)
        k = j;

    if (k != i)
      swap(base + i * size , base + k * size, size);
  }
}

static void insert_sort(void *base,
                        const size_t num,
                        const size_t size,
                      #if __clang__ 
                        compar compar)
                      #else
                        compar *compar)
                      #endif
{
  int i, j;
  void *tmp = NULL;

  tmp = malloc(size);
  if (tmp == NULL)
    return;

  for (i = 1; i < num; ++i)
  {
    __COPY_DATA_(tmp, base + i * size, size);

    for (j = i - 1; j >= 0 && compar(tmp, base + j * size) < 0; --j)
      __COPY_DATA_(base + (j + 1) * size, base + j * size, size);

    if (j + 1 != i)
      __COPY_DATA_(base + (j + 1) * size, tmp, size);
  }
  
  free(tmp);
}

static void q_sort(void *base, 
                   int l,
                   int r,
                   const size_t size, 
                 #if __clang__ 
                   compar compar)
                 #else
                   compar *compar)
                 #endif
{
  int i = l, j = r;

  if (i >= j)
    return;

  while (i < j)
  {
    while (i < j && compar(base + j * size, base + i * size) >= 0)
      --j;

    if (i < j) 
      swap(base + i++ * size, base + j * size, size);

    while (i < j && compar(base + i * size, base + j * size) <= 0)
      ++i;

    if (i < j) 
      swap(base + i * size, base + j-- * size, size);
  }

  q_sort(base, l, i - 1, size, compar);
  q_sort(base, i + 1, r, size, compar);
}

static void quick_sort(void *base,
                       const size_t num,
                       const size_t size,
                     #if __clang__ 
                       compar compar)
                     #else
                       compar *compar)
                     #endif
{
  q_sort(base, 0, num - 1, size, compar);
}

void mysort_sort(void *base,
                 const size_t num,
                 const size_t size,
             #if __clang__ 
                compar compar,
             #else
                compar *compar,
             #endif
                int mode)
{
  switch (mode)
  {
    case BUBBLE_SORT:
      bubble_sort(base, num, size, compar);
      break;
    case SELECTION_SORT:
      select_sort(base, num, size, compar);
      break;
    case INSERTION_SORT:
      insert_sort(base, num, size, compar);
      break;
    case QUICK_SORT:
      quick_sort(base, num, size, compar);
      break;
    case MERGE_SORT:
      // TODO: MERGE_SORT
      break;
    default:
      break;
  }
}

void mysort_destroy(struct MySort *ptr)
{
  free(ptr);
}
