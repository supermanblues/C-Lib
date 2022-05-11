/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-09
 * @version: 0.0.3
 * @description: Various Sorting Algorithm Header File
 */
/* ========================== Sorting Start ========================= */
#ifndef __SORTING_H_
#define __SORTING_H_

#ifndef __COPY_DATA_
#define __COPY_DATA_(dst, src, size) memcpy(dst, src, size)
#endif

typedef int compar(const void *, const void *);
typedef void sort(void *base, const size_t, const size_t, compar *);

typedef struct MySort
{
  /* 冒泡排序  */
  sort *bubble_sort;

  /* 简单选择排序 */
  sort *select_sort;

  /* 直接插入排序 */
  sort *insert_sort;

  /* 快速排序 */
  sort *quick_sort;

  /* 归并排序 */
  sort *merge_sort;

  /* 希尔排序 */
  sort *shell_sort;

  /* 堆排序 */
  sort *heap_sort;

  /* 桶排序 */
  sort *bucket_sort;

} MySort;

struct MySort * CreateMySort(void);

void DestroyMySort(struct MySort *);

#endif
/* ========================== Sorting End ========================= */