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

	void input(int inputSource); //��������ͼ���ڽӾ���
	void output(); //���ͼ

	void BreastFirstSearch(vertex start);
	void DepthFirstSearch(vertex start);

	//��Դ���·��
	void Dijkstra(vertex start);
	void BellmanFord(vertex start);

	//��Դ���·��
	void FloydWarshall();

	//��С������(�������ͼ������ͼ����С��������Ϊ��С����ͼ)
	void Prim(vertex start);//˼���Dijkstraһ������̰��˼�롣Dijkstra��Prim���˸��������Ҫ����Դ�㵽������ľ��룬��Primֻ��Ҫ����ʣ��㵽MST�е�ľ��뼴�ɡ�
	void Kruskal(vertex start);

	//��������
	void topologicalSort();
private:
	//���ѡ��������ֺ���
	bool stillUnvisited(bool isVisited[]);//�ж�ͼ�нڵ��Ƿ���ʹ�

	//Dijkstra���ֺ���
	int minIndex(int *distance, int size, bool *isFound);//����δ�ҵ���С�����ͼ���е���С����

	//Kruskal���ֺ���
	vertex nodeRoot(vertex v); //���ؽڵ�v�����Ƚڵ�
	vertex *fatherNode;//���ֱ���

	//�����������ֱ���
	int *inDegree;//��¼ÿ���ڵ���������
	vertex *InDegreeZeroVertexSet;//���Ϊ0�Ľڵ㼯��
	int InDegreeZeroVertexCnt;//���Ϊ0�ڵ������
	void topoSortInitiation();//�����������������ʱ��Ҫ�õ��ı������г�ʼ��
	void findInDegreeZeroVertex();//Ѱ���������Ϊ0�Ľڵ�
	vertex *topoSortSequence;//��������

	int nodes;
	int edges;
	unDirectedEdge *edgeSet; //��������ߵ���Ϣ
	vertex adjacency[NODESIZE][NODESIZE];
};

Graph::Graph()
{
	nodes = 0;
}

void Graph::topoSortInitiation()
{
	//��ʼ����¼������ݼ���,��Ϊ0
	inDegree = new int[nodes];
	for (int i = 0; i < nodes; i++)
		inDegree[i] = 0;

	//��ʼ�����Ϊ0�Ľڵ㼯��
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

//inputSource��������ķ�ʽ�Ǵӿ���̨���루1�������ı����루2��
void Graph::input(int inputSource)
{
	if (inputSource == 1)
	{
		//��ȡ�ڵ���
		cout << "How many nodes: ";
		cin >> nodes;

		//��ʼ���ڽӾ���
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

		/************��������ʱ���õ�***********/
		topoSortInitiation();
		/************��������ʱ���õ�***********/

		//�Ƿ�Ϊ����ͼ
		bool isDirected;
		cout << "Is the graph directed?";
		cin >> isDirected;

		//��ȡ����
		cout << "How many edges: ";
		cin >> edges;

		//���������ͼ��ʼ��edgeSet
		if (!isDirected)
		{
			edgeSet = new unDirectedEdge[edges];
			fatherNode = new vertex[nodes];

			for (int i = 0; i < nodes; i++)
				fatherNode[i] = i;
		}

		//��ȡ�ߵľ�����Ϣ
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

			/************��������ʱ���õ�***********/
			//β�ڵ���Ȳ�Ϊ0
			inDegree[end]++;
			/************��������ʱ���õ�***********/
		}

		/************��������ʱ���õ�***********/
		findInDegreeZeroVertex();
		/************��������ʱ���õ�***********/
	}
	else if (inputSource == 2)//���ı�����
	{
		ifstream infile;
		infile.open("graphInput.txt");

		if (!infile)
		{
			cout << "graphInput.txt can't open\n";
			return;
		}

		//���ļ���ȡͼ����Ϣl
		//��ȡ�ڵ���
		infile >> nodes;

		//��ʼ���ڽӾ���
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

		/************��������ʱ���õ�***********/
		topoSortInitiation();
		/************��������ʱ���õ�***********/

		//��ȡ����
		infile >> edges;

		//��ȡͼ�Ƿ�Ϊ����ͼ
		bool isDirected;
		infile >> isDirected;

		cout << nodes << " nodes and " << edges << " edges\n";

		if (!isDirected)
		{
			cout << "It's an undirected graph.\n";
			//�����ֱ������г�ʼ��
			edgeSet = new unDirectedEdge[edges];
			fatherNode = new vertex[nodes];

			for (int i = 0; i < nodes; i++)
				fatherNode[i] = i;
		}
		else
			cout << "It's a directed graph.\n";

		//��ȡ�ߵľ�����Ϣ
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

			/************��������ʱ���õ�***********/
			//β�ڵ���Ȳ�Ϊ0
			inDegree[end]++;
			/************��������ʱ���õ�***********/
		}

		/************��������ʱ���õ�***********/
		findInDegreeZeroVertex();
		/************��������ʱ���õ�***********/

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

			//����v�����ĵ㶼�ŵ����к�
			for (int i = 0; i < nodes; i++)
			{
				//�����ĵ�
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
		bool *isVisited = new bool[nodes];//��¼�ڵ��Ƿ���ʹ���1��ʾ���ʹ���0��ʾδ���ʹ�

		//���÷��������ֵΪ0����ʾȫδ���ʹ�
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

			//����v�����ĵ㶼����ջ��
			for (int i = 0; i < nodes; i++)
			{
				//�����ĵ�
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
	bool *isFound = new bool[nodes]; //��ʾͼ�еĽڵ��Ƿ���ӵ�������
	for (int i = 0; i < nodes; i++)
		isFound[i] = false;

	int *distance = new int[nodes]; //��ʾԴ��start��ͼ�������ڵ����̾���
	for (int i = 0; i < nodes; i++)
		distance[i] = adjacency[start][i];

	isFound[start] = true;
	int min = AWAY;
	for (int i = 0; i < nodes; i++)
	{
		//Step 1: ��δ�ҵ����·���ļ�����Ѱ�����·���ĵ������
		int min_index = -1;
		min_index = minIndex(distance, nodes, isFound);
		isFound[min_index] = true;

		//Step 2:����distance����
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

	//�����start��ͼ�����������̾���
	cout << "Single Source Shortest Path(Dijkstra)\n";
	for (int i = 0; i < nodes; i++)
	{
		if (i != start)
			cout << start << " -> " << i << " " << distance[i] << endl;
	}
}

void Graph::BellmanFord(vertex start)
{
	//����Դ�㵽���������������̾��룬����distance[i]��ʾԴ��start����i����̾��루�ڵ�ǰ�����ܹ������ıߣ�
	int *distance = new int[nodes];

	//��ʼ��distance����
	for (int i = 0; i < nodes; i++)
		distance[i] = adjacency[start][i];

	//���е�����ÿ���㾭�����бߺ����̾���
	for (int v = 0; v < nodes - 1; v++)//�ڵ�v�ε���(����v���ڵ�)ʱ��distance(v) = min(distance(v-1), start�����������ڵ�ľ���+�����ڵ㵽Ŀ��ľ���)
	{
		//���Ӷ�Ϊ�ڵ���*�ߣ���Ϊͼ�Ĵ�����ͨ���ڽӾ��󴢴�ģ����Կ���ȥ��n^3
		for (int source = 0; source < nodes; source++)
		{
			for (int end = 0; end < nodes; end++)
			{
				if (source != end && adjacency[source][end] != AWAY)
				{
					//�����ɳڼ���(relaxation)
					int min = distance[source] + adjacency[source][end];
					if (distance[end] > min)
						distance[end] = min;
				}
			}
		}
	}

	//�ж��Ƿ���ڸ�Ȩ���������Ȼ���ҵ�ʹ�����С�ıߣ���ô�޷�������·��
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

	//�����̾���
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
	//����distance��ά���飬��������ͼ�и��㵽���������̾���
	int **distance = new int*[nodes];
	for (int i = 0; i < nodes; i++)
		distance[i] = new int[nodes];

	//��ʼ����ά����
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
			distance[i][j] = adjacency[i][j];
	}

	//FloydWarshall
	//�ȿ���middle���䣬��Ϊ�ڽ����ɳڼ���ʱ���õ����º�ľ��룬��������������©�����º�ľ���
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

	//���Ҫ�õ������ڵ�����·������ô���Զ�������һ����ά��������¼i��j�����ĵ㣬�ٶԶ�ά�������·������

	//�����̾������
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
			cout << distance[i][j] << " ";

		cout << endl;
	}
}

void Graph::Prim(vertex start)
{
	//��ά����mst��¼��С�������ĵ�ͱ�Ȩֵ
	int **mst = new int*[nodes];
	for (int i = 0; i < nodes; i++)
		mst[i] = new int[nodes];

	//��ʼ����ά����mst
	for (int i = 0; i < nodes; i++)
		for (int j = 0; j < nodes; j++)
			mst[i][j] = AWAY;

	//����distance��¼δ��ѡ�еĵ㵽��С����������̾���
	int *distance = new int[nodes];

	//����isAddedToMST��ʾ�ڵ��Ƿ��Ѿ����������С����������
	bool *isAddedToMST = new bool[nodes];

	//����neighbour��¼distance���鵽��С�������ıߵ���һ��
	vertex *neighbour = new vertex[nodes];

	//��Դ��start�ľ����ʼ������distance������isAddedToMST������neighbour
	for (int i = 0; i < nodes; i++)
	{
		distance[i] = adjacency[start][i];
		isAddedToMST[i] = false;
		neighbour[i] = start;
	}

	isAddedToMST[start] = true;

	//Prim�㷨
	for (int i = 0; i < nodes - 1; i++)
	{
		int min = AWAY;
		vertex vertexToADD;
		//�ҳ�distance�����е���С����������С����
		for (int distanceIndex = 0; distanceIndex < nodes; distanceIndex++)
		{
			if (!isAddedToMST[distanceIndex] && distance[distanceIndex] < min)
			{
				min = distance[distanceIndex];
				vertexToADD = distanceIndex;
			}
		}

		//���ҵ���С����ĵ�����ά����mst����������isAddedToMST
		mst[neighbour[vertexToADD]][vertexToADD] = min;
		isAddedToMST[vertexToADD] = true;

		//��������neighbour
		for (int j = 0; j < nodes; j++)
		{
			if (!isAddedToMST[j] && distance[j] > adjacency[j][vertexToADD])
			{
				distance[j] = adjacency[j][vertexToADD];
				neighbour[j] = vertexToADD;
			}
		}
	}

	//�����Դ��start��ʼ����С������
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
		{
			if (mst[i][j] != AWAY)
				cout << i << "->" << j << " " << mst[i][j] << endl;
		}
	}
}

bool edgeCmp(unDirectedEdge edge1, unDirectedEdge edge2)//�����������ֺ��������ر�Ȩֵ��С�ı�
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
	//mst������С�������Ľ������СΪ�ڵ���-1
	unDirectedEdge *mst = new unDirectedEdge[nodes - 1];

	//�Ա߼���������
	sort(edgeSet, edgeSet + edges, edgeCmp);

	//��mst���г�ʼ��
	mst[0].start = edgeSet[0].start;
	mst[0].end = edgeSet[0].end;
	mst[0].value = edgeSet[0].value;

	fatherNode[mst[0].start] = mst[0].start;
	fatherNode[mst[0].end] = mst[0].start;

	//Kruskal
	int mstIndex = 1;//��С������������
	int mstWeightSum = edgeSet[0].value;//��С��������Ȩֵ��

	for (int i = 1; i < edges; i++)
	{
		vertex rootNodeStart = nodeRoot(edgeSet[i].start);
		vertex rootNodeEnd = nodeRoot(edgeSet[i].end);

		//�ߵ������ڲ�ͬ����ͨ��֧�У��������ѡ�еıߺ�ԭMST�����ɻ���
		if (rootNodeStart != rootNodeEnd)
		{
			mst[mstIndex++] = edgeSet[i];
			fatherNode[edgeSet[i].end] = edgeSet[i].start;
			mstWeightSum += edgeSet[i].value;
		}
	}

	//����С�������Ľ�����������̨
	cout << "MST weight sum is " << mstWeightSum << endl;

	for (int i = 0; i < mstIndex; i++)
		cout << mst[i].start << " " << mst[i].end << " " << mst[i].value << endl;
}

//������ڽӱ�ʵ�ֵĻ�,�Աߵķ��ʾ���O(E),�������Ӷ�ΪO(V+E);
//��������ڽӾ���ʵ�ֵĻ����Աߵķ��ʾ���O(V+V^2)=O(V^2)
void Graph::topologicalSort()
{
	topoSortSequence = new vertex[nodes];//��ʼ����������
	int topoIndex = 0;//�������ڵ�����������е��±�����

	//�ڳ�ʼ����ʱ���Ѿ��ҳ����Ϊ0�Ľڵ㼯��InDegreeZeroVertexSet
	for (int i = 0; i < InDegreeZeroVertexCnt; i++)
	{
		//�����Ϊ0�Ľڵ��������������
		cout << InDegreeZeroVertexSet[i] << " vertex degree = 0" << endl;

		vertex InDegreeZeroVertex = InDegreeZeroVertexSet[i];
		topoSortSequence[topoIndex++] = InDegreeZeroVertex;

		//�����õ����������е�
		for (int vertexJ = 0; vertexJ < nodes; vertexJ++)
		{
			//�ҵ�InDegreeZeroVertex��ָ�Ľڵ�
			if (InDegreeZeroVertex != vertexJ && adjacency[InDegreeZeroVertex][vertexJ] != AWAY)
			{
				//ɾȥ��<InDegreeZeroVertex,vertexJ>
				inDegree[vertexJ]--;

				//ɾȥ�ñߺ�,û�����������(�����Ϊ0),�򽫸õ��������������
				if (inDegree[vertexJ] == 0)
					InDegreeZeroVertexSet[InDegreeZeroVertexCnt++] = vertexJ;
			}
		}
	}

	//���ͼ�л��б�,��ͼ���л�,û����������

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