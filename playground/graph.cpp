//class graph( graph is stored in adjacency matrix)
//It includes graph array I/O
//BFS and DFS
//Dijkstra         2015.1.3
//BellmanFord      2015.1.9
//Floyd-Warshall   2015.1.11
//Prim             2015.1.14
//Kruskal          2015.1.17
//Topological sort 2015.3.9

#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <algorithm>

using namespace std;

const int NODESIZE = 100;
const int AWAY = 9999;
typedef int vertex;

struct unDirectedEdge
{
	int start;
	int end;
	int value;
};

class Graph
{
public:
	Graph();

	void input(int inputSource); //输入描述图的邻接矩阵
	void output(); //输出图

	void BreastFirstSearch(vertex start);
	void DepthFirstSearch(vertex start);

	//单源最短路径
	void Dijkstra(vertex start);
	void BellmanFord(vertex start);

	//多源最短路径
	void FloydWarshall();

	//最小生成树(针对无向图，有向图的最小生成树称为最小树形图)
	void Prim(vertex start);//思想和Dijkstra一样都是贪心思想。Dijkstra比Prim多了个步骤就是要更新源点到其他点的距离，而Prim只需要更新剩余点到MST中点的距离即可。
	void Kruskal(vertex start);

	//拓扑排序
	void topologicalSort();
private:
	//深搜、广搜助手函数
	bool stillUnvisited(bool isVisited[]);//判断图中节点是否访问过

	//Dijkstra助手函数
	int minIndex(int *distance, int size, bool *isFound);//返回未找到最小距离的图集中的最小距离

	//Kruskal助手函数
	vertex nodeRoot(vertex v); //返回节点v的祖先节点
	vertex *fatherNode;//助手变量

	//拓扑排序助手变量
	int *inDegree;//记录每个节点的入度数据
	vertex *InDegreeZeroVertexSet;//入度为0的节点集合
	int InDegreeZeroVertexCnt;//入度为0节点的数量
	void topoSortInitiation();//对上面进行拓扑排序时需要用到的变量进行初始化
	void findInDegreeZeroVertex();//寻找所有入度为0的节点
	vertex *topoSortSequence;//拓扑序列

	int nodes;
	int edges;
	unDirectedEdge *edgeSet; //储存无向边的信息
	vertex adjacency[NODESIZE][NODESIZE];
};

Graph::Graph()
{
	nodes = 0;
}

void Graph::topoSortInitiation()
{
	//初始化记录入度数据集合,设为0
	inDegree = new int[nodes];
	for (int i = 0; i < nodes; i++)
		inDegree[i] = 0;

	//初始化入度为0的节点集合
	InDegreeZeroVertexSet = new vertex[nodes];
	InDegreeZeroVertexCnt = 0;
}

void Graph::findInDegreeZeroVertex()
{
	for (int i = 0; i < nodes; i++)
	{
		if (inDegree[i] == 0)
		{
			InDegreeZeroVertexSet[InDegreeZeroVertexCnt] = i;
			InDegreeZeroVertexCnt++;
		}
	}
}

//inputSource表明输入的方式是从控制台输入（1）还是文本输入（2）
void Graph::input(int inputSource)
{
	if (inputSource == 1)
	{
		//获取节点数
		cout << "How many nodes: ";
		cin >> nodes;

		//初始化邻接矩阵
		for (int i = 0; i < nodes; i++)
		{
			for (int j = 0; j < nodes; j++)
			{
				if (i == j)
					adjacency[i][j] = 0;
				else
					adjacency[i][j] = AWAY;
			}
		}

		/************拓扑排序时会用到***********/
		topoSortInitiation();
		/************拓扑排序时会用到***********/

		//是否为有向图
		bool isDirected;
		cout << "Is the graph directed?";
		cin >> isDirected;

		//获取边数
		cout << "How many edges: ";
		cin >> edges;

		//如果是无向图初始化edgeSet
		if (!isDirected)
		{
			edgeSet = new unDirectedEdge[edges];
			fatherNode = new vertex[nodes];

			for (int i = 0; i < nodes; i++)
				fatherNode[i] = i;
		}

		//获取边的具体信息
		cout << "Input edge like 1 2 5:\n";
		vertex start, end, value;
		for (int i = 0; i < edges; i++)
		{
			cin >> start >> end >> value;
			adjacency[start][end] = value;

			if (!isDirected)
			{
				adjacency[end][start] = value;
				edgeSet[i].start = start;
				edgeSet[i].end = end;
				edgeSet[i].value = value;
			}

			/************拓扑排序时会用到***********/
			//尾节点入度不为0
			inDegree[end]++;
			/************拓扑排序时会用到***********/
		}

		/************拓扑排序时会用到***********/
		findInDegreeZeroVertex();
		/************拓扑排序时会用到***********/
	}
	else if (inputSource == 2)//从文本读入
	{
		ifstream infile;
		infile.open("graphInput.txt");

		if (!infile)
		{
			cout << "graphInput.txt can't open\n";
			return;
		}

		//从文件读取图的信息l
		//读取节点数
		infile >> nodes;

		//初始化邻接矩阵
		for (int i = 0; i < nodes; i++)
		{
			for (int j = 0; j < nodes; j++)
			{
				if (i == j)
					adjacency[i][j] = 0;
				else
					adjacency[i][j] = AWAY;
			}
		}

		/************拓扑排序时会用到***********/
		topoSortInitiation();
		/************拓扑排序时会用到***********/

		//读取边数
		infile >> edges;

		//读取图是否为有向图
		bool isDirected;
		infile >> isDirected;

		cout << nodes << " nodes and " << edges << " edges\n";

		if (!isDirected)
		{
			cout << "It's an undirected graph.\n";
			//对助手变量进行初始化
			edgeSet = new unDirectedEdge[edges];
			fatherNode = new vertex[nodes];

			for (int i = 0; i < nodes; i++)
				fatherNode[i] = i;
		}
		else
			cout << "It's a directed graph.\n";

		//读取边的具体信息
		int start, end, value;
		int edgeIndex = 0;
		while (!infile.eof())
		{
			infile >> start >> end >> value;

			cout << start << " " << end << " " << value << endl;

			adjacency[start][end] = value;
			if (!isDirected)
			{
				adjacency[end][start] = value;
				edgeSet[edgeIndex].start = start;
				edgeSet[edgeIndex].end = end;
				edgeSet[edgeIndex].value = value;
				edgeIndex++;
			}

			/************拓扑排序时会用到***********/
			//尾节点入度不为0
			inDegree[end]++;
			/************拓扑排序时会用到***********/
		}

		/************拓扑排序时会用到***********/
		findInDegreeZeroVertex();
		/************拓扑排序时会用到***********/

		infile.close();

		cout << "Graph input is finished.\n";
	}
}

void Graph::output()
{
	cout << "Graph is like:\n";

	cout << "   ";
	for (int i = 0; i < nodes; i++)
		cout << i << " ";

	cout << endl;

	for (int i = 0; i < nodes; i++)
	{
		cout << i << ": ";
		for (int j = 0; j < nodes; j++)
		{
			cout << adjacency[i][j] << " ";
		}

		cout << endl;
	}
}

bool Graph::stillUnvisited(bool isVisited[])
{
	for (int i = 0; i < nodes; i++)
	{
		if (!isVisited[i])
			return true;

		if (i == nodes - 1)
			return false;
	}
}

void Graph::BreastFirstSearch(vertex start)
{
	if (start >= nodes || start < 0)
		cout << "Start node is out of range.\n";
	else
	{
		bool *isVisited = new bool[nodes];
		for (int i = 0; i < nodes; i++)
			isVisited[i] = false;

		queue<vertex> q;
		q.push(start);
		isVisited[start] = true;

		while (stillUnvisited(isVisited))
		{
			vertex v;
			if (!q.empty())
				v = q.front();
			else
			{
				for (int i = 0; i < nodes; i++)
				{
					if (!isVisited[i])
					{
						v = i;
						q.push(v);
						break;
					}
				}
			}

			q.pop();

			cout << v << " ";

			isVisited[v] = true;

			//将与v相连的点都排到队列后
			for (int i = 0; i < nodes; i++)
			{
				//相连的点
				if (i != v && adjacency[v][i] != AWAY && !isVisited[i])
					q.push(i);
			}
		}

		cout << endl;
	}
}

void Graph::DepthFirstSearch(vertex start)
{
	if (start >= nodes || start < 0)
		cout << "Start node is out of range.\n";
	else
	{
		bool *isVisited = new bool[nodes];//记录节点是否访问过，1表示访问过，0表示未访问过

		//设置访问数组初值为0，表示全未访问过
		for (int i = 0; i < nodes; i++)
			isVisited[i] = false;

		stack<vertex> s;
		s.push(start);
		isVisited[start] = true;

		while (stillUnvisited(isVisited))
		{
			vertex v;
			if (!s.empty())
				v = s.top();
			else
			{
				for (int i = 0; i < nodes; i++)
				{
					if (!isVisited[i])
					{
						v = i;
						s.push(v);
						break;
					}
				}
			}

			cout << v << " ";

			s.pop();

			isVisited[v] = true;

			//将与v相连的点都存入栈中
			for (int i = 0; i < nodes; i++)
			{
				//相连的点
				if (i != v && adjacency[v][i] != AWAY && !isVisited[i])
					s.push(i);
			}
		}

		cout << endl;
	}
}

int Graph::minIndex(int *distance, int size, bool *isFound)
{
	int min = AWAY;
	int index = -1;

	for (int i = 0; i < size; i++)
	{
		if (!isFound[i] && distance[i] < min)
		{
			min = distance[i];
			index = i;
		}
	}

	return index;
}

void Graph::Dijkstra(vertex start)
{
	bool *isFound = new bool[nodes]; //表示图中的节点是否被添加到集合中
	for (int i = 0; i < nodes; i++)
		isFound[i] = false;

	int *distance = new int[nodes]; //表示源点start到图中其他节点的最短距离
	for (int i = 0; i < nodes; i++)
		distance[i] = adjacency[start][i];

	isFound[start] = true;
	int min = AWAY;
	for (int i = 0; i < nodes; i++)
	{
		//Step 1: 在未找到最短路径的集合中寻找最短路径的点的索引
		int min_index = -1;
		min_index = minIndex(distance, nodes, isFound);
		isFound[min_index] = true;

		//Step 2:更新distance数组
		int minDistance = distance[min_index];
		for (int j = 0; j < nodes; j++)
		{
			if (!isFound[j])
			{
				if (minDistance + adjacency[min_index][j] < distance[j])
					distance[j] = minDistance + adjacency[min_index][j];
			}
		}
	}

	//输出从start到图中其他点的最短距离
	cout << "Single Source Shortest Path(Dijkstra)\n";
	for (int i = 0; i < nodes; i++)
	{
		if (i != start)
			cout << start << " -> " << i << " " << distance[i] << endl;
	}
}

void Graph::BellmanFord(vertex start)
{
	//表明源点到其他各个顶点的最短距离，其中distance[i]表示源点start到点i的最短距离（在当前迭代能够经过的边）
	int *distance = new int[nodes];

	//初始化distance数组
	for (int i = 0; i < nodes; i++)
		distance[i] = adjacency[start][i];

	//进行迭代对每个点经过所有边后的最短距离
	for (int v = 0; v < nodes - 1; v++)//在第v次迭代(经过v个节点)时，distance(v) = min(distance(v-1), start到其他各个节点的距离+各个节点到目标的距离)
	{
		//复杂度为节点数*边，因为图的储存是通过邻接矩阵储存的，所以看上去是n^3
		for (int source = 0; source < nodes; source++)
		{
			for (int end = 0; end < nodes; end++)
			{
				if (source != end && adjacency[source][end] != AWAY)
				{
					//进行松弛计算(relaxation)
					int min = distance[source] + adjacency[source][end];
					if (distance[end] > min)
						distance[end] = min;
				}
			}
		}
	}

	//判断是否存在负权环，如果仍然能找到使距离变小的边，那么无法求出最短路径
	bool NoShortestPath = false;
	for (int source = 0; source < nodes; source++)
	{
		for (int end = 0; end < nodes; end++)
		{
			if (source != end && adjacency[source][end] != AWAY)
			{
				int min = distance[source] + adjacency[source][end];
				if (distance[end] > min)
				{
					NoShortestPath = true;
					break;
				}
			}
		}
	}

	//输出最短距离
	if (!NoShortestPath)
	{
		for (int i = 0; i < nodes; i++)
			cout << start << "->" << i << " : " << distance[i] << endl;
	}
	else
		cout << "There is a minus loop. Shortest path can't be found.\n";
}

void Graph::FloydWarshall()
{
	//声明distance二维数组，用来储存图中各点到其他点的最短距离
	int **distance = new int*[nodes];
	for (int i = 0; i < nodes; i++)
		distance[i] = new int[nodes];

	//初始化二维数组
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
			distance[i][j] = adjacency[i][j];
	}

	//FloydWarshall
	//先控制middle不变，因为在进行松弛计算时会用到更新后的距离，如果放在最里面会漏掉更新后的距离
	for (int middle = 0; middle < nodes; middle++)
	{
		for (int source = 0; source < nodes; source++)
		{
			for (int end = 0; end < nodes; end++)
			{
				if (distance[source][end] > distance[source][middle] + distance[middle][end])
					distance[source][end] = distance[source][middle] + distance[middle][end];
			}
		}
	}

	//如果要得到各个节点的最短路径，那么可以额外声明一个二维数组来记录i到j经过的点，再对二维数组进行路径遍历

	//输出最短距离矩阵
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
			cout << distance[i][j] << " ";

		cout << endl;
	}
}

void Graph::Prim(vertex start)
{
	//二维数组mst记录最小生成树的点和边权值
	int **mst = new int*[nodes];
	for (int i = 0; i < nodes; i++)
		mst[i] = new int[nodes];

	//初始化二维数组mst
	for (int i = 0; i < nodes; i++)
		for (int j = 0; j < nodes; j++)
			mst[i][j] = AWAY;

	//数组distance记录未被选中的点到最小生成树的最短距离
	int *distance = new int[nodes];

	//数组isAddedToMST表示节点是否已经被加入进最小生成树集中
	bool *isAddedToMST = new bool[nodes];

	//数组neighbour记录distance数组到最小生成树的边的另一端
	vertex *neighbour = new vertex[nodes];

	//以源点start的距离初始化数组distance、数组isAddedToMST、数组neighbour
	for (int i = 0; i < nodes; i++)
	{
		distance[i] = adjacency[start][i];
		isAddedToMST[i] = false;
		neighbour[i] = start;
	}

	isAddedToMST[start] = true;

	//Prim算法
	for (int i = 0; i < nodes - 1; i++)
	{
		int min = AWAY;
		vertex vertexToADD;
		//找出distance数组中到最小生成树的最小距离
		for (int distanceIndex = 0; distanceIndex < nodes; distanceIndex++)
		{
			if (!isAddedToMST[distanceIndex] && distance[distanceIndex] < min)
			{
				min = distance[distanceIndex];
				vertexToADD = distanceIndex;
			}
		}

		//将找到最小距离的点加入二维数组mst并更新数组isAddedToMST
		mst[neighbour[vertexToADD]][vertexToADD] = min;
		isAddedToMST[vertexToADD] = true;

		//更新数组neighbour
		for (int j = 0; j < nodes; j++)
		{
			if (!isAddedToMST[j] && distance[j] > adjacency[j][vertexToADD])
			{
				distance[j] = adjacency[j][vertexToADD];
				neighbour[j] = vertexToADD;
			}
		}
	}

	//输出以源点start开始的最小生成树
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
		{
			if (mst[i][j] != AWAY)
				cout << i << "->" << j << " " << mst[i][j] << endl;
		}
	}
}

bool edgeCmp(unDirectedEdge edge1, unDirectedEdge edge2)//排序函数的助手函数，返回边权值较小的边
{
	return edge1.value < edge2.value;
}

vertex Graph::nodeRoot(vertex v)
{
	vertex father = fatherNode[v];

	while (father != fatherNode[father])
		father = fatherNode[father];

	return father;
}

void Graph::Kruskal(vertex start)
{
	//mst储存最小生成树的结果，大小为节点数-1
	unDirectedEdge *mst = new unDirectedEdge[nodes - 1];

	//对边集进行排序
	sort(edgeSet, edgeSet + edges, edgeCmp);

	//对mst进行初始化
	mst[0].start = edgeSet[0].start;
	mst[0].end = edgeSet[0].end;
	mst[0].value = edgeSet[0].value;

	fatherNode[mst[0].start] = mst[0].start;
	fatherNode[mst[0].end] = mst[0].start;

	//Kruskal
	int mstIndex = 1;//最小生成树的索引
	int mstWeightSum = edgeSet[0].value;//最小生成树的权值和

	for (int i = 1; i < edges; i++)
	{
		vertex rootNodeStart = nodeRoot(edgeSet[i].start);
		vertex rootNodeEnd = nodeRoot(edgeSet[i].end);

		//边的两点在不同的连通分支中（即加入该选中的边后，原MST不构成环）
		if (rootNodeStart != rootNodeEnd)
		{
			mst[mstIndex++] = edgeSet[i];
			fatherNode[edgeSet[i].end] = edgeSet[i].start;
			mstWeightSum += edgeSet[i].value;
		}
	}

	//将最小生成树的结果输出到控制台
	cout << "MST weight sum is " << mstWeightSum << endl;

	for (int i = 0; i < mstIndex; i++)
		cout << mst[i].start << " " << mst[i].end << " " << mst[i].value << endl;
}

//如果用邻接表实现的话,对边的访问就是O(E),整个复杂度为O(V+E);
//而如果是邻接矩阵实现的话，对边的访问就是O(V+V^2)=O(V^2)
void Graph::topologicalSort()
{
	topoSortSequence = new vertex[nodes];//初始化拓扑序列
	int topoIndex = 0;//用来将节点插入拓扑序列的下标索引

	//在初始化的时候已经找出入度为0的节点集合InDegreeZeroVertexSet
	for (int i = 0; i < InDegreeZeroVertexCnt; i++)
	{
		//将入度为0的节点插入拓扑序列中
		cout << InDegreeZeroVertexSet[i] << " vertex degree = 0" << endl;

		vertex InDegreeZeroVertex = InDegreeZeroVertexSet[i];
		topoSortSequence[topoIndex++] = InDegreeZeroVertex;

		//遍历该点引出的所有点
		for (int vertexJ = 0; vertexJ < nodes; vertexJ++)
		{
			//找到InDegreeZeroVertex所指的节点
			if (InDegreeZeroVertex != vertexJ && adjacency[InDegreeZeroVertex][vertexJ] != AWAY)
			{
				//删去边<InDegreeZeroVertex,vertexJ>
				inDegree[vertexJ]--;

				//删去该边后,没有其他的入边(即入度为0),则将该点放入拓扑序列中
				if (inDegree[vertexJ] == 0)
					InDegreeZeroVertexSet[InDegreeZeroVertexCnt++] = vertexJ;
			}
		}
	}

	//如果图中还有边,则图中有环,没有拓扑序列

	for (int i = 0; i < topoIndex; i++)
		cout << topoSortSequence[i] << " ";

	cout << endl;
}

int main()
{
	Graph g;
	g.input(2);
	//g.output();

	g.topologicalSort();

	return 0;
}