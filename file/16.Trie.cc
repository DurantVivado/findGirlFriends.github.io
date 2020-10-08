//字典树，或前缀树模板
#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
class Trie {
public:
    /** Initialize your data structure here. */
    vector<Trie*> child;
    bool end;//结束的标志，表示在该节点结束
    char val; 
    Trie() {
        val = ' ';
        end = false;
        child.resize(26);
    }
    Trie(char c) {
        val = c;
        end = false;
        child.resize(26);
    }
    
    void _insert(Trie* node, string word, int i)
    {
        if(i>=word.size()) {node->end=true;return;}   
        auto &n = node->child[(int)(word[i]-'a')];
         n = (n==nullptr)?new Trie(word[i]):n;
        _insert(n,word,i+1);
    }
    /** Inserts a word into the trie. */
    void insert(string word) {
        //root does not save char
        if(!this) return;
        _insert(this,word,0);
    }
    
    /** Returns if the word is in the trie. */
    void _search(string mode, Trie *node, string s, int i,bool &isExist)
    {//递归搜索，s为字符串，i为编号
      // 上一个字符搜索到了才进行下一次搜索
       if(i<s.size()&&node->child[(int)(s[i]-'a')] &&node->child[(int)(s[i]-'a')]->val==s[i]&&!isExist) 
        _search(mode,node->child[(int)(s[i]-'a')],s,i+1,isExist);
        if(!isExist)
        if(mode == "search") isExist = (i==s.size()&&node->end);
        else isExist = (i==s.size());
    }
    bool search(string word) {
        if(!this) return false;
        bool isExist = false;
        _search("search",this,word,0,isExist);
        return isExist;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    
    bool startsWith(string prefix) {
        if(!this) return false;
        bool isExist = false;
        _search("prefix",this,prefix,0,isExist);
        return isExist;
    }
};
int main(){

    Trie* trie = new Trie();

    trie->insert("apple");
    bool a= trie->search("applepie");   // 返回 true
    bool b =trie->search("app");     // 返回 false
    bool c = trie->startsWith("app"); // 返回 true
    trie->insert("app");   
    bool d = trie->search("app");     // 返回 true
    return 0;
}
/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */