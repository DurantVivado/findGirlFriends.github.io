//获取数组哈希编码
//f(a)=\sum\limits_{i=0}^{n-1}b^i×a_i(mod \ P)
#include <queue>
#include <vector>
#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

vector<int> temp;
const int MIN_VAL = -100;
const int MAX_VAL = 100;
int getHash(int base, int mod)
{//这里的base为数组的最大值, min_val 为数组可能最小值，题目给出,为了避免负数的情况
//这里的mod 是一个大素数
//时间复杂度 O(N) 慎用
    int hashVal = 0;
    for(auto &c:temp)
    {
        hashVal = 1LL*hashVal*base % mod + (c - MIN_VAL + 1);  
        hashVal %= mod;
    }
    return hashVal;

}
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
    
    //此题即为删除最短无序子数组
    //我们需要找到一个开区间(i,j)，满足arr[i]<<arr[j]，且[0,i]和[j,n-1]是增序，返回(j-i-1)
    //需要考虑完全正序的情况
    stack<int> mono;
    int res = 0, n = arr.size();
    mono.push(arr[0]);
    for(int i = 1;i < n;i++)
    {
        if(arr[i] < arr[i-1])
        {
            mono.pop();//将前一个元素弹出
            res++;
        }
        // cout<<mono.top()<<endl;
        if(arr[i]>=mono.top()) mono.push(arr[i]);
        else res++;
        
    }
    return res;
    }
};
int func()
{
    int hashValue = getHash(263, (int)(1E9)+7);
}

int main()
{
    Solution s;
    vector<int> arr = {5,4,3,2,1};
    auto res = s.findLengthOfShortestSubarray(arr);
    return 0;
}