/*
 * @Description: 
 * @Version: 2.0
 * @Autor: wangmiao
 * @Date: 2020-08-02 11:37:29
 * @LastEditors: Durant Thorvals
 * @LastEditTime: 2020-09-30 17:14:17
 */
    
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
vector<int> preorderTraversal(TreeNode* root) {
    if(!root) return {};
    vector<TreeNode*> node_stack;
    vector<int> res;
    TreeNode *node = root;
    while(node||!node_stack.empty())
    {
        while(node!=nullptr)
        {
            node_stack.push_back(node);
            res.push_back(node->val);
            node = node->left;
        }
        node = node_stack.back();node_stack.pop_back();
        
        node = node->right;
        
    }
    delete node;
    return res;
}

vector<int> inorderTraversal(TreeNode* root) {
    if(!root) return {};
    vector<TreeNode*> node_stack;
    vector<int> res;
    TreeNode *node = root;
    while(node||!node_stack.empty())
    {
        while(node!=nullptr)
        {
            node_stack.push_back(node);
            node = node->left;
        }
        node = node_stack.back();node_stack.pop_back();
        res.push_back(node->val);            
        node = node->right;
        
    }
    delete node;
    return res;
}
vector<int> postorder(TreeNode* root )
{
    if(!root) return {};
    vector<int> postorder;
    stack<TreeNode*> stack;
    TreeNode * node = root, *lastvisit = nullptr;
    while(node||!stack.empty())
    {
        while(node)
        {
            stack.push(node);
            node = node->left;
        }
        //采用一个标记记录上一次偏离的节点是否为右节点来决定是否把根节点加入到结果中
        //如果右子节点存在
        node = stack.top(); stack.pop();
        if(!node->right || lastvisit == node->right)
        {
            postorder.emplace_back(node->val);//左右节点
            lastvisit = node;
            node = nullptr;
            
        }
        else 
        {
            stack.push(node);//将根节点加入到stack
            node = node->right;
        }
        
    }
    delete node;
    delete lastvisit;
    return postorder;
}


vector<int> levelorder(TreeNode *root)
{
    if(!root) return {};
    vector<int> postorder;
    queue<TreeNode*> q;
    q.push(root);
    TreeNode *node;
    while(!q.empty())
    {
        int q_size = q.size();
        for(int i = 0;i < q_size;i++)
        {
            node = q.front();
            postorder.emplace_back(node->val);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
            delete node;
            q.pop(); 
        }

    }
    return postorder;
}

// 线索二叉树
enum Flag{
    LINK,
    CLUE,
};//设置标志位，是正常二叉树还是线索
struct ThreadTree
{
    int val;
    ThreadTree *left, *right;
    Flag left_flag, right_flag;
    ThreadTree(int x):val(x),left(nullptr),right(nullptr),left_flag(LINK),right_flag(LINK){}
    
};

void preConstruct()