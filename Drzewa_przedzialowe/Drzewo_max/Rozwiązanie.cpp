#include<iostream>
#include<string>
#define inf -2147483647
using namespace std;
int maax(int *Tab,int a,int b)
{
    int x=inf;
    while(a<=b)
    {
        if(a%2==1)
        {
             x=max(x,Tab[a]);
             a++;
        }
        if(b%2==0)
        {
            x=max(x,Tab[b]);
            b--;
        }
        a=a/2;b=b/2;
    }
    return x;
}
void update(int *Tab,int a, int b)
{
    Tab[a]=b;
    a=a/2;
    while(a>=1)
    {
        Tab[a]=max(Tab[2*a],Tab[2*a+1]);
        a=a/2;
    }
}
int main()
{
    int g;cin>>g;
    while(g--)
    {
        int taxes, q; cin>>taxes>>q;
        int m=1;
        while (m<taxes)
            m=m*2;
        int Tab[2*m];
        for(int i=m;i<2*m;i++)
            Tab[i]=inf;
        for (int i=m;i<taxes+m;i++)
            cin>>Tab[i];
        for(int i=m-1;i>0;i--)
            Tab[i]=max(Tab[2*i],Tab[2*i+1]);
        for(int i=0;i<q;i++)
        {
            string s;cin>>s;
            int a,b;cin>>a>>b;
            if(s[0]=='M')
                cout<<maax(Tab,a+m-1,b+m-1)<<endl;
            else
              update(Tab,a+m-1,b);
        }
    }

}
