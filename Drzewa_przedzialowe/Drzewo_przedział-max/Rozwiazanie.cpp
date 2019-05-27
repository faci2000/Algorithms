#include<stdio.h>
#include<iostream>
using namespace std;
struct cell
{
    int l,r;
    int val,mod;
    bool active_m=0;
    bool active_v=0;
};
void set_lr(cell *Tab,int x,int m)
{
    if(x>=m)
    {
        Tab[x].l=x-m;
        Tab[x].r=x-m;
        return;
    }
    set_lr(Tab,x*2,m);
    set_lr(Tab,x*2+1,m);
    Tab[x].l=Tab[x*2].l;
    Tab[x].r=Tab[x*2+1].r;
}
void lazy(cell *Tab,int x,int mx)
{
    Tab[x].active_m=0;
    Tab[2*x].mod=mx;
    //Tab[2*x].val=max(Tab[2*x].mod,Tab[2*x].val);
    Tab[2*x].active_m=1;
    Tab[2*x+1].mod=mx;
    //Tab[2*x+1].val=max(Tab[2*x+1].mod,Tab[2*x+1].val);
    Tab[2*x+1].active_m=1;
    Tab[x].mod=0;
}
int maax(int start,int finish,int x,cell *Tab)
{
    int w_1=0,w_2=0;
    if(Tab[x].l==start&&Tab[x].r==finish)
        return Tab[x].val;
    else
    {
        if(Tab[x].active_v==1)
        {
            Tab[x].active_v=0;
            Tab[2*x].val=Tab[x].val;
            Tab[2*x].active_v=1;
            Tab[2*x+1].val=Tab[x].val;
            Tab[2*x+1].active_v=1;
        }
        int c=(Tab[x].l+Tab[x].r)/2;
        if(start<=c)
            w_1=maax(start,min(finish,c),2*x,Tab);
        if(finish>c)
            w_2=maax(max(start,c+1),finish,2*x+1,Tab);
    }
    return max(w_1,w_2);
}
void add(cell *Tab, int start,int finish,int x,int mx)
{
    if(Tab[x].l==start&&Tab[x].r==finish)
    {

            Tab[x].mod=(mx+1);
            Tab[x].val=(mx+1);
            Tab[x].active_m=1;
            Tab[x].active_v=1;
            return;
    }
    else
    {   if(Tab[x].active_m==1)
            lazy(Tab,x,mx);

        int c=(Tab[x].l+Tab[x].r)/2;
        if(start<=c)
            add(Tab,start,min(finish,c),2*x,mx);
        if(finish>c)
            add(Tab,max(start,c+1),finish,2*x+1,mx);
    }
    Tab[x].val=max(Tab[2*x].val,Tab[2*x+1].val)+Tab[x].mod;
}
int main()
{
    int sizee,blocks; scanf("%d %d",&sizee,&blocks);
    int m=1;
    while(m<sizee)
        m*=2;
    cell Tab[2*m]={};
    set_lr(Tab,1,m);
    for(int i=0;i<blocks;i++)
    {
        int left, right; scanf("%d %d",&right,&left);
        right+=(left-1);
        int mx=maax(left,right,1,Tab);
        //cout<<mx<<endl;
        add(Tab,left,right,1,mx);
    }
    printf("%d",Tab[1].val, "\n");
}