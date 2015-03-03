/*
 *  gSpan algorithm implemented by coolypf
  *  http://blog.csdn.net/coolypf
   */

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int LABEL_MAX = 3000;
int min_support;
int nr_graph;

struct Graph
{
	vector<int> node_label;
	vector<int> *edge_next, *edge_label;
	vector<int> gs;

	void removeEdge(int x, int a, int y)
	{
		for (size_t i = 0; i < node_label.size(); ++i)
		{
			int t;
			if (node_label[i] == x)
				t = y;
			else if (node_label[i] == y)
				t = x;
			else
				continue;
			for (size_t j = 0; j < edge_next[i].size(); ++j)
			{
				if (edge_label[i][j] == a && node_label[edge_next[i][j]] == t)
				{
					/* remove edge */
					edge_label[i][j] = edge_label[i].back();
					edge_label[i].pop_back();
					edge_next[i][j] = edge_next[i].back();
					edge_next[i].pop_back();
					j--;
				}
			}
		}
	}

	bool hasEdge(int x, int a, int y)
	{
		for (size_t i = 0; i < node_label.size(); ++i)
		{
			int t;
			if (node_label[i] == x)
				t = y;
			else if (node_label[i] == y)
				t = x;
			else
				continue;
			for (size_t j = 0; j < edge_next[i].size(); ++j)
				if (edge_label[i][j] == a && node_label[edge_next[i][j]] == t)
					return true;
		}
		return false;
	}
} *GS;

struct GraphData
{
	vector<int> nodel;
	vector<bool> nodev;

	vector<int> edgex;
	vector<int> edgey;
	vector<int> edgel;
	vector<bool> edgev;
};

class EdgeFrequency
{
	int *array;
	int u, v;

public:
	void init(int max_node_label, int max_edge_label)
	{
		u = max_node_label + 1;
		v = u * (max_edge_label + 1);
		array = new int[u * v];
	}

	int& operator()(int x, int a, int y) { return array[x * v + a * u + y]; }

	int operator()(int x, int a, int y) const { return array[x * v + a * u + y]; }
} EF;

struct Edge
{
	int ix, iy;
	int x, a, y;

	Edge(int _ix, int _iy, int _x, int _a, int _y) : ix(_ix), iy(_iy), x(_x), a(_a), y(_y) {}

	bool operator<(const Edge &e) const
	{
		if (ix > iy)
		{
			if (e.ix < e.iy)
				return true;
			if (iy < e.iy || (iy == e.iy && a < e.a))
				return true;
		}
		else if (e.ix < e.iy)
		{
			if (ix > e.ix)
				return true;
			if (ix == e.ix)
			{
				if (x < e.x)
					return true;
				if (x == e.x && (a < e.a || (a == e.a && y < e.y)))
					return true;
			}
		}
		return false;
	}
};

struct GraphCode
{
	vector<const Edge *> seq;
	vector<int> gs;
};

vector<Graph *> S;// graph mining result

void subgraph_mining(GraphCode &gc, int next);

int main(int argc, char **argv)
{
	clock_t clk = clock();

	/* parse command line options */
	assert(argc == 5);
	int num = atoi(argv[3]), denom = atoi(argv[4]);
	assert(num && denom && num <= denom);

	/* read graph data */
	FILE *fp = fopen(argv[1], "r");
	assert(fp);
	bool occ_node_label[LABEL_MAX + 1], occ_edge_label[LABEL_MAX + 1];
	int freq_node_label[LABEL_MAX + 1], freq_edge_label[LABEL_MAX + 1];
	memset(freq_node_label, 0, sizeof(freq_node_label));
	memset(freq_edge_label, 0, sizeof(freq_edge_label));
	GraphData *gd = NULL;
	vector<GraphData *> v_gd;
	while (1)
	{
		static char dummy[10];
		if (fscanf(fp, "%s", dummy) <= 0)
		{
			if (gd)
			{
				v_gd.push_back(gd);
				for (int i = 0; i <= LABEL_MAX; ++i)
				{
					if (occ_node_label[i])
						freq_node_label[i]++;
					if (occ_edge_label[i])
						freq_edge_label[i]++;
				}
			}
			break;
		}
		if (*dummy == 't')
		{
			int id;
			fscanf(fp, "%s%d", dummy, &id);
			if (gd)
			{
				v_gd.push_back(gd);
				for (int i = 0; i <= LABEL_MAX; ++i)
				{
					if (occ_node_label[i])
						freq_node_label[i]++;
					if (occ_edge_label[i])
						freq_edge_label[i]++;
				}
			}
			if (id < 0) break;
			assert(id == (int)v_gd.size());
			gd = new GraphData;
			memset(occ_node_label, 0, sizeof(occ_node_label));
			memset(occ_edge_label, 0, sizeof(occ_edge_label));
		}
		else if (*dummy == 'v')
		{
			int id, label;
			fscanf(fp, "%d%d", &id, &label);
			assert(id == (int)gd->nodel.size() && label <= LABEL_MAX);
			gd->nodel.push_back(label);
			gd->nodev.push_back(true);
			occ_node_label[label] = true;
		}
		else if (*dummy == 'e')
		{
			int x, y, label;
			fscanf(fp, "%d%d%d", &x, &y, &label);
			assert(x < (int)gd->nodel.size() && y < (int)gd->nodel.size() && label <= LABEL_MAX);
			gd->edgex.push_back(x);
			gd->edgey.push_back(y);
			gd->edgel.push_back(label);
			gd->edgev.push_back(true);
			occ_edge_label[label] = true;
		}
		else
			assert(0);
	}
	fclose(fp);

	min_support = v_gd.size() * num / denom;
	if (min_support < 1)
		min_support = 1;
	printf("%d graphs with minSup = %d\n", (int)v_gd.size(), min_support);

	/* sort labels of vertices and edges in GS by their frequency */
	int rank_node_label[LABEL_MAX + 1], rank_edge_label[LABEL_MAX + 1];
	for (int i = 0; i <= LABEL_MAX; ++i)
	{
		rank_node_label[i] = i;
		rank_edge_label[i] = i;
	}
	for (int i = LABEL_MAX; i > 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			int tmp;
			if (freq_node_label[rank_node_label[j]] < freq_node_label[rank_node_label[j + 1]])
			{
				tmp = rank_node_label[j];
				rank_node_label[j] = rank_node_label[j + 1];
				rank_node_label[j + 1] = tmp;
			}
			if (freq_edge_label[rank_edge_label[j]] < freq_edge_label[rank_edge_label[j + 1]])
			{
				tmp = rank_edge_label[j];
				rank_edge_label[j] = rank_edge_label[j + 1];
				rank_edge_label[j + 1] = tmp;
			}
		}
	}

	/* remove infrequent vertices and edges */
	/* ralabel the remaining vertices and edges in descending frequency */

	int max_node_label = 0, max_edge_label = 0;
	for (int i = 0; i <= LABEL_MAX; ++i)
	{
		if (freq_node_label[rank_node_label[i]] >= min_support)
			max_node_label = i;
		if (freq_edge_label[rank_edge_label[i]] >= min_support)
			max_edge_label = i;
	}
	printf("remaining max vertex, edge label: %d, %d\n", max_node_label, max_edge_label);

	int rank_to_node_label[LABEL_MAX + 1], rank_to_edge_label[LABEL_MAX + 1];
	memcpy(rank_to_node_label, rank_node_label, sizeof(rank_to_node_label));
	for (int i = 0; i <= LABEL_MAX; ++i)
		rank_node_label[rank_to_node_label[i]] = i;
	memcpy(rank_to_edge_label, rank_edge_label, sizeof(rank_to_edge_label));
	for (int i = 0; i <= LABEL_MAX; ++i)
		rank_edge_label[rank_to_edge_label[i]] = i;

	for (size_t i = 0; i < v_gd.size(); ++i)
	{
		GraphData &gd = *v_gd[i];
		for (size_t j = 0; j < gd.nodel.size(); ++j)
		{
			if (freq_node_label[gd.nodel[j]] < min_support)
				gd.nodev[j] = false;
			else
				gd.nodel[j] = rank_node_label[gd.nodel[j]];
		}
		for (size_t j = 0; j < gd.edgel.size(); ++j)
		{
			if (!gd.nodev[gd.edgex[j]] || !gd.nodev[gd.edgey[j]])
			{
				gd.edgev[j] = false;
				continue;
			}
			if (freq_edge_label[gd.edgel[j]] < min_support)
				gd.edgev[j] = false;
			else
				gd.edgel[j] = rank_edge_label[gd.edgel[j]];
		}

		/* re-map vertex index */
		map<int, int> m;
		int cur = 0;
		for (size_t j = 0; j < gd.nodel.size(); ++j)
		{
			if (!gd.nodev[j]) continue;
			m[j] = cur++;
		}
		for (size_t j = 0; j < gd.edgel.size(); ++j)
		{
			if (!gd.edgev[j]) continue;
			gd.edgex[j] = m[gd.edgex[j]];
			gd.edgey[j] = m[gd.edgey[j]];
		}
	}

	/* build graph set */
	nr_graph = (int)v_gd.size();
	GS = new Graph[nr_graph];
	for (int i = 0; i < nr_graph; ++i)
	{
		Graph &g = GS[i];
		GraphData &gd = *v_gd[i];
		for (size_t j = 0; j < gd.nodel.size(); ++j)
			if (gd.nodev[j])
				g.node_label.push_back(gd.nodel[j]);
		g.edge_next = new vector<int>[g.node_label.size()];
		g.edge_label = new vector<int>[g.node_label.size()];
		for (size_t j = 0; j < gd.edgel.size(); ++j)
		{
			if (!gd.edgev[j]) continue;
			g.edge_label[gd.edgex[j]].push_back(gd.edgel[j]);
			g.edge_label[gd.edgey[j]].push_back(gd.edgel[j]);
			g.edge_next[gd.edgex[j]].push_back(gd.edgey[j]);
			g.edge_next[gd.edgey[j]].push_back(gd.edgex[j]);
		}
	}

	/* find all subgraphs with only one vertex for reference */
	for (int i = 0; i <= max_node_label; ++i)
	{
		Graph *g = new Graph;
		g->node_label.push_back(i);
		for (int j = 0; j < nr_graph; ++j)
		{
			const Graph &G = GS[j];
			for (size_t k = 0; k < G.node_label.size(); ++k)
			{
				if (G.node_label[k] == i)
				{
					g->gs.push_back(j);
					break;
				}
			}
		}
		S.push_back(g);
	}

	/* enumerate all frequent 1-edge graphs in GS */

	EF.init(max_node_label, max_edge_label);
	for (int x = 0; x <= max_node_label; ++x)
	{
		for (int a = 0; a <= max_edge_label; ++a)
		{
			for (int y = x; y <= max_node_label; ++y)
			{
				int count = 0;
				for (int i = 0; i < nr_graph; ++i)
					if (GS[i].hasEdge(x, a, y))
						count++;
				EF(x, a, y) = count;
				EF(y, a, x) = count;
			}
		}
	}

	for (int x = 0; x <= max_node_label; ++x)
	{
		for (int a = 0; a <= max_edge_label; ++a)
		{
			for (int y = x; y <= max_node_label; ++y)
			{
				if (EF(x, a, y) < min_support)
					continue;
				GraphCode gc;
				for (int i = 0; i < nr_graph; ++i)
					if (GS[i].hasEdge(x, a, y))
						gc.gs.push_back(i);
				Edge e(0, 1, x, a, y);
				gc.seq.push_back(&e);
				subgraph_mining(gc, 2);

				/* GS <- GS - e */
				for (int i = 0; i < nr_graph; ++i)
					GS[i].removeEdge(x, a, y);
			}
		}
	}

	/* output mining result */

	printf("Found %d frequent subgraphs\n", (int)S.size());

	fp = fopen(argv[2], "w");
	assert(fp);
	for (int i = 0; i < (int)S.size(); ++i)
	{
		const Graph &g = *S[i];
		fprintf(fp, "t # %d * %d\nx", i, (int)g.gs.size());
		for (size_t j = 0; j < g.gs.size(); ++j)
			fprintf(fp, " %d", g.gs[j]);
		fprintf(fp, "\n");
		for (size_t j = 0; j < g.node_label.size(); ++j)
			fprintf(fp, "v %d %d\n", (int)j, rank_to_node_label[g.node_label[j]]);
		if (g.node_label.size() < 2)
		{
			fprintf(fp, "\n");
			continue;
		}
		for (int j = 0; j < (int)g.node_label.size(); ++j)
		{
			for (size_t k = 0; k < g.edge_label[j].size(); ++k)
				if (j < g.edge_next[j][k])
					fprintf(fp, "e %d %d %d\n", j, g.edge_next[j][k], rank_to_edge_label[g.edge_label[j][k]]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	printf("Total time: (%d / %d) seconds\n", (int)(clock() - clk), (int)CLOCKS_PER_SEC);

	return 0;
}

/* traverse a graph and find its minimal DFS code */
class Traveler
{
	const vector<const Edge *> &s;
	const Graph &g;
	bool is_min;
	vector<int> g2s;
	vector<vector<bool> > f;

	void DFS(vector<int> &v, int c, int next)
	{
		if (c >= (int)s.size())
			return;
		vector<int> bak;
		while (!v.empty())
		{
			bool flag = false;
			int x = v.back();
			for (size_t i = 0; i < g.edge_next[x].size(); ++i)
			{
				int y = g.edge_next[x][i];
				if (f[x][y]) continue;
				flag = true;
				if (g2s[y] < 0)
				{
					Edge e(g2s[x], next, g.node_label[x], g.edge_label[x][i], g.node_label[y]);
					if (*s[c] < e) continue;
					if (e < *s[c])
					{
						is_min = false;
						return;
					}
					g2s[y] = next;
					v.push_back(y);
					f[x][y] = true;
					f[y][x] = true;
					DFS(v, c + 1, next + 1);
					if (!is_min) return;
					f[x][y] = false;
					f[y][x] = false;
					v.pop_back();
					g2s[y] = -1;
				}
				else
				{
					Edge e(g2s[x], g2s[y], g.node_label[x], g.edge_label[x][i], g.node_label[y]);
					if (*s[c] < e) continue;
					if (e < *s[c])
					{
						is_min = false;
						return;
					}
					f[x][y] = true;
					f[y][x] = true;
					DFS(v, c + 1, next);
					if (!is_min) return;
					f[x][y] = false;
					f[y][x] = false;
				}
			}
			if (flag) break;
			bak.push_back(v.back());
			v.pop_back();
		}
		while (!bak.empty())
		{
			v.push_back(bak.back());
			bak.pop_back();
		}
	}

public:
	Traveler(const vector<const Edge *> &_s, const Graph &_g) : s(_s), g(_g), is_min(true) {}

	bool isMin() const { return is_min; }

	void travel()
	{
		g2s.resize(0);
		g2s.resize(g.node_label.size(), -1);
		f.resize(g.node_label.size());
		for (size_t i = 0; i < g.node_label.size(); ++i)
		{
			f[i].resize(0);
			f[i].resize(g.node_label.size(), false);
		}

		for (size_t i = 0; i < g.node_label.size(); ++i)
		{
			int x = g.node_label[i];
			if (x > s[0]->x) continue;
			assert(x == s[0]->x);
			vector<int> v(1, i);
			g2s[i] = 0;
			DFS(v, 0, 1);
			g2s[i] = -1;
		}
	}
};

/* traverse a subgraph and find its children in graph */
class SubTraveler
{
	const vector<const Edge *> &s;
	const Graph &g;
	set<Edge> &c;
	int next;
	vector<int> rm;// rightmost
	vector<int> s2g;
	vector<int> g2s;
	vector<vector<bool> > f;

	void DFS(int p)
	{
		int x, y;

		if (p >= (int)s.size())
		{
			/* grow from rightmost path, pruning stage (3) */
			int at = 0;
			while (at >= 0)
			{
				x = s2g[at];
				for (size_t i = 0; i < g.edge_label[x].size(); ++i)
				{
					y = g.edge_next[x][i];
					if (f[x][y])
						continue;
					int ix = g2s[x], iy = g2s[y];
					assert(ix == at);
					Edge ne(0, 1, g.node_label[x], g.edge_label[x][i], g.node_label[y]);
					/* pruning */
					if (EF(ne.x, ne.a, ne.y) < min_support)
						continue;
					/* pruning stage (1) */
					if (ne < *s[0])
						continue;
					/* pruning stage (2) */
					if (iy >= 0)
					{
						if (ix <= iy)
							continue;
						bool flag = false;
						for (size_t j = 0; j < g.edge_label[y].size(); ++j)
						{
							int z = g.edge_next[y][j], w = g.edge_label[y][j];
							if (!f[y][z])
								continue;
							if (w > ne.a || (w == ne.a && g.node_label[z] > ne.x))
							{
								flag = true;
								break;
							}
						}
						if (flag)
							continue;
					}
					else
						iy = next;
					ne.ix = ix;
					ne.iy = iy;
					c.insert(ne);

				}
				at = rm[at];
			}
			return;
		}

		const Edge &e = *s[p];
		x = s2g[e.ix];
		assert(g.node_label[x] == e.x);

		for (size_t i = 0; i < g.edge_label[x].size(); ++i)
		{
			if (g.edge_label[x][i] != e.a)
				continue;
			y = g.edge_next[x][i];
			if (f[x][y])
				continue;
			if (g.node_label[y] != e.y)
				continue;
			if (s2g[e.iy] < 0 && g2s[y] < 0)
			{
				s2g[e.iy] = y;
				g2s[y] = e.iy;
				f[x][y] = true;
				f[y][x] = true;
				DFS(p + 1);
				f[x][y] = false;
				f[y][x] = false;
				g2s[y] = -1;
				s2g[e.iy] = -1;
			}
			else
			{
				if (y != s2g[e.iy])
					continue;
				if (e.iy != g2s[y])
					continue;
				f[x][y] = true;
				f[y][x] = true;
				DFS(p + 1);
				f[x][y] = false;
				f[y][x] = false;
			}
		}
	}

public:
	SubTraveler(const vector<const Edge *> &_s, const Graph &_g, set<Edge> &_c)
		: s(_s), g(_g), c(_c) {}

	void travel(int _next)
	{
		next = _next;
		s2g.resize(0);
		s2g.resize(next, -1);
		g2s.resize(0);
		g2s.resize(g.node_label.size(), -1);
		f.resize(g.node_label.size());
		for (size_t i = 0; i < g.node_label.size(); ++i)
		{
			f[i].resize(0);
			f[i].resize(g.node_label.size(), false);
		}

		/* find rightmost path */
		rm.resize(0);
		rm.resize(next, -1);
		for (size_t i = 0; i < s.size(); ++i)
			if (s[i]->iy > s[i]->ix && s[i]->iy > rm[s[i]->ix])
				rm[s[i]->ix] = s[i]->iy;

		for (size_t i = 0; i < g.node_label.size(); ++i)
		{
			if (g.node_label[i] != s[0]->x)
				continue;
			s2g[s[0]->ix] = (int)i;
			g2s[i] = s[0]->ix;
			DFS(0);
			g2s[i] = -1;
			s2g[s[0]->ix] = -1;
		}
	}
};

void subgraph_mining(GraphCode &gc, int next)
{
	/* construct graph from DFS code */
	Graph *g = new Graph;
	vector<const Edge *> &s = gc.seq;
	g->node_label.resize(next);
	g->edge_label = new vector<int>[next];
	g->edge_next = new vector<int>[next];
	for (size_t i = 0; i < s.size(); ++i)
	{
		int ix = s[i]->ix, iy = s[i]->iy, a = s[i]->a;
		g->node_label[ix] = s[i]->x;
		g->node_label[iy] = s[i]->y;
		g->edge_label[ix].push_back(a);
		g->edge_label[iy].push_back(a);
		g->edge_next[ix].push_back(iy);
		g->edge_next[iy].push_back(ix);
	}

	/* minimum DFS code pruning stage (4) */
	Traveler t(s, *g);
	t.travel();
	if (!t.isMin())
	{
		delete[] g->edge_label;
		delete[] g->edge_next;
		delete g;
		return;
	}

	S.push_back(g);

	/* enumerate potential children with 1-edge growth */
	map<Edge, vector<int> > m;
	for (size_t i = 0; i < gc.gs.size(); ++i)
	{
		set<Edge> c;
		SubTraveler st(s, GS[gc.gs[i]], c);
		st.travel(next);
		for (set<Edge>::const_iterator j = c.begin(); j != c.end(); ++j)
			m[*j].push_back(gc.gs[i]);
	}

	/* mining subgraph children */
	for (map<Edge, vector<int> >::iterator i = m.begin(); i != m.end(); ++i)
	{
		const Edge *e = &i->first;
		vector<int> &spp = i->second;
		if ((int)spp.size() < min_support)
			continue;
		GraphCode child_gc;
		child_gc.gs.swap(spp);
		child_gc.seq = s;
		child_gc.seq.push_back(e);
		if (e->iy == next)
			subgraph_mining(child_gc, next + 1);
		else
			subgraph_mining(child_gc, next);
	}

	g->gs.swap(gc.gs);
}
