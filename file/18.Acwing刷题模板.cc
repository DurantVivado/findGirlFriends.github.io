#include <iostream>
#include <cstdio>
#include <climits>
#include <cstring>
#include <vector>
using namespace std;
const int N_MAX = 1010, MOD = (int)1E9+7;
int N,C;//物品数量和容积
int dp[N_MAX],M[N_MAX];//方案数
int main()
{
    int v,w,line = 0;
    cin>>N>>C;
    // memset(dp,INT_MIN,sizeof(dp));//为了使价值从0开始计数，我们把dp数组初始化为-inf
    M[0] = 1;//价值为0的方案为1，即全不放
    for(int i = 0;i < N;i++)
    {
        cin>>v>>w;
        for(int k = C;k >= v;k--)
        {   
            int t  = max(dp[k],dp[k - v] + w);//考虑选第i件物品和不选第i件物品，注意它们价值可能相同
            int s = 0;// 不是M[k]，否则三种方案叠加
            if(t == dp[k-v]+w) s += M[k-v];
            if(t == dp[k]) s += M[k];//这里不能写成else if ，两种路径分开考虑，求的是总方案数
            dp[k] = t;
            M[k] =s%MOD;
            // printf("i:%d,k:%d,dp:%d,M:%d\n",i,k,dp[k],M[k]);
            
        }
    }
    int res = 0, maxw = 0;
    for(int j = 0;j <= C;j++)
    {
        // cout<<dp[j]<<","<<M[j]<<endl;
        if(dp[j] == dp[C])
        {
            res += M[j];
            res %= MOD;
            // cout<<res;
        }
    }
    
    
    cout<<res;
    return 0;
}