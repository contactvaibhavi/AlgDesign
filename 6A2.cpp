#include <bits/stdc++.h>

using namespace std;

#define MOD 10000

class HeapY
{
	vector<int> v;
	bool m;

	void swap(int x, int y)
	{
		int temp = v[x];
		v[x] = v[y];
		v[y] = temp;
	}

	void siftDown(int i)
	{
		if(i >= v.size())
			return;

		int l = i*2;
		int r = i*2 + 1;
		int optimal= i;

		if(l < v.size() && ((m && v[l] > v[optimal]) || (!m && v[l] < v[optimal])) )
			optimal = l;

		if(r < v.size() && ((m && v[r] > v[optimal]) || (!m && v[r] < v[optimal])) )
			optimal = r;

		if(optimal != i)
		{
		    swap(optimal, i);
		    siftDown(optimal);
		}
	}

	void siftUp(int i)
	{
		if(i == 0)
			return;

		int par = i/2;

		if((m && v[i] > v[par]) || (!m && v[i] < v[par]))
		{
		    swap(i, par);
			siftUp(par);
		}
		}

public:
	void setMode(bool mode)
	{
		m = mode;
	}

	bool empty(void)
	{
		return v.empty();
	}

	int peekRoot(void)
	{
		return v[0]; 
	}

	int extractRoot(void)
	{
		int x = v[0];
		v[0]  = v[v.size()-1];
		v.pop_back();

		siftDown(0);

		return x;
	}

	void insert(int x)
	{
		v.push_back(x);

		siftUp(v.size()-1);
	}

	int size(void)
	{
		return v.size();
	}
};

int main()
{
	freopen("Median.txt", "r", stdin);

	int N = 10000;

	HeapY maxx;
	HeapY minn;

	maxx.setMode(1);
	minn.setMode(0);

	int rMedian = 0;

	int x;
	for(int i=0;i<N;i++)
	{
		cin>>x;

		if(maxx.empty())
			maxx.insert(x);
		else	
		{
			int maxL = maxx.peekRoot();

			if(x <= maxL)
			{
				if(maxx.size() == minn.size())
					maxx.insert(x);
				else
				{
					int z = maxx.extractRoot();

					minn.insert(z);
					maxx.insert(x);
				}
			}
			else 
			{
				minn.insert(x);

				if(maxx.size() == minn.size())
					;
				else
				{
					int z = minn.extractRoot();

					maxx.insert(z);
				}
			}
		}

		rMedian = (rMedian + maxx.peekRoot()%MOD) % MOD;
	}

	cout<<rMedian<<endl;

	return 0;
}