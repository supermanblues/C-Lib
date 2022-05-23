/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-23
 * @version: 0.0.6
 * @description: Various Sorting Algorithm Header File
 */
/* ========================== Sorting Start ========================= */
#ifndef __SORTING_H_
#define __SORTING_H_

#ifndef __COPY_DATA_
#define __COPY_DATA_(dst, src, size) memcpy(dst, src, size)
#endif

#if __clang__
typedef int (^compar)(const void *, const void *);
#else
typedef int compar(const void *, const void *);
#endif

typedef enum
{
  BUBBLE_SORT,    /** 冒泡排序 */
  SELECTION_SORT, /** 简单选择排序 */
  INSERTION_SORT, /** 直接插入排序  */
  QUICK_SORT,     /** 快速排序 */
  MERGE_SORT      /** 归并排序 */
} SORT_MODE;

typedef struct MySort
{
#if __clang__
  void (*sort) (void *, const size_t, const size_t, compar, int);
#else
  void (*sort) (void *, const size_t, const size_t, compar *, int);
#endif
} MySort;

struct MySort * mysort_create(void);

void mysort_destroy(struct MySort *);
#endif
/* ========================== Sorting End ========================= */