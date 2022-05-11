/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-07
 * @version: 0.0.8
 * @description: Binary Search Tree Header File
 */
/* ========================== BST Start ========================= */
#ifndef __BST_H__
#define __BST_H__

typedef enum { BST_TRAVEL_LEVELORDER,
               BST_TRAVEL_PREORDER,
               BST_TRAVEL_INORDER,
               BST_TRAVEL_POSTORDER } BST_TRAVEL_MODE;

typedef int compare(const void *, const void *);

typedef void visit(const void *);

typedef struct TreeNode
{
  struct TreeNode *left;
  struct TreeNode *right;
  char data[];
} TreeNode;

typedef struct BST
{
  struct TreeNode *root;
  size_t datasize;

  visit *vis;   /* 访问BST中节点数据的回调函数 */
  compare *cmp;

  int (*size) (struct BST *);
  int (*empty) (struct BST *);

  /** 在屏幕上输出一颗BST树 */
  void (*draw) (struct BST *);

  /** 查找元素 */
  const void * (*search) (struct BST *, const void *key);
  
  /** 新增元素 */
  int (*insert) (struct BST *, const void *key, const void *data);
  
  /** 删除元素 */
  int (*delete) (struct BST *, const void *key);

  /** 求BST中最大值的数据元素 */
  const void * (*maximum) (struct BST *);
  
  /** 求BST中最小值的数据元素 */
  const void * (*minimum) (struct BST *);

  /** 求一颗BST树的高度 */
  int (*height) (struct BST *);

  /** 把一颗BST树变平衡 */
  void (*balance) (struct BST *);

  /** 遍历一颗树 */
  void (*travel) (struct BST *, BST_TRAVEL_MODE mode);

} BST;

struct BST *
CreateBST(const size_t datasize, compare *, visit *);

void DestroyBST(struct BST *);

#endif
/* ========================== BST End ========================= */