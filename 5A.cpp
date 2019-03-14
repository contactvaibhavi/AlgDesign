#include <bits/stdc++.h>
#include <time.h>
#include <unistd.h>

using namespace std;

struct edge
{
	int to;
	int wt;
};

struct node
{
	int vertex;
	int cost;
};

class HeapX
{
	vector<node> V;
	bool minn;

	void swap(vector<node> &V, int a, int b)
	{
		// cout<<V[a].vertex<<" "<<V[b].vertex<<endl;
		node temp = V[a];
		V[a] = V[b];
		V[b] = temp;
		// cout<<V[a].vertex<<" "<<V[b].vertex<<endl;
	}

	void siftUp(int i)
	{
		if(i == 0)
			return;

		int par = i/2;

		if((minn && V[i].cost < V[par].cost) || (!minn && V[i].cost > V[par].cost))
		{
			swap(V, i, par);

			siftUp(par);
		}
	}

	void siftDown(int i)
	{
		if(i == V.size())
			return;

		int optimal = i;
		int lChild = 2*i;
		int rChild = 2*i + 1;

		if(lChild < V.size() && ((minn && V[lChild].cost < V[optimal].cost) || (!minn && V[lChild].cost > V[optimal].cost)))
			optimal = lChild;

		if(rChild < V.size() && ((minn && V[rChild].cost < V[optimal].cost) || (!minn && V[rChild].cost > V[optimal].cost)))
			optimal = rChild;

		if(optimal != i)
		{
			swap(V, i, optimal);

			siftDown(optimal);
		}
	}

public:
	void setMode(bool mode)
	{
		minn = mode;		
	}

	void push(node Node)
	{
		V.push_back(Node);

		siftUp(V.size()-1);
	}

	node top(void)
	{
		if(V.empty())
		{
			node temp;
			temp.vertex = -1;
			temp.cost = -1;

			return temp;
		}

		return V[0];
	}

	void pop(void)
	{
		if(V.empty())
			return;

		int n = V.size();
		
		V[0] = V[n-1];
		V.pop_back();

		siftDown(0);
	}	

	void clear(void)
	{
		V.clear();
	}

	bool empty(void)
	{
		return V.empty();
	}
};

class Graph
{
	int N;
	list<edge> *adj;

	int t;
	int S;
public:
	Graph(int N)
	{
		this->N = N;
		t = 0;
		S = 0;

		adj = new list<edge>[N];
	}

	void addEdge(int from, int to, int wt)
	{
		edge temp;
		temp.to = to;
		temp.wt = wt;

		adj[from].push_back(temp);
	}

	void printGraph(void)
	{
		for(int i=0;i<N;i++)
		{
			cout<<(i)<<"->"<<endl;

			list<edge>::iterator it;
			for(it = adj[i].begin(); it != adj[i].end(); it++)
			{
				cout<<"("<<it->to<<", "<<it->wt<<")";
			}
			cout<<endl;
		}
	}

	int dijkstraHeap(int dest)
	{
		vector<int> cost(N, 0);

		for (int i=0; i<N; i++)
			cost[i] = INT_MAX;

		cost[0] = 0;
 
		HeapX pq;
		pq.setMode(1);

		node source;
		source.vertex = 0;
		source.cost = 0;

		pq.push(source);

		while (!pq.empty())
		{
			node curr = pq.top();
			pq.pop();

			int u = curr.vertex;

			if(u+1 == dest)
				break;

			list<edge>::iterator it;
			for(it = adj[u].begin(); it != adj[u].end(); it++)
			{
				int v = it->to;
				int l_uv = it->wt;

				if(cost[v] == INT_MAX || cost[u] + l_uv < cost[v])
				{
					cost[v] = cost[u] + l_uv;

					node temp;
					temp.vertex = v;
					temp.cost   = cost[v];

					pq.push(temp);
				}
			}
		}



		pq.clear();

		return cost[dest-1];
	}
};

int main()
{
	int N = 200;

	freopen("dijkstraData.txt", "r", stdin);

	Graph G(N);

	int x=0;
	while(x < N)
	{
		string line;
		getline(cin, line);

		int f = 1;
		string s = "";
		string B = "", C = "";

		for(int i=0; i<line.length(); i++)
		{
			if(line[i] == ' ' || line[i] == '\t')
			{
				if(f == 2)
				{
					C = s;

					f = 1;
					s = "";

					G.addEdge(stoi(B) - 1, x, stoi(C));
					G.addEdge(x, stoi(B) - 1, stoi(C));
				}
				else 
				{
					s = "";
				}
			}
			else if(line[i] == ',')
			{
				B = s;

				f = 2;
				s = "";
			}
			else
			{
				s += line[i];
			}
		}

		x++;
	}

	 // G.printGraph();
	int destArr[10] = {7,37,59,82,99,115,133,165,188,197};
	for(int i=0;i<10;i++)
	{
		int dest;
		cin>>dest;

		cout<<G.dijkstraHeap(destArr[i])<<" ";
	}
	cout<<endl;

	return 0;
}