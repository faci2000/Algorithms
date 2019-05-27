#include<cstdio>
#include<vector>
#include<stack>
#include<utility>
using namespace std;
enum color
{
    white=0,
    grey=1,
    black=2
};
void calculate(vector<vector<int>  > &Diet, vector<int> &SubtreeSize, vector<bool> &ArticulationPoint,  vector<bool> &FallAway, vector<int> &Level, int envoys)
{
    for(int i=0;i<envoys;i++)
    {
        int long long rest=envoys-1,answer=0;
        if(ArticulationPoint[i])
        {
            for(int j=0;j<Diet[i].size();j++)
            {
                if(FallAway[Diet[i][j]]&&(Level[Diet[i][j]]>Level[i]))
                {
                    answer+=(long long int)SubtreeSize[Diet[i][j]]*(SubtreeSize[Diet[i][j]]-1);
                    rest-=SubtreeSize[Diet[i][j]];
                }
            }
            printf("%lld\n",(long long int)answer+(rest*(rest-1)));
        }
        else
            printf("%lld\n",(long long int)(envoys-1)*(envoys-2));
    }
}
void dfs(vector<vector<int>  > &Diet, vector<color> &Colors, vector<int> &Level, vector<int> &Low, vector<bool> &ArticulationPoint,
         vector<int> &SubtreeSize, stack<pair<int,int> > &TempSubtree, vector<bool> &FallAway, int x)
{
    Colors[x]=grey;
    Low[x]=Level[x];
    for(int i=0;i<Diet[x].size();i++)
    {
        int y = Diet[x][i];
        if(Colors[y]==white)
        {
            pair<int,int> temp; temp.first=x; temp.second = y;
            TempSubtree.push(temp);
            Level[y]=Level[x]+1;
            dfs(Diet,Colors,Level,Low,ArticulationPoint,SubtreeSize,TempSubtree,FallAway,y);
            if((x>0&&Low[y]>=Level[x])||(x==0&&Low[y]>=Level[x]&&i>0)||(x==0&&Low[y]>Level[x]&&i==0))
            {
                ArticulationPoint[x]=true;
                FallAway[y]=true;
                while(TempSubtree.top().first!=x)
                {
                    SubtreeSize[y]++;
                    TempSubtree.pop();
                }
                SubtreeSize[y]++;
                TempSubtree.pop();

            }
            Low[x]=min(Low[x],Low[y]);
            SubtreeSize[x]+=SubtreeSize[y];
        }
        if(Colors[y]==grey&&Level[x]-1!=Level[y])
        {
            Low[x]=min(Low[x],Level[y]);
        }
    }
    Colors[x]=black;
}
int main()
{
    int xd;scanf("%d", &xd);
    while(xd--)
    {
        int envoys,friendships; scanf("%d %d", &envoys, &friendships);
        vector<vector<int>  > Diet (envoys);
        for(int i=0;i<friendships;i++)
        {
            int temp_1,temp_2; scanf("%d %d", &temp_1, &temp_2);
            Diet[temp_1-1].push_back(temp_2-1);
            Diet[temp_2-1].push_back(temp_1-1);
        }
        vector<color> Colors (envoys,white);
        vector<int> Level (envoys,0);
        vector<int> Low (envoys);
        vector<bool> ArticulationPoint (envoys,false);
        vector<bool> FallAway (envoys,false);
        vector<int> SubtreeSize (envoys,0);
        stack<pair<int,int> > TempSubtree;
        dfs(Diet,Colors,Level,Low,ArticulationPoint,SubtreeSize,TempSubtree,FallAway,0);
        /*for(int i=0;i<envoys;i++)
            printf("%d | ",Low[i]);
        printf("\n");
        for(int i=0;i<envoys;i++)
            printf("%d | ",Level[i]);
        printf("\n");
    for(int i=0;i<envoys;i++)
            printf("%d | ",SubtreeSize[i]);
        printf("\n");*/
        calculate(Diet,SubtreeSize,ArticulationPoint,FallAway,Level,envoys);
    }
}
