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
void KMR(vector<vector<int>> &Tab, int Tab_size)
{
    int m=1,level=0, xz=Tab_size;
    while(m*2<xz)
    {   Tab_size=Tab_size-m;
        vector<part> Temp_vec;
        int i=0;
        while(i<Tab_size)
        {
            part x;
            x.first=Tab[i][level];
            x.second=Tab[i+m][level];
            x.nr=i;//printf("%d %d %d\n",Tab[i][level],Tab[i+m][level],i);
            Temp_vec.push_back(x);
            i++;
        }
        sort(Temp_vec.begin(),Temp_vec.end());
        {
            int nr=0;
            Tab[Temp_vec[0].nr].push_back(0);
            for(i=1;i<Temp_vec.size();i++)
            {
                if(Temp_vec[i].first==Temp_vec[i-1].first&&Temp_vec[i].second==Temp_vec[i-1].second)
                    Tab[Temp_vec[i].nr].push_back(nr);
                else
                {
                    nr++;
                    Tab[Temp_vec[i].nr].push_back(nr);
                }
            }
        }
        m*=2;level++;
    }
}
int Find(vector<vector<int>> &Tab, int Tab_size)
{
    int left=1,right=Tab_size,xz=Tab_size;
    int good=1;
    while(left<right)
    {
        int middle=(left+right)/2;
        int pow=1,level=0;
        Tab_size=xz;
        while(pow<=middle)
        {
            pow*=2;
            level++;
        }
        level--;
        pow/=2;
        Tab_size-=(middle-1);
        //printf("%d %d %d %d\n",pow,level,middle,Tab_size);
        vector<part> Temp_vec;
        for(int i=0;i<Tab_size;i++)
        {
            part x;
            x.first=Tab[i][level];
            x.second=Tab[i+middle-pow][level];
            x.nr=i;//printf("%d %d %d\n",Tab[i][level],Tab[i+middle-pow][level],i);
            Temp_vec.push_back(x);
        }
        sort(Temp_vec.begin(),Temp_vec.end());//printf("x");
        bool different=true;
        for(int i=1;i<Temp_vec.size();i++)
        {
            if(Temp_vec[i].first==Temp_vec[i-1].first&&Temp_vec[i].second==Temp_vec[i-1].second)
            {
                different=false;
                break;
            }
        }
        if(different==true)
            {
                right=middle;
                good=middle;
            }
        else
            left=middle+1;
    }
    return min(left,right);
}
int main()
{
    int Mom;scanf("%d",&Mom);
    while(Mom--)
    {
        int lines;scanf("%d",&lines);
        vector<vector<int>> Poem (lines);
        for(int i=0;i<lines;i++)
        {
            int temp; scanf("%d",&temp);
            Poem[i].push_back(temp);
        }
        KMR(Poem,lines);
        printf("%d\n",Find(Poem,lines));
    }

}