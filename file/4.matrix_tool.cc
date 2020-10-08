#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
//给vector类型的二维矩阵进行打印
template<class T>
void printMatrix(vector<vector<T>> &mat)
{
    if(!mat.size()||!mat[0].size()) return;
    for(int i = 0;i < mat.size();i++)
    {   cout<<mat[i]<<",";
    cout<<endl; 
    }
    cout<<endl;
}

template <class T>
ostream& operator<<(ostream& ostr, const vector<T>&x){
if (x.size()==0){
    ostr<<"[]";
    return ostr;
}
ostr<<"["<<x[0];
for (int i = 1; i < x.size(); ++i){
    ostr<<", "<<x[i];
}
ostr<<"]";
return ostr;
}

int main()
{
    vector<vector<int>> matrix{{1,2,3},{4,5,6},{7,8,9}};
    printMatrix<int>(matrix);
    // cout<<matrix<<endl;
    // vector<int> a{1,2,3};
    // cout<<a<<endl;
    return 0;
}