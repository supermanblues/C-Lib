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
#include "../common/test-utils.h"

static int cmp_by_stud_math_desc(const void * a, const void *b)
{
  struct Student *s1 = (struct Student *) a;
  struct Student *s2 = (struct Student *) b;

  return (s2->math - s1->math);
}

static int cmp_stud_by_chinese(const void *a, const void *b)
{
  const struct Student *s1 = (struct Student *) a;
  const struct Student *s2 = (struct Student *) b;

  return s1->chinese - s2->chinese;
}

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
  assert( arr->max(arr, cmp_int) == NULL );
  assert( arr->min(arr, cmp_int) == NULL );

  for (i = 0; i < DATA_SIZE; ++i)
    arr->push_front(arr, DATA + i);

  assert( !arr->empty(arr) );
  assert( arr->size(arr) == DATA_SIZE );
  assert( *(int *) arr->back(arr) == *DATA );
  assert( *(int *) arr->front(arr) == *(DATA + DATA_SIZE - 1) );
  assert( *(int *) arr->min(arr, cmp_int) == *DATA );
  assert( *(int *) arr->max(arr, cmp_int) == *(DATA + DATA_SIZE - 1));

  arr->reverse(arr);
  for (i = 0; i < DATA_SIZE; ++i)
    assert( __IS_SAME_(arr->get(arr, i), DATA + i, sizeof *DATA) );

  for (i = 0; i < DATA_SIZE; ++i)
    arr->pop_back(arr);

  assert( arr->empty(arr) );
  arr_destroy(arr);
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

  arr_destroy(arr);
}

void test_findAndSort(void)
{
  int i;
  struct ARRAY *studs = NULL;

  int stud_id, stud_math;
  struct Student *s = NULL;

  studs = Create_Array(sizeof *STUDS);
  if (studs == NULL)
  {
    fprintf(stderr, "The studs create failed. GoodBye!");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < STUD_SIZE; ++i)
    studs->push_back(studs, STUDS + i);

  studs->travel(studs, print_s);
  fputc(10, stdout);

  stud_id = 1, s = studs->search(studs, &stud_id, stud_id_match);
  assert( __IS_SAME_(s, STUDS, sizeof *s) );

  stud_id = 10, assert( studs->search(studs, &stud_id, stud_id_match) == NULL);

  stud_math = 67, s = studs->search(studs, &stud_math, stud_math_match);
  assert( __IS_SAME_(s, STUDS + 4, sizeof *s) );
  
  studs->sort(studs, cmp_by_stud_math_desc);
  assert( is_sorted(studs->base, studs->size(studs), studs->datasize, cmp_by_stud_math_desc) );

  print_s(studs->min(studs, cmp_stud_by_chinese));
  print_s(studs->max(studs, cmp_stud_by_chinese));

  // stud_math = 53, s = studs->bsearch(studs, &stud_math, stud_math_match);
  arr_destroy(studs);
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
  test_array_2d();

  return ~~(0 ^ 0);
}