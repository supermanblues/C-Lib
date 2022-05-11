/**
 * @author: wangxiaoqiang
 * @version: 0.01
 * @create-date: 2022-04-25
 * @modify-date: 2022-04-25
 */
/* ======================== Trie Tree Start  ========================*/
#ifndef __TRIE_H__
#define __TRIE_H__

#define NODE_CHILDREN_LEN   128

typedef struct TrieNode
{
  int prefix_count;
  int word_count;  /* 字典树中的单词的数量   */

  struct TrieNode 
      *children[NODE_CHILDREN_LEN];

} TrieNode;

typedef struct Trie
{
  struct TrieNode *root;

  void (*insert) (struct Trie *, const char *);

  int  (*search) (struct Trie*, const char *);
  int  (*startsWith) (struct Trie*, const char *);

  int  (*countWordsEqualTo) (struct Trie *, const char *);
  int  (*countWordsStartingWith) (struct Trie *, const char *);

  int  (*eraseWord) (struct Trie *, const char *);
  void (*travel) (struct Trie *);

} Trie;

struct Trie * CreateTrie(void);

void DestroyTrie(struct Trie *);

#endif
/* ======================== Trie Tree End  ========================*/