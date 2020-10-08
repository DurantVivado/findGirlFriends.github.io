/*
 * @Description: 
 * @Version: 2.0
 * @Autor: wangmiao
 * @Date: 2020-10-05 15:58:07
 * @LastEditors: Durant Thorvals
 * @LastEditTime: 2020-10-06 23:10:49
 */

// 高斯消元法
#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;
class Math
{public:
    int gcd(int a, int b)
    {
        return (!b)?a:gcd(b,a%b);
    }

    int lcm(int a, int b)
    {
        return a/gcd(a,b)*b;
    }
    int Gauss(vector<vector<int>> &matrix, vector<int> b)
    {
    /**
     * @description: 利用Gauss消元法解方程
     * @param matrix为系数矩阵 
     * @return {type} None
     * @author: Durant Thorvals
     * @complexity: Time:O(1),Space:O(1)
     */    

    }

};

int main()
{
    Math s;
    int N = 3;
    return 0;
}