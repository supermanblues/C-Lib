/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-01
 * @modify-date: 2020-05-16
 * @version: 0.0.7
 * @description: Common Unit Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "common.h"
#include "test-utils.h"

const char *str = "0wangqiang!@Window123Window456Window789";

signed main(int argc, char const *argv[])
{
  int digits = 0;

  freopen("common-test.in", "r", stdin);

  for (const char* pch = str; *pch != '\0'; ++pch)
    if (is_digit(*pch)) ++digits;

  assert( digits == 10 );

  int a = r(), b = r();
  ll c = r(), d = r();

  assert( a == 1234560 && b == -123456 );
  assert( c == LLONG_MIN && d == LLONG_MAX );

  fclose(stdin);
  return ~~(0 ^ 0);
}