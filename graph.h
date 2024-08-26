#pragma once
#include<iostream>
#include<stack>
#include<vector>
#include<queue>
using namespace std;
class Digraph
{
private:
	int V_num;
	int E_num;
	vector<vector<int>> adj; //由某个定点指出

public:
	Digraph();
	Digraph(int v);
	void addedge(int key1, int key2);
	vector<vector<int>> get_adj() { return adj; }
	int get_v() { return V_num; }
	int get_e() { return E_num; }
	void see();
	Digraph reverse();
};

class Directed_DFS//可达性
{
private:
	Digraph* x;
	vector<int> marked;
	int start;
	vector<int> source;
	void DFS(int s);
public:
	Directed_DFS(Digraph* a,int s);
	Directed_DFS(Digraph* a, vector<int> s);
	bool check(int v) { return marked[v]; }
};

class DFS_order
{
private:
	Digraph* x;
	vector<bool> marked;
	vector<int> res;
	int start;
public:
	DFS_order(Digraph* a,int s):x(a),start(s){ marked.assign(x->get_v(), false); }
	vector<int> ret() { vector<int> r = res; res.clear(); return r; }
	vector<bool> mark() { return marked; }
	void pre(int s);//前序
	void post(int s);//后序
	void repost(int s);//逆后序
};

class Is_Circle//基于深搜鉴别有环图
{
private:
	Digraph* x;
	vector<bool> marked;
	stack<int> rope;
	void DFS(int s, int from);
	bool find(int v, stack<int> r);
	bool cycle;
public:
	Is_Circle(Digraph* a);
	bool get_cycle() { return cycle; }
};

class Topological//拓扑排序
{
private:
	Digraph* x;
	vector<bool> m;
public:
	Topological(Digraph* a):x(a){}
	vector<int> order_withoutcheck();
	vector<int> order();
};

class KosarajuSCC
{
private:
	Digraph* x;
	vector<int> marked;
	vector<int> id;
	int count;
	void DFS(int s);
public:
	KosarajuSCC(Digraph* a);
	bool stronglyConnected(int v, int w) { return id[v] == id[w]; }
	int get_id(int v) { return id[v]; }
	int get_count() { return count; }
};