// Fibonacci.cpp : Defines the entry point for the console application.
//

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

  for(int i=1; i<=n; i++)
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
    return 1;

  return FibonacciExponential(n-1, opCounter) + FibonacciExponential(n-2, opCounter);
}

int main( )  
{
  int opCounter = 0;
  int n = 10;
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
