/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-13
 * @modify-date: 2020-05-13
 * @version: 0.0.1
 * @description: Dynamic Array Header File
 */
/* ========================== Dynamic Array Start ========================= */
#ifndef __ARRAY_H_
#define __ARRAY_H_

#ifndef __COMPAR_
#define __COMPAR_
typedef int compar(const void *, const void *);
#endif

#ifndef __COPY_DATA_
#define __COPY_DATA_(dst, src, size) memcpy(dst, src, size);
#endif

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
  const void * (*get) (struct ARRAY *, int);

  /** 返回数组中第一个位置元素的内存地址 */
  const void * (*front) (struct ARRAY *);
  
  /** 返回数组中最后一个位置元素的内存地址 */
  const void * (*back) (struct ARRAY *);
  
  /** 同上 */
  const void * (*rear) (struct ARRAY *);

  /* 查找数组元素 */
  void * (*find) (struct ARRAY *, const void *key, compar *);

  /** 
   * 在数组中第 index (0-based) 个位置前插入元素
   * @return -1: 空间满; -2: index不合法; 0: 插入成功;
   **/
  int (*insert) (struct ARRAY *, int index, const void *data);
  
  /** 删除数组中第 index (0-based) 个位置的元素 */
  int (*delete) (struct ARRAY *, int index);

  int (*push_front) (struct ARRAY *, const void *);
  int (*push_back) (struct ARRAY *, const void *);

  int (*pop_front) (struct ARRAY *);
  int (*pop_back) (struct ARRAY *);

  void * (*minimum) (struct ARRAY *);

  void * (*maximum) (struct ARRAY *);
  
  /** 从头至尾（0 ... length - 1）遍历数组 */
  void (*travel) (struct ARRAY *, void (*visit) (const void *));

  /** 排序数组 */
  void (*sort) (struct ARRAY *, compar *);

  /** 逆置数组 */
  void (*reverse) (struct ARRAY *);

} ARRAY, ARR;

struct ARRAY * CreateArray(size_t capacity, int datasize);

void DestroyArray(struct ARRAY *);

#endif
/* ========================== Dynamic Array End   ========================= */