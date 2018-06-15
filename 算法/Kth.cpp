#include <ctime>  
#include <iostream>   
#include<fstream>
using namespace std;

template <class Type>
void Swap(Type &x, Type &y);

inline int Random(int x, int y);

template <class Type>
void quickSort(Type array[], int X, int Y);

template <class Type>
int Partition(Type a[], int p, int r, Type x);

template <class Type>
Type Select(Type a[], int p, int r, int k);

int main()
{
	//��ʼ������  
	int a[100];
	int k;
	ofstream outfile("f1.dat", ios::out);
	if (!outfile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	cout << "��������Ҫѡ��ĵ�kС��Ԫ��:" << endl;
	cin >> k;
	outfile << k << "\n";
	//�������ѭ��������  
	srand((unsigned)time(0));
	outfile << "������ɵ���������:" << "\n";
	for (int i = 0; i<100; i++)
	{
		if (i % 10 == 0)
			outfile << "\n";
		a[i] = Random(0, 500);
		outfile << "a[" << i << "]:" << a[i] << " ";
	}
	outfile << "\n";

	outfile << "��" << k << "СԪ����" << Select(a, 0, 99, k) << "\n";

	//�������򣬶ԱȽ��  
	quickSort(a, 0, 99);

	for (int i = 0; i<100; i++)
	{
		if (i % 10 == 0)
			outfile << "\n";
		outfile << "a[" << i << "]:" << a[i] << " ";
	}
	outfile << "\n";
}

template <class Type>
void Swap(Type &x, Type &y)
{
	Type temp = x;
	x = y;
	y = temp;
}

inline int Random(int x, int y)
{
	int ran_num = rand() % (y - x) + x;
	return ran_num;
}


//��������
template <class Type>
void quickSort(Type array[], int X, int Y) //X,Y�ֱ����������ʼ�±�
{
	int z, y, i, k;
	if (X<Y)
	{
		z = X;
		y = Y;
		k = array[z];  //�ؼ�ֵ
		do {
			while ((z<y) && (array[y] >= k))
				y--;
			if (z<y)               //�ұߵ�Ԫ��С��k���Ƶ�k����ߡ�
			{
				array[z] = array[y];
				z++;
			}
			while ((z<y) && array[z] <= k)
				z++;
			if (z<y)  //��ߵ�ֵС��k���Ƶ���k���ұ�
			{
				array[y] = array[z];
			}

		} while (z != y);
		array[z] = k;//����keyֵ��array[z] 
		quickSort(array, X, z - 1);//��z������������
		quickSort(array, z + 1, Y);//��z���Ҳ��������
	}
}

template <class Type>
int Partition(Type a[], int p, int r, Type x)
{
	int i = p - 1, j = r + 1;

	while (true)
	{
		while (a[++i]<x && i<r);
		while (a[--j]>x);
		if (i >= j)
		{
			break;
		}
		Swap(a[i], a[j]);
	}
	return j;
}


template <class Type>
Type Select(Type a[], int p, int r, int k)
{
	if (r - p<75)
	{
		quickSort(a, p, r);

		return a[p + k - 1];
	}
	//(r-p-4)/5�൱��n-5  
	for (int i = 0; i <= (r - p - 4) / 5; i++)
	{
		//��Ԫ��ÿ5���ֳ�һ�飬�ֱ����򣬲���������λ����a[p+i]����λ��  
		//ʹ������λ������������������࣬�Ա��һ��������λ������λ��  
		quickSort(a, p + 5 * i, p + 5 * i + 4);
		Swap(a[p + 5 * i + 2], a[p + i]);
	}
	//����λ������λ��  
	Type x = Select(a, p, p + (r - p - 4) / 5, (r - p - 4) / 10);
	int i = Partition(a, p, r, x);
	int j = i - p + 1;
	if (k <= j)
	{
		return Select(a, p, i, k);
	}
	else
	{
		return Select(a, i + 1, r, k - j);
	}
}