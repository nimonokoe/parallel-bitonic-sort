
#include "sort0.h"

/* #define NUM_THREADS	2 */

int N, *InputArray, *OutputArray;

int main()
{
  int NUM_THREADS = 2;
  char s;
  char in_file[256] = "SortData100000_0.txt";
  char out_file[256] = "Sorted100000_0.txt";
  char comp_file[256] = "Result100000_0.txt";
  char log_file[256] = "log.txt";
  FILE *fp, *fp_log;
  if((fp_log = fopen(log_file, "w")) == NULL){
    printf("Log file open error!\n");
    return 0;
  }

  for(int experiment_times = 0; experiment_times<10; experiment_times++){
    for(NUM_THREADS = 1; NUM_THREADS<=30; NUM_THREADS++){
      int i, *iap, *oap, v;
      double start_time=0, end_time=0;
      printf("Odd-Even Sort Start\n");
      omp_set_num_threads(NUM_THREADS);
      printf("num of threads: %d\n", NUM_THREADS);
      printf("# of processors: %d\n", omp_get_num_procs());
      printf("max # of threads: %d\n", omp_get_max_threads());
    
      readfile(in_file);
      for(i=0, iap=InputArray, oap=OutputArray; i<N; i++, iap++, oap++) 
	*oap = *iap;
      start_time += omp_get_wtime();

      sortprog(OutputArray, 0, N-1); 

      end_time += omp_get_wtime();

      writefile(out_file);

      /* Verify */
      printf("Verify Start!\n");
      fp = fopen(comp_file, "r");
      fscanf(fp, "%d", &N);
      for (i = 0, oap = OutputArray; i < N; i++, oap++) {
	fscanf(fp, "%d", &v);
	if (*oap != v) {
	  printf("WRONG at %d-th line (value %d should be %d)\n", i, *oap, v);
	  break;
	}
      }
      fclose(fp);

      if (i == N) printf("Verify OK!\n");

      printf("processing time (sec) = %g\n", 
	     (float)(end_time-start_time));
      fprintf(fp_log, "%f, ", (float)(end_time-start_time));
    }
    fprintf(fp_log, "\n");
  }
  fclose(fp_log);
  scanf("%c", &s);
  return 0;
}
