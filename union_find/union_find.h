/**
 * @author: wangxiaoqiang
 * @version: 0.0.2
 * @create-date: 2022-04-25
 * @modify-date: 2022-05-07
 * @description: UnionFind Header File
 */
/* ========================= UnionFind Start ========================= */
#ifndef __UNIONFIND_H__
#define __UNIONFIND_H__

struct UnionFind {
  int* parents;
  int count; /* 初始联通分量的数量  */
  int (*find) (struct UnionFind *, int);
  int (*unite) (struct UnionFind *, int, int);
  int (*connected) (struct UnionFind *, int, int);
  int (*comp_size) (struct UnionFind *);
};

struct UnionFind * CreateUnionFind(int);

void DestroyUnionFind(struct UnionFind *);

#endif
/* ========================= UnionFind End ========================= */