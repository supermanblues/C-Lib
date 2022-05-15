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

const char *str = "0wangqiang!@Window123Window456Window789";

signed main(int argc, char const *argv[])
{
  int digits = 0;
  int data[DATA_SIZE];

  freopen("common-test.in", "r", stdin);

  for (const char* pch = str; *pch != '\0'; ++pch)
    if (is_digit(*pch)) ++digits;

  assert( digits == 10 );

  int a = r(), b = r();
  ll c = r(), d = r();

  assert( a == 1234560 && b == -123456 );
  assert( c == LLONG_MIN && d == LLONG_MAX );

  for_(i, 0, DATA_SIZE)
    *(data + i) = *(DATA + i);

  assert( __IS_SAME_(data, DATA, DATA_SIZE * sizeof *data) );

  for_prev_(i, DATA_SIZE - 1, ~0)
    *(data + DATA_SIZE - 1 - i) = *(DATA + i);
    
  reverse(data, DATA_SIZE, sizeof *data);
  assert( __IS_SAME_(data, DATA, DATA_SIZE * sizeof *data) );

  fclose(stdin);
  return ~~(0 ^ 0);
}