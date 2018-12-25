#include <bits/stdc++.h>

using namespace std;

class Graph
{
	int N;
	list<int> *adj;

	int t;
	int S;
public:
	Graph(int N)
	{
		this->N = N;
		t = 0;
		S = 0;

		adj = new list<int>[N];
	}

	void addEdge(int from, int to)
	{
		adj[from].push_back(to);
	}

	void printGraph(void)
	{
		for(int i=0;i<10;i++)
		{
			cout<<(i)<<"->"<<endl;

			list<int>::iterator it;
			for(it = adj[i].begin(); it != adj[i].end(); it++)
			{
				cout<<(*it)<<" ";
			}
			cout<<endl;
		}
	}

	vector<int> findMax5(vector<int> v)
	{
		int n = v.size();

		vector<int> maxx(5, 0);
		
		for(int turn=0;turn<5;turn++)
		{
			int mval = 0, mpos = 0;

			for(int i=0;i<v.size(); i++)
			{
				if(v[i] > mval)
				{
					mval = v[i];
					mpos = i;
				}
			}
			maxx[turn]  = mval;

			v[mpos] = 0;
		}
		return maxx;
	}

	void Transpose(void)
	{
		list<int> *adjT = new list<int>[N];

		for(int i=0;i<N;i++)
		{
			list<int>::iterator it;
			for(it = adj[i].begin(); it!=adj[i].end(); it++)
			{
				int to = (*it), from = i;
				adjT[to].push_back(from);
			}
		}

		adj = adjT;
	}

	void DFS1(int i, vector<int> &V, vector<int> &F, vector<int> &visited)
	{
		visited[i] = 1;

		list<int>::iterator it;
		for(it=adj[i].begin(); it!=adj[i].end(); it++)
		{
			int v = *it;
			if(!visited[v])
				DFS1(v, V, F, visited);
		}

		t++;
		F[i] = t;

		V.push_back(i);
	}

	void DFSLoop1(vector<int> &V, vector<int> &F)
	{
		vector<int> visited(N, 0);

		for(int i = N-1; i>=0; i--)
		{
			if(!visited[i])
				DFS1(i, V, F, visited);
		}
	}

	void DFS2(int i, vector<bool> &visited, vector<int> &leader, int &ct)
	{
		ct++;
		visited[i] = 1;
		leader[i] = S;

		list<int>::iterator it;
		for(it=adj[i].begin(); it!=adj[i].end(); it++)
		{
			int v = *it;
			if(!visited[v])
				DFS2(v, visited, leader, ct);
		}
	}

	void DFSLoop2(vector<int> V, vector<int> &sccSizeOfLeader, vector<int> &leader)
	{
		int maxFinishTime = t;

		vector<bool> visited(N, 0);

		int nSCC = 0;
		for(int i = maxFinishTime; i>= 1; i--)
		{
			int v = V[i];
			if(!visited[v])
			{
				nSCC++;

				S = v;
				
				int ct = 0;
				DFS2(v, visited, leader, ct);
				sccSizeOfLeader[S] = ct;
			}
		}
	}

	vector<int> SCC(void)
	{
		t = 0;
		S = 0;

		vector<int> V;
		V.push_back(-1);

		vector<int> F(N, 0);

		Transpose();
		DFSLoop1(V, F);

		vector<int> sccSizeOfLeader(N, 0);
		vector<int> leader(N, 0);
		
		Transpose();
		DFSLoop2(V, sccSizeOfLeader, leader);

 		vector<int> largest5 = findMax5(sccSizeOfLeader);
		 
		for(int i=0;i<5;i++)
			cout<<largest5[i]<<",";
		cout<<endl;
		 return sccSizeOfLeader;
	}
};

int main()
{
	int N =  875714;

	freopen("SCC.txt", "r", stdin);

	Graph G(N);

	int x=0;
	while(x < 5105043)
	{
		int a, b;
		cin>>a>>b;

		if(a == b)
			continue;

		--a; --b;
		G.addEdge(a, b);
		x++;
	}

	
	vector<int> scc = G.SCC();

	return 0;
}