
#include "sort0.h"
#include <math.h>
#include <stdbool.h>
#define greater(i,j)	((i) > (j))
#define less(i, j)      ((i) < (j))
#define exch(i,j)	{int k; k=(i); (i)=(j); (j)=(k);}
#define min(i, j)       ((i) < (j))?(i):(j)
#define max(i, j)       ((i) < (j))?(j):(i)
/* #define DEBUG */

void odd_even_sort(int *A, int l, int r){
  int diff=0;
  int is_sorted = 0;
#ifdef DEBUG
  printf("[odd-even before] ");
  for(int i=l; i<=r; i++)printf("%d ", A[i]);
  printf("\n");
#endif
  
  while(is_sorted!=3){
    is_sorted |= (1<<diff);
    if(l < r){
#pragma omp parallel for
      for(int i=l+diff; i<r; i+=2){    
	if(greater(A[i], A[i+1])){
	  exch(A[i], A[i+1]);
	  is_sorted &= ~(1<<diff);
	}
      }
    }else{
#pragma omp parallel for
      for(int i=r+diff; i<l; i+=2){    
	if(less(A[i], A[i+1])){
	  exch(A[i], A[i+1]);
	  is_sorted &= ~(1<<diff);
	}
      }    
    }
    diff = (diff+1)%2;
  }
#ifdef DEBUG
  printf("[odd-even after] ");
  for(int i=l; i<=r; i++)printf("%d ", A[i]);
  printf("\n");
#endif

}

int make_bitonic(int *A, int l, int r){
  odd_even_sort(A, l, (l+r)/2);
  odd_even_sort(A, r, (l+r)/2+1);
#ifdef DEBUG
  printf("[bitonic] ");
  for(int i=l; i<=r; i++)printf("%d ", A[i]);
  printf("\n");
#endif
  return (l+r)/2+1;
}

void comparator(int *A, int l, int mid, int r){
  if(l >= r) return;
  if((r-l)%2 == 0){
    odd_even_sort(A, l, r);
    return;
  }else{
#ifdef DEBUG
    printf("[comparator] %d %d %d\n", l, mid, r);
    printf ("[comparator before]");
    for(int i=l; i<=r; i++) printf("%d ", A[i]);
    printf("\n");
#endif
    int diff = mid-l;
    if(mid-l > r-mid+1){
      diff-=1;
    }

#pragma omp parallel for  
    for(int i = l; i < mid; i++){
      if(greater(A[i], A[i+diff])) exch(A[i], A[i+diff]);
    }
  }

#ifdef DEBUG
  printf ("[comparator after]");
  for(int i=l; i<=r; i++) printf("%d ", A[i]);
  printf("\n");

  printf("\n");
#endif
  comparator(A, l, (l+mid-1)/2+1, mid-1);
  comparator(A, mid, (mid+r)/2+1, r);  
}



void sortprog(int *A, int l, int r) {
  int piv;
  piv = make_bitonic(A, l, r);
  comparator(A, l, piv, r);
#ifdef DEBUG
  for(int i=l; i<=r; i++)  printf("%d ", A[i]);
  printf("\n");
#endif
}

