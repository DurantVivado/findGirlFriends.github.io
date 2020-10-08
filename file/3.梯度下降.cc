//梯度下降
#include <vector>
#include <iostream>
using namespace std;
class GradientDescent
{
    vector<vector<double>> positions;
    double f(double x, double y)
    {

    }
    vector<double> getDerivative(double x, double y)
    {//对 (x,y)到position点集中任意一点的导数再求和
    }

    double getMinDistSum_GradDescent(vector<vector<double>> &positions)
    {
        this->positions = positions;
        int n = positions.size();//点的个数
        double x = 0.0, y = 0.0;
        double lr = 0.1;//学习率
        double alpha = 0.99;//学习率衰减因子
        for(auto &c: positions)
        {
            x += c[0];
            y += c[1];
        }
        x = x/n; y = y/n;//算术平均点
        long maxloop = 30000;//最大迭代次数
        double cost0 = f(x,y);//初始的cost
        double min_x, min_y;
        double epsilon = 1e-8;//最小精度
        while((maxloop--)>0)
        {
            printf("iter:%ul\n",maxloop);
            vector<double> k = getDerivative(x,y);
            double dx = k[0], dy = k[1];
            x -= dx*lr;// 按梯度下降，很熟悉有木有
            y -= dy*lr;
            printf("x:%.3f, y:%.3f,lr:%.6f, cost:%.6f\n",x ,y,lr , cost0);
            
            double cost1 = f(x,y);
            if((cost0 - cost1) >= epsilon)
            {
                cost0 = cost1; //更新最短距离
                min_x = x;
                min_y = y;
            }
            else if((cost0 - cost1) < 0)// 说明学习率大了，要降低学习率
            {
                lr *= alpha;
                if(lr==0) break;
            }
            else
            {
                break;
            }
    
        }
        return cost0;

    }

};

