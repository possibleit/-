#include "stdio.h"
#include "stdlib.h"

#define MAXN 100

long binomial_coefficient(int n, int m)// ��n��ѡ��m
{
	int i, j;
	long bc[MAXN][MAXN]; //����ʽϵ����
	for (i = 0; i <= n; i++) //��˹������ÿ�е�һ����ȫ��1
	{
		bc[i][0] = 1;
	}
	for (j = 0; j <= n; j++) // ��˹������ÿ�����һ����ȫ��1
	{
		bc[j][j] = 1;
	}

	for (i = 1; i <= n; i++) //״̬ת�Ʒ���
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
	printf("�������ʽ��n��k:\n");
	scanf_s("%d%d", &n, &m);
    int res = binomial_coefficient(n, m);
	printf("Result =  %d\n", res);
	system("pause");
	return 0;
}