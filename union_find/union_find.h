/**
 * @author: wangxiaoqiang
 * @version: 0.0.4
 * @create-date: 2022-04-25
 * @modify-date: 2022-05-15
 * @description: UnionFind Header File
 */
/* ========================= UnionFind (Disjoint Set) Start ========================= */
#ifndef __UNIONFIND_H__
#define __UNIONFIND_H__

typedef struct UnionFind
{
  struct ARRAY *parents;    /** 存放整型元素的动态数组 */
  size_t count;             /** 初始联通分量的数量 */

  /** 返回联通分量的数量  */
  size_t (*size) (struct UnionFind *);
  
  int (*find) (struct UnionFind *, int);

  int (*unite) (struct UnionFind *, int, int);

  int (*connected) (struct UnionFind *, int, int);

} UnionFind;

struct UnionFind * CreateUnionFind(int);

void DestroyUnionFind(struct UnionFind *);

#endif
/* ========================= UnionFind (Disjoint Set) End ========================= */