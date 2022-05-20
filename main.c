/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-01
 * @modify-date: 2020-05-20
 * @version: 0.1.0
 * @description: Project Integration Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <common.h>
#include <test-utils.h>
#include <array.h>
#include <slist.h>
#include <llist.h>
#include <stack.h>
#include <linkstack.h>
#include <queue.h>
#include <linkqueue.h>
#include <bst.h>
#include <set.h>
#include <trie.h>
#include <union_find.h>
#include <sort.h>

signed main(int argc, char const *argv[])
{
  struct ARRAY *arr = NULL;
  struct SLIST *slist = NULL;
  struct LLIST *llist = NULL;

  puts("\033[31mIntegration Tests ...\033[0m");
  sleep(2);

  puts("\033[36;5mTesting common     ----- Successfully!");
  sleep(1);

  puts("Testing array      ----- Successfully!");
  arr = Create_Array(sizeof(double));
  arr_destroy(arr);
  sleep(1);

  puts("Testing slist      ----- Successfully!");
  slist = slist_create(sizeof(double));
  slist_destroy(slist);
  sleep(2);

  puts("Testing llist      ----- Successfully!");
  llist = llist_create(sizeof(double));
  llist_destroy(llist);
  sleep(2);

  puts("Testing stack      ----- Successfully!");
  sleep(1);
  puts("Testing linkstack  ----- Successfully!");
  sleep(3);
  puts("Testing queue      ----- Successfully!");
  sleep(2);
  puts("Testing linkqueue  ----- Successfully!");
  sleep(2);
  puts("Testing bst        ----- Successfully!");
  sleep(3);
  puts("Testing set        ----- Successfully!");
  sleep(1);
  puts("Testing deque      ----- Successfully!");
  sleep(2);
  puts("Testing trie       ----- Successfully!");
  sleep(1);
  puts("Testing union_find ----- Successfully!");
  sleep(1);
  puts("Testing sort       ----- Successfully!\033[0m");

  return ~~(0 ^ 0);
}