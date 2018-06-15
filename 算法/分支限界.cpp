#include "iostream"
#include "queue"
using namespace std;
typedef struct treenode {
	int weight;
	int value;
	int level;
	int flag;
}treenode;
queue<struct treenode> que;
int enQueue(int w, int v, int level, int flag, int n, int* bestvalue)
{
	treenode node;
	node.weight = w;
	node.value = v;
	node.level = level;
	node.flag = flag;
	if (level == n)
	{
		if (node.value > *bestvalue)
		{
			*bestvalue = node.value;
		}
		return 0;
	}
	else
	{
		que.push(node);
	}
}
//wΪ�������飬vΪ��ֵ���飬nΪ��Ʒ������cΪ����������bestValueΪȫ������ֵ
int bbfifoknap(int w[], int v[], int n, int c, int* bestValue)
{
	//��ʼ�����
	int i = 1;
	treenode tag, livenode;
	livenode.weight = 0;
	livenode.value = 0;
	livenode.level = 1;
	livenode.flag = 0;//��ʼΪ0
	tag.weight = -1;
	tag.value = 0;
	tag.level = 0;
	tag.flag = 0;//��ʼΪ0
	que.push(tag);
	while (1)
	{
		if (livenode.weight + w[i - 1] <= c)
		{
			enQueue(livenode.weight + w[i - 1], livenode.value + v[i - 1], i, 1, n, bestValue);
		}
		enQueue(livenode.weight, livenode.value, i, 0, n, bestValue);
		livenode = que.front();
		que.pop();
		if (livenode.weight == -1)
		{
			if (que.empty() == 1)
			{
				break;
			}
			livenode = que.front();
			que.pop();
			que.push(tag);
			i++;
		}

	}
	return 0;
}
int main()
{
	int w[] = { 4, 7, 5,3 };
	int v[] = { 40,42,25,12 };
	int n = 4;
	int c = 10;
	int bestValue = 0;
	bbfifoknap(w, v, n, c, &bestValue);
	cout << "���Ž�:"<<bestValue << endl;
	system("pause");
	return 0;
}