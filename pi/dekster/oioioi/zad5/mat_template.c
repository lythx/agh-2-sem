#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 40

void read_vector(double x[], int n) {
	for(int i = 0; i < n; ++i) {
		scanf("%lf", x++);
	}
}

void print_vector(double x[], int n) {
	for(int i = 0; i < n; ++i) {
		printf("%.4f ", x[i]);
	}
	printf("\n");
}

void read_mat(double A[][SIZE], int m, int n) {
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%lf", &A[i][j]);
		}
	}
}

void print_mat(double A[][SIZE], int m, int n) {
  double eps = 0.0001;
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
      if(fabs(A[i][j]) < eps) {
        printf("%.4f ", -0.0);
      } else {
        printf("%.4f ", A[i][j]);
      }
		}
		printf("\n");
	}
}

// 1. Calculate matrix product, AB = A X B
// A[m][p], B[p][n], AB[m][n]
void mat_product(double A[][SIZE], double B[][SIZE], double AB[][SIZE], int m, int p, int n) {
  for(int i = 0; i < m; i++) {
    for(int j = 0; j < n; j++) {
      double prod = 0.0;
      for(int k = 0; k < p; k++) {
        prod += A[i][k] * B[k][j];
      }
      AB[i][j] = prod;
    }
  }
}


// 2. Matrix triangulation and determinant calculation - simplified version
// (no rows' swaps). If A[i][i] == 0, function returns NAN.
// Function may change A matrix elements.
double gauss_simplified(double A[][SIZE], int n) {
  double det = 1.0;
  for(int i = 0; i < n; i++) {
    if(A[i][i] == 0) {
      return NAN;
    }
    det *= A[i][i];
    for(int j = i + 1; j < n; j++) {
      double p = -A[j][i] / A[i][i];
      for(int k = i + 1; k < n; k++) {
        A[j][k] += A[i][k] * p;
      }
    }
  }
  return det;
}

void backward_substitution_index(double A[][SIZE], const int indices[], double x[], int n) {
}

void swap(int* a, int* b){
  int c = *a;
  *a = *b;
  *b = c;
}

// 3. Matrix triangulation, determinant calculation, and Ax = b solving - extended version
// (Swap the rows so that the row with the largest, leftmost nonzero entry is on top. While
// swapping the rows use index vector - do not copy entire rows.)
// If max A[i][i] < eps, function returns 0.
// If det != 0 && b != NULL && x != NULL then vector x should contain solution of Ax = b.

double gauss(double A[][SIZE], const double b[], double x[], const int n, const double eps) {
  int rows[n];
  for(int i = 0; i < n; i++) {
    rows[i] = i;
  }
  double b_copy[n];
  for(int i = 0; i < n; i++) {
    b_copy[i] = b[i];
  }
  double det = 1.0;
  for(int i = 0; i < n; i++){
    int mx = i;
    for(int j = i + 1; j < n; j ++) {
      if(fabs(A[rows[j]][i]) > fabs(A[rows[mx]][i])) {
        mx = j;
      }
    }
    if(mx != i) {
      swap(&rows[i], &rows[mx]);
      det *= -1.0;
    }
    if(fabs(A[rows[i]][i]) < eps) {
      return 0.0;
    }
    det *= A[rows[i]][i];
    for(int j = i + 1; j < n; j++) {
      double p = -A[rows[j]][i] / A[rows[i]][i];
      for(int k = i + 1; k < n; k++) {
        A[rows[j]][k] += A[rows[i]][k] * p;
      }
      b_copy[rows[j]] += b_copy[rows[i]] * p;
    }
  }
  if(det != 0) {
    for(int i = n - 1; i >= 0; i--) {
      double s = b_copy[rows[i]];
      for(int j = n - 1; j > i; j--) {
        s -= x[j] * A[rows[i]][j];
      }
      x[i] = s / A[rows[i]][i];
    }
  }
  return det;
}


// 4. Returns the determinant; B contains the inverse of A (if det(A) != 0)
// If max A[i][i] < eps, function returns 0.
double matrix_inv(double A[][SIZE], double B[][SIZE], int n, double eps) {
  double C[SIZE][SIZE];
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      C[i][j] = i == j ? 1.0 : 0.0;
    }
  }
  int rows[n];
  for(int i = 0; i < n; i++) {
    rows[i] = i;
  }
  double det = 1.0;
  for(int i = 0; i < n; i++){
    int mx = i;
    for(int j = i + 1; j < n; j ++) {
      if(fabs(A[rows[j]][i]) > fabs(A[rows[mx]][i])) {
        mx = j;
      }
    }
    if(mx != i) {
      swap(&rows[i], &rows[mx]);
      det *= -1.0;
    }
    if(fabs(A[rows[i]][i]) < eps) {
      return 0.0;
    }
    double val = A[rows[i]][i];
    det *= val;
    for(int j = i; j < n; j++) {
      A[rows[i]][j] /= val;
    }
    for(int j = 0; j < n; j++) {
      C[rows[i]][j] /= val;
    }
    for(int j = 0; j < n; j++) {
      if(i == j) {
        continue;
      }
      double p = -A[rows[j]][i] / A[rows[i]][i];
      for(int k = i; k < n; k++) {
        A[rows[j]][k] += A[rows[i]][k] * p;
      }
      for(int k = 0; k < n; k++) {
        C[rows[j]][k] += C[rows[i]][k] * p;
      }
    }
  }
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      B[i][j] = C[rows[i]][j];
    }
  }
  return det;
}

int main(void) {

	double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
	double b[SIZE], x[SIZE], det, eps = 1.e-13;

	int to_do;
	int m, n, p;

	scanf ("%d", &to_do);

	switch (to_do) {
		case 1:
			scanf("%d %d %d", &m, &p, &n);
			read_mat(A, m, p);
			read_mat(B, p, n);
			mat_product(A, B, C, m, p, n);
			print_mat(C, m, n);
			break;
		case 2:
			scanf("%d", &n);
			read_mat(A, n, n);
			printf("%.4f\n", gauss_simplified(A, n));
			break;
		case 3:
			scanf("%d", &n);
			read_mat(A,n, n);
			read_vector(b, n);
			det = gauss(A, b, x, n, eps);
			printf("%.4f\n", det);
			if (det) print_vector(x, n);
			break;
		case 4:
			scanf("%d", &n);
			read_mat(A, n, n);
			det = matrix_inv(A, B, n, eps);
			printf("%.4f\n", det);
			if (det) print_mat(B, n, n);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

