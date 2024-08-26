#include "graph.h"

Digraph::Digraph()
{
	cout << "input vertex" << endl;
	cin >> V_num;
	cout << "input edges" << endl;
	cin >> E_num;
	adj.assign(V_num, vector<int>(0));
	cout << "input" << endl;
	for (int i = 0; i < E_num; i++)
	{
		int v, m;
		cin >> v >> m;
		adj[v].push_back(m);
	}
}

Digraph::Digraph(int v):V_num(v)
{
	adj.resize(v, vector<int>(0));
}

void Digraph::addedge(int key1, int key2)
{
	adj[key1].push_back(key2);
	E_num++;
}

void Digraph::see()
{
	cout << V_num << ' ' << E_num << endl;
	for (int i = 0; i < V_num; i++)
	{
		cout << i << ':';
		for (int j : adj[i])
			cout << j << ' ';
		cout << endl;
	}
}

Digraph Digraph::reverse()
{
	Digraph res(V_num);
	for (int i = 0; i < V_num; i++)
	{
		for (int j : adj[i])
			res.addedge(j, i);
	}
	return res;
}

void Directed_DFS::DFS(int s)
{
	marked[s] = true;
	const auto& list = x->get_adj();
	for (int i : list[s])
	{
		if (!marked[i])
		{
			DFS(i);
		}
	}
}

Directed_DFS::Directed_DFS(Digraph* a, int s) :x(a), start(s)
{
	marked.assign(x->get_v(), false);
	DFS(start);
}

Directed_DFS::Directed_DFS(Digraph* a, vector<int> s):x(a),source(s)
{
	marked.assign(x->get_v(), false);
	for (int i : source)
	{
		if (!marked[i])
			DFS(i);
	}
}


void Is_Circle::DFS(int s, int from)// 双向链接也算环
{
	marked[s] = true;
	rope.push(s);
	const auto& list = x->get_adj();
	for (int i : list[s])
	{
		//if (i == from)
			//continue;
		if (!marked[i])
			DFS(i, s);
		else if (find(i, rope))
		{
			cycle = true;
			return;
		}
	}
	rope.pop();
}

bool Is_Circle::find(int v, stack<int> r)
{
	while (!r.empty()) 
	{
		if (r.top() == v) 
		{
			return true;
		}
		r.pop();
	}
	return false;
}

Is_Circle::Is_Circle(Digraph* a):x(a)
{
	marked.assign(x->get_v(), false);
	cycle = false;
	for (int i = 0; i < marked.size(); i++)
	{
		if (cycle == true)
			return;
		if (!marked[i])
		{
			DFS(i, INT_MIN);
		}
	}
}

void DFS_order::pre(int s)
{
	res.push_back(s);
	marked[s] = true;
	const auto& list = x->get_adj();
	for (int i : list[s])
	{
		if (!marked[i])
			pre(i);
	}
}

void DFS_order::post(int s)
{
	marked[s] = true;
	const auto& list = x->get_adj();
	for (int i : list[s])
	{
		if (!marked[i])
			post(i);
	}
	res.push_back(s);
}

void DFS_order::repost(int s)
{
	marked[s] = true;
	const auto& list = x->get_adj();
	for (int i : list[s])
	{
		if (!marked[i])
			repost(i);
	}
	res.insert(res.begin(), s);
}  

vector<int> Topological::order_withoutcheck()
{
	vector<int> res;
	DFS_order tem(x, 0);
	m = tem.mark();
	for (int i = 0; i < x->get_v(); i++)
	{
		if (!m[i])
		{
			tem.repost(i);//逆后排序并拼接
			m = tem.mark();
			vector<int> t = tem.ret();
			res.insert(res.begin(), t.begin(), t.end());
		}
	}
	return res;
}

vector<int> Topological::order()
{
	vector<int> res;
	Is_Circle y(x);
	if (y.get_cycle())//只要有环就无法拓扑排序
		return res;
	res = order_withoutcheck();
	return res;
}

void KosarajuSCC::DFS(int s)
{
	marked[s] = true;
	id[s] = count;
	auto adj = x->get_adj();
	for (int i : adj[s])
	{
		if (!marked[i])
			DFS(i);
	}
}

KosarajuSCC::KosarajuSCC(Digraph* a):x(a)
{
	count = 0;
	marked.assign(x->get_v(), false);
	id.assign(x->get_v(), 0);
	Digraph rex = x->reverse();
	Topological ofrex(&rex);
	vector<int> rpofrex = ofrex.order_withoutcheck();
	for (int s : rpofrex)
	{
		if (!marked[s])
		{
			DFS(s);
			count++;
		}
	}
}
