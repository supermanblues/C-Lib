/*
 * @author: waingxiaoqiang
 * @create-date: 2020-05-13
 * @modify-date: 2020-06-03
 * @version: 1.0.0
 * @description: Dynamic Array Header File
 */
/* ========================== Dynamic Array Start ========================= */
#ifndef __ARRAY_H_
#define __ARRAY_H_

#include <stdio.h>

#if __clang__

typedef int (^compar)(const void *, const void *);
typedef void (^visit)(const void *);
typedef void (^callback)(int, void *, const void *);

#else

typedef int compar(const void *, const void *);
typedef void visit(const void *);
typedef void callback(int, void *, const void *);

#endif

#ifndef __COPY_DATA_
#define __COPY_DATA_(dst, src, size) memcpy(dst, src, size);
#endif

#define Create_Array(datasize) arr_create(1, datasize)

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

  /** 清空数组 */
  void (*clear) (struct ARRAY *);

  /** 返回数组中元素的个数 */
  size_t (*size) (struct ARRAY *);
  
  /** 返回数组中第 index (0-based) 个位置元素的内存地址 */
  void * (*get) (struct ARRAY *, int);

  int (*set) (struct ARRAY *, int, const void *);

  /** 返回数组中第一个位置元素的内存地址 */
  void * (*front) (struct ARRAY *);
  
  /** 返回数组中最后一个位置元素的内存地址 */
  void * (*back) (struct ARRAY *);

  /** 
   * 在数组中第 index (0-based) 个位置前插入元素
   * @return -1: index不合法; 0: 插入成功; (理论上不存在空间占满的情况)
   **/
  int (*insert) (struct ARRAY *, int index, const void *data);
  
  /** 
   * 删除数组中第 index (0-based) 个位置的元素
   * @return -1: index不合法; 0: 删除成功;
   **/
  int (*remove) (struct ARRAY *, int index);

  /** 二维数组删除一行 */ 
  int (*delete_row) (struct ARRAY *, int index);

  /** vector-liked */
  int (*push_front) (struct ARRAY *, const void *);
  int (*push_back) (struct ARRAY *, const void *);
  
  int (*pop_front) (struct ARRAY *);
  int (*pop_back) (struct ARRAY *);

  /** 填充数组 */
  void (*fill) (struct ARRAY *, const void *);

#if __clang__
  void (*travel) (struct ARRAY *, visit);

  void * (*search) (struct ARRAY *, const void *key, compar);

  void * (*max) (struct ARRAY *, compar);
  
  void * (*min) (struct ARRAY *, compar);

  void (*accumulate) (struct ARRAY *, void *, callback);
#else
  void (*travel) (struct ARRAY *, visit *);

  void * (*search) (struct ARRAY *, const void *key, compar *);

  void * (*max) (struct ARRAY *, compar *);
  
  void * (*min) (struct ARRAY *, compar *);

  void (*accumulate) (struct ARRAY *, void *, callback *);
#endif

  /** 排序数组 */
  void (*sort) (struct ARRAY *, int (*compar)(const void *, const void *));

  /** 逆置数组 */
  void (*reverse) (struct ARRAY *);

} ARRAY;

struct ARRAY * arr_create2D(size_t init_capacity, int datasize);
void arr_destroy2D(struct ARRAY *);

struct ARRAY * arr_create(size_t init_capacity, int datasize);

void arr_destroy(struct ARRAY *);

#endif
/* ========================== Dynamic Array End   ========================= */
