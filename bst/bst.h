/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-19
 * @version: 0.1.0
 * @description: Binary Search Tree Header File
 */
/* ========================== BST Start ========================= */
#ifndef __BST_H__
#define __BST_H__

typedef enum { BST_TRAVEL_LEVELORDER,
               BST_TRAVEL_PREORDER,
               BST_TRAVEL_INORDER,
               BST_TRAVEL_POSTORDER } BST_TRAVEL_MODE;

typedef int compar(const void *, const void *);

typedef void (^visit)(const void *);

#define bst_create(datasize, compar, visit) CreateBST(datasize, compar, visit)
#define bst_destroy(ptr) DestroyBST(ptr)

typedef struct TreeNode
{
  struct TreeNode *left;
  struct TreeNode *right;
  char data[];
} TreeNode;

typedef struct BST
{
  struct TreeNode *root;
  int datasize;
  size_t length;

  /** 访问BST中节点数据的回调函数 */
  visit visit;

  compar *compar;

  /** 判断BST是否为空  */
  int (*empty) (struct BST *);

  /** 返回BST中元素的个数 */
  size_t (*size) (struct BST *);

   /** 求一颗BST子数的节点个数 */
  size_t (*count) (struct BST *);

  /** 在屏幕上输出一颗BST树 */
  void (*draw) (struct BST *);

  /** 查找元素 */
  void * (*search) (struct BST *, const void *key);
  
  /** 新增元素 
   *@return -1: 节点内存分配失败; -2: 插入重复数据  0: 成功;
   */
  int (*insert) (struct BST *, const void *key, const void *data);
  
  /** 删除元素 */
  int (*delete) (struct BST *, const void *key);

  /** 求BST中最大值的数据元素 */
  const void * (*max) (struct BST *);
  
  /** 求BST中最小值的数据元素 */
  const void * (*min) (struct BST *);

  /** 求一颗BST树的高度 */
  int (*height) (struct BST *);

  /** 把一颗BST树变平衡 */
  void (*balance) (struct BST *);

  /** 遍历一颗树 */
  void (*travel) (struct BST *, int mode);

} BST;

// Deprecated: use bst_create instead
struct BST * CreateBST(int datasize, compar *, visit);

// Deprecated: use bst_destroy instead
void DestroyBST(struct BST *);

#endif
/* ========================== BST End ========================= */