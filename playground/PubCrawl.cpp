#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef int vertex;

struct unDirectedEdge
{
	vertex start;
	vertex end;
	int value;
};

bool edgeCmp(unDirectedEdge edge1, unDirectedEdge edge2)
{
	return edge1.value < edge2.value;
}

vertex nodeRoot(vertex v, vertex *fatherNode)
{
	vertex father = fatherNode[v];

	while (father != fatherNode[father])
		father = fatherNode[father];

	return father;
}

int Kruskal(vertex start, unDirectedEdge *edgeSet, vertex *fatherNode,int edgeCnt, int nodeCnt)
{
	//mst储存最小生成树的结果，大小为节点数-1
	unDirectedEdge *mst = new unDirectedEdge[nodeCnt - 1];

	//对边集进行排序
	sort(edgeSet, edgeSet + edgeCnt, edgeCmp);

	//对mst进行初始化
	mst[0].start = edgeSet[0].start;
	mst[0].end = edgeSet[0].end;
	mst[0].value = edgeSet[0].value;

	fatherNode[mst[0].start] = mst[0].start;
	fatherNode[mst[0].end] = mst[0].start;

	//Kruskal
	int mstIndex = 1;//最小生成树的索引
	int mstWeightSum = edgeSet[0].value;//最小生成树的权值和

	for (int i = 1; i < edgeCnt; i++)
	{
		vertex rootNodeStart = nodeRoot(edgeSet[i].start, fatherNode);
		vertex rootNodeEnd = nodeRoot(edgeSet[i].end, fatherNode);

		//cout << i << " rootNodeStart " << rootNodeStart << endl;
		//cout << i << " rootNodeEnd " << rootNodeEnd << endl;

		//边的两点在不同的连通分支中（即加入该选中的边后，原MST不构成环）
		if (rootNodeStart != rootNodeEnd)
		{
			mst[mstIndex++] = edgeSet[i];
			fatherNode[edgeSet[i].end] = edgeSet[i].start;
			mstWeightSum += edgeSet[i].value;
		}
	}

	for (int i = 0; i <edgeCnt; i++)
	{
		//cout << i << " start " << edgeSet[i].start << endl;
		//cout << i << " end " << edgeSet[i].end << endl;
		if ((edgeSet[i].start == start && edgeSet[i].end == nodeCnt) ||
			(edgeSet[i].end == start && edgeSet[i].start == nodeCnt))
		{
			mstWeightSum += edgeSet[i].value;
			break;
		}
	}


	//sum up the minimum spanning tree
	//cout << "MST weight sum is " << mstWeightSum << endl;

	//cout << mstWeightSum / double(nodeCnt)<<endl;

	//for (int i = 0; i < mstIndex; i++)
	//	cout << mst[i].start << " " << mst[i].end << " " << mst[i].value << endl;

	return mstWeightSum;
}

//turn string into integer
int str_2_int(string s, int startIndex, int length)
{
	string substr = s.substr(startIndex, length);

	int digit = 1;
	int sum = 0;

	for (int i = 0; i < substr.size(); i++)
	{
		digit = substr[i] - '0';
		for (int j = 0; j < substr.size() - i - 1; j++)
			digit *= 10;

		sum += digit;
	}

	return sum;
}

//find whether there is node in vertex set
bool isInVertexSet(vector<vertex>vertexSet,vertex node)
{
	bool result = false;

	for (int i = 0; i < vertexSet.size(); i++)
	{
		if (vertexSet[i] == node)
		{
			result = true;
			break;
		}
	}

	return result;
}

void get_best_tour(const vector<string> &city_map) 
{
	//count of edge
	int edges = city_map.size();
	unDirectedEdge *edgeSet = new unDirectedEdge[edges];
	
	//initiate edgeSet
	int nodes = 0;
	vector<vertex> vertexSet;
	for (int i = 0; i < city_map.size(); i++)
	{
		//find the first and last comma index
		int firstCommaIndex = city_map[i].find_first_of(",");
		int secondCommaIndex = city_map[i].find_last_of(",");

		//get edge's start node, end node and value
		vertex start = str_2_int(city_map[i], 0, firstCommaIndex - 0);
		vertex end = str_2_int(city_map[i], firstCommaIndex + 1, secondCommaIndex - firstCommaIndex - 1);
		int value = str_2_int(city_map[i], secondCommaIndex + 1, city_map[i].size() - secondCommaIndex - 1);

		//turn city_map into edgeSet
		edgeSet[i].start = start;
		edgeSet[i].end = end;
		edgeSet[i].value = value;

		//get count of vertex
		if (!isInVertexSet(vertexSet, start))
		{
			vertexSet.push_back(start);
			nodes++;
		}

		if (!isInVertexSet(vertexSet, end))
		{
			vertexSet.push_back(end);
			nodes++;
		}
	}

	//initiate helper variable
	vertex *fatherNode = new vertex[nodes+1];

	for (int i = 1; i <= nodes; i++)
		fatherNode[i] = i;

	//cout << "nodes " << nodes << " edges " << edges << endl;

	//for (int i = 0; i < edges; i++)
	//	cout << edgeSet[i].start << " " << edgeSet[i].end << " " << edgeSet[i].value<< endl;

	//Kruskal
	int minWeightSum = Kruskal(1, edgeSet, fatherNode, edges, nodes);

	cout << minWeightSum / double(nodes);
}

int main()
{
	//vector<string> v;
	//v.push_back("1,2,1");
	//v.push_back("2,3,1");
	//v.push_back("1,3,1");
	//v.push_back("3,4,2");
	//v.push_back("4,1,3");

	//get_best_tour(v);

	cout << 44 % 9;

	return 0;
}