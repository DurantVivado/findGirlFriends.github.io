>> 1584. 给定点的坐标，找到最小生成树
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
class Kruskal {
    int res,n;
    vector<int> fa;
    vector<int> rank;
public:
    struct edge
    {
        int e1, e2;//两个端点的编号
        int Mahattan_dis;//曼哈顿距离
        edge(int e1,int e2, int m):e1(e1),e2(e2),Mahattan_dis(m){}
        bool operator< (const edge& other) const
        {
            return Mahattan_dis < other.Mahattan_dis;
        }
    };
    
    int Mahattan(vector<vector<int>>& points, int i, int j)
    {
        return abs(points[i][0]-points[j][0]) + abs(points[i][1]-points[j][1]);
    }
    
    
    int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();
    init(n);
    vector<edge> edges;
    res  = 0;
    for(int i = 0; i < n;i++)
    for(int j = i+1; j < n;j++)
    {
        edges.emplace_back(i,j,Mahattan(points,i,j)); 
    }   
    sort(edges.begin(),edges.end());//按从小到大排序
    int num = n;//独立的子树的个数
    for(auto &e:edges)
    {
        if(merge(e.e1,e.e2))
        {
            res += e.Mahattan_dis;
            num--;
        }
        if(num == 1) return res;
    }
    return -1;
    
    }
    inline void init(int n)
    {
        for(int i = 0;i <= n;i++) 
        {
            fa.emplace_back(i);
            rank.emplace_back(1);
        } 
    }
    int find(int x)
    {
        if(fa[x] == x) 
            return x;
        fa[x] = find(fa[x]); 
        return fa[x];
    }
    bool merge(int i,int j)
    {//合并的两条边必须是不同子树
        int x = find(i),y = find(j);
        if(x==y) return false;
        fa[x] = y;
        return true;
    }
};

class Prim {
    //适合稠密图
    int res,n;
    vector<int> fa;
    vector<int> rank;
public:
    
    int Mahattan(vector<vector<int>>& points, int i, int j)
    {
        return abs(points[i][0]-points[j][0]) + abs(points[i][1]-points[j][1]);
    }
    typedef pair<int,int> data;
    template<typename T>
    struct cmp
    {
        bool operator()(T const &left, T const &right)
        {
        // 以y比较。输出结果为y较大的在前y相同时，先进入队列的元素在前。
            return (left.second > right.second); // left.first在后面，顶部元素first最大
        }
    };

    int minCostConnectPoints(vector<vector<int>>& points) {
    //Prim 算法又被称为加点法
    int n = points.size();
    res = 0;
    vector<bool> vis(n+1);
    //任选一个点作为起始点，没有必要构建边，
    //遍历小顶堆，每次从中取出代价最小的边，（需判断点是否已经取过，需要标记列表）
    //若最后只有一个树，或者 小顶堆为空，说明已构建完MST
    priority_queue<data,vector<data>,cmp<data>> lheap;//p1:点序号，p2:Mahattan距离，
    int start = 0, edge = 0;
    lheap.push(data(0,0));
    while(!lheap.empty() )
    {
        int next = lheap.top().first;
        if(vis[next]) {lheap.pop();continue;}//如果访问过则直接跳过
        vis[next] = true; edge+=1;
        res += lheap.top().second;
        lheap.pop();
        if(edge == n) break;
        for(int i = 0;i < n;i++)
        if(!vis[i])
        {
            lheap.push(data(i,Mahattan(points,i,next)));
        }  
        

    }
    return res;

    

    
    }
   
};
