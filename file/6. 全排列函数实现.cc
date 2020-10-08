#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

    template<class T>
    bool nextPermutation_demo(vector<T>& nums) {
        if(!nums.size()) return false;
        int n = nums.size();
        int curr = n-1, pre = curr - 1;
        for(;pre>=0 && nums[curr] <= nums[pre];curr--,pre--);//找到第一个nums[pre]<nums[curr]的数
        if(pre<0)
        {
         reverse(nums.begin(),nums.end());
         return false;//说明为字典序最大数
        }//再从尾部开始找到第一个比pre大的数 
        for(curr = n-1; nums[curr] <= nums[pre];curr--  );
        //交换nums[curr]与nums[pre]
        swap(nums[curr],nums[pre]);
        reverse(nums.begin()+pre+1,nums.end());
        return true;

    }


int main()
{
    vector<int> nums{1,3,2};//{2,2,7,5,4,3,2,2,1};//{7,6,9,8,7,7,7,6,5,0};//{7,6,9,8,7,7,7};//{1,3,2};//
    bool res = nextPermutation_demo(nums);
    return 0;
}
