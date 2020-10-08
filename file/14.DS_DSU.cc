//并查集模板DSU
#include <queue>
#include <vector>
#include <iostream>

using namespace std;
const int MAXN = 1000;
//建议直接加入Solution 类中，而不是新建一个类
//MAXN一般为数组大小，如果是二维数组，为m*n
class DSU
{
int fa[MAXN];
public:
inline void init(int n)
{
    for(int i = 0;i <= n;i++) fa[i] = i; 
}
int find(int x)
{
    return (x==fa[x])?x:(fa[x]==find(fa[x]));
}
inline void merge(int i,int j)
{
    fa[find(i)] = find(j);
}
};

class DSU_opt
{
int fa[MAXN];
int rank[MAXN];
public:
inline void init(int n)
{
    for(int i = 0;i <= n;i++) 
    {
        fa[i] = i;
        rank[i] = 1;
    } 
}
int find(int x)
{
    return (x==fa[x])?x:(fa[x]==find(fa[x]));
}
inline void merge(int i,int j)
{
    int x = find(i),y = find(j);
    if(rank[x] <= rank[y]) 
        fa[x] = y;
    else 
        fa[y] = x;
    if(rank[x]==rank[y]&&x!=y)
    {//如果秩相同，则新节点深度++
        rank[y]++;
    }
    
}
};