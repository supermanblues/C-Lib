/**
 * @author: waingxiaoqiang
 * @version: 0.0.7
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-10
 * @description: Binary Search Tree Unit Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bst.h"
#include <test-utils.h>

static int cmp_by_stu_chinese(const void *key, const void *record)
{
  const int *k = (int *) key;
  const struct Student *r = (struct Student *) record;

  return (*k - r->chinese);
}

void test(void)
{
  int i, x;
  const int data[] = { 0, 3, 4, 5, 7, 9, 11, 19, 32, 57 };
  
  struct BST *bst1 = NULL;
  struct BST *bst2 = NULL;
  const struct Student *s = NULL;

  printf("\033[2J\033[?25l"); // clear screen and not display cursor

  bst1 = bst_create(sizeof(int), cmp_int, print_int);
  if (bst1 == NULL)
  {
    fprintf(stderr, "The bst1 create failed. GoodBye!\n");
    exit(EXIT_FAILURE);
  }

  assert( bst1->empty(bst1) );
  assert( bst1->size(bst1) == 0 );
  assert( bst1->height(bst1) == 0 );
  assert( bst1->min(bst1) == NULL );
  assert( bst1->max(bst1) == NULL );

  for (i = 0; i < sizeof(data) / sizeof(*data); ++i)
    bst1->insert(bst1, data + i, data + i);

  x = 0, assert( bst1->insert(bst1, &x, &x) == -2 ); // 测试插入重复数据的返回值

  assert( !bst1->empty(bst1) );
  assert( bst1->size(bst1) == 10);
  assert( bst1->size(bst1) == bst1->count(bst1));
  assert( bst1->height(bst1) == 10 );
  assert( *(int *) bst1->min(bst1) == min(data, 10) );
  assert( *(int *) bst1->max(bst1) == max(data, 10) );

  for (i = sizeof(data) / sizeof(*data) - 1; i >= 0; --i)
    assert( *(int *) bst1->search(bst1, data + i) == *(data + i) );

  x = 72, assert( bst1->search(bst1, &x) == NULL );
  bst1->insert(bst1, &x, &x);
  assert( *(int *) bst1->search(bst1, &x) == x );

  x = 40, assert( bst1->search(bst1, &x) == NULL );
  bst1->insert(bst1, &x, &x);
  assert( *(int *) bst1->search(bst1, &x) == x );

  bst1->balance(bst1);
  bst1->draw(bst1);

  fputs("\033[36;7m层序遍历：\033[0m\n", stdout);
  bst1->travel(bst1, BST_TRAVEL_LEVELORDER);

  fputs("\n\n\033[36;7m先序遍历：\033[0m\n", stdout);
  bst1->travel(bst1, BST_TRAVEL_PREORDER);
  
  fputs("\n\n\033[36;7m中序遍历：\033[0m\n", stdout);
  bst1->travel(bst1, BST_TRAVEL_INORDER);
  
  fputs("\n\n\033[36;7m后序遍历：\033[0m\n", stdout);
  bst1->travel(bst1, BST_TRAVEL_POSTORDER);

  bst2 = bst_create(sizeof(struct Student), cmp_by_stu_chinese, print_s);
  if (bst2 == NULL)
  {
    bst_destroy(bst1);
    exit(EXIT_FAILURE);
  }

  assert( bst2->empty(bst2) );
  assert( bst2->size(bst2) == 0 );
  assert( bst2->height(bst2) == 0 );
  assert( bst2->min(bst2) == NULL );
  assert( bst2->max(bst2) == NULL );

  for (i = 0; i < sizeof(STUDS) / sizeof(*STUDS); ++i)
    bst2->insert(bst2, &(STUDS + i)->chinese, STUDS + i);

  assert( !bst2->empty(bst2) );
  assert( bst2->size(bst2) == STUD_SIZE );
  assert( bst2->size(bst2) == bst2->count(bst2) );
  assert( bst2->height(bst2) == 4 );

  fputs("\n\nMinimum and Maximum\n", stdout);
  print_s(bst2->min(bst2));
  print_s(bst2->max(bst2));

  for (i = sizeof(STUDS) / sizeof(*STUDS) - 1; i >= 0; --i)
  {
    s = bst2->search(bst2, &STUDS[i].chinese);
    assert(s->chinese == STUDS[i].chinese);
  }

  fputs("\033[36;7m层序遍历：\033[0m\n", stdout);
  bst2->travel(bst2, BST_TRAVEL_LEVELORDER);

  fputs("\n\n\033[36;7m先序遍历：\033[0m\n", stdout);
  bst2->travel(bst2, BST_TRAVEL_PREORDER);
  
  fputs("\n\n\033[36;7m中序遍历：\033[0m\n", stdout);
  bst2->travel(bst2, BST_TRAVEL_INORDER);
  
  fputs("\n\n\033[36;7m后序遍历：\033[0m\n", stdout);
  bst2->travel(bst2, BST_TRAVEL_POSTORDER);

  x = 83,  bst2->delete(bst2, &x);
  assert( bst2->search(bst2, &x) == NULL );

  x = 100, assert( bst2->delete(bst2, &x) == -1 ); // 测试删除不存在数据时的返回值
  
  fputs("\nInOrder: \n", stdout);
  bst2->travel(bst2, BST_TRAVEL_INORDER);        // 按语文成绩升序排列 

  bst_destroy(bst1), bst_destroy(bst2);
  printf("\033[?25h"); // display cursor
}

signed main(int argc, char const *argv[])
{
  test();
  return ~~(0 ^ 0);
}