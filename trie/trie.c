#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

void insert(struct Trie *, const char *);

int search(struct Trie *, const char *);
int startsWith(struct Trie *, const char *);

int countWordsEqualTo(struct Trie *, const char *);
int countWordsStartingWith(struct Trie *, const char *);

int eraseWord(struct Trie *, const char *);
void travel(struct Trie *);

/* static inner function */
static struct TrieNode * init_trie_node_(struct TrieNode *);
static void travel_(struct TrieNode *);
static void free_trie_node_(struct TrieNode *);

struct Trie * CreateTrie(void)
{
  struct Trie *trie;

  trie = malloc(sizeof *trie);
  if (trie == NULL)
    return NULL;

  trie->root = malloc(sizeof *trie->root);
  if (trie->root == NULL)
    return NULL;

  init_trie_node_(trie->root);

  /* =============== Operations ===============  */
  trie->insert     = insert;
  trie->search     = search;
  trie->startsWith = startsWith;

  trie->countWordsEqualTo      = countWordsEqualTo;
  trie->countWordsStartingWith = countWordsStartingWith;
  trie->eraseWord              = eraseWord;
  trie->travel                 = travel;

  return trie;
}

void insert(struct Trie *trie, const char *word)
{
  if (trie == NULL)
    return;

  int index;
  struct TrieNode *ptr;
  struct TrieNode *new;

  ptr = trie->root;
  for (const char *pch = word; *pch != '\0'; ++pch)
  {

    index = *pch;
    if (ptr->children[index] == NULL)
    {
      new = malloc(sizeof *new);
      if (new == NULL)
        return;

      ptr->children[index] = init_trie_node_(new);
    }

    ptr = ptr->children[index];
    ++ptr->prefix_count;
  }

  ++ptr->word_count;
}

int search(struct Trie *trie, const char *word)
{
  return (countWordsEqualTo(trie, word) > 0);
}

int startsWith(struct Trie *trie, const char *prefix)
{
  return (countWordsStartingWith(trie, prefix) > 0);
}

int countWordsEqualTo(struct Trie *trie, const char *word)
{
  if (trie == NULL)
    return 0;

  int index;
  struct TrieNode *ptr = trie->root;

  for (const char *pch = word; *pch != '\0'; ++pch)
  {
    index = *pch;
    if (ptr->children[index] == NULL)
      return 0;

    ptr = ptr->children[index];
  }

  return ptr->word_count;
}

int countWordsStartingWith(struct Trie *trie, const char* prefix)
{
  if (trie == NULL)
    return 0;

  int index;
  struct TrieNode *ptr = trie->root;

  for (const char *pch = prefix; *pch != '\0'; ++pch)
  {
    index = *pch;
    if (ptr->children[index] == NULL)
      return 0;

    ptr = ptr->children[index];
  }

  return ptr->prefix_count;
}

int eraseWord(struct Trie *trie, const char *word)
{
  if (trie == NULL)
    return -1;

  if (!search(trie, word)) /* not found! */
    return -1;

  int index;
  struct TrieNode *ptr = trie->root;

  for (const char *pch = word; *pch != '\0'; ++pch)
  {
    index = *pch;
    ptr = ptr->children[index];
    --ptr->prefix_count;
  }

  --ptr->word_count;
  return 0;
}

void travel(struct Trie *trie)
{
  if (trie == NULL)
    return;

  travel_(trie->root);
}

void DestroyTrie(struct Trie *trie)
{
  if (trie == NULL)
    return;

  free_trie_node_(trie->root);
  free(trie);
}

static struct TrieNode * init_trie_node_(struct TrieNode *ptr)
{
  if (ptr == NULL)
    return NULL;

  memset(ptr, 0, sizeof *ptr);
  return ptr;
}

static void travel_(struct TrieNode *ptr)
{
  if (ptr == NULL)
    return;

  int i;
  for (i = 0; i < NODE_CHILDREN_LEN; ++i)
  {
    if (ptr->children[i] != NULL)
    {
      putchar(i);
      if (ptr->children[i]->word_count)
        printf("\t%d",  ptr->children[i]->word_count);
      putchar(10);
      travel_(ptr->children[i]);
    }
  }
}

static void free_trie_node_(struct TrieNode *ptr)
{
  if (ptr == NULL)
    return;

  int i;
  for (i = 0; i < NODE_CHILDREN_LEN; ++i)
  {
    if (ptr->children[i] != NULL)
      free_trie_node_(ptr->children[i]);
  }

  free(ptr);
}
