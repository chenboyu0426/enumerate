#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

#define maxn 500+10

typedef int Matrix[maxn][maxn];
int vis[maxn];
int prime[maxn];

void sieve(int n)
{
	int m = (int) sqrt(n+0.5);
	memset(vis, 0, sizeof(vis));
	
	for(int i = 2; i <= m; i++)
	{	
		if(!vis[i])
		{
			for(int j = i*i; j <= n; j += i){
				vis[j] = 1;
			}
		}
	}	
}

int generate_prime(int n)
{
	sieve(n);
	int c = 0;
	
	for(int i = 2; i < n; i++){
		if(!vis[i]) prime[c++] = i;
	}
	return c;
}

int rank(Matrix A, int m, int n)
{
	int i = 0, j = 0, k, r, u;
	
	while(i < m && j < n)
	{
		r = i;
		for(k = i; k < m; k++)
		{
			if(A[k][j])
			{
				r = k;
				break;
			}
		}
		if(A[r][j])
		{
			if(r != i)
				for(k = 0; k <= n; k++) swap(A[r][k], A[i][k]);
			for(u = i+1; u < m; u++){
				if(A[u][j])
					for(k = i; k <= n; k++) A[u][k] ^= A[i][k];
			}
			i++;
		}
		j++;
	}
	cout << i << endl;
	return i;
}

Matrix A;
int maxp = 0;

int main()
{	
	int m = generate_prime(500);
	int cas;
	scanf("%d", &cas);
	
	while(cas--)
	{
		int n, maxp = 0;
		long long x;
		scanf("%d", &n);
		memset(A, 0, sizeof(A));
		
		for(int i = 0; i< n; i++){
			scanf("%lld", &x);
			for(int j = 0; j < m; j++){
				
				while(x % prime[j] == 0){
					maxp = max(maxp, j);
					x /= prime[j];
					A[j][i] ^= 1;
				}
				printf("%d ", A[j][i]);
			}
			cout << endl;
		}
		
		int r = rank(A, maxp+1, n);
		cout << (1LL << (n-r))-1 << endl;
	}
}
