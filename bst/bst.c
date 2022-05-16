/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-13
 * @version: 0.0.8
 * @description: Binary Search Tree Implementation File
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bst.h"
#include "../array/array.h"
#include "../stack/linkstack.h"
#include "../queue/linkqueue.h"

int bst_size(struct BST *);
int bst_empty(struct BST *);
void bst_draw(struct BST *);

const void * bst_search(struct BST *, const void *);

int bst_insert(struct BST *, const void *, const void *);
int bst_delete(struct BST *, const void *);

const void * bst_maximum(struct BST *);
const void * bst_minimum(struct BST *);

int bst_height(struct BST *);
void bst_balance(struct BST *);
void bst_travel(struct BST *, BST_TRAVEL_MODE mode);

static const void *
bst_search_(struct TreeNode *, const void *, compare *);

static int
bst_insert_(struct TreeNode **, const void *, const void *,  const size_t, compare *);

static struct TreeNode *
bst_delete_(struct TreeNode *, const void *, compare *);

static int
bst_size_(struct TreeNode *);

static struct TreeNode *
bst_maximum_(struct TreeNode *);

static struct TreeNode *
bst_minimum_(struct TreeNode *);

static int
bst_height_(struct TreeNode *);

static void
bst_balance_(struct TreeNode **);

static void
bst_turn_left(struct TreeNode **);

static void
bst_turn_right(struct TreeNode **);

struct BST * CreateBST(int datasize, compare *cmp, visit *vis)
{
  struct BST *bst = NULL;

  if (datasize <= 0 || cmp == NULL)
    return NULL;

  bst = (struct BST *) malloc(sizeof *bst);
  if (bst == NULL)
    return NULL;

  bst->root = NULL;
  bst->cmp  = cmp;
  bst->vis  = vis;
  bst->datasize = datasize;

  /* =============== Operations =============== */
  bst->size    = bst_size;
  bst->empty   = bst_empty;
  bst->draw    = bst_draw;
  bst->search  = bst_search;
  bst->insert  = bst_insert;
  bst->delete  = bst_delete;
  bst->maximum = bst_maximum;
  bst->minimum = bst_minimum;
  bst->height  = bst_height;
  bst->balance = bst_balance;
  bst->travel  = bst_travel;

  return bst;
}

int bst_size(struct BST *bst)
{
  return bst_size_(bst->root);
}

static int bst_size_(struct TreeNode *root)
{
  if (root == NULL)
    return 0;

  return bst_size_(root->left) + 1 + bst_size_(root->right);
}

/* 比函数将来必改 */
static void bst_draw_(struct TreeNode *root, int d, int l, int r)
{
  if (root == NULL)
    return;

  int val = *(int*) root->data;
  int mid = (l + r) >> 1;

  printf("\033[%d;%dH\033[33m%d\033[0m\033[49m", d * 3, 80 + mid, val);
  fflush(stdout);
  sleep(1);
  
  bst_draw_(root->left,  d + 1, l, mid - 1);
  bst_draw_(root->right, d + 1, mid + 1, r);
}

void bst_draw(struct BST *bst)
{
  if (bst->root == NULL)
    return;

  int h = bst_height_(bst->root);
  int w = (1 << h) - 1;

  printf("\033[1;80H\033[32;3;5mBinary Search Tree:\033[0m");
  bst_draw_(bst->root, 1, 0, w - 1);
  fputc(10, stdout);
}

int bst_empty(struct BST *bst)
{
  return (bst->root == NULL);
}

const void * bst_search(struct BST *bst, const void *key)
{
  return bst_search_(bst->root, key, bst->cmp);
}

static const void *
bst_search_(struct TreeNode *root, const void *key, compare *cmp)
{

  int sub;

  if (root == NULL)
    return NULL;

  sub = cmp(key, root->data);
  if (sub == 0)
    return root->data;

  return (sub < 0 ? bst_search_(root->left, key, cmp)
      : bst_search_(root->right, key, cmp));
}

int bst_delete(struct BST *bst, const void *key)
{
  if (bst_search_(bst->root, key, bst->cmp) == NULL)
    return -1;

  bst->root = bst_delete_(bst->root, key, bst->cmp);
  return 0;
}

static struct TreeNode * bst_delete_(struct TreeNode *root, const void *key, compare *cmp)
{

  int sub;

  if (root == NULL)
    return NULL;

  sub = cmp(key, root->data);
  if (sub < 0)
  {
    root->left = bst_delete_(root->left, key, cmp);
    return root;
  }
  if (sub > 0)
  {
    root->right = bst_delete_(root->right, key, cmp);
    return root;
  }

  struct TreeNode *ptr;
  if (!root->left || !root->right)
  {
    ptr = (root->left ? root->left : root->right);
    free(root);
    return ptr;
  }

  ptr = root->right;
  bst_minimum_(ptr)->left = root->left;
  root->left = root->right = NULL;
  free(root);

  return ptr;
}

int bst_insert(struct BST *bst, const void *key, const void *data)
{
  return bst_insert_(&bst->root, key, data, bst->datasize, bst->cmp);
}

static int bst_insert_(struct TreeNode **root,
                   const void *key,
                   const void *data,
                   const size_t datasize,
                   compare *cmp)
{
  int sub;

  if (*root == NULL)
  {
    *root = (struct TreeNode *) malloc(sizeof(**root) + datasize);
    if (*root == NULL)
      return -1;

    memcpy((*root)->data, data, datasize);
    (*root)->left  = NULL;
    (*root)->right = NULL;

    return 0;
  }

  sub = cmp(key, (*root)->data);
  if (sub == 0)
    return -2; // 插入重复数据

  return (sub < 0 ? bst_insert_(&(*root)->left, key, data, datasize, cmp)
        : bst_insert_(&(*root)->right, key, data, datasize, cmp));
}

const void * bst_maximum(struct BST *bst)
{
  if (bst_empty(bst))
    return NULL;

  return bst_maximum_(bst->root)->data;
}

const void * bst_minimum(struct BST *bst)
{
  if (bst_empty(bst))
    return NULL;

  return bst_minimum_(bst->root)->data;
}

static struct TreeNode * bst_maximum_(struct TreeNode *root)
{
  if (root == NULL || root->right == NULL)
    return root;

  return bst_maximum_(root->right);
}

static struct TreeNode * bst_minimum_(struct TreeNode *root)
{
  if (root == NULL || root->left == NULL)
    return root;

  return bst_minimum_(root->left);
}

int bst_height(struct BST *bst)
{
  return bst_height_(bst->root);
}

static int bst_height_(struct TreeNode *root)
{
  int lh, rh;

  if (root == NULL)
    return 0;

  lh = bst_height_(root->left);
  rh = bst_height_(root->right);

  return 1 + (lh > rh ? lh : rh);
}

void bst_balance(struct BST *bst)
{
  bst_balance_(&bst->root);
}

static void bst_balance_(struct TreeNode **root)
{
  int sub;

  if (*root == NULL)
    return;

  while (1)
  {
    sub = bst_size_((*root)->left) - bst_size_((*root)->right);
    if (sub >= -1 && sub <= 1)
      break;

    if (sub < -1) /* 右子树重，进行左旋 */
      bst_turn_left(root);
    else          /* 左子树重，进行右旋 */
      bst_turn_right(root);
  }

  bst_balance_(&(*root)->left);
  bst_balance_(&(*root)->right);
}

static void bst_turn_left(struct TreeNode **root)
{
  struct TreeNode *cur = NULL;

  cur = *root;
  *root = cur->right;
  cur->right = NULL;

  bst_minimum_(*root)->left = cur;
}

static void bst_turn_right(struct TreeNode **root)
{
  struct TreeNode *cur = NULL;

  cur = *root;
  *root = cur->left;
  cur->left = NULL;

  bst_maximum_(*root)->right = cur;
}

#ifndef __bst_preorder_iter_impl
static void preOrder(struct TreeNode *root, visit *vis)
{
  if (root == NULL)
    return;

  vis(root->data);
  preOrder(root->left,  vis);
  preOrder(root->right, vis);
}
#else
static void preOrder(struct TreeNode *root, visit *vis)
{
  struct LinkStack *st = NULL;
  struct TreeNode *cur = NULL;

  if (root == NULL)
    return;

  st = CreateLinkStack(sizeof cur);
  if (st == NULL)
    return;

  st->push(st, &root);

  while (st->pop(st, &cur) == 0)
  {
    vis(cur->data);
    if (cur->right != NULL)
      st->push(st, &cur->right);

    if (cur->left != NULL)
      st->push(st, &cur->left);
  }

  DestroyLinkStack(st);
}
#endif

#ifndef __bst_inorder_iter_impl
static void inOrder(struct TreeNode *root, visit* vis)
{
  if (root == NULL)
    return;

  inOrder(root->left,  vis);
  vis(root->data);
  inOrder(root->right, vis);
}
#else
static void inOrder(struct TreeNode *root, visit* vis)
{
  struct LinkStack *st = NULL;
  struct TreeNode *cur = NULL;

  if (root == NULL)
    return;

  st = CreateLinkStack(sizeof cur);
  if (st == NULL)
    return;

  cur = root;

  while (!st->empty(st) || cur != NULL)
  {
    while (cur != NULL)
    {
      st->push(st, &cur);
      cur = cur->left;
    }

    st->pop(st, &cur);
    vis(cur->data);
    cur = cur->right;
  }

  DestroyLinkStack(st);
}
#endif

#ifndef __bst_postorder_iter_impl
static void postOrder(struct TreeNode *root, visit *vis)
{
  if (root == NULL)
    return;

  postOrder(root->left,  vis);
  postOrder(root->right, vis);
  vis(root->data);
}
#else
static void postOrder(struct TreeNode *root, visit *vis)
{
  int i;
  struct ARRAY *arr = NULL;
  struct LinkStack *st = NULL;
  struct TreeNode *cur = NULL;

  if (root == NULL)
    return;

  st = CreateLinkStack(sizeof cur);
  if (st == NULL)
    return;

  arr = Create_Array(sizeof cur);
  if (arr == NULL)
  {
    DestroyLinkStack(st);
    return;
  }

  st->push(st, &root);

  while (st->pop(st, &cur) == 0)
  {
    arr->push_back(arr, &cur);
    if (cur->left != NULL)
      st->push(st, &cur->left);

    if (cur->right != NULL)
      st->push(st, &cur->right);
  }

  arr->reverse(arr);
  for (i = 0; i < arr->size(arr); ++i)
    vis((*(struct TreeNode **) arr->get(arr, i))->data);

  DestroyArray(arr);
  DestroyLinkStack(st);
}
#endif

static void levelOrder(struct TreeNode *root, visit *vis)
{
  struct LinkQueue *qu = NULL;
  struct TreeNode *cur = NULL; 

  qu = CreateLinkQueue(sizeof(struct TreeNode *));
  if (qu == NULL)
    return;

  qu->push(qu, &root);

  while (!qu->empty(qu))
  {
    qu->pop(qu, &cur);
    vis(cur->data);

    if (cur->left != NULL)
      qu->push(qu, &cur->left);
    
    if (cur->right != NULL)
      qu->push(qu, &cur->right);
  }

  DestroyLinkQueue(qu);
}

void bst_travel(struct BST *bst, BST_TRAVEL_MODE mode)
{
  if (bst->root == NULL || bst->vis == NULL)
    return;

  switch (mode)
  {
    case BST_TRAVEL_LEVELORDER:
      levelOrder(bst->root ,bst->vis);
      break;
    case BST_TRAVEL_PREORDER:
      preOrder(bst->root, bst->vis);
      break;
    case BST_TRAVEL_INORDER:
      inOrder(bst->root, bst->vis);
      break;
    case BST_TRAVEL_POSTORDER:
      postOrder(bst->root, bst->vis);
      break;
    default:
      break;
  }
}

static void destroy_node_(struct TreeNode *root)
{
  if (root == NULL)
    return;

  destroy_node_(root->left);
  destroy_node_(root->right);
  free(root);
}

void DestroyBST(struct BST *bst)
{
  if (bst == NULL)
    return;

  destroy_node_(bst->root);
  free(bst);
}