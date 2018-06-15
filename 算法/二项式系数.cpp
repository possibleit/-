#include "stdio.h"
#include "stdlib.h"

#define MAXN 100

long binomial_coefficient(int n, int m)// 从n中选择m
{
	int i, j;
	long bc[MAXN][MAXN]; //二项式系数表
	for (i = 0; i <= n; i++) //帕斯卡三角每行第一个数全是1
	{
		bc[i][0] = 1;
	}
	for (j = 0; j <= n; j++) // 帕斯卡三角每行最后一个数全是1
	{
		bc[j][j] = 1;
	}

	for (i = 1; i <= n; i++) //状态转移方程
	{
		for (j = 1; j < i; j++)
		{
			bc[i][j] = bc[i - 1][j - 1] + bc[i - 1][j];
		}
	}
	return bc[n][m];
}
int main()
{
	int n, m;
	printf("输入二项式的n和k:\n");
	scanf_s("%d%d", &n, &m);
    int res = binomial_coefficient(n, m);
	printf("Result =  %d\n", res);
	system("pause");
	return 0;
}