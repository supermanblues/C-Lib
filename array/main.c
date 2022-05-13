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

  arr = CreateArray(10, sizeof(*DATA));
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
}

void test_insert(void)
{
  int i, x;
  struct ARRAY *arr = NULL;

  arr = CreateArray(10, sizeof(*DATA));
  if (arr == NULL)
  {
    fprintf(stderr, "The arr create failed. GoodBye!");
    exit(EXIT_FAILURE);
  }

  x = 5;
  assert( arr->insert(arr, 110, &x) == -2 );
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

  arr = CreateArray(10, sizeof(*STUDS));
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

  // sorting before:
  arr->travel(arr, print_s);
  fputc(10, stdout);
  
  /* 按数学成绩从高到低排序, 数学成绩相同则按学号从小到大排序 */
  arr->sort(arr, cmp_stud);

  // sorting after:
  arr->travel(arr, print_s);
  fputc(10, stdout);

  DestroyArray(arr);
}

signed main(int argc, char const *argv[])
{
  test_basic();
  test_insert();
  test_findAndSort();

  return ~~(0 ^ 0);
}