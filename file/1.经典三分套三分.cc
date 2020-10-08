//使用前，请修改文件名为非中文，谢谢 2020.7.15
//原题L1515
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class Solution {
public:
    vector<vector<int>> positions;
    double eps = 1e-6;//设置精度
    double minx, miny;
    double f( double x, double y)
    {//单谷峰值凸函数，可以用三分法求解
        double sum_dist = 0;
        for(auto &c:positions)
            sum_dist += sqrt(pow(c[0]-x,2)+pow(c[1]-y,2));
        return sum_dist;
    }
    double get_y_MinDist(double l, double r, double mx)
    {//该函数在[l,r]区间内寻找 在满足x=mx条件下 满足 (r-l)<eps 的y坐标
        double m1, m2, k1, k2;
        while((r-l) > eps)
        {
            m1 = l + (r-l)/3.0;//三分之一点
            m2 = l + (r-l)*2.0/3.0;//三分之二点
            k1 = f(mx,m1);//这里的mx和m1千万不能搞反了，前面是横坐标后面是纵坐标
            k2 = f(mx,m2);
            if(k1 < k2) r = m2;
            else l = m1;
        }
        return (l+r)/2;//注意这里是l,即y坐标
    
    }
    double get_xy_MinDist(double l, double r)
    {//该函数在[l,r]区间内不断寻找满足(r-l)<eps的子区间左端点作为x坐标，并调用get_y_MinDist进行迭代
        double m1, m2, k1, k2, L =l, R = r;
        while((r-l) > eps)
        {
            m1 = l + (r-l)/3.0;//三分之一点
            m2 = l + (r-l)*2.0/3.0;//三分之二点 注意double类型除法，除数和被除数至少有一个是double型！！！！
            k1 = f(m1,get_y_MinDist(L,R,m1));
            k2 = f(m2,get_y_MinDist(L,R,m2));
            minx = m1;
            
            if(k1 < k2) {miny = get_y_MinDist(L,R,m1);r = m2;}
            else {miny = get_y_MinDist(L,R,m2);l = m1;}
        }
        return k1;//注意这里是k1，相当于距离平方和开方f
    }
    double getMinDistSum(vector<vector<int>>& positions) {
        //因为是单谷函数，很适合采用采用三分法
        this->positions = positions;
        int lhs = 0, rhs = 100;
        return get_xy_MinDist(lhs, rhs);
    }
};

int main()
{
    vector<vector<int>> pos = {{0,1},{3,2},{4,5},{7,6},{8,9},{11,1},{2,12}};//2.8284271247461898与真实值差距较大
    Solution s;
    double res = s.getMinDistSum(pos);
    return 0;  
}