#include <stdio.h>
#include <stdlib.h>

void FizzBuzz(int n); // <- declaration (so compiler stops complaining)

int compare(const void *A, const void *B);

int main() {
  // arr length (must declare explicitly)
  // PERSONAL NOTE: cannot use sizeof(arr)/sizeof(type) since sizeof() only 
  // knows compile-time sizes. 
  // TLDR sizeof() does not work for malloc'ed arrays. Thus the length must be 
  // tracked in a separate variable
  int n = 20;
  // typecast allocated mem to array of pointers to integers
  int* arr = (int*) malloc(n * sizeof(int));

  for (int i = 0; i < n; i++) {
    // PERSONAL NOTE: arr[i] = *(arr + i) where arr (the array pointer) is 
    // getting i (the element we are looking for) added to it so we get the
    // address of the next element and then derference it to access that value
    // (lowk my boy Ritchie was a genius)
    arr[i] = i + 1; // +1 b/c we want to begin populating with 1 onwards
  }

  for (int i = 0; i < n; i++) {
    printf("Array FizzBuzz: %d, ", arr[i]);
    FizzBuzz(arr[i]);
    printf("\n");
  }

  for (int i = 1; i <= 30; i++) {
    printf("1-30 FizzBuzz: %d,", i);
    FizzBuzz(i);
    printf("\n");
  }

  /* q-sort portion */

  qsort(arr, n, sizeof(arr[0]), compare);

  printf("Sorted array:\n");
  for (int i = 0; i < n; i++) {
    printf("%d\n", arr[i]);
  }

  // free my boi
  free(arr);

  return 0;
}

void FizzBuzz(int n) {
  if (n % 3 == 0) {
    printf("Fizz");
  }
  if (n % 5 == 0) {
    printf("Buzz");
  }
}

int compare(const void *A, const void *B) {
  // cast to integers b/c compare has to be const void *A as params for some
  // reason
  int *a = A;
  int *b = B;

  // # > 0 if A < B (2nd bigger than 1st)
  // # < 0 if A > B (1st bigger than 2nd)
  // # = 0 if A = B
  return *b - *a;
}