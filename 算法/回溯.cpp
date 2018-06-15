#include "stdio.h"
#include "stdlib.h"
int bestValue = 0, curWeight = 0, curValue = 0;
int backtrack_knapsack(int w[], int v[], int c, int n, int i)
{
	if (i > n)
	{
		if (curValue > bestValue)
		{
			bestValue = curValue;
		}
		return 0;
	}
	if (curWeight + w[i - 1] <= c)//ËÑË÷×ó×ÓÊ÷
	{
		curWeight += w[i - 1];
		curValue += v[i - 1];
		backtrack_knapsack(w, v, c, n, i + 1);
		curWeight -= w[i - 1];
		curValue -= v[i - 1];
	}
	backtrack_knapsack(w, v, c, n, i + 1);//ËÑË÷ÓÒ×ÓÊ÷
	return 0;
}
int main()
{
	int weight[4] = { 4,7,5,3 };
	int value[4] = { 40,42,25,12 };
	int c = 10;
	backtrack_knapsack(weight, value, c, 4, 1);
	printf("×îÓÅ½â:");
	printf("%d\n", bestValue);
	system("pause");
	return 1;
}