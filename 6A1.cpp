#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

int main()
{
	freopen("algo1-programming_prob-2sum.txt", "r", stdin);

	map <ll, bool> mp;
	unordered_map<ll, bool> targets;	

	int N = 1000000;	
	ll ans = 0;

	for(int i=0;i<N;i++)
	{
		ll x;
		cin>>x;

		mp[x] = 1;
	}

	map<ll, bool>::iterator it, l, L, R;

	ll a = -10000LL, b = 10000LL;

	for(it = mp.begin(); it != mp.end(); it++)
	{
		ll key = it->first;
		L   = mp.lower_bound(a - key);
		R   = mp.upper_bound(b - key);

		for(l = L; l!=R; l++)
		{
			ll t = l->first + it->first;

			if(l->first != key && targets.find(t) == targets.end())
			{
				targets[t] = 1;
				ans++;
			}
		}
	}
	cout<<ans<<endl;

	return 0;
}