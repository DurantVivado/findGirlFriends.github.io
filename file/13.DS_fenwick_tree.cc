#include <iostream>
#include <vector>
using namespace std;
struct BinTree:vector<int>
{// mainly used for calculating sums of an interval 
  explicit BinTree(int k)// By default initialize a k-size empty vector
  {
      assign(k+1, 0);// valid subscript begins at 1 not logic 0,
  }  
    int low_bit(int x)
    {//pow(2,x)
        return (x&(-x));
    }
    int sum(int k)
    {
        return (k>0)?sum(k-low_bit(k))+(*this)[k]:0;
    }
    int last()
    {
        return size()-1;
    }
    void add(int k, int w)
    {// add k to node w
        if(k > last()) return;
        (*this)[k] += w;
        add(k+low_bit(k),w);
    }   
};

int main()
{
    BinTree test(8);
    for(int i = 1; i < 8;i++)
    {
        test.add(i, i);
    }

    for(int i = 1; i < 8;i++)
    {
        cout<<test.sum(i)<<endl;
    }
    
    return 0;

}