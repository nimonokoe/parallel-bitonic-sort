#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>

extern int N;	/* Number of sorted integers */
extern int *InputArray;		/* Input List */
extern int *OutputArray;	/* Output List */

void readfile(char *);
void writefile(char *);

void sortprog(int *, int, int);
