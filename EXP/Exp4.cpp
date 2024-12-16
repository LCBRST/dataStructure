#include <iostream>
using namespace std;

#define MaxInt 32767                    					//表示极大值，即∞
#define MVNum 100                       					//最大顶点数
typedef char VerTexType;              			//假设顶点的数据类型为字符型
typedef int ArcType;                  	//假设边的权值类型为整型



//------------图的邻接矩阵-----------------
typedef struct
{
    VerTexType vexs[MVNum];            						//顶点表
    ArcType arcs[MVNum][MVNum];      						//邻接矩阵
    int vexnum,arcnum;                						//图的当前点数和边数
} Graph;


//------------图的遍历-----------------
bool visited[MVNum];           					//访问标志数组，其初值为"false"
int FirstAdjVex(Graph G, int v);				//返回v的第一个邻接点
int NextAdjVex(Graph G, int v, int w);		//返回v相对于w的下一个邻接点


int *D=new int[MVNum];	                 	//用于记录最短路的长度
bool *S=new bool[MVNum];          		//标记顶点是否进入S集合
int *Path=new int[MVNum];				//用于记录最短路顶点的前驱


//----队列的定义及操作--------
typedef struct
{
    ArcType *base;							//初始化的动态分配存储空间
    int front;								//头指针，若队列不空，指向队头元素
    int rear;					//尾指针，若队列不空，指向队尾元素的下一个位置
} sqQueue;

int LocateVex(Graph G, VerTexType v);

void CreateGraph(Graph &G) {
    cout << "请输入顶点数和边数：" << endl;
    cin >> G.vexnum >> G.arcnum;

    cout << "请输入顶点信息：" << endl;
    for (int i = 0; i < G.vexnum; i++) {
        cin >> G.vexs[i];  // 输入每个顶点的名称
    }

    // 初始化邻接矩阵
    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            if (i == j) {
                G.arcs[i][j] = 0;
            } else {
                G.arcs[i][j] = MaxInt;  // 初始化为无穷大
            }
        }
    }

    cout << "请输入边的信息（起点、终点、权值）：" << endl;
    for (int k = 0; k < G.arcnum; k++) {
        VerTexType start, end;  // 使用顶点名
        int weight;
        cin >> start >> end >> weight;

        // 查找起点和终点的索引
        int startIndex = LocateVex(G, start);
        int endIndex = LocateVex(G, end);

        // 如果起点和终点都存在，则更新邻接矩阵
        if (startIndex != -1 && endIndex != -1) {
            G.arcs[startIndex][endIndex] = weight;  // 假设是有向图，更新邻接矩阵
        } else {
            cout << "输入的顶点无效，请重新输入！" << endl;
        }
    }
}

void DFS(Graph G, int v) {
    visited[v] = true;
    cout << G.vexs[v] << " ";  // 访问该顶点
    for (int w = FirstAdjVex(G, v); w != -1; w = NextAdjVex(G, v, w)) {
        if (!visited[w]) {
            DFS(G, w);
        }
    }
}

void DFSTraverse(Graph G) {
    fill(visited, visited + G.vexnum, false);  // 初始化visited数组
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            DFS(G, i);  // 从每个未访问的节点开始递归
        }
    }
}

void BFSTraverse(Graph G) {
    fill(visited, visited + G.vexnum, false);  // 初始化visited数组
    sqQueue Q;
    Q.base = new ArcType[MVNum];
    Q.front = Q.rear = 0;

    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            visited[i] = true;
            cout << G.vexs[i] << " ";
            Q.base[Q.rear++] = i;  // 将起始顶点入队
            while (Q.front != Q.rear) {
                int v = Q.base[Q.front++];
                for (int w = FirstAdjVex(G, v); w != -1; w = NextAdjVex(G, v, w)) {
                    if (!visited[w]) {
                        visited[w] = true;
                        cout << G.vexs[w] << " ";
                        Q.base[Q.rear++] = w;  // 将邻接点入队
                    }
                }
            }
        }
    }
    delete[] Q.base;
}

void ShortestPath_DIJ(Graph G, int v0) {
    fill(D, D + G.vexnum, MaxInt);
    fill(S, S + G.vexnum, false);
    D[v0] = 0;
    Path[v0] = -1;

    for (int i = 0; i < G.vexnum; i++) {
        int minDist = MaxInt, u = -1;
        // 找到当前距离最小的顶点u
        for (int v = 0; v < G.vexnum; v++) {
            if (!S[v] && D[v] < minDist) {
                minDist = D[v];
                u = v;
            }
        }
        if (u == -1) break;  // 如果所有点都已访问完
        S[u] = true;

        // 更新与u相邻的顶点的最短路径
        for (int v = 0; v < G.vexnum; v++) {
            if (!S[v] && G.arcs[u][v] != MaxInt && D[u] + G.arcs[u][v] < D[v]) {
                D[v] = D[u] + G.arcs[u][v];
                Path[v] = u;
            }
        }
    }
}

void DisplayPath(Graph G, int v0, int v) {
    if (v != v0) {
        DisplayPath(G, v0, Path[v]);
        cout << " -> " << G.vexs[v];
    } else {
        cout << G.vexs[v];
    }
}

int FirstAdjVex(Graph G, int v) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.arcs[v][i] != MaxInt) {
            return i;
        }
    }
    return -1;
}

int NextAdjVex(Graph G, int v, int w) {
    for (int i = w + 1; i < G.vexnum; i++) {
        if (G.arcs[v][i] != MaxInt) {
            return i;
        }
    }
    return -1;
}

int LocateVex(Graph G, VerTexType v) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vexs[i] == v) {
            return i;  // 找到顶点v的位置，返回索引
        }
    }
    return -1;  // 如果未找到，返回-1
}


//主函数
int main()
{
    Graph G;
    int i, j,num_start, num_destination;
    VerTexType start, destination;
    cout << "************图的创建**************" << endl << endl;
    CreateGraph(G);
    cout << endl;
    cout << "图G创建完成！" << endl << endl;
    for(i = 0 ; i < G.vexnum ; ++i)
    {
        for(j = 0; j < G.vexnum; ++j)
        {
            if(j != G.vexnum - 1)
            {
                if(G.arcs[i][j] != MaxInt)
                    cout << G.arcs[i][j] << "\t";
                else
                    cout << "∞" << "\t";
            }
            else
            {
                if(G.arcs[i][j] != MaxInt)
                    cout << G.arcs[i][j] <<endl;
                else
                    cout << "∞" <<endl;
            }
        }
    }//for
    cout << endl<< "************图的遍历**************" << endl << endl;
    cout << endl<< "深度优先搜索遍历图结果：" << endl;
    DFSTraverse(G);
    cout << endl<< endl<< "广度优先搜索遍历图结果：" << endl;
    BFSTraverse(G);
    cout << endl<< endl<< "************迪杰斯特拉算法求最短路径**************" << endl << endl;
    cout << endl<< "请依次输入起始点、终点名称：";
    cin >> start >> destination;
    num_start = LocateVex(G, start);
    num_destination = LocateVex(G, destination);
    ShortestPath_DIJ(G, num_start);
    cout << endl <<"最短路径为：";
    DisplayPath(G, num_start, num_destination);
    cout << G.vexs[num_destination]<<endl;
    cout << endl <<"最短路径长度为：";
    cout << D[num_destination]<<endl;
    cout << endl <<"202308324229 梁健涛";
    return 0;
}//main
