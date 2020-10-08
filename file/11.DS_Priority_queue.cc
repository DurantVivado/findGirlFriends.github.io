#include <functional>
#include <queue>
#include <vector>
#include <iostream>
 
template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n'; longlongmin
}
// pair为键值想top为最小元素怎么办 
template<typename T>
struct cmp
{
    bool operator()(T const &left, T const &right)
    {
    // 以y比较。输出结果为y较大的在前y相同时，先进入队列的元素在前。
        if(left.first == right.first) return (left.second > right.second);
        return (left.first < right.first); // left.first在后面，顶部元素first最大
    }
};

int main() {
    std::priority_queue<int> q;
    q.emplace()
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q.push(n);
 
    print_queue(q);
 
    std::priority_queue<int, std::vector<int>, std::greater<int> > q2;
 
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q2.push(n);
 
    print_queue(q2);
 
    // 用 lambda 比较元素。
    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
 
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q3.push(n);
 
    print_queue(q3);
 
}
//自定义数据类型
struct node
    {
        int x, y;
        node(int i, int j):x(i),y(j){}
    };

struct cmp
{
    bool operator()(node const &left, node const &right)
    {
    // 以y比较。输出结果为y较大的在前y相同时，先进入队列的元素在前。
        if (left.y == right.y)
            return left.x > right.x;
        return (left.y > right.y);
    }
};
class Solution {
public:
    
    
    
    vector<vector<int>> res;
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        if(!people.size()) return {};
        //思路，每次找到数组中k最小的数排在前面，如果k相同，那么身高要尽可能大

        priority_queue<node,vector<node>,cmp> pq;
        for(auto &p:people) 
            pq.push(node(p[0],p[1]));
        while(!pq.empty()) 
        {
            res.push_back({pq.top().x,pq.top().y});
            pq.pop();
        }
        return res;
    }
};