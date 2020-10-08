#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
struct SegTreeNode{
    int start;
    int end;
    int sum;
    int lazytag;//function when the [l,r] is not completely covered in target interval
    SegTreeNode* left;
    SegTreeNode* right;
    SegTreeNode():start(0),end(0),sum(0),lazytag(0),left(NULL),right(NULL){}
    SegTreeNode(int s, int e):start(s),end(e),sum(0),left(NULL),right(NULL){}
    SegTreeNode(int s, int e, int sum):start(s),end(e),sum(sum),left(NULL),right(NULL){}

};
//构造线段树
inline void build(SegTreeNode *self, int l, int r)
{
    if(l>r) return;
    self->start = l; self->end =  r;
    if(l==r) self->sum = l;
    else
    {
        int mid = (l+r)>>1;
        self->left = new SegTreeNode();
        build(self->left,l,mid);
        self->right = new SegTreeNode();
        build(self->right,mid+1,r);
        self->sum = self->left->sum + self->right->sum;
    }
}
// //_____________________________区间查询，单点添加______________________________________________
// inline int interval_search(SegTreeNode *self, int l, int r)
// {
//     if(l<=self->start && r>=self->end)
//     {
//         return self->sum;
//     }
//     if(l>self->end || r<self->start) return 0;
//     int s = 0;
//     if(self->left->end>=l) s += interval_search(self->left, l, r); 
//     if(self->right->start<=r) s += interval_search(self->right,l ,r);
//     return s;
// }
// inline void single_add(SegTreeNode*self, int pos, int k)
// {
//     // k is the number to be added to pos-indice element
//     if(self->start == self->end)//if it is leaf, found it
//     {
//         self->sum += k;
//         return;
//     }
//     if(pos <= self->left->end) single_add(self->left, pos, k);
//     else single_add(self->right,pos,k);
//     self->sum = self->left->sum + self->right->sum;
// }
// //_____________________________区间添加，单点查询______________________________________________
// inline void interval_add(SegTreeNode* self,int i, int j,int k)
// {
//     if(i<=self->start&&self->end<=j) // if current interval is totally surrounded by target interval
//     {
//         self->sum += k;
//         return ;
//     }
//     if(self->left->end >= i) interval_add(self->left, i, j, k);
//     if(self->right->start <= j) interval_add(self->right, i, j, k);
//     self->sum = self->left->sum + self->right->sum;

// }
// int ans = 0;
// inline int single_search(SegTreeNode *self, int pos)
// {
//     if(self->start == self->end) 
//     {
//         ans = self->sum;
//         return ans;
//     }
//     if(pos <= self->left->end) single_search(self->left,pos);
//     else single_search(self->right,pos);
//     return ans;
// }
//________________________________改进的lazytag算法__________________________
void push_down(SegTreeNode *self)
{
    if(self->lazytag!=0)
    {
        self->left->lazytag += self->lazytag;
        self->right->lazytag += self->lazytag;
        int mid = (self->start + self->end)>>1;
        self->left->sum += self->lazytag*(mid - self->start + 1);
        self->right->sum += self->lazytag*(self->end - mid);
        self->lazytag = 0;
    }
}

inline void add(SegTreeNode *self, int i, int j, int k)
{
    if(i<= self->start && self->end <= j)//if current interval is not totally covered, then attach lazytag
    {
        self->sum += k*(self->end - self->start + 1);// add k according to length of interval
        self->lazytag += k;
        return;
    }
    push_down(self);
    if(self->left->end >= i) add(self->left,i,j,k);
    if(self->right->start <= j) add(self->right,i,j,k);
    self->sum = self->left->sum + self->right->sum; 
}
inline int interval_search(SegTreeNode *self, int l ,int r)
{
    if(l<=self->start && self->end<=r)
    {
        return self->sum;
    }
    if(self->left->start>r||self->right->end<l) return 0;
    push_down(self);
    int s = 0;
    if(self->left->end>=l) s+=interval_search(self->left,l,r);
    if(self->right->start<=r) s+=interval_search(self->right, l, r);
    return s;
}

int main()
{
    //单点查询，区间求和。
    SegTreeNode *st = new SegTreeNode();
    build(st, 0, 10);
    // int interval_res = interval_search(st,3,7); 
    SegTreeNode *stt = st;
    // single_add(stt,4,-1);
    // SegTreeNode *sttt = st;
    // interval_add(sttt,3,7,1);
    // int single_res = single_search(st, 4);
    add(stt,3,7,2);
    int interval_res = interval_search(st,2,6);
    return 0;
}