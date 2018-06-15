#include "iostream"  
#include "stdio.h"  
#include "stdlib.h"  
using namespace std;
int parent[10];
int n, m;
int i, j;

struct edge {
	int u, v, w; //�ߵĶ��㣬Ȩֵ  
}edges[10];

//��ʼ�����鼯  
void UFset() {
	for (i = 1; i <= n; i++) 
		parent[i] = -1;
}

//����i�ĸ� 
int find(int i) {
	int temp;
	//����λ��  
	for (temp = i; parent[temp] >= 0; temp = parent[temp]);
	//ѹ��·��  
	while (temp != i) {
		int t = parent[i];
		parent[i] = temp;
		i = t;
	}
	return temp;
}
//�ϲ�����Ԫ��a,b  
void merge(int a, int b) {
	int r1 = find(a);
	int r2 = find(b);
	int tmp = parent[r1] + parent[r2]; //�������Ͻڵ����ĺ�  
	if (parent[r1] > parent[r2]) 
	{
		parent[r1] = r2;
		parent[r2] = tmp;
	}
	else 
	{
		parent[r2] = r1;
		parent[r1] = tmp;
	}
}

void kruskal() {
	int sumWeight = 0;
	int num = 0;
	int u, v;
	UFset();
	for (int i = 0; i<m; i++)
	{
		u = edges[i].u;
		v = edges[i].v;

		if (find(u) != find(v)) 
		{ //u��v����һ������  
			printf("����ߣ�%d %d,Ȩֵ�� %d\n", u, v, edges[i].w);
			sumWeight += edges[i].w;
			num++;
			merge(u, v); //���������߼���һ�����ϡ�  
		}
	}
	printf("weight of MST is %d \n", sumWeight);
}

//�ȽϺ������û�����  
int cmp(const void * a, const void * b) {
	edge * e1 = (edge *)a;
	edge * e2 = (edge *)b;
	return e1->w - e2->w;
}

int main() {
	printf("����ͼ�ĵ�ͱ���");
	scanf_s("%d %d", &n, &m);
	for (i = 0; i<m; i++) {
		printf("����ߵĽڵ��Ȩֵ");
		scanf_s("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
	}
	qsort(edges, m, sizeof(edge), cmp);
	kruskal();
	system("pause");
	return 0;
}