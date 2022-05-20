/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-10
 * @modify-date: 2020-05-11
 * @version: 0.0.7
 * @description: Unit Test Hepler Functions Header File
 */
/* ========================== Test Hepler Functions Start ========================= */
#ifndef __TEST_HELPER_
#define __TEST_HELPER_

#ifndef __IS_SAME
#define __IS_SAME_(a, b, size) ( memcmp(a, b, size) == 0 )
#endif

#ifndef __COPY_DATA_
#define __COPY_DATA_(dst, src, size) memcpy(dst, src, size)
#endif

#define DATA_SIZE  5
#define STUD_SIZE  5

typedef struct Student
{
  int id;
  char name[32];
  int math;
  int chinese;
} Student;

static const int DATA[ DATA_SIZE ] = { 1, 2, 3, 4, 5 };

static const struct Student STUDS[ STUD_SIZE ] = {
  {1, "stud1", 42, 69},
  {2, "stud2", 53, 71},
  {3, "stud3", 98, 61},
  {4, "stud4", 42, 83},
  {5, "stud5", 67, 92}
};

int cmp_int(const void *, const void *);

int cmp_stud(const void *, const void *);

void print_int(const void *);

void print_s(const void *);

void reverse(void *, const size_t, const size_t);

int is_sorted(const void *, const size_t, const size_t, int (*compar)(const void *, const void *));

#endif
/* ========================== Test Hepler Functions End ========================= */