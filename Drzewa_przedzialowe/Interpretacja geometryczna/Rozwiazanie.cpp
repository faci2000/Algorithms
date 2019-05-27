#include<algorithm>
#include<cstdio>
#include<utility>
#include<vector>
#define offset 4194304
  
using namespace std;
struct station
{
    int l;
    int r;
    int val;
    int mod;
};

struct vertice{
    int x,y,value,connection;
};
void set_lr(vector<station> &Tab,int x,int a)
{
    if(x>=a)
    {
        Tab[x].l=x-a;
        Tab[x].r=x-a;
        return;
    }
    set_lr(Tab,x*2,a);
    set_lr(Tab,x*2+1,a);
    Tab[x].l=Tab[x*2].l;
    Tab[x].r=Tab[x*2+1].r;
}
void add(int start,int finish,int added,int x,vector<station> &Tab)
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
bool compare ( vertice a, vertice b)
{
    return (a.y<b.y);
}
bool operator < (vertice a,vertice b)
{
    if(a.x<b.x)
        return true;
    else if(a.x==b.x&&a.value>b.value)
        return true;
    else
        return false;
}
void print_tab(vector<vertice> &Verticies )
{
    for(int i=0;i<Verticies.size();i++)
    {
        printf("x: %d y: %d value: %d connection: %d\n",Verticies[i].x,Verticies[i].y,Verticies[i].value,Verticies[i].connection);
    }
    printf("\n");
}
int main()
{
    int q;scanf("%d",&q);
    while(q--)
    {
        int rectangles; scanf("%d",&rectangles);
        vector<pair<int,int> > Connect (rectangles);
        vector<vertice> Verticies (rectangles*2);
        for(int i=0;i<rectangles*2;i+=2)
        {
            pair<int,int> left_down;
            pair<int, int> right_up;
            scanf("%d %d %d %d", &left_down.first,&left_down.second,&right_up.first,&right_up.second);
            Verticies[i].x=left_down.first;
            Verticies[i].y=left_down.second;
            Verticies[i].value=1;
            Verticies[i].connection=i/2;
            Verticies[i+1].x=right_up.first;
            Verticies[i+1].y=right_up.second;
            Verticies[i+1].value=-1;
            Verticies[i+1].connection=i/2;
        }
        sort(Verticies.begin(),Verticies.end(),compare);
        //print_tab(Verticies);
        int nr=0;
        int last=Verticies[0].y;
        Verticies[0].y=nr;
        for(int i=1;i<Verticies.size();i++)
        {
            if(last==Verticies[i].y)
            {
                Verticies[i].y=nr;
            }
            else
            {
                last=Verticies[i].y;
                nr++;
                Verticies[i].y=nr;
            }
        }
        nr++;
        
        sort(Verticies.begin(),Verticies.end());//print_tab(Verticies);
        for(int i=0;i<Verticies.size();i++)
        {
            if(Verticies[i].value==1)
                Connect[Verticies[i].connection].first=i;
            else
                Connect[Verticies[i].connection].second=i;
        }
        // for(int i=0;i<Connect.size();i++)
        // {
        //     printf("begin: %d end: %d\n",Connect[i].first,Connect[i].second);
        // }
        int m=1;
        while(m<nr)
        {
            m*=2;
        }
        vector<station> Track (m*2);
        set_lr(Track,1,m);//printf("x");
        int maax=-1;
        for(int i=0;i<rectangles*2;i++)
        {
            //printf("%d %d %d\n",Field[i].begin,Field[i].end,Field[i].value);
            if(Verticies[i].value==1)
                add(Verticies[i].y,Verticies[Connect[Verticies[i].connection].second].y,/*value*/1,1,Track);
            else
                add(Verticies[Connect[Verticies[i].connection].first].y,Verticies[i].y,/*value*/-1,1,Track);
            //printf("i: %d max: %d\n",i+1,max(maax,Track[1].val));
            maax=max(maax,Track[1].val);
            
        }
        printf("%d\n",maax);
    }
}