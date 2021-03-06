/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-25
 * @modify-date: 2020-05-10
 * @version: 0.0.5
 * @description: SqQueue and LinkQueue Unit Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "queue.h"
#include "linkqueue.h"
#include <test-utils.h>

void test_SqQueue(void)
{
  int i;
  int data[ DATA_SIZE ];
  struct SqQueue *q = NULL;

  q = qu_create(sizeof(int), DATA_SIZE);
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
  assert( __IS_SAME_(data, DATA, DATA_SIZE * sizeof(*DATA)) );

  qu_destroy(q);
}

void test_LinkQueue(void)
{
  int i;
  struct Student studs[STUD_SIZE];
  struct LinkQueue *q = NULL;

  q = lqu_create(sizeof *studs);
  if (q == NULL)
  {
    fprintf(stderr, "The q create failed. GoodBye!\n");
    exit(EXIT_FAILURE);
  }

  assert( q->empty(q) );
  assert( q->size(q) == 0 );
  assert( q->front(q) == NULL );
  assert( q->peek(q) == NULL );
  assert( q->back(q) == NULL );
  assert( q->rear(q) == NULL );

  for (i = 0; i < STUD_SIZE; ++i)
    q->push(q, STUDS + i);

  assert( !q->empty(q) );
  assert( q->size(q) == STUD_SIZE );
  assert( __IS_SAME_(q->front(q), STUDS, sizeof *studs) );
  assert( __IS_SAME_(q->peek(q), STUDS,  sizeof *studs) );
  assert( __IS_SAME_(q->back(q), STUDS + STUD_SIZE - 1, sizeof *studs) );
  assert( __IS_SAME_(q->rear(q), STUDS + STUD_SIZE - 1, sizeof *studs) );

  i = 0;
  while (q->pop(q, studs + i++) == 0);

  assert( __IS_SAME_(studs, STUDS, STUD_SIZE * sizeof *studs) );

  lqu_destroy(q);
}

signed main(int argc, char const *argv[])
{
  test_SqQueue();
  test_LinkQueue();

  return ~~(0 ^ 0);
}