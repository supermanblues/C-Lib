/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-13
 * @modify-date: 2020-05-13
 * @version: 0.0.1
 * @description: Dynamic Array Unit Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "array.h"
#include "../sort/sort.h"
#include "../common/test-utils.h"

static int stud_id_match(const void *key, const void *record)
{
  const int *k = (int *) key;
  const struct Student *r = (struct Student *) record;

  return (*k - r->id);
}

static int stud_math_match(const void *key, const void *record)
{
  const int *k = (int *) key;
  const struct Student *r = (struct Student *) record;

  return (*k - r->math);
}

void test_basic(void)
{
  int i;
  struct ARRAY *arr = NULL;

  arr = Create_Array(sizeof *DATA);
  if (arr == NULL)
  {
    fprintf(stderr, "The arr create failed. GoodBye!");
    exit(EXIT_FAILURE);
  }

  assert( arr->empty(arr) );
  assert( arr->size(arr) == 0 );
  assert( arr->front(arr) == NULL );
  assert( arr->back(arr) == NULL );
  assert( arr->rear(arr) == NULL );

  for (i = 0; i < DATA_SIZE; ++i)
    arr->push_back(arr, DATA + i);

  assert( !arr->empty(arr) );
  assert( arr->size(arr) == DATA_SIZE );
  assert( *(int *) arr->front(arr) == *DATA );
  assert( *(int *) arr->back(arr) == *(DATA + DATA_SIZE - 1) );
  assert( *(int *) arr->rear(arr) == *(DATA + DATA_SIZE - 1) );

  for (i = 0; i < DATA_SIZE; ++i)
    assert( __IS_SAME_(arr->get(arr, i), DATA + i, sizeof *DATA) );

  DestroyArray(arr);
}

void test_insert(void)
{
  int i, x;
  struct ARRAY *arr = NULL;

  arr = Create_Array(sizeof *DATA);
  if (arr == NULL)
  {
    fprintf(stderr, "The arr create failed. GoodBye!");
    exit(EXIT_FAILURE);
  }

  x = 5;
  assert( arr->insert(arr, 110, &x) == -1 );
  assert( arr->push_front(arr, &x) == 0 );

  x = 1;
  assert( arr->push_back(arr, &x) == 0 );

  x = 4;
  for (i = 1; i < 4; ++i, --x)
    arr->insert(arr, i, &x);

  arr->reverse(arr);

  assert( __IS_SAME_(arr->front(arr), DATA, DATA_SIZE * sizeof *DATA) );

  DestroyArray(arr);
}

void test_findAndSort(void)
{
  int i;
  struct ARRAY *arr = NULL;

  int stud_id, stud_math;
  struct Student *s;

  arr = Create_Array(sizeof *STUDS);
  if (arr == NULL)
  {
    fprintf(stderr, "The arr create failed. GoodBye!");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < STUD_SIZE; ++i)
    arr->push_back(arr, STUDS + i);

  arr->travel(arr, print_s);

  stud_id = 1, s = arr->find(arr, &stud_id, stud_id_match);
  assert( __IS_SAME_(s, STUDS, sizeof *s) );

  stud_id = 10, assert( arr->find(arr, &stud_id, stud_id_match) == NULL);

  stud_math = 67, s = arr->find(arr, &stud_math, stud_math_match);
  assert( __IS_SAME_(s, STUDS + 4, sizeof *s) );
  
  /* 按数学成绩从高到低排序, 数学成绩相同则按学号从小到大排序 */
  arr->sort(arr, cmp_stud, QUICK_SORT);
  assert( is_sorted(arr->base, arr->size(arr), arr->datasize, cmp_stud) );

  DestroyArray(arr);
}

void test_array_2d(void)
{
  const int M = 4, N = 4;

  int i, j, m, n;
  char c;
  struct ARRAY *arr_2d = NULL, *row = NULL;

  const double data[ ][ 4 ] = {{1.1, 2.2, 3.3, 4.4}, {5.5, 6.6, 7.7, 8.8}, {9.9, 10.10, 11.11, 12.12}, {13.13, 14.14, 15.15, 16.16}};

  // array of array (array中的每一个元素都是一个 flexible array)
  // 相当于 java的 List<List<Integer>> list = new ArrayList<>();
  arr_2d = arr_create2D(M, sizeof(double));
  if (arr_2d == NULL)
  {
    fprintf(stderr, "The arr_2d create failed. GoodBye!");
    exit(EXIT_FAILURE);
  }

  printf("%zu %zu\n", arr_2d->length, arr_2d->capacity);

  for (i = 0; i < M; ++i)
  {
    row = *(struct ARRAY **) arr_2d->get(arr_2d, i);
    for (j = 0; j < N; ++j)
      row->push_back(row, *(data + i) + j);
  }

  for (i = 0, m = arr_2d->size(arr_2d); i < m; ++i)
  {
    row = *(struct ARRAY **) arr_2d->get(arr_2d, i);
    for (j = 0, n = row->size(row); j < n; ++j)
      printf("%-6.2lf%c", *(double *) row->get(row, j), j == n - 1 ? 10 : 0);
  }
  fputc(10, stdout);

  row = Create_Array(sizeof(char));
  if (row == NULL)
    exit(EXIT_FAILURE);

  for (i = 0; i < 26; ++i)
  {
    c = i + 65;
    row->push_back(row, &c);
  }
  arr_2d->push_front(arr_2d, &row);

  row = Create_Array(sizeof(char));
  if (row == NULL)
    exit(EXIT_FAILURE);

  for (i = 0; i < 26; ++i)
  {
    c = i + 97;
    row->push_back(row, &c);
  }
  arr_2d->push_back(arr_2d, &row);

  row = Create_Array(sizeof(double));
  if (row == NULL)
    exit(EXIT_FAILURE);
  double x = 1.234;
  row->push_back(row, &x);

  x = 3.1415926;
  row->push_back(row, &x);

  arr_2d->insert(arr_2d, 4, &row);

  puts("delete before:");
  for (i = 0, m = arr_2d->size(arr_2d); i < m; ++i)
  {
    row = *(struct ARRAY **) arr_2d->get(arr_2d, i);
    for (j = 0, n = row->size(row); j < n; ++j) 
    {
      if (i == 0 || i == m - 1)
        printf("%-2c%c", *(char *) row->get(row, j), j == n - 1 ? 10 : 0);
      else
        printf("%-6.2lf%c", *(double *) row->get(row, j), j == n - 1 ? 10 : 0);
    }
  }

  puts("\ndelete after:");
  arr_2d->delete_row(arr_2d, 3);
  
  for (i = 0, m = arr_2d->size(arr_2d); i < m; ++i)
  {
    row = *(struct ARRAY **) arr_2d->get(arr_2d, i);
    for (j = 0, n = row->size(row); j < n; ++j) 
    {
      if (i == 0 || i == m - 1)
        printf("%-2c%c", *(char *) row->get(row, j), j == n - 1 ? 10 : 0);
      else
        printf("%-6.2lf%c", *(double *) row->get(row, j), j == n - 1 ? 10 : 0);
    }
  }

  arr_destroy2D(arr_2d);
}

signed main(int argc, char const *argv[])
{
  test_basic();
  test_insert();
  test_findAndSort();

  putc(10, stdout);
  test_array_2d();

  return ~~(0 ^ 0);
}