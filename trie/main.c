/**
 * @author: wangxiaoqiang
 * @version: 0.0.2
 * @create-date: 2022-04-25
 * @modify-date: 2022-05-07
 * @description: Trie Tree Unit Tests File
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "trie.h"
#include <test-utils.h>

signed main(int argc, char const *argv[]) {

  int i, found;
  struct Trie *trie;
  char * words[] = {"be", "bad", "bee", "beer", "boy", "be", "be",
                    "a", "app", "apple", "app", 
                    "wang", "w", "wc", "wang"};

  trie = CreateTrie();
  if (trie == NULL)
    exit(-1);

  for (i = 0; i < sizeof(words) / sizeof(*words); ++i)
    trie->insert(trie, *(words + i));

  trie->travel(trie);

  assert( trie->countWordsStartingWith(trie, "b") == 7 );
  assert( trie->countWordsStartingWith(trie, "be") == 5 ); 
  assert( trie->countWordsStartingWith(trie, "bx") == 0 ); 

  assert( trie->countWordsStartingWith(trie, "a") == 4 );
  assert( trie->countWordsStartingWith(trie, "ap") == 3 ); 
  assert( trie->countWordsStartingWith(trie, "app") == 3 );
  assert( trie->countWordsStartingWith(trie, "axx") == 0 );

  assert( trie->countWordsStartingWith(trie, "w") == 4 );
  assert( trie->countWordsStartingWith(trie, "wc") == 1 );
  assert( trie->countWordsStartingWith(trie, "wang") == 2 );
  assert( trie->countWordsStartingWith(trie, "wxx") == 0 ); 

  found = trie->search(trie, "wang");
  assert(found == 1);

  found = trie->search(trie, "axxx");
  assert(found == 0);

  found = trie->startsWith(trie, "ap");
  assert(found == 1);

  found = trie->startsWith(trie, "apxx");
  assert(found == 0);

  /* ================ erase test ===================  */
  assert( trie->countWordsEqualTo(trie, "wang") == 2 );

  assert( trie->eraseWord(trie, "wang") == 0);
  assert( trie->countWordsEqualTo(trie, "wang") == 1 );
  
  assert( trie->eraseWord(trie, "wang") == 0);
  assert( trie->countWordsEqualTo(trie, "wang") == 0 );

  found = trie->search(trie, "wang");
  assert(found == 0);

  found = trie->startsWith(trie, "wang");
  assert(found == 0);

  assert( trie->eraseWord(trie, "wang") == -1);

  DestroyTrie(trie);
  return ~~(1 ^ 1);
}