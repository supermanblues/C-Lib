/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-01
 * @modify-date: 2020-05-16
 * @version: 0.0.7
 * @description: Common Unit Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "common.h"
#include "test-utils.h"
#include "../array/array.h"

const char *str = "0wangqiang!@Window123Window456Window789";

struct ARRAY *INT_DATA  = NULL;
struct ARRAY *STUD_DATA = NULL;

void init_test_data(void)
{
  int i;

  INT_DATA = Create_Array(sizeof *DATA);
  STUD_DATA = Create_Array(sizeof *STUDS);

  for (i = 0; i < DATA_SIZE; ++i)
    INT_DATA->push_back(INT_DATA, DATA + i);

  for (i = 0; i < STUD_SIZE; ++i)
    STUD_DATA->push_back(STUD_DATA, STUDS + i);

  // 供全局使用，万万不能Destroy!
}

signed main(int argc, char const *argv[])
{
  int digits = 0;
  int data[ DATA_SIZE ];

  freopen("common-test.in", "r", stdin);

  init_test_data();
  for (const char* pch = str; *pch != '\0'; ++pch)
    if (is_digit(*pch)) ++digits;

  assert( digits == 10 );

  int a = r(), b = r();
  ll c = r(), d = r();

  assert( a == 1234560 && b == -123456 );
  assert( c == LLONG_MIN && d == LLONG_MAX );
 
  INT_DATA->travel(INT_DATA, print_int);
  for_(i, 0, INT_DATA->size(INT_DATA))
    *(data + i) = *(int *) INT_DATA->get(INT_DATA, i);

  assert( __IS_SAME_(data, DATA, DATA_SIZE * sizeof *data) );
  
  INT_DATA->reverse(INT_DATA);
  for_prev_(i, DATA_SIZE - 1, ~0)
    *(data + DATA_SIZE - 1 - i) = *(int *) INT_DATA->get(INT_DATA, i);
    
  assert( __IS_SAME_(data, DATA, DATA_SIZE * sizeof *data) );

  fclose(stdin);
  return ~~(0 ^ 0);
}