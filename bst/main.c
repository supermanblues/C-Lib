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
#include "../common/test-utils.h"

static int cmp_by_val(const void *key, const void *record)
{
  const int *k = (int *) key;
  const int *r = (int *) record;

  return (*k - *r);
}

static int cmp_by_stu_chinese(const void *key, const void *record)
{
  const int *k = (int *) key;
  const struct Student *r = (struct Student *) record;

  return (*k - r->chinese);
}

static void print_int_val(const void *record)
{
  if (record == NULL)
    return;

  printf("%d ", *(int*) record);
}

signed main(int argc, char const *argv[])
{
  int i, x;
  const int DATA[] = { 0, 3, 4, 5, 7, 9, 11, 19, 32, 57 };
  
  struct BST *bst1 = NULL;
  struct BST *bst2 = NULL;
  const struct Student *s = NULL;

  printf("\033[2J\033[?25l"); // clear screen and not display cursor

  bst1 = CreateBST(sizeof(int), cmp_by_val, print_int_val);
  if (bst1 == NULL)
  {
    fprintf(stderr, "The bst1 create failed. GoodBye!\n");
    exit(EXIT_FAILURE);
  }

  assert( bst1->empty(bst1) );
  assert( bst1->size(bst1) == 0 );
  assert( bst1->height(bst1) == 0 );
  assert( bst1->minimum(bst1) == NULL );
  assert( bst1->maximum(bst1) == NULL );

  for (i = 0; i < sizeof(DATA) / sizeof(*DATA); ++i)
    bst1->insert(bst1, DATA + i, DATA + i);

  x = 0, assert( bst1->insert(bst1, &x, &x) == -2 ); // 测试插入重复数据的返回值

  assert( !bst1->empty(bst1) );
  assert( bst1->size(bst1) == 10);
  assert( bst1->height(bst1) == 10 );
  assert( *(int *) bst1->minimum(bst1) == min(DATA, 10) );
  assert( *(int *) bst1->maximum(bst1) == max(DATA, 10) );

  for (i = sizeof(DATA) / sizeof(*DATA) - 1; i >= 0; --i)
    assert( *(int *) bst1->search(bst1, DATA + i) == *(DATA + i) );

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

  bst2 = CreateBST(sizeof(struct Student), cmp_by_stu_chinese, print_s);
  if (bst2 == NULL)
  {
    DestroyBST(bst1);
    exit(EXIT_FAILURE);
  }

  assert( bst2->empty(bst2) );
  assert( bst2->size(bst2) == 0 );
  assert( bst2->height(bst2) == 0 );
  assert( bst2->minimum(bst2) == NULL );
  assert( bst2->maximum(bst2) == NULL );

  for (i = 0; i < sizeof(STUDS) / sizeof(*STUDS); ++i)
    bst2->insert(bst2, &(STUDS + i)->chinese, STUDS + i);

  assert( !bst2->empty(bst2) );
  assert( bst2->size(bst2) == STUD_SIZE );
  assert( bst2->height(bst2) == 4 );

  fputs("\n\nMinimum and Maximum\n", stdout);
  print_s(bst2->minimum(bst2));
  print_s(bst2->maximum(bst2));

  for (i = sizeof(STUDS) / sizeof(*STUDS) - 1; i >= 0; --i)
  {
    s = bst2->search(bst2, &STUDS[i].chinese);
    assert(s->chinese == STUDS[i].chinese);
  }

  fputs("\nLevelOrder: \n", stdout);
  bst2->travel(bst2, BST_TRAVEL_LEVELORDER);

  fputs("\nPreOrder: \n", stdout);
  bst2->travel(bst2, BST_TRAVEL_PREORDER);
  
  fputs("\nInOrder: \n", stdout);
  bst2->travel(bst2, BST_TRAVEL_INORDER);
  
  fputs("\nPostOrder: \n", stdout);
  bst2->travel(bst2, BST_TRAVEL_POSTORDER);

  x = 83,  bst2->delete(bst2, &x);
  assert( bst2->search(bst2, &x) == NULL );

  x = 100, assert( bst2->delete(bst2, &x) == -1 ); // 测试删除不存在数据时的返回值
  
  fputs("\nInOrder: \n", stdout);
  bst2->travel(bst2, BST_TRAVEL_INORDER);        // 按语文成绩升序排列 

  DestroyBST(bst1), DestroyBST(bst2);

  printf("\033[?25h"); // 显示光标
  return ~~(0 ^ 0);
}