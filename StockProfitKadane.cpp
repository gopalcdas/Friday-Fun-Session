// StockProfitKadane.cpp
// 21st Friday Fun Session – 9th Jun 2017
// 

#include <stdio.h>
#include <limits>  

void StockDpN(double price[], int n, double &maxProfit)
{
  double minPriceSoFar = price[0];
  maxProfit = 0;

  for(int i=1; i<n; i++)
  {
    if(price[i] - minPriceSoFar > maxProfit)
		  maxProfit = price[i] - minPriceSoFar;

    if(price[i] < minPriceSoFar)
      minPriceSoFar = price[i];
  }
}

void StockKadaneDpN(double profit[], int n, double &maxProfit)
{
  double curProfit = 0;
  maxProfit = 0;

  for(int i=1; i<n; i++)
  {
    curProfit = curProfit > 0 ? curProfit + profit[i] : profit[i];
		
    if(curProfit > maxProfit)
      maxProfit =  curProfit;
  }
}

int main()
{
  double price[] = { 2, 10, 5, 12, 1, 3, 11, 9 };
  int n = sizeof(price)/sizeof(price[0]);

  double maxProfit = 0;
  StockDpN(price, n, maxProfit);
  if(maxProfit > 0)
    printf("Make $: %f\n\n", maxProfit);
  else
    printf("Don't buy stock!\n\n");

	// convert price to profit/loss array
  double *profit = new double[n];	
  profit[0] = 0;
  for(int i=1; i<n; i++)
    profit[i] = price[i] - price[i-1];

  maxProfit = 0;
  StockKadaneDpN(profit, n, maxProfit);
  if(maxProfit > 0)
    printf("Make $: %f\n\n", maxProfit);
  else
    printf("Don't buy stock!\n\n");
}
