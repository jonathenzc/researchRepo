//#include <iostream>
//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
//#include <queue>
//#include <algorithm>
//#include <fstream>
//#include <string>
//
//const int N = 2210;
//const int maxn = 2000;
//const int maxm = 201010;
//const int inf = 1e8;
//#define MIN INT_MIN
//#define MAX 1e6
//#define LL long long
//#define init(a) memset(a,0,sizeof(a))
//#define FOR(i,a,b) for(int i = a;i<b;i++)
//#define max(a,b) (a>b)?(a):(b)
//#define min(a,b) (a>b)?(b):(a)
//using namespace std;
//int ma[1150][1150];
//bool vis[1150];
//int num = 0, n;
//
//void DFS(int k)
//{
//	vis[k] = 1;
//	FOR(i, 1, n + 1)
//	{
//		if (ma[k][i] && !vis[i])
//		{
//			DFS(i);
//		}
//	}
//}
//int main()
//{
//	int  m, a, b,c;
//	char e;
//	m = 1121;//±ßµÄ¸öÊý
//	init(ma); init(vis);
//	num = 0;
//
//	ifstream in;
//	in.open("edge.txt");
//	in >> e >> a >> b >> c;
//	ma[a][b] = ma[b][a] = 1;
//	
//	while (!in.eof())
//	{
//		in >> e >> a >> b >> c;
//		ma[a][b] = ma[b][a] = 1;
//	}
//
//	FOR(i, 1, n + 1)
//	{
//		if (!vis[i])
//		{
//			DFS(i);
//			num++;
//		}
//
//	}
//	cout << num << endl;
//
//	in.close();
//
//	return 0;
//}

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string>

const int N = 2210;
const int maxn = 2000;
const int maxm = 201010;
const int inf = 1e8;
#define MIN INT_MIN
#define MAX 1e6
#define LL long long
#define init(a) memset(a,0,sizeof(a))
#define FOR(i,a,b) for(int i = a;i<b;i++)
#define max(a,b) (a>b)?(a):(b)
#define min(a,b) (a>b)?(b):(a)
using namespace std;
int ma[1150][1150];
bool vis[1150];
int num = 0, n;

int main()
{
	int  m, a, b,c;
	char e;

	ifstream in;
	ofstream out;
	in.open("graph.txt");
	out.open("out.txt");
	in >> e >> a >> b;
	out << e << a << b<<endl;
	while (!in.eof())
	{
		in >> e;
		if (e == 'v')
		{
			in >> a >> b;
			out << e << " " << a << " " << 1 << endl;
		}
		else if (e=='e')
		{
			in >> a >> b >> c;
			out << e << " " << a << " " << b << " " << c << endl;
		}
		else
		{
			char jin;
			in >> jin >> a;
			out << e << " " << jin << " " << a << endl;
		}
	}


	in.close();
	out.close();

	return 0;
}