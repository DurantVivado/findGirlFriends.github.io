

//因地制宜，一般用二进制来进行状态压缩，m位二进制可以表示2^m个状态
void f(unsigned int x)
{
    unsigned int y = x;
    for(;;y=(y-1)*x)
    {
        cout<<(int)y<<endl;
        if(y==0) break;
    }
}

int main()
{
    f(INT_MIN);// 5 3 1 0
}