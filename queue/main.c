/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-25
 * @modify-date: 2020-05-10
 * @version: 0.0.5
 * @description: SqQueue and LinkQueue Unit Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"
#include "linkqueue.h"
#include "../common/test-utils.h"

void test_SqQueue(void)
{
  int i;
  int data[ DATA_SIZE ];
  struct SqQueue *q = NULL;

  q = CreateSqQueue(sizeof(int), DATA_SIZE);
  if (q == NULL)
  {
    fprintf(stderr, "The q create failed. GoodBye!\n");
    exit(EXIT_FAILURE);
  }

  assert( q->empty(q) );
  assert( q->size(q) == 0 );
  
  for (i = 0; i < DATA_SIZE; ++i)
    q->push(q, DATA + i);

  assert( !q->empty(q) );
  assert( q->size(q) == DATA_SIZE );
  assert( *(int *) q->get_front(q) == *DATA );
  assert( *(int *) q->get_rear(q) == *(DATA + DATA_SIZE - 1) );

  i = 0;
  while (q->pop(q, data + i++) == 0);

  assert( q->empty(q) );
  assert( q->size(q) == 0 );
  assert( is_same(data, DATA, DATA_SIZE * sizeof(*DATA)) );

  DestroyQueue(q);
}

void test_LinkQueue(void)
{
  int i;
  struct Student studs[STUD_SIZE];
  struct LinkQueue *q = NULL;

  q = CreateLinkQueue(sizeof(struct Student));
  if (q == NULL)
  {
    fprintf(stderr, "The q create failed. GoodBye!\n");
    exit(EXIT_FAILURE);
  }

  assert( q->empty(q) );
  assert( q->size(q) == 0 );
  assert( q->front(q) == NULL );
  assert( q->peek(q) == NULL );

  for (i = 0; i < STUD_SIZE; ++i)
    q->push(q, STUDS + i);

  assert( !q->empty(q) );
  assert( q->size(q) == STUD_SIZE );

  assert( is_same(q->front(q), STUDS, sizeof(struct Student)) );
  assert( is_same(q->peek(q), STUDS,  sizeof(struct Student)) );

  i = 0;
  while (q->pop(q, studs + i++) == 0);

  assert( is_same(studs, STUDS, STUD_SIZE * sizeof(struct Student)) );

  DestroyLinkQueue(q);
}

signed main(int argc, char const *argv[])
{
  test_SqQueue();
  test_LinkQueue();

  return ~~(0 ^ 0);
}