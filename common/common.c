/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-07
 * @version: 0.0.3
 * @description: Common Implementation File
 */
#include <stdio.h>
#include <iso646.h>

#include "common.h"

int is_digit(const char c)
{
  return (c >= 48 and c <= 57);
}

ll fast_read(void)
{
  ll n = 0, sign = 1;
  char c = getchar();
  while (not is_digit(c))
  {
    if (c == '-') sign = ~0;
    c = getchar();
  }
  while (is_digit(c))
  {
    n = (n << 1) + (n << 3) + (c ^ 48);
    c = getchar();
  }

  return sign * n;
}