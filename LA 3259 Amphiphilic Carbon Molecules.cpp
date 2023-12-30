#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

struct posit{
	int x, y;
	double r; //極角
	bool operator< (posit &tmp){
		return tmp.r > r;
	} 
}p[1005], op[1005]; //p為相對基準點座標 op為實際座標 

int n, color[1005];

bool Left(posit a, posit b){ // 判斷點是否在線段左側 
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
			
			int L = 0, R = 0, cnt = 2; //L紀錄目前走到位置 R紀錄最後一點位置 cnt為點的數量
			
			while(L < k) // 以基準點對每個點當基準線 
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
