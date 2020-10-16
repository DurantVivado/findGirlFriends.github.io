/*
 * @Description: 
 * @Version: 2.0
 * @Autor: wangmiao
 * @Date: 2020-07-12 17:54:22
 * @LastEditors: Durant Thorvals
 * @LastEditTime: 2020-09-21 14:44:52
 */
/*
根据LC1514改编而成的Dijkstra模板
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef double weight_type ;
class Solution
{
public:
vector<pair<weight_type, int>> e[10005];//这个vector的元素类型为<weight_type,int>,第一个存储到当前点的权重，第二个存储顶点，长度为10005
bool visited[10005];//表示当前点是否被访问,为什么是10005因为题目要求2 <= n <= 10^4
int edge_len;//边的个数
int vetice_num;//顶点个数
vector<int> vetice;//包含所有顶点的vector  
int n;// 顶点个数
vector<vector<int>> edges;//边数组
vector<weight_type> weight;//权重数组，和边数组对应
//**重要，初始化图，根据题目修改相应入口参数

/**
 * @description: 初始化图
 * @param {type} //n为顶点的个数，edges为边个数，s为对应权重，start为起点，end为终点,direct是true为双向,false为单向
 * @return {type} Null
 * @author: Durant Thorvals
 */
void init_graph(int n, vector<vector<int>>& edges, vector<weight_type>& s, bool direct)
{
    this->n = n;
    this->edges = edges;
    this->weight = s;
    edge_len = edges.size();//边的个数
    vetice_num = n;
    for(int i = 0;i<edge_len;i++)
    {
        e[edges[i][0]].push_back({s[i],edges[i][1]});
        if(direct) e[edges[i][1]].push_back({s[i],edges[i][0]});//因为是双向的，所以要再加一条相反的边     
    }
    for(int i = 0; i < edge_len;i++)
    {
            if(!count(vetice.begin(),vetice.end(),edges[i][0])) vetice.push_back(edges[i][0]);
            if(!count(vetice.begin(),vetice.end(),edges[i][1])) vetice.push_back(edges[i][1]);
    }

}

/**
 * @description: //这是一个相乘求大路径版本的dijkstra
 * @param {type} start为起点，end为终点
 * @return {type} 返回到达end的最小相乘距离，若不能到达，返回-1 
 * @author: Durant Thorvals
 */
weight_type dijkstra_mul( int start, int end) {
//不能处理带负权的边
    priority_queue<pair<weight_type,int>> pq;//用一个优先队列，顶部是权重最小的，这样可以把时间复杂度降低至O((e+n)logn)
    //优先队列是按照pair的第一个元素进行排序
    //将起点的坐标放入
    vector<weight_type> minDis(vetice_num,0);//与e不同的是，存储的是最大的权重

    pq.push({1.0,start});//相乘值从1.0开始, 如果是cost从0开始
    minDis[start] = 1.0;//同上
    while(!pq.empty())//队列不为空
    {
        auto k  = pq.top();//w表示权重，v表示节点
        pq.pop();
        if(visited[k.second]) continue;//如果该节点已经访问过，则继续
        visited[k.second] = true;//标记为已经访问过
        minDis[k.second] = k.first;
        if(k.second == end) break;
        for(auto t:e[k.second])//搜寻与当前节点k相邻的所有节点
            if(!visited[t.second])//如果当前节点存在且没有被访问过
                pq.push({t.first * k.first,t.second});//则加入到优先队列之中
    }
    return minDis[end]==INT32_MIN?-1:minDis[end];
    }
/**
 * @description: //这是一个相加求大路径版本的dijkstra
 * @param {type} start为起点，end为终点
 * @return {type} 返回到达end的最小相加距离，若不能到达，返回-1 
 * @author: Durant Thorvals
 */
weight_type dijkstra_add( int start, int end) {
//n为顶点的个数，edges为边个数，s为对应权重，start为起点，end为终点,direct是true为双向,false为单向
//如果不能到达返回-1
//不能处理带负权的边
    
    priority_queue<pair<weight_type,int>> pq;//用一个优先队列，顶部是权重最小的，这样可以把时间复杂度降低至O((e+n)logn)
    //优先队列是按照pair的第一个元素进行排序
    //将起点的坐标放入
    vector<weight_type> minDis(vetice_num,INT32_MAX);//与e不同的是，存储的是最大的权重

    pq.push({0,start});//相乘值从1.0开始, 如果是cost从0开始
    minDis[start] = 0;//同上
    while(!pq.empty())//队列不为空
    {
        auto k  = pq.top();//w表示权重，v表示节点
        pq.pop();
        if(visited[k.second]) continue;//如果该节点已经访问过，则继续
        visited[k.second] = true;//标记为已经访问过
        minDis[k.second] = k.first;
        if(k.second == end) break;
        for(auto t:e[k.second])//搜寻与当前节点k相邻的所有节点
            if(!visited[t.second])//如果当前节点存在且没有被访问过
                pq.push({t.first + k.first,t.second});//则加入到优先队列之中
    }
    return minDis[end]==INT32_MIN?-1:minDis[end];
    }       
/**
 * @description: //这是一个求所有路径版本的dijkstra
 * @param {type} start为起点，end为终点
 * @return {type} 返回到达end的最小相加距离，若不能到达，返回-1 
 * @author: Durant Thorvals
 * @complexity:O(VlogV+E), where E is the number of edges, and V denotes the number of vertices.
 */

vector<weight_type> dijkstra_all(int start) {
//n为顶点的个数，edges为边个数，s为对应权重，start为起点，遍历所有边,返回一个数组，表示到达各个顶点的最小开销
//不能处理带负权的边, 因为dijkstra基于贪心策略，因而有负值容易形成环不能处理
    priority_queue<pair<weight_type,int>> pq;//用一个优先队列，顶部是权重最小的，这样可以把时间复杂度降低至O((e+n)logn)
    //优先队列是按照pair的第一个元素进行排序
    //将起点的坐标放入
    vector<weight_type> minDis(vetice_num+1,INT32_MAX);//与e不同的是，存储的是最大的权重

    pq.push({0,start});//权重值从1.0开始
    minDis[start] = 0;
    while(!pq.empty())//队列不为空
    {
        auto k  = pq.top();//w表示权重，v表示节点
        pq.pop();
        if(visited[k.second]) continue;//如果该节点已经访问过，则继续
        visited[k.second] = true;//标记为已经访问过
        minDis[k.second] = k.first;
        // if(k.second == end) break;
        for(auto t:e[k.second])//搜寻与当前节点k相邻的所有节点
            if(!visited[t.second])//如果当前节点存在且没有被访问过
                pq.push({t.first + k.first,t.second});//则加入到优先队列之中
    }
    return minDis;
}
/**
 * @description: //这是一个普通版本的dijkstra，不考虑节点是否访问问题
 * @param {type} start为起点，end为终点
 * @return {type} 返回到达end的最小相加距离，若不能到达，返回-1 
 * @author: Durant Thorvals
 * @complexity:O(VlogV+E), where E is the number of edges, and V denotes the number of vertices.
 */
template<typename T>
struct cmp
{
    bool operator()(T const &left, T const &right)
    {
    // 以y比较。输出结果为y较大的在前y相同时，先进入队列的元素在前。
        return (left.first > right.first); // left.first在后面，顶部元素first最大
    }
};
typedef pair<weight_type,int> data;
weight_type dijkstra( int start, int end) {
//不能处理带负权的边
    if(start == end ) return 0;
    //优先队列是按照pair的第一个元素进行排序
    vector<weight_type> minDis(vetice_num,INT32_MAX);//与e不同的是，存储的是最大的权重
    priority_queue<data,vector<data>,cmp<data>> pq;//用一个优先队列，顶部是权重最小的，这样可以把时间复杂度降低至O((e+n)logn)
    
    pq.push({0,start});//相乘值从1.0开始, 如果是cost从0开始
    minDis[start] = 0;//同上
    while(!pq.empty()&&pq.top().second!=end)//队列不为空
    {
        auto cur  = pq.top().second;//w表示权重，v表示节点
        pq.pop();
        for(auto t:e[cur])//搜寻与当前节点k相邻的所有节点
        {
            int dis = t.first;
            int nextnode = t.second;
            if((minDis[cur] + dis) < minDis[nextnode])
           { 
                minDis[nextnode] = minDis[cur] + dis;  
                pq.push({minDis[nextnode],nextnode});//则加入到优先队列之中
            }
        }
    }
    return minDis[end]==INT32_MIN?-1:minDis[end];
    }  
    
template<class T1, class T2> 
struct pair_hash//没这个pair 就不能在unorder——map快乐的玩耍了
{
    size_t operator() (const pair<T1, T2>& p) const
    {
        return hash<T1>()(p.first) ^ hash<T2>()( p.second);//异或思想
    }
    //如果遇到了<3,5>和<5,3>怎么办，皮神有想法，再把两个hash判断一遍
    
    bool operator()(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs) const
    {
        return equal_to<T1>()(lhs.first,rhs.first) && equal_to<T2>()(lhs.second,rhs.second);
    }
};
typedef pair<int,int> bind;
//floyd算法 O(n^3) 暴力DP，一般不推荐
weight_type floyd(int n, vector<vector<int>>& edges, vector<weight_type>& s,int start, int end){
//BLM 这是唯一的多源最短路算法，用邻接矩阵存储，可以处理负权边，但不能处理负环，只用跑一次，任意两点间最短距离能求
    unordered_map<pair<int,int>,weight_type,pair_hash<int,int>,pair_hash<int,int>> minDis;
    int edge_num = edges.size();
    for(int i = 0; i < edge_num;i++)
    {
            minDis[{edges[i][0],edges[i][1]}] = s[i];
            minDis[{edges[i][1],edges[i][0]}] = s[i];
    }    
    for(auto m:edges)//遍历中间点
        for(auto s:edges)//遍历起点
        if(m[0]!=s[0])
        for(auto e:edges)//遍历终点
        if(s[0]!=e[0])
        {
            minDis[{s[0],e[0]}] = max(minDis[{s[0],e[0]}],minDis[{s[0],m[0]}]*minDis[{m[0],e[0]}]);//状态转移方程
            minDis[{e[0],s[0]}] = max(minDis[{e[0],s[0]}],minDis[{e[0],m[0]}]*minDis[{m[0],s[0]}]);//状态转移方程
        }
    return minDis[{start,end}];        
    
}
//判断是否有负环
bool bellman_ford()
{//可以处理负权边，甚至可以处理负环，它是单源最短路算法，可以判断是否有负环
    vector<weight_type> minDis(vetice_num+1, INT32_MAX);
    for(auto &c:vetice) minDis[c] = 0;
    bool flag = false;//默认是无负环
    for(int i = 0; i < n; i++ )//进行第一步松弛操作
        for(int j = 0;j < n;j++)
        if(i!=j && minDis[vetice[j]]+e[vetice[j]][i].first < minDis[vetice[i]] )
            minDis[vetice[i]] = minDis[vetice[j]]+e[vetice[j]][i].first;
    for(auto &edge:edges)//检测松弛是否成功，对每一条边
        for(auto &neig:e[edge[0]])
        if(neig.second==edge[1] && minDis[edge[0]] + neig.first < minDis[edge[1]])
            flag = true;

    return flag;

}
//判断负环的同时找到最短路径, O(ne)时间复杂度
//1.相乘版本
weight_type spfa_mul(int start,int end)
{//spfa是bellman-ford算法的优化，开一个队列,同时引入标记
    queue<int> q;
    vector<weight_type> minDis(vetice_num+1, 0);//假设序号是连续的，出题老师没有bt到这种程度
    minDis[start] = 1.0;//原点最短路是1
    q.push(start);
    visited[start] = true;//标记为已经访问
    vector<int> cnt(vetice_num,0);//用于计算某个节点松弛的次数
    while(!q.empty())
    {
        int k = q.front();
        // if(k==end) break; 这里不能提前break，而Dijkstra可以为什么？
        q.pop();
        visited[k] = false;//擦去标记
        cnt[k]++;
        if(cnt[k]>=n) 
            {cerr<<"Nonnegative Loop Exists!"<<endl;return -1;}//如果计数大于n,表明有负环
        for(auto t:e[k])//搜寻与当前节点k相邻的所有节点
            if(minDis[t.second] < minDis[k] * t.first)//如果可以进行松弛
            {   
                minDis[t.second] = minDis[k] * t.first;
                if(!visited[t.second])//如果当前节点存在且没有被访问过
                {
                    q.push(t.second);//放到队尾
                    visited[t.second] = true;//并且标记
                }    
            }
    }
    return minDis[end]==INT32_MIN?-1:minDis[end];

}
//2.相加版本
weight_type spfa_add(int start,int end)
{//spfa是bellman-ford算法的优化，开一个队列,同时引入标记
    queue<int> q;
    vector<weight_type> minDis(vetice_num+1, INT32_MAX);//假设序号是连续的，出题老师没有bt到这种程度
    minDis[start] = 0;//原点最短路是1
    q.push(start);
    visited[start] = true;//标记为已经访问
    vector<int> cnt(vetice_num,0);//用于计算某个节点松弛的次数
    while(!q.empty())
    {
        int k = q.front();
        // if(k==end) break; 这里不能提前break，而Dijkstra可以为什么？
        q.pop();
        visited[k] = false;//擦去标记
        cnt[k]++;
        if(cnt[k]>=n) 
            {cerr<<"Nonnegative Loop Exists!"<<endl;return -1;}//如果计数大于n,表明有负环
        for(auto t:e[k])//搜寻与当前节点k相邻的所有节点
            if(minDis[t.second] > minDis[k] + t.first)//如果可以进行松弛
            {   
                minDis[t.second] = minDis[k] + t.first;
                if(!visited[t.second])//如果当前节点存在且没有被访问过
                {
                    q.push(t.second);//放到队尾
                    visited[t.second] = true;//并且标记
                }    
            }
    }
    return minDis[end]==INT32_MIN?-1:minDis[end];

}

};

int main()
{
    //浮点数如何表示
    // unsigned long aULval = 1;
    // double* aDoublePtr = (double*)&aULval;
    // printf("%f", *aDoublePtr);

    int n = 6;
    vector<vector<int>> edges ={{0,1},{0,2},{0,3},{0,4},{0,5},{1,2},{2,3},{3,4},{4,5},{1,5}};
    vector<weight_type> succProb = {2,1,5,4,3,2,1,1,4,3};
    int start = 0;
    int end = 3;
    Solution s;
    s.init_graph(n,edges,succProb,true);
    // weight_type res = s.dijkstra(start,end);
    // bool res = s.bellman_ford();
    weight_type res = s.dijkstra(start,end);
    return 0; 
     
}