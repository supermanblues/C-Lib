/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-14
 * @version: 0.0.5
 * @description: Various Sorting Algorithm Header File
 */
/* ========================== Sorting Start ========================= */
#ifndef __SORTING_H_
#define __SORTING_H_

#ifndef __COPY_DATA_
#define __COPY_DATA_(dst, src, size) memcpy(dst, src, size)
#endif

#ifndef __COMPAR_
#define __COMPAR_
typedef int compar(const void *a, const void *b);
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
  void (*sort) (void *, const size_t, const size_t, compar *, SORT_MODE);
} MySort;

struct MySort * CreateMySort(void);

void DestroyMySort(struct MySort *);

#endif
/* ========================== Sorting End ========================= */