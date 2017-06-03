// Fibonacci.cpp
// 2nd Friday Fun Session – 13th Jan 2017
// https://gopalcdas.wordpress.com/2017/06/03/finding-fibonacci-exponential-vs-linear/

#include <iostream>
#include <time.h>

int FibonacciLinear(int n, int &opCounter)
{
  opCounter++;
	
  if(n == 0 || n == 1)
    return n;

  int result = 0;
  int previousPrevious = 0;
  int immediatePrevious = 1;	

  for(int i=2; i<=n; i++)
  {
    opCounter++;
		
    result = immediatePrevious + previousPrevious;

    previousPrevious = immediatePrevious;
    immediatePrevious = result;
  }
	
  return result;;
}

int FibonacciExponential(int n, int &opCounter)
{
  opCounter++;

  if(n == 0 || n == 1)
    return n;

  return FibonacciExponential(n-1, opCounter) + FibonacciExponential(n-2, opCounter);
}

int main( )  
{
  int opCounter = 0;
  int n = 40; // execution time, roughly 10 seconds
  int result;

  clock_t tStart = clock();
  result = FibonacciExponential(n, opCounter);
  printf("Answer: %d\nNumber of operations: %d\n", result, opCounter);
  printf("Time taken (Exponential): %.2fs\n\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

  tStart = clock();
  opCounter = 0;
  result = FibonacciLinear(n, opCounter);
  printf("Answer: %d\nNumber of operations: %d\n", result, opCounter);
  printf("Time taken (Linear): %.2fs\n\n\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}
