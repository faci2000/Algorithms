#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
struct part{
    int first,second,nr;
};
bool operator < (part a, part b)
{
    if(a.first<b.first)
        return true;
    if(a.first==b.first&&a.second<b.second)
        return true;
    else
        return false;
}
void KMR(vector<int> &Tab, int Tab_size)
{
    int m=1, xz=Tab_size;
    while(m*2<xz/2)
    {   Tab_size=Tab_size-m;
        vector<part> Temp_vec;
        int i=0;
        while(i<Tab_size)
        {
            part x;
            x.first=Tab[i];
            x.second=Tab[i+m];
            x.nr=i;
            Temp_vec.push_back(x);
            i++;
        }
        sort(Temp_vec.begin(),Temp_vec.end());
        {
            int nr=0;
            Tab[Temp_vec[0].nr]=0;
            for(i=1;i<Temp_vec.size();i++)
            {
                if(Temp_vec[i].first==Temp_vec[i-1].first&&Temp_vec[i].second==Temp_vec[i-1].second)
                    Tab[Temp_vec[i].nr]=nr;
                else
                {
                    nr++;
                    Tab[Temp_vec[i].nr]=nr;
                }
            }
        }
        m*=2;
    }
}
int Find(int Tab_size, vector<int> &KMR_Results)
{
        int middle=Tab_size/2;
        int pow=1;
        while(pow<middle)
            pow*=2;
        pow/=2;
        vector<part> Temp_vec;
        for(int i=0;i<Tab_size/2;i++)
        {
            part x;
            x.first=KMR_Results[i];
            x.second=KMR_Results[i+middle-pow];
            x.nr=i;//printf("%d %d %d\n",KMR_Results[i],KMR_Results[i+middle-pow],i);
            Temp_vec.push_back(x);
        }
        sort(Temp_vec.begin(),Temp_vec.end());
        for(int i=0;i<Temp_vec.size();i++)
            KMR_Results[i]=Temp_vec[i].nr;
}
void input(int length,vector<int> &Way,vector<int> &KMR_Results)
{
    int i;
    for(i=0;i<length;i++)
    {
        char temp;scanf(" %c",&temp);
        if(temp=='L')
        {
            Way[i]=1;
            KMR_Results[i]=1;
        }
        else
        {
            Way[i]=2;
            KMR_Results[i]=2;
        }
    }
    for(i=length;i<2*length;i++)
    {
        Way[i]=0;
        KMR_Results[i]=0;
    }
}
void Display(vector<int> &Way,int *Sufix,vector<int>&LCP,vector<int>&KMR_results,int length)
{
    for(int i=0;i<length;i++)
    {
        
        if(Sufix[i]!=0)
            printf("%d ",max(LCP[Sufix[i]],LCP[Sufix[i]-1]));//DEBUG MAXA!!!
        else
            printf("%d ",LCP[Sufix[i]]);
    }
    printf("\n");
}
void Do_LCP(int *Sufix,vector<int> &Way,vector<int>&LCP,vector<int>&KMR_results,int length)
{

    for(int i=0;i<length;i++)
        Sufix[KMR_results[i]]=i;
    int d=0;
    for(int i=0;i<length;i++)
    {
        d=max(d-1,0);
        if(Sufix[i]==length-1)
        {//printf("%d\n", i);
            LCP[Sufix[i]]=0;
            continue;
        }
        int place=KMR_results[Sufix[i]];
        int next_place=KMR_results[Sufix[i]+1];
        place+=d;next_place+=d;
        while(Way[place]==Way[next_place])
        {
            d++;
            place++;
            next_place++;//printf("%d %d\n",Sufix[i], d);
        }
        LCP[Sufix[i]]=d;
    }
}
int main()
{
    int St_Claus; scanf("%d",&St_Claus);
    while(St_Claus--)
    {
        int length;scanf("%d",&length);
        vector<int> Way(2*length);
        vector<int>KMR_results(2*length);
        vector<int>LCP(length);
        int Sufix[length]={};
        input(length,Way,KMR_results);
        KMR(KMR_results,2*length);
        Find(length*2,KMR_results);
        Do_LCP(Sufix,Way,LCP,KMR_results,length);
        Display(Way,Sufix,LCP,KMR_results,length);
    }
}