//FSA模板
#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
class Solution {
public:
    enum state
    {
        //列举你所有的转移状态

        STATE_INIT,
        // // STATE_SPACE,
        // STATE_SIGN,
        // STATE_INTEGER,
        // STATE_POINT_INT,
        // STATE_POINT_NOT_INT,
        // STATE_DECIMAL,
        // STATE_EXP,
        // STATE_EXP_SIGN,
        // STATE_EXP_INT,
        STATE_END,
    };
    enum charType
    {
        //列举你所有数据状态，一般是char，string
        // CHAR_NUM,
        // CHAR_SPACE,
        // CHAR_POINT,
        // CHAR_EXP,
        // CHAR_SIGN,
        // CHAR_INVALID,
    };
    charType getCharType(char ch)
    {//数据分析，返回枚举类型
        // if(ch>='0'&&ch<='9') return CHAR_NUM;
        // else if (ch == ' ') return CHAR_SPACE;
        // else if(ch == '.') return CHAR_POINT;
        // else if(ch == 'E'||ch == 'e') return CHAR_EXP;
        // else if (ch=='+'||ch=='-') return CHAR_SIGN;
        // else return CHAR_INVALID;
    }
    YourReturnType YourFunc(string s) {
        //定义初始状态
        state sta = STATE_INIT;
        //用哈希表存储状态转移方程
        unordered_map<state,unordered_map<charType,state>> transfer{
            {
                STATE_INIT, {{CHAR_SPACE,STATE_INIT},
                            {CHAR_SIGN, STATE_SIGN},
                            {CHAR_NUM, STATE_INTEGER},
                            {CHAR_POINT,STATE_POINT_NOT_INT}
            }},
            {
                STATE_SIGN,{{CHAR_NUM, STATE_INTEGER},
                           {CHAR_POINT, STATE_POINT_NOT_INT},
            }},
            {
                STATE_DECIMAL,  {{CHAR_NUM, STATE_DECIMAL},
                                {CHAR_EXP, STATE_EXP},
                                {CHAR_SPACE, STATE_END}
            }},
            {
                STATE_INTEGER,  {{CHAR_NUM, STATE_INTEGER},
                                {CHAR_EXP,STATE_EXP},
                                {CHAR_POINT,STATE_POINT_INT},
                                {CHAR_SPACE,STATE_END}
            }},
            {
                STATE_POINT_NOT_INT,{{CHAR_NUM, STATE_DECIMAL}
            }},
            {
                STATE_POINT_INT,{{CHAR_SPACE,STATE_END},
                                {CHAR_NUM,STATE_DECIMAL},
                                {CHAR_EXP,STATE_EXP}
            }},
            {
                STATE_EXP,  {{CHAR_SIGN, STATE_EXP_SIGN},
                            {CHAR_NUM, STATE_EXP_INT}
            }},
            {
                STATE_EXP_SIGN,{{CHAR_NUM, STATE_EXP_INT}
            }},
            {
                STATE_EXP_INT,{{CHAR_NUM,STATE_EXP_INT},
                                {CHAR_SPACE,STATE_END}}
            },
            {
                STATE_END,{{CHAR_SPACE,STATE_END},}
            }
        };
    
        for(int i = 0; i < len; i++)
        {
            charType ct = getCharType(s[i]);
            //如果是非法状态，直接返回false
        
            if(!transfer[sta].count(ct)) return false;
            sta = transfer[sta][ct];
            
        } 
        //根据结束状态返回
        return sta == STATE_END || sta == STATE_INTEGER || sta == STATE_POINT_INT || sta == STATE_DECIMAL|| sta == STATE_EXP_INT;
    }
};