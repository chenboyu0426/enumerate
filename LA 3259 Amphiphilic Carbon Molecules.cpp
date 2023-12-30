#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

struct posit{
	int x, y;
	double r; //����
	bool operator< (posit &tmp){
		return tmp.r > r;
	} 
}p[1005], op[1005]; //p���۹����I�y�� op����ڮy�� 

int n, color[1005];

bool Left(posit a, posit b){ // �P�_�I�O�_�b�u�q���� 
	return (a.x*b.y - a.y*b.x) >= 0;
}

int solve()
{
	if(n <= 2) return 2;
	int ans = 0;
	
	for(int i = 0; i < n; i++){
		int k = 0;
		
		for(int j = 0; j < n; j++){
			if(i != j)
			{
				p[k].x = op[j].x - op[i].x;
				p[k].y = op[j].y - op[i].y;
				if(color[j]){
					p[k].x = -p[k].x;
					p[k].y = -p[k].y;
				}
				p[k].r = atan2(p[k].y, p[k].x);
				k++;
			}
		
			sort(p, p+k);
			
			int L = 0, R = 0, cnt = 2; //L�����ثe�����m R�����̫�@�I��m cnt���I���ƶq
			
			while(L < k) // �H����I��C���I���ǽu 
			{
				if(L == R){
					R = (R+1) % k;
					cnt++;
				}
				while(L != R && Left(p[L], p[R])){
					R = (R+1) % k;
					cnt++;
				}
				cnt--;	
				L++;
				ans = max(ans, cnt);
			} 
		}
	}
	return ans;
}

int main()
{
	while(scanf("%d", &n) && n)
	{
		for(int i = 0; i < n; i++){
			scanf("%d%d%d", &op[i].x, &op[i].y, &color[i]);
		}
		
		int ans = solve();
		printf("%d\n", ans);
	}
} 
