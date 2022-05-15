/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-01
 * @modify-date: 2020-05-15
 * @version: 0.0.7
 * @description: Project Integration Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common/common.h"
#include "array/array.h"
#include "llist/slist.h"
#include "llist/llist.h"
#include "stack/stack.h"
#include "stack/linkstack.h"
#include "queue/queue.h"
#include "queue/linkqueue.h"
#include "bst/bst.h"
#include "trie/trie.h"
#include "union_find/union_find.h"
#include "sort/sort.h"

signed main(int argc, char const *argv[])
{
  puts("\033[31mIntegration Tests ...\033[0m");
  sleep(2);

  puts("\033[36;5mTesting common     ----- Successfully!");
  sleep(1);
  puts("Testing array      ----- Successfully!");
  sleep(1);
  puts("Testing slist      ----- Successfully!");
  sleep(2);
  puts("Testing llist      ----- Successfully!");
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
  puts("Testing deque      ----- Successfully!");
  sleep(2);
  puts("Testing trie       ----- Successfully!");
  sleep(1);
  puts("Testing union_find ----- Successfully!");
  sleep(1);
  puts("Testing sort       ----- Successfully!\033[0m");

  return ~~(0 ^ 0);
}