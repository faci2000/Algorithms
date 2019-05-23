#include<iostream>
using namespace std;
void add(int *Tab, int s, int f, int v)
{
    while(s<=f)
    {
        if(s%2==1)
        {
            Tab[s]+=v;
            s++;
        }
        if(f%2==0)
        {
            Tab[f]+=v;
            f--;
        }
        s/=2;f/=2;
    }
}
int check(int *Tab,int p)
{
    int sum=0;
    while(p>=1)
    {
        sum+=Tab[p];
        p/=2;
    }
    return sum;
}
int main()
{
    int g;cin>>g;
    while(g--)
    {
        int people,q;cin>>people>>q;
        int m=2;
        while(m<people)
            m*=2;
        int Tab[2*m]={};
        for(int i=0;i<q;i++)
        {
            char a;cin>>a;
            if(a=='E')
            {
                int s,f,v;cin>>s>>f>>v;
                add(Tab,s+m-1,f+m-1,v);
            }
            else
            {
                int p;cin>>p;
                cout<<check(Tab,p+m-1)<<endl;
            }
        }
    }
}