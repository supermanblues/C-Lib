/*
 * @author: waingxiaoqiang
 * @create-date: 2020-05-13
 * @modify-date: 2020-05-14
 * @version: 0.0.2
 * @description: Dynamic Array Header File
 */
/* ========================== Dynamic Array Start ========================= */
#ifndef __ARRAY_H_
#define __ARRAY_H_

#include "../sort/sort.h"

#ifndef __COMPAR_
#define __COMPAR_
typedef int compar(const void *a, const void *b);
#endif

#ifndef __MATCH_
#define __MATCH_
typedef int match(const void *key, const void *record);
#endif

#ifndef __COPY_DATA_
#define __COPY_DATA_(dst, src, size) memcpy(dst, src, size);
#endif

#define Create_Array(datasize) CreateArray(1, datasize)

typedef struct ARRAY
{
  void *base;      /** 存储数据元素的基地址 */
  int datasize;    /** 单个数据元素占用的空间 */
  size_t length;   /** 实际存储在数组中的元素数量 */
  size_t capacity; /** 数组的容量 */

  /** 判断数组是否为空 */
  int (*empty) (struct ARRAY *);

  /** 判断数组是否为满 */
  int (*full) (struct ARRAY *);

  /** 返回数组中元素的个数 */
  size_t (*size) (struct ARRAY *);
  
  /** 返回数组中第 index (0-based) 个位置元素的内存地址 */
  void * (*get) (struct ARRAY *, int);

  /** 返回数组中第一个位置元素的内存地址 */
  void * (*front) (struct ARRAY *);
  
  /** 返回数组中最后一个位置元素的内存地址 */
  void * (*back) (struct ARRAY *);
  
  /** 同上 */
  void * (*rear) (struct ARRAY *);

  /* 查找数组元素 */
  void * (*find) (struct ARRAY *, const void *key, match *);

  /** 
   * 在数组中第 index (0-based) 个位置前插入元素
   * @return -1: index不合法; 0: 插入成功; (理论上不存在空间占满的情况)
   **/
  int (*insert) (struct ARRAY *, int index, const void *data);
  
  /** 
   * 删除数组中第 index (0-based) 个位置的元素
   * @return -1: 空数组; -2: index不合法; 0: 删除成功;
   **/
  int (*delete) (struct ARRAY *, int index);

  /** vector-liked */
  int (*push_front) (struct ARRAY *, const void *);
  int (*push_back) (struct ARRAY *, const void *);
  
  int (*pop_front) (struct ARRAY *);
  int (*pop_back) (struct ARRAY *);

  /** 初始化数组 */
  void (*init) (struct ARRAY *, const void *);
  
  /** 遍历数组 */
  void (*travel) (struct ARRAY *, void (*visit) (const void *));

  /** 排序数组 */
  void (*sort) (struct ARRAY *, compar *, SORT_MODE);

  /** 逆置数组 */
  void (*reverse) (struct ARRAY *);

} ARRAY, ARR;

struct ARRAY * CreateArray(size_t capacity, int datasize);

void DestroyArray(struct ARRAY *);

#endif
/* ========================== Dynamic Array End   ========================= */