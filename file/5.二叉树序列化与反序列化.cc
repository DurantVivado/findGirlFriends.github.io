#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

template <typename T> 
class Codec
{
    public:
    
    string serialize(T* root) {
        if (!root) return "";
        vector<T*> res{root};
        queue<T*> node_Q;//用于从树中解析出数字到res数组中
        string s = "[";
        node_Q.push(root);
        while (!node_Q.empty())
        {
            T *node = node_Q.front();node_Q.pop();
            if (node->left)
            {
                node_Q.push(node->left);
                res.push_back(node->left);
            }else
                res.push_back(NULL);
            if (node->right)
            {
                node_Q.push(node->right);
                res.push_back(node->right);
            }else
                res.push_back(NULL);
        }
        while(!res.back()) res.pop_back();//去掉多余的NULL
        for (auto &c:res) 
            if(c) {s += to_string(c->val);s+=",";}
            else  s += "null,";
        s.pop_back();
        s+="]";
        return s;
    }
  
  
    T* deserialize(string data) {
        //data forms like "[72,1,4,6,null,5,3,null,null,null,null,null,2]"
        //时间复杂度：O(n),空间复杂度O(3n)
        if(!data.size()) return NULL;

        vector<string> data_list;
        string num;
        bool num_flag = false;
        //将字符串转换为只含有数字和Null的数组,考虑负号和多位数
        for(int i = 0; i < data.size();i++)
        {
            if((data[i]>='0'&&data[i]<='9')||data[i]=='-')
            {
                num += data[i];
                num_flag = true;
            }
            else if(data[i] == 'n')
            {
                if(i==1) return nullptr;
                data_list.push_back("null");
                i += 3;
            }
            else if(num_flag) {data_list.push_back(num);num = "";num_flag = false;}

        }
        T *root = new T(stoi(data_list[0]));
        queue<T*> node_Q; //用于装载所有不为null的节点
        data_list.erase(data_list.begin());
        for(auto &c: data_list) 
            if (c!="null") node_Q.push(new T(stoi(c)));
            else node_Q.push(NULL);
        queue<T*> node_stack; //用于构建树结构
        node_stack.push(root);
        while (!node_stack.empty())
        {
            T * node = node_stack.front();node_stack.pop();
            if (!node) continue;
            if (!node_Q.empty()) 
            {
                node->left = node_Q.front();node_Q.pop();
                node_stack.push(node->left);
            }
            else node->left = NULL;
            if (!node_Q.empty()) 
            {    
                node->right = node_Q.front();node_Q.pop();
                node_stack.push(node->right);
            }
            else node->right = NULL;
        }
        return root;
    }
};
    
int main()
{
    string test = "[-72,1,4,6,null,5,-3,null,null,null,null,null,2]";
    Codec<TreeNode> c;
    TreeNode *root = c.deserialize(test);
    string res = c.serialize(root);
    return 0;
}