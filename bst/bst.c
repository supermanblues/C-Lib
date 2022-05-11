/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-06
 * @version: 0.0.7
 * @description: Binary Search Tree Implementation File
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bst.h"
#include "../stack/linkstack.h"
#include "../queue/linkqueue.h"

int size(struct BST *);
int empty(struct BST *);
void draw(struct BST *);

const void * search(struct BST *, const void *);

int insert(struct BST *, const void *, const void *);
int delete(struct BST *, const void *);

const void * maximum(struct BST *);
const void * minimum(struct BST *);

int height(struct BST *);

void balance(struct BST *);

void travel(struct BST *, BST_TRAVEL_MODE mode);

static const void *
search_(struct TreeNode *, const void *, compare *);

static int
insert_(struct TreeNode **, const void *, const void *,  const size_t, compare *);

static struct TreeNode *
delete_(struct TreeNode *, const void *, compare *);

static int
size_(struct TreeNode *);

static struct TreeNode *
maximum_(struct TreeNode *);

static struct TreeNode *
minimum_(struct TreeNode *);

static int
height_(struct TreeNode *);

static void
balance_(struct TreeNode **);

static void
turn_left(struct TreeNode **);

static void
turn_right(struct TreeNode **);

struct BST * CreateBST(const size_t datasize, compare *cmp, visit *vis)
{
  // 守护
  if (datasize <= 0 || cmp == NULL)
    return NULL;

  struct BST *bst = NULL;

  bst = (struct BST *) malloc(sizeof *bst);
  if (bst == NULL)
    return NULL;

  bst->root  = NULL;

  bst->cmp = cmp;
  bst->vis = vis;
  bst->datasize = datasize;

  /* =============== Operations =============== */
  bst->size    = size;
  bst->empty   = empty;
  bst->draw    = draw;
  bst->search  = search;
  bst->insert  = insert;
  bst->delete  = delete;
  bst->maximum = maximum;
  bst->minimum = minimum;
  bst->height  = height;
  bst->balance = balance;
  bst->travel  = travel;

  return bst;
}

int size(struct BST *bst)
{
  return size_(bst->root);
}

static int size_(struct TreeNode *root)
{
  if (root == NULL)
    return 0;

  return size_(root->left) + 1 + size_(root->right);
}

/* 比函数将来必改 */
static void draw_(struct TreeNode *root, int d, int l, int r)
{
  if (root == NULL)
    return;

  int val = *(int*) root->data;
  int mid = (l + r) >> 1;

  printf("\033[%d;%dH\033[33m%d\033[0m\033[49m", d * 3, 80 + mid, val);
  fflush(stdout);
  sleep(1);
  
  draw_(root->left,  d + 1, l, mid - 1);
  draw_(root->right, d + 1, mid + 1, r);
}

void draw(struct BST *bst)
{
  if (bst->root == NULL)
    return;

  int h = height_(bst->root);
  int w = (1 << h) - 1;

  printf("\033[1;80H\033[32;3;5mBinary Search Tree:\033[0m");
  draw_(bst->root, 1, 0, w - 1);
  fputc(10, stdout);
}

int empty(struct BST *bst)
{
  return (bst->root == NULL);
}

const void * search(struct BST *bst, const void *key)
{
  return search_(bst->root, key, bst->cmp);
}

static const void *
search_(struct TreeNode *root, const void *key, compare *cmp)
{

  int sub;

  if (root == NULL)
    return NULL;

  sub = cmp(key, root->data);
  if (sub == 0)
    return root->data;

  return (sub < 0 ? search_(root->left, key, cmp)
      : search_(root->right, key, cmp));
}

int delete(struct BST *bst, const void *key)
{
  if (search_(bst->root, key, bst->cmp) == NULL)
    return -1;

  bst->root = delete_(bst->root, key, bst->cmp);
  return 0;
}

static struct TreeNode * delete_(struct TreeNode *root, const void *key, compare *cmp)
{

  int sub;

  if (root == NULL)
    return NULL;

  sub = cmp(key, root->data);
  if (sub < 0)
  {
    root->left = delete_(root->left, key, cmp);
    return root;
  }
  if (sub > 0)
  {
    root->right = delete_(root->right, key, cmp);
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
  minimum_(ptr)->left = root->left;
  root->left = root->right = NULL;
  free(root);

  return ptr;
}

int insert(struct BST *bst, const void *key, const void *data)
{
  return insert_(&bst->root, key, data, bst->datasize, bst->cmp);
}

static int insert_(struct TreeNode **root,
                   const void *key,
                   const void *data,
                   const size_t datasize,
                   compare *cmp)
{
  int sub;

  if (*root == NULL)
  {
    *root = malloc(sizeof(**root) + datasize);
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

  return (sub < 0 ? insert_(&(*root)->left, key, data, datasize, cmp)
        : insert_(&(*root)->right, key, data, datasize, cmp));
}

const void * maximum(struct BST *bst)
{
  if (empty(bst))
    return NULL;

  return maximum_(bst->root)->data;
}

const void * minimum(struct BST *bst)
{
  if (empty(bst))
    return NULL;

  return minimum_(bst->root)->data;
}

static struct TreeNode * maximum_(struct TreeNode *root)
{
  if (root == NULL || root->right == NULL)
    return root;

  return maximum_(root->right);
}

static struct TreeNode * minimum_(struct TreeNode *root)
{
  if (root == NULL || root->left == NULL)
    return root;

  return minimum_(root->left);
}

int height(struct BST *bst)
{
  return height_(bst->root);
}

static int height_(struct TreeNode *root)
{
  int lh, rh;

  if (root == NULL)
    return 0;

  lh = height_(root->left);
  rh = height_(root->right);

  return 1 + (lh > rh ? lh : rh);
}

void balance(struct BST *bst)
{
  balance_(&bst->root);
}

static void balance_(struct TreeNode **root)
{
  int sub;

  if (*root == NULL)
    return;

  while (1)
  {
    sub = size_((*root)->left) - size_((*root)->right);
    if (sub >= -1 && sub <= 1)
      break;

    if (sub < -1) /* 右子树重，进行左旋 */
      turn_left(root);
    else          /* 左子树重，进行右旋 */
      turn_right(root);
  }

  balance_(&(*root)->left);
  balance_(&(*root)->right);
}

static void turn_left(struct TreeNode **root)
{
  struct TreeNode *cur = NULL;

  cur = *root;
  *root = cur->right;
  cur->right = NULL;

  minimum_(*root)->left = cur;
}

static void turn_right(struct TreeNode **root)
{
  struct TreeNode *cur = NULL;

  cur = *root;
  *root = cur->left;
  cur->left = NULL;

  maximum_(*root)->right = cur;
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

  st = CreateLinkStack(sizeof(struct TreeNode *));
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

  st = CreateLinkStack(sizeof(struct TreeNode *));
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

void travel(struct BST *bst, BST_TRAVEL_MODE mode)
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