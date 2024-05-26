#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#define TAB_SIZE  1000
#define BUF_SIZE  1000

// 1
////////////////////////////////////////////////////////////

int get(int cols, int row, int col, const int* A) {
  return A[cols * row + col];
}

void set(int cols, int row, int col, int* A, int value) {
  A[cols * row + col] = value;
}

void prod_mat(int rowsA, int colsA, int colsB, int* A, int* B, int* AB) {
  for(int i = 0; i < rowsA; i++) {
    for(int j = 0; j < colsB; j++) {
      int prod = 0;
      for(int k = 0; k < colsA; k++) {
        prod += get(colsA, i, k, A) * get(colsB, k, j, B);
      }
      set(colsB, i, j, AB, prod);
    }
  }
}

void read_mat(int rows, int cols, int* t) {
  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
      int val;
      scanf("%d", &val);
      set(cols, i, j, t, val);
    }
  }
}

void print_mat(int rows, int cols, int* t) {
  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
      int val = get(cols, i, j, t);
      printf("%d ", val);
    }
    printf("\n");
  }
}

// 2
/////////////////////////////////////////////////////////////

int read_ints_from_line(char* c_buf, int *int_buf, int index) {
  fgets(c_buf, BUF_SIZE, stdin);
  int i = 0;
  int j = index;
  while(c_buf[i] != '\n') {
    int_buf[j] = 0;
    int sign = 1;
    while(c_buf[i] != ' ' && c_buf[i] != '\n') {
      if(c_buf[i] == '-') {
        sign = -1;
        i += 1;
      }
      int_buf[j] = int_buf[j] * 10 + (c_buf[i] - '0');
      i += 1;
    }
    int_buf[j] *= sign;
    if(c_buf[i] == ' ') {
      i += 1;
    }
    j += 1;
  }
  return j - index;
}

int read_int_lines_cont(int* ptr_array[]) {
  int* arr = ptr_array[0];
  char c_buf[BUF_SIZE];
  int i = 0, j = 0, count;
  while(!feof(stdin)) {
    count = read_ints_from_line(c_buf, arr, i);
    if(count == 0) {
      break;
    }
    ptr_array[j] = &arr[i];
    i += count;
    j += 1;
  }
  return j;
}

void write_int_line_cont(int *ptr_array[], int n) {
  int* ptr = ptr_array[n];
  int* endptr = ptr_array[n + 1];
  while(ptr != endptr) {
    printf("%d ", *ptr);
    ptr++;
  }
}

// 3
///////////////////////////////////////////////////////////

int read_char_lines(char *array[]) {
  int i = 0;
  char buf[BUF_SIZE];
  while(!feof(stdin)) {
    fgets(buf, BUF_SIZE, stdin);
    int len = strlen(buf);
    array[i] = (char *)malloc(len + 1);
    strcpy(array[i], buf);
    i++;
  }
  array[i] = NULL;
  return i;
}

void write_char_line(char *array[], int n) {
  printf("%s\n", array[n]);
}

void delete_lines(char *array[]) {
  int i = 0;
  while(array[i] != NULL) {
    free(array[i]);
    i += 1;
  }
}

// 4
////////////////////////////////////////////////

typedef struct {
	int *values;
	int len;
	double average;
} line_type;

int read_int_lines(line_type lines_array[]) {
  int lines=0;
  //size_t len=32;
  int tab[TAB_SIZE];
  int cnt,suma;
  char line[BUF_SIZE];
  char *word;
  char space[]=" ";
  //getline(&line,&len,stdin);
  fgets(line,BUF_SIZE,stdin);
  while (strlen(line)-1 && !feof(stdin) && !ferror(stdin)){
    cnt=suma=0;
    word=strtok(line,space);
    while (word!=NULL){
      tab[cnt++]=atoi(word);
      suma+=tab[cnt-1];
      word=strtok(NULL,space);
    }
    lines_array[lines].values=(int *)malloc(sizeof(int)*cnt);
    lines_array[lines].len=cnt;
    lines_array[lines].average=suma/cnt;
    for (int i=0; i<cnt; i++){
      *(lines_array[lines].values+i)=tab[i];
    }
    lines++;
    //getline(&line,&len,stdin);
    fgets(line,BUF_SIZE,stdin);
  }
  return lines;
}

void write_int_line(line_type lines_array[], int n) {
  for (int i=0; i<lines_array[n].len; i++){
    printf("%d ",*(lines_array[n].values+i));
  }
  printf("\n%.2f\n",lines_array[n].average);
}

void delete_int_lines(line_type array[], int line_count) {
  for (int i=0; i<line_count; i++){
    free(array[i].values);
  }
}

int cmp (const void *a, const void *b) {
  line_type *fir=(line_type *)a;
  line_type *sec=(line_type *)b;
  double diff=fir->average-sec->average;
  if (diff<0) return -1;
  else if (diff>0) return 1;
  else return 0;
}

void sort_by_average(line_type lines_array[], int line_count) {
  qsort(lines_array,line_count,sizeof(line_type),cmp);
}

// 5
///////////////////////////////////////////////////////////

typedef struct {
	int r, c, v;
} triplet;

int read_sparse(triplet* triplet_array, int n_triplets) {
  for (int i = 0; i < n_triplets; i++){
    scanf("%d %d %d", &triplet_array[i].r, &triplet_array[i].c, &triplet_array[i].v);
  }
  return n_triplets;
}

int cmp_triplets(const void* t1, const void* t2) {
  triplet *x = (triplet *)t1;
  triplet *y = (triplet *)t2;
  double d = x->r - y->r;
  if(d != 0) { return d; }
  return x->c - y->c;
}

void make_CSR(triplet* triplet_array, int n_triplets, int rows, int* V, int* C, int* R) {
  qsort(triplet_array, n_triplets, sizeof(triplet), cmp_triplets);
  for(int i = 0; i < rows + 1; i++) {
    R[i] = 0;
  }
  for(int i = 0; i < n_triplets; i++) {
    V[i] = triplet_array[i].v;
    C[i] = triplet_array[i].c;
    for (int j = triplet_array[i].r + 1; j < rows + 1; j++) {
      R[j] += 1;
    }
  }
}

void multiply_by_vector(int rows, const int* V, const int* C, const int* R,
						const int* x, int* y) {
  for(int i = 0; i < rows; i++) {
    y[i] = 0;
    for(int j = R[i]; j < R[i + 1]; j++) {
      y[i] += V[j] * x[C[j]];
    }
  }
}

void read_vector(int* v, int n) {
  for(int i = 0; i < n; i++) {
    scanf("%d", &v[i]);
  }
}

void write_vector(int* v, int n) {
  for (int i = 0; i < n; i++){
    printf("%d ", v[i]);
  }
  printf("\n");
}

// auxiliary
////////////////////////////////////////////////////////////

int read_int(void) {
	char c_buf[BUF_SIZE];
	fgets(c_buf, BUF_SIZE, stdin);
	return (int)strtol(c_buf, NULL, 10);
}

int main(void) {
	int to_do = read_int();

	int A[TAB_SIZE], B[TAB_SIZE], AB[TAB_SIZE];
	int n, lines_counter, rowsA, colsA, rowsB, colsB;
	int rows, cols, n_triplets;
	char* char_lines_array[TAB_SIZE] = { NULL };
	int continuous_array[TAB_SIZE];
	int* ptr_array[TAB_SIZE];
	triplet triplet_array[TAB_SIZE];
	int V[TAB_SIZE], C[TAB_SIZE], R[TAB_SIZE];
	int x[TAB_SIZE], y[TAB_SIZE];
	line_type int_lines_array[TAB_SIZE];

	switch (to_do) {
		case 1:
			scanf("%d %d", &rowsA, &colsA);
			read_mat(rowsA, colsA, A);
			scanf("%d %d", &rowsB, &colsB);
			read_mat(rowsB, colsB, B);
			prod_mat(rowsA, colsA, colsB, A, B, AB);
			print_mat(rowsA, colsB, AB);
			break;
		case 2:
			n = read_int() - 1; // we count from 1 :)
			ptr_array[0] = continuous_array;
			read_int_lines_cont(ptr_array);
			write_int_line_cont(ptr_array, n);
			break;
		case 3:
			n = read_int() - 1;
			read_char_lines(char_lines_array);
			write_char_line(char_lines_array, n);
			delete_lines(char_lines_array);
			break;
		case 4:
			n = read_int() - 1;
			lines_counter = read_int_lines(int_lines_array);
			sort_by_average(int_lines_array, lines_counter);
			write_int_line(int_lines_array, n);
			delete_int_lines(int_lines_array, lines_counter);
			break;
		case 5:
			scanf("%d %d %d", &rows, &cols, &n_triplets);
			n_triplets = read_sparse(triplet_array, n_triplets);
			read_vector(x, cols);
			make_CSR(triplet_array, n_triplets, rows, V, C, R);
			multiply_by_vector(rows, V, C, R, x, y);
			write_vector(V, n_triplets);
			write_vector(C, n_triplets);
			write_vector(R, rows + 1);
			write_vector(y, rows);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

