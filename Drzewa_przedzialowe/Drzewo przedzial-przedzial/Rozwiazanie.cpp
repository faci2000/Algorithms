#include<iostream>
using namespace std;
struct station
{
    int l;
    int r;
    int val;
    int mod;
};
void set_lr(station *Tab,int x,int m)
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
void add(int start,int finish,int added,int x,station *Tab)
{
    if(Tab[x].l==start&&Tab[x].r==finish)
    {
        Tab[x].mod+=added;
        Tab[x].val+=added;
        return;
    }
    else
    {
        int c=(Tab[x].l+Tab[x].r)/2;
        if(start<=c)
            add(start,min(finish,c),added,2*x,Tab);
        if(finish>c)
            add(max(start,c+1),finish,added,2*x+1,Tab);
    }
    Tab[x].val=max(Tab[2*x].val,Tab[2*x+1].val)+Tab[x].mod;
}
int maax(int start,int finish,int x,station *Tab)
{
    //cout<<Tab[x].l<<" "<<Tab[x].r<<" || "<<start<<" "<<finish<<endl;
    int w_1=0,w_2=0;
    if(Tab[x].l==start&&Tab[x].r==finish)
        return Tab[x].val;
    else
    {
        int c=(Tab[x].l+Tab[x].r)/2;
        //cout<<c<<endl;
        if(start<=c)
            w_1=maax(start,min(finish,c),2*x,Tab);
        if(finish>c)
            w_2=maax(max(start,c+1),finish,2*x+1,Tab);
    }
    return max(w_1,w_2)+Tab[x].mod;
}
int main()
{
    int q;cin>>q;
    while(q--)
    {
        int cities,seats,asks; cin>>cities>>seats>>asks;
        int m=1;
        while(m<cities-1)
            m*=2;
        station Track[m*2]={};
        set_lr(Track,1,m);
        //cout<<Track[asks].l<<" "<<Track[asks].r<<endl;
        for(int i=0;i<asks;i++)
        {
            int start,finish,people;cin>>start>>finish>>people;
            //cout<<"m:"<<maax(start-1,finish-2,1,Track)<<endl;
            if(maax(start-1,finish-2,1,Track)>seats-people)
            {
                cout<<"N"<<endl;
                continue;
            }
            else
            {
                cout<<"T"<<endl;
                add(start-1,finish-2,people,1,Track);
            }
        }
    }
}