/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-13
 * @modify-date: 2020-05-24
 * @version: 0.0.2
 * @description: Dynamic Array Unit Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "array.h"
#include <test-utils.h>

static int cmp_by_stud_math_desc(const void * a, const void *b)
{
  struct Student *s1 = (struct Student *) a;
  struct Student *s2 = (struct Student *) b;

  return (s2->math - s1->math);
}

void test_basic(void)
{
  int i;
  int s = 0, prod = 1, maximum = -0x7fffffff, minimum = 0x7fffffff;
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
  
  assert( arr->max(arr, ^(const void *cur, const void *max) {
    return *(int *) cur - *(int *) max;
  }) == NULL );

  assert( arr->min(arr, ^(const void *cur, const void *min) {
    return *(int *) cur - *(int *) min;
  }) == NULL );

  for (i = 0; i < DATA_SIZE; ++i)
    arr->push_front(arr, DATA + i);

  assert( !arr->empty(arr) );
  assert( arr->size(arr) == DATA_SIZE );
  assert( *(int *) arr->back(arr) == *DATA );
  assert( *(int *) arr->front(arr) == *(DATA + DATA_SIZE - 1) );

  assert( *(int *) arr->min(arr, ^(const void *cur, const void *min) {
    return *(int *) cur - *(int *) min;
  }) == *DATA );

  assert( *(int *) arr->max(arr, ^(const void *cur, const void *max) {
    return *(int *) cur - *(int *) max;
  }) == *(DATA + DATA_SIZE - 1));
  
  arr->accumulate(arr, &s, ^(int index, void *prev, const void *cur) {
    *(int *) prev += * (int *) cur;
  });
  assert( s == 1 + 2 + 3 + 4 + 5 );

  arr->accumulate(arr, &prod, ^(int index, void *prev, const void *cur) {
    *(int *) prev *= *(int *) cur;
  });
  assert( prod == 1 * 2 * 3 * 4 * 5 );

  arr->accumulate(arr, &maximum, ^(int index, void *prev, const void *cur) {
    int *p = (int *) prev;
    int *c = (int *) cur;
    *p = *c > *p ? *c : *p;
  });
  
  assert( maximum == *(int *) arr->max(arr, ^(const void *cur, const void *max) {
    return *(int *) cur - *(int *) max;
  }) );

  arr->accumulate(arr, &minimum, ^(int index, void *prev, const void *cur) {
    int *p = (int *) prev;
    int *c = (int *) cur;
    *p = *c < *p ? *c : *p;
  });

  assert( minimum == *(int *) arr->min(arr, ^(const void *cur, const void *min) {
    return *(int *) cur - *(int *) min;
  }) );

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

  arr = Create_Array(sizeof x);
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

  for (i = 1, x = 4; i < 4; ++i, --x)
    arr->insert(arr, i, &x);

  arr->reverse(arr);
  assert( __IS_SAME_(arr->base, DATA, DATA_SIZE * sizeof *DATA) );

  arr_destroy(arr);
}

void test_findAndSort(void)
{
  int i;
  float tot_score = 0; 
  int stud_id, stud_math;

  struct ARRAY *studs = NULL;

  studs = Create_Array(sizeof *STUDS);
  if (studs == NULL)
  {
    fprintf(stderr, "The studs create failed. GoodBye!");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < STUD_SIZE; ++i)
    studs->push_back(studs, STUDS + i);

  studs->travel(studs, ^(const void *r) {
    const struct Student *s = (struct Student *) r;
    printf("id: %d\tname: %s\tmath: %d\tchinese: %d\n", s->id, s->name, s->math, s->chinese);
  });
  fputc(10, stdout);

  stud_id = 1;
  assert( __IS_SAME_(studs->search(studs, &stud_id, ^(const void *key, const void *record) {
    const int *k = (int *) key;
    const struct Student *r = (struct Student *) record;
    return (*k - r->id);
  }), STUDS, sizeof *STUDS) );

  stud_id = 10;
  assert( studs->search(studs, &stud_id, ^(const void *key, const void *record) {
    const int *k = (int *) key;
    const struct Student *r = (struct Student *) record;
    return (*k - r->id);
  }) == NULL);

  stud_math = 67;
  assert( __IS_SAME_(studs->search(studs, &stud_math, ^(const void *key, const void *record) {
    const int *k = (int *) key;
    const struct Student *r = (struct Student *) record;
    return (*k - r->math);
  }), STUDS + 4, sizeof *STUDS) );
  
  studs->sort(studs, cmp_by_stud_math_desc);
  assert( is_sorted2(studs->base, studs->size(studs), studs->datasize, cmp_by_stud_math_desc) );

  print_s(studs->min(studs, ^(const void *cur, const void *min) {
    const struct Student *s1 = (struct Student *) cur;
    const struct Student *s2 = (struct Student *) min;
    return s1->chinese - s2->chinese;
  }));

  print_s(studs->max(studs, ^(const void *cur, const void *max) {
    const struct Student *s1 = (struct Student *) cur;
    const struct Student *s2 = (struct Student *) max;
    return s1->chinese - s2->chinese;
  }));

  studs->accumulate(studs, &tot_score, ^(int index, void *prev, const void *cur) {
    struct Student *s = (struct Student *) cur;
    *(float *) prev += (s->math + s->chinese) / 2.0;
  });
  printf("总平均成绩为: %lf\n每名学生的平均成绩为: %.2lf\n", tot_score, tot_score / studs->length);

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