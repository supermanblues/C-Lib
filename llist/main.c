/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-11
 * @version: 0.0.8
 * @description: Singly-Linked List And Doubly-Linked Circular List Unit Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "slist.h"
#include "llist.h"
#include <test-utils.h>

void test_mock_stack_using_slist(void)
{
  int i, data[ DATA_SIZE ];
  struct SLIST *st = NULL;

  st = slist_create(sizeof *DATA);
  if (st == NULL)
  {
    fprintf(stderr, "The st create failed. GoodBye!\n");
    exit(EXIT_FAILURE);
  }

  assert( st->empty(st) );
  assert( st->size(st) == 0 );
  assert( st->front(st) == NULL );
  assert( st->rear(st) == NULL );

  for (i = 0; i < DATA_SIZE; ++i)
    st->push_front(st, DATA + i);

  st->travel(st, ^(const void *data) {
    printf("%d ", *(int *) data);
  });
  fputc(10, stdout);

  assert( !st->empty(st) );
  assert( st->size(st) == DATA_SIZE );

  assert( __IS_SAME_(st->front(st), DATA + DATA_SIZE - 1, sizeof *data) );
  assert( __IS_SAME_(st->rear(st), DATA, sizeof *data) );

  i = 0;
  st->reverse(st);
  while (st->pop_front(st, data + i++) == 0)
    continue;

  assert( __IS_SAME_(data, DATA, DATA_SIZE * sizeof *data) );
  slist_destroy(st);
}

void test_mock_stack_using_llist(void)
{
  int i, data[ DATA_SIZE ];
  struct LLIST *st = NULL;

  st = llist_create(sizeof *DATA);
  if (st == NULL)
  {
    fprintf(stderr, "The st create failed. GoodBye!\n");
    exit(EXIT_FAILURE);
  }

  assert( st->empty(st) );
  assert( st->size(st) == 0 );
  assert( st->front(st) == NULL );
  assert( st->rear(st) == NULL );

  for (i = 0; i < DATA_SIZE; ++i)
    st->push_front(st, DATA + i);

  assert( !st->empty(st) );
  assert( st->size(st) == DATA_SIZE );

  assert( __IS_SAME_(st->front(st), DATA + DATA_SIZE - 1, sizeof *DATA) );
  assert( __IS_SAME_(st->rear(st), DATA, sizeof(*DATA)) );

  i = 0;
  while (st->pop_front(st, data + i++) == 0)
    continue;

  reverse(data, DATA_SIZE, sizeof *DATA);
  assert( __IS_SAME_(data, DATA, DATA_SIZE * sizeof *DATA) );

  llist_destroy(st);
}

void test_mock_queue_using_slist(void)
{
  int i;
  struct Student studs[ STUD_SIZE ];
  struct SLIST *qu = NULL;

  qu = slist_create(sizeof *STUDS);
  if (qu == NULL)
  {
    fprintf(stderr, "The qu create failed. GoodBye!\n");
    exit(EXIT_FAILURE);
  }

  assert( qu->empty(qu) );
  assert( qu->size(qu) == 0 );
  assert( qu->front(qu) == NULL );
  assert( qu->rear(qu) == NULL );

  for (i = 0; i < STUD_SIZE; ++i)
    qu->push_back(qu, STUDS + i);

  assert( !qu->empty(qu) );
  assert( qu->size(qu) == STUD_SIZE );
  assert( __IS_SAME_(qu->front(qu), STUDS, sizeof *STUDS) );
  assert( __IS_SAME_(qu->back(qu),  STUDS + STUD_SIZE - 1, sizeof *STUDS) );
  assert( __IS_SAME_(qu->rear(qu),  STUDS + STUD_SIZE - 1, sizeof *STUDS) );

  i = 0;
  while (qu->pop_front(qu, studs + i++) == 0)
    continue;

  assert( __IS_SAME_(studs, STUDS, STUD_SIZE * sizeof *studs) );

  slist_destroy(qu);
}

void test_mock_queue_using_llist(void)
{
  int i;
  struct Student studs[STUD_SIZE];
  struct LLIST *qu = NULL;

  qu = llist_create(sizeof *STUDS);
  if (qu == NULL)
  {
    fprintf(stderr, "The qu create failed. GoodBye!\n");
    exit(EXIT_FAILURE);
  }

  assert( qu->empty(qu) );
  assert( qu->size(qu) == 0 );
  assert( qu->front(qu) == NULL );
  assert( qu->rear(qu) == NULL );

  for (i = 0; i < STUD_SIZE; ++i)
    qu->push_back(qu, STUDS + i);

  assert( !qu->empty(qu) );
  assert( qu->size(qu) == STUD_SIZE );

  assert( __IS_SAME_(qu->front(qu), STUDS, sizeof *STUDS) );
  assert( __IS_SAME_(qu->rear(qu),  STUDS + STUD_SIZE - 1, sizeof *STUDS) );

  i = 0;
  while (qu->pop_front(qu, studs + i++) == 0)
    continue;

  assert( __IS_SAME_(studs, STUDS, STUD_SIZE * sizeof *STUDS) );

  llist_destroy(qu);
}

void test_mock_deque()
{
  int i;
  DEQUE *dq = NULL;
  struct Student s;

  dq = CreateDeque(sizeof(struct Student));
  if (dq == NULL)
  {
    fprintf(stderr, "The dq create failed. GoodBye\n");
    exit(EXIT_FAILURE);
  }

  assert( dq->empty(dq) );
  assert( dq->size(dq) == 0);
  assert( dq->front(dq) == NULL );
  assert( dq->rear(dq) == NULL );

  /* queue-liked */
  fputs("ordered output!\n", stdout);
  for (i = 0; i < STUD_SIZE; ++i)
    dq->push_back(dq, STUDS + i);

  dq->travel(dq, ^(const void *r) {
    const struct Student *s = (struct Student *) r;
    printf("id: %d\tname: %s\tmath: %d\tchinese: %d\n", s->id, s->name, s->math, s->chinese);
  });

  while (dq->pop_front(dq, &s) == 0)
    continue;

  /* stack-liked */
  fputs("\nreversed output!\n", stdout);
  for (i = 0; i < STUD_SIZE; ++i)
    dq->push_front(dq, STUDS + i);

  dq->travel(dq, ^(const void *r) {
    const struct Student *s = (struct Student *) r;
    printf("id: %d\tname: %s\tmath: %d\tchinese: %d\n", s->id, s->name, s->math, s->chinese);
  });

  while (dq->pop_front(dq, &s) == 0)
    continue;

  DestroyDeque(dq);
}

signed main(int argc, char const *argv[])
{
  test_mock_stack_using_slist();
  test_mock_stack_using_llist();

  test_mock_queue_using_slist();
  test_mock_queue_using_llist();
  
  test_mock_deque();

  return ~~(1 ^ 1);
}

