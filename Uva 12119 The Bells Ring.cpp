#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e6 + 5;
typedef long long ll;

ll T;
ll total, num[maxn];
ll p_cnt, prime[maxn], vis[maxn];
ll f_cnt, factor[maxn], cnt[maxn]; //cnt[]為質因數數量

ll GCD(ll a, ll b){
    return (b == 0 ? a : GCD(b, a%b));
}

ll LCM(ll a, ll b){
    ll k = GCD(a, b);
    return a*b / k;
}

void sieve_prime(ll n)
{
    p_cnt = 0;
    memset(vis, 0, sizeof(vis));

    for(ll i = 2; i <= n; i++)
    {
        if(vis[i]){
            continue;
        }

        prime[p_cnt++] = i;
        for(ll j = i*i; j <= n; j += i){
            vis[j] = 1;
        }
    }
}

void find_factor(ll n)
{
    f_cnt = 0;
    memset(cnt, 0, sizeof(cnt));

    for(ll i = 0; i < p_cnt; i++) //scan質數
    {
        if(n % prime[i] == 0)
        {
            factor[f_cnt] = prime[i];
            while(n % prime[i] == 0)
            {
                n /= prime[i];
                cnt[f_cnt]++;
            }
            f_cnt++;
        }
    }

    if(n > 1){ //沒有除了自己外的質因數
        factor[f_cnt] = n;
        cnt[f_cnt++] = 1;
    }
}

void dfs(int d, ll p) // 利用factor[]枚舉所有因數
{
    if(p > 1e6) return;

    if(d == f_cnt){
        num[total++] = p; // 將因數存入num[] 裡
        return;
    }

    for(int i = 0; i <= cnt[d]; i++) // cnt[d] 為 factor[d] 的數量
    {
        dfs(d+1, p);
        p *= factor[d];
    }
}

int main()
{
    int cas = 1;
    sieve_prime(maxn);

    while(scanf("%lld", &T) && T)
    {
        int result = total = 0; // total為 因數的個數
        printf("Scenario %d:\n", cas++);
        find_factor(T);
        dfs(0, 1);
        sort(num, num+total);

        for(int i = 0; i < total; i++) // 枚舉三個因數
        {
            for(int j = i+1; j < total; j++)
            {
                if(num[j] - num[i] > 25) break;

                ll d = LCM(num[i], num[j]); // 最小公倍數

                for(int k = j+1; k < total; k++)
                {
                    if(num[k] - num[i] > 25) break;

                    if(LCM(d, num[k]) == T)
                    {
                        printf("%d %d %d\n", num[i], num[j], num[k]);
                        result++;
                    }
                }
            }
        }

        if(result == 0) printf("Such bells don't exist\n");
        printf("\n");
    }
}
