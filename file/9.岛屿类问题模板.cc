#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int m,n;//岛屿的尺寸
    const vector<vector<int>> direct = {{-1,0},{1,0},{0,1},{0,-1}};
    
    bool outRange(int x, int y)
    {
        return (x>=m||y>=n||x<0||y<0) ;//越界检查
    }
    void dfs(int x, int y,vector<vector<char>>& board)
    {//act表明现在的状态：1. 处于陆地x，为寻找下一个湖状态 2. 处于封闭湖中 3. 处于开放湖中
     // 默认处于封闭湖中
        if(outRange(x,y)||board[x][y]!='O') return;
        board[x][y] = 'A';
        
        for(auto &d:direct)
        {
            dfs(x+d[0],y+d[1],board);
        }

    }
    void solve(vector<vector<char>>& board) {
    m = board.size(); n = board[0].size();
  
    for(int x = 0; x < m; x++)
    for(int y = 0; y < n; y++)
    ·····
    }
};
int main()
{
    vector<vector<char>> board ={{'X','X','X','X'},
                                 {'X','O','O','X'},
                                 {'X','X','O','X'},
                                 {'X','O','X','X'}};
    Solution s;
    s.solve(board);
    return 0;
}