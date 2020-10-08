/*
 * @Description: 
 * @Version: 2.0
 * @Autor: wangmiao
 * @Date: 2020-06-17 21:43:38
 * @LastEditors: Durant Thorvals
 * @LastEditTime: 2020-09-30 11:04:55
 */
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <forward_list>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(NULL){};
    
};

// typedef struct LNode{  
//  int data;  
//  struct LNode *next;  
// }LNode,*LinkList;//则定义LinkList L;时，L为链表的头指针。  


class Linkedlist {
public:
    ListNode* initLinked(vector<int> arr)
    {
        if(!arr.size()) return nullptr;
        ListNode *head = new ListNode(arr[0]);
        ListNode *temp = head;
        for(int i = 1;i < arr.size();i++)
        {
            head->next = new ListNode(arr[i]);
            head = head->next;
        }
        return temp;
    }
    ListNode* reverseList(ListNode* head) {
        //Official method2: regression
        if(!head || !head->next) return head;
        ListNode *nextnode = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;   
        return nextnode;
    }
    //——————————————————————————————————————————————————————————————————————————————————————————————————
    void printLinked(ListNode *head)
    {
        if(!head) return ;
        ListNode *temp = head;
        while(temp)
        {
            cout<<temp->val<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
  
};


int main()
{
    // 创建含整数的 list
    std::list<int> l = { 7, 5, 16, 8 };
//     //双向链表
//     std::list 是支持常数时间从容器任何位置插入和移除元素的容器。不支持快速随机访问。它通常实现为双向链表。与 std::forward_list 相比，此容器提供双向迭代但在空间上效率稍低。

// 在 list 内或在数个 list 间添加、移除和移动元素不会非法化迭代器或引用。迭代器仅在对应元素被删除时非法化。
    std::forward_list<int> fl = {1,2,4,3,2};
//  td::forward_list 是支持从容器中的任何位置快速插入和移除元素的容器。不支持快速随机访问。它实现为单链表，且实质上与其在 C 中实现相比无任何开销。与 std::list 相比，此容器在不需要双向迭代时提供更有效地利用空间的存储。
    // 添加整数到 list 开头
    l.push_front(25);
    // 添加整数到 list 结尾
    l.push_back(13);
 
    // 以搜索插入 16 前的值
    auto it = std::find(l.begin(), l.end(), 16);
    if (it != l.end()) {
        l.insert(it, 42);
    }
 
    // 迭代并打印 list 的值
    for (int n : l) {
        std::cout << n << '\n';
    }
}