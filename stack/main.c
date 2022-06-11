/** 
 * @author: wiangxiaoqiang
 * @version: 0.0.7
 * @create-date: 2022-04-23
 * @modify-date: 2022-05-14
 * @description: SqStack and LinkStack Unit Tests File
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stack.h"
#include "linkstack.h"
#include "../common/test-utils.h"

void test_SqStack(void)
{
  int i;
  int data[ DATA_SIZE ];
  struct SqStack *st = NULL;

  st = st_create(sizeof *DATA);
  if (st == NULL)
  {
    fprintf(stderr, "The st create failed. GoodBye!\n");
    exit(EXIT_FAILURE);
  }

  assert( st->empty(st) );
  assert( st->size(st) == 0 );
  assert( st->top(st) == NULL );

  for (i = 0; i < sizeof(DATA) / sizeof(*DATA); ++i)
    st->push(st, DATA + i);

  assert( !st->empty(st) );
  assert( st->size(st) == DATA_SIZE );
  assert( *(int *) st->top(st) == *(DATA + DATA_SIZE - 1) );

  i = 0;
  while (st->pop(st, data + i++) == 0);

  reverse(data, DATA_SIZE, sizeof(int));
  assert( __IS_SAME_(data, DATA, DATA_SIZE * sizeof(int)) );

  st_destroy(st);
}

void test_LinkStack(void)
{
  int i;
  struct Student studs[STUD_SIZE];
  struct LinkStack *st = NULL;

  st = lstk_create(sizeof *STUDS);
  if (st == NULL)
  {
    fprintf(stderr, "The st create failed. GoodBye!\n");
    exit(EXIT_FAILURE);
  }

  assert( st->empty(st) );
  assert( st->size(st) == 0 );
  assert( st->top(st) == NULL );
  assert( st->peek(st) == NULL );

  for (i = 0; i < STUD_SIZE; ++i)
    st->push(st, STUDS + i);

  assert( !st->empty(st) );
  assert( st->size(st) == STUD_SIZE );

  assert( __IS_SAME_(st->top(st), STUDS + STUD_SIZE - 1, sizeof(struct Student)) );
  assert( __IS_SAME_(st->peek(st), STUDS + STUD_SIZE - 1, sizeof(struct Student)) );

  i = 0;
  while (st->pop(st, studs + i++) == 0);

  reverse(studs, STUD_SIZE, sizeof(struct Student));
  assert( __IS_SAME_(studs, STUDS, STUD_SIZE * sizeof(struct Student)) );

  lstk_destroy(st);
}

signed main(int argc, char const *argv[])
{
  test_SqStack();
  test_LinkStack();
  
  return ~~(0 ^ 0);
}
