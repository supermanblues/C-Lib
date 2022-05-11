/**
 * @author: waingxiaoqiang
 * @create-date: 2020-05-10
 * @modify-date: 2020-05-11
 * @version: 0.0.7
 * @description: Unit Test Hepler Functions Header File
 */
/* ========================== Test Hepler Functions Start ========================= */
#define __IS_SAME_(a, b, size) ( memcmp(a, b, size) == 0 )
#define __COPY_DATA_(dst, src, size) memcpy(dst, src, size)

typedef int compar(const void *, const void *);

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
  {1, "stud1", 44, 69},
  {2, "stud2", 53, 71},
  {3, "stud3", 98, 61},
  {4, "stud4", 42, 83},
  {5, "stud5", 67, 92}
};

int cmp_int(const void *, const void *);

int cmp_stud(const void *, const void *);

void print_s(const void *);

int max(const int arr[], const size_t n);

int min(const int arr[], const size_t n);

int is_same(const void *p, const void *q, const size_t size);

void reverse(void *arr, const size_t num, const size_t size);

int is_sorted(const void *data, const size_t num, const size_t size, compar* cmp);
/* ========================== Test Hepler Functions End ========================= */