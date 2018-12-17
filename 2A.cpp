#include<bits/stdc++.h>

using namespace std;

typedef long long int ll;

int medianOfThree(ll a[], int l, int r)
{
	int n = (r-l+1);
	int mid_index = n/2 - (n%2==0 ? 1 : 0);
	int mid = l+mid_index;

	int x=a[l], y=a[r], z=a[mid];

	int minn=min(min(x, y), z), maxx=max(max(x, y), z);

	if(x > minn && x < maxx)
		return l;

	if(y > minn && y < maxx)
		return r;

	if(z > minn && z < maxx)
		return mid;
}

int getPivot(ll a[], int l, int r, int mode)
{
	switch(mode)
	{
		case 0: return l;
		case 1: return r;
		case 2: return medianOfThree(a, l, r);
	}
}

int partitionR(ll a[], int l, int r, int pivot, ll &ct)
{
	swap(a[r], a[pivot]);

	ct = ct + (ll) (r-l+1-1);

	int i=l-1, j=l;

	for(;j<r;j++)
	{
		if(a[j] < a[r])
		{
			i++;
			swap(a[i], a[j]);
		}
	}

	i++;
	swap(a[i], a[r]);

	return i;
}

int partitionL(ll a[], int l, int r, int pivot, ll &ct)
{
	swap(a[l], a[pivot]);

	ct = ct + (ll) (r-l+1-1);

	int i=l, j=l+1;

	for(;j<=r;j++)
	{
		if(a[j] < a[l])
		{
			i++;
			swap(a[i], a[j]);
		}
	}

	swap(a[i], a[l]);

	return i;
}

void quickSort(ll a[], int l, int r, int mode, ll &ct)
{
	if(l>=r)
		return;

	int pivot = getPivot(a, l, r, mode);

	int p = partitionL(a, l, r, pivot, ct);
	quickSort(a, l, p-1, mode, ct);
	quickSort(a, p+1, r, mode, ct);
}

void printArr(ll a[], int l, int r)
{
	while(l<=r)
	cout<<a[l++]<<" ";
	
	cout<<endl;
}

int main()
{
	ll n = 10000;
	freopen("QuickSort.txt", "r", stdin);

	ll a[10001]={0};
	for(int i=0;i<n;i++)
		cin>>a[i];

	ll ct=0;

	quickSort(a, 0, n-1, 2, ct);

	printArr(a, 0, n-1);

	cout<<ct<<endl;

	return 0;
}