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
	//初始化数组  
	int a[100];
	int k;
	ofstream outfile("f1.dat", ios::out);
	if (!outfile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	cout << "请输入想要选择的第k小的元素:" << endl;
	cin >> k;
	outfile << k << "\n";
	//必须放在循环体外面  
	srand((unsigned)time(0));
	outfile << "随机生成的数组如下:" << "\n";
	for (int i = 0; i<100; i++)
	{
		if (i % 10 == 0)
			outfile << "\n";
		a[i] = Random(0, 500);
		outfile << "a[" << i << "]:" << a[i] << " ";
	}
	outfile << "\n";

	outfile << "第" << k << "小元素是" << Select(a, 0, 99, k) << "\n";

	//重新排序，对比结果  
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


//快速排序
template <class Type>
void quickSort(Type array[], int X, int Y) //X,Y分别是数组的起始下标
{
	int z, y, i, k;
	if (X<Y)
	{
		z = X;
		y = Y;
		k = array[z];  //关键值
		do {
			while ((z<y) && (array[y] >= k))
				y--;
			if (z<y)               //右边的元素小于k，移到k的左边。
			{
				array[z] = array[y];
				z++;
			}
			while ((z<y) && array[z] <= k)
				z++;
			if (z<y)  //左边的值小于k，移到看k的右边
			{
				array[y] = array[z];
			}

		} while (z != y);
		array[z] = k;//复制key值到array[z] 
		quickSort(array, X, z - 1);//对z的左侧进行排序
		quickSort(array, z + 1, Y);//对z的右侧进行排序
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
	//(r-p-4)/5相当于n-5  
	for (int i = 0; i <= (r - p - 4) / 5; i++)
	{
		//将元素每5个分成一组，分别排序，并将该组中位数与a[p+i]交换位置  
		//使所有中位数都排列在数组最左侧，以便进一步查找中位数的中位数  
		quickSort(a, p + 5 * i, p + 5 * i + 4);
		Swap(a[p + 5 * i + 2], a[p + i]);
	}
	//找中位数的中位数  
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