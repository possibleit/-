#include "iostream"
#include "stdio.h"
#include<windows.h>  
using namespace std;
const int inf = 65535;
typedef struct arcnode {///存边  
	int adjvex;
	int weight;
	arcnode *nextarc;///指向下一条边的指针  
}arcnode;

typedef struct vnode {///存点  
	int data;
	arcnode *firstarc;
}vnode, Adjvex[20];

typedef struct {///存图  
	int vexnum, arcnum;///节点数 和 边数  
	Adjvex vertices;///存放图中节点信息的数组  
}ALGraph;

typedef struct Minimum {///存各节点的最小权值信息  
	int data;        
	int lowcost;
	int flag;
}Minimum, closedge[20];

int LocateVex(ALGraph G, int u) {
	for (int i = 0; i<G.vexnum; i++) {
		if (G.vertices[i].data == u)
			return i;
	}
	return 0;
}
void CreateGraph(ALGraph &G) {
	int v1, v2;
	int w;
	arcnode *p, *q;
	cout << "输入节点数目" << endl;
	cin >> G.vexnum;
	cout << "输入边数目" << endl;
	cin >> G.arcnum;
	for (int i = 0; i<G.vexnum; i++) {
		cout << "输入节点值" << endl;
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
	for (int i = 0; i<G.arcnum; i++) {
		p = new arcnode;
		q = new arcnode;
		if (p == NULL || q == NULL) {
			return;
		}
		int k, j;
		cout << "输入边的节点和权值" << endl;
		cin >> v1 >> v2 >> w;
		k = LocateVex(G, v1);
		j = LocateVex(G, v2);
		p->nextarc = G.vertices[k].firstarc;
		q->nextarc = G.vertices[j].firstarc;
		G.vertices[k].firstarc = p;
		p->weight = w;  
		p->adjvex = j;
		G.vertices[j].firstarc = q;
		q->weight = w;
		q->adjvex = k;
	}
}

int minimum(ALGraph G, closedge MinEdge) {
	int first;
	int k;
	int i;
	int min;
	for (i = 0; i<G.vexnum; i++) {
		if (MinEdge[i].lowcost != 0) {
			min = MinEdge[i].lowcost;
			first = i;
			break;
		}
	}
	k = i;
	for (i = first; i<G.vexnum; i++) {
		if (min>MinEdge[i].lowcost && MinEdge[i].lowcost != 0) {
			min = MinEdge[i].lowcost;
			k = i;
		}
	}
	return k;
}
int MinSpanTree(ALGraph G, int u) {
	int ans = 0;
	arcnode *p;
	closedge MinEdge;
	int k = LocateVex(G, u);
	for (int i = 0; i<G.vexnum; i++)
		MinEdge[i].flag = 0;
	for (int i = 0; i<G.vexnum; i++) {
		if (i != k) {
			MinEdge[i].data = u;
			for (p = G.vertices[i].firstarc; p != NULL; p = p->nextarc) {
				if (p->adjvex == k) {
					MinEdge[i].lowcost = p->weight;
					MinEdge[i].flag = 1;
				}
				else if (MinEdge[i].flag == 0) {
					MinEdge[i].lowcost = inf;
				}
			}
		}
		MinEdge[k].data = G.vertices[k].data;
		MinEdge[k].lowcost = 0;///添加完了  
	}
	for (int i = 1; i<G.vexnum; i++) {
		k = minimum(G, MinEdge);
		cout << G.vertices[k].data << "  " << MinEdge[k].data << "  " << MinEdge[k].lowcost << endl;
		ans += MinEdge[k].lowcost;
		MinEdge[k].lowcost = 0;   //将结点加入U中  
		for (p = G.vertices[k].firstarc; p != NULL; p = p->nextarc) {
			if (MinEdge[p->adjvex].lowcost>p->weight) {
				MinEdge[p->adjvex].lowcost = p->weight;
				MinEdge[p->adjvex].data = G.vertices[k].data;
			}
		}
	}
	return ans;
}

int main() {
	ALGraph G;
	CreateGraph(G);
	int ans = MinSpanTree(G, G.vertices[0].data);
	cout << ans << endl;
	system("pause");
	return 0;
}