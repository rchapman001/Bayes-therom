/*
Copyright (c) 2016-2020 Jeremy Iverson
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/* assert */
#include <assert.h>

/* fabs */
#include <math.h>

/* printf, fopen, fclose, fscanf, scanf */
#include <stdio.h>

/* EXIT_SUCCESS, malloc, calloc, free, qsort */
#include <stdlib.h>

struct distance_metric {
  size_t viewer_id;
  double distance;
};

int
main(int argc, char * argv[])
{
  size_t n, m;

  /* Validate command line arguments. */
  assert(2 == argc);

  /* ... */
  char const * const fn = argv[1];

  /* Validate input. */
  assert(fn);

  /* Open file. */
  FILE * const fp = fopen(fn, "r");
  assert(fp);

  /* Read file. */
  fscanf(fp, "%zu %zu", &n, &m);

  /* Allocate memory. */
  double * const rating = malloc(n * m * sizeof(*rating));

  /* Check for success. */
  assert(rating);

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      fscanf(fp, "%lf", &rating[i * m + j]);
    }
  }

  /* Close file. */
  int const ret = fclose(fp);
  assert(!ret);

  /* Allocate more memory. */
  double * const urating = malloc(m * sizeof(*urating));

  /* Check for success. */
  assert(urating);

  /* Get user input. */
  for (size_t j = 0; j < m - 1; j++) {
    printf("Enter your rating for movie %zu: ", j + 1);
    scanf("%lf", &urating[j]);
  }

  /* Allocate more memory. */
  double prob[10] = { 0.0 };
  double orgRatings[10] = { 0.0 };
  /* Compute probabilities */
  for (int k = 0; k < 10; k++) {
    for (size_t i = 0; i < n; i++) {
      prob[k] += (rating[i * m + 4] == (k + 1) / 2.0);
      orgRatings[k] += (rating[i * m + 4] == (k + 1) / 2.0);
    }
  }

  /* Finalize computation of probabilities. */
  for (int k = 0; k < 10; k++) {
    prob[k] /= n;
  }

  double data[40] = {0.0};
  double problty10[10] = {0.0};
  double rate = 0.5;
  
  for (int r = 0; r <= 10; r += 1)
  {
    for (int f = 0; f < n -1; f++)  
    {
	for (int c = 0; c<m-1; c++)
	{
          if(r < (m - 1)){
	    if(urating[c] == rating[f * m + c] && (rate == rating[f * m + m]))
		data[(c*10) + r] += 1;
          }
	}
    }
   rate += 0.5;
  } 

  for (int t = 0; t < 10; t ++)
  {
     if (prob[t] == 0)
     {
	problty10[t] = 0.0;
     }
     else 
     {
        problty10[t] = orgRatings[t] * (data[t] / orgRatings[t]) * (data[t + 10] / orgRatings[t]) * (data[t + 20] / orgRatings[t]) * (data[t + 30] / orgRatings[t]);
     }

  }

   int maximum = 0;
   int maximumIndex = 0;
   for (int v = 0; v < 10; v++)
   {
	if(problty10[v] >= maximum)
	{
	  maximum = problty10[v];
	  maximumIndex = v;
	}
   }

printf("my prediction bassed on Bayes therom is: %.1lf" , (maximumIndex + 1) / 2.0);
 
  /*
  for (int k = 0; k < 10; k++) {
    printf("prob[%d] = %lf\n", k, prob[k]);
  }
  */

  /* Output prediction. */
  //printf("The predicted rating for movie five is %.1lf.\n", ???);

  /* Deallocate memory. */
  free(rating);
  free(urating);

  return EXIT_SUCCESS;
}
