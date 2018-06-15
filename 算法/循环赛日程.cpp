#include<iostream>  
#include<stdlib.h>
using namespace std;
void tournament(int n, int **b);
void copy(int n, int **b);
void print(int **b, int k);
int main()
{
	int k, n = 1;
	cout << "有2^k支队伍，输入k" << endl;
	cin >> k;
	for (int i = 1; i <= k; i++)
		n *= 2;
	int **b = new int *[n];
	for (int i = 0; i <= n; i++)
	{
		b[i] = new int[n];
	}
	for (int p = 0; p < n; p++)
		for (int q = 0; q < n; q++)
			b[p][q] = 0;
	tournament(n, b);
	print(b, n);
	system("pause");
	return 0;

}
void tournament(int n, int **b)
{
	if (n == 1)
	{
		b[0][0] = 1;
		return;
	}
	tournament(n / 2, b);
	copy(n, b);
	return;
}
void copy(int n, int **b)
{
	int m, i, j;
	m = n / 2;
	for (i = 0; i < m; i++)
		for (j = 0; j < m; j++)
		{
			b[i][j + m] = b[i][j] + m;
			b[i + m][j] = b[i][j] + m;
			b[i + m][j + m] = b[i][j];
		}
}
void print(int **b, int n)
{
	for (int p = 0; p < n; p++)
	{
		for (int q = 0; q < n; q++)
			cout << b[p][q] << " ";
		cout << endl;
	}
}