/*
 * @Description: Prefix Sum Utility
 * @Version: 2.0
 * @Autor: Durant
 * @Date: 2020-10-02 16:55:11
 * @LastEditors: Durant Thorvals
 * @LastEditTime: 2020-10-02 22:49:21
 */

#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class PrefixSum
{
    public:
    int lowbit(int x){return x&(-x);}
    long long lowbit(long long x){return x&(-x);}
    vector<int> genPrefixSum(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> prefixSum;
        prefixSum.push_back(nums[0]);
        for(int i = 1; i < n;i++)
            prefixSum.push_back(prefixSum[i-1] + nums[i]);
        return prefixSum;
    }
    vector<long long > genPrefixSum(vector<long long>& nums)
    {
        int n = nums.size();
        vector<long long> prefixSum;
        prefixSum.push_back(nums[0]);
        for(int i = 1; i < n;i++)
            prefixSum.push_back(prefixSum[i-1] + nums[i]);
        return prefixSum;
    }
    
};

int main()
{
    PrefixSum p;
    vector<int> nums = {1,2,3,4,5};
    auto res = p.genPrefixSum(nums);
    return 0;
}