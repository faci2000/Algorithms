#include<cstdio>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
enum color
{
    white=0,
    grey=1,
    black=2
};
void bfs(vector<vector<int>  > &Diet, vector<color> &Colors,vector<int> &PlayerSteps, int start, color check)
{
        queue<int> Queue;
        Queue.push(start);
        Colors[start] = check;
        PlayerSteps[start]= 0;
        while(!Queue.empty())
        {
            int x= Queue.front();
            Queue.pop();
            for(int i=0;i<Diet[x].size();i++)
            {
                int y=Diet[x][i];
                if(Colors[y]!=check)
                {
                    Colors[y]=check;
                    PlayerSteps[y]=PlayerSteps[x]+1;
                    Queue.push(y);
                }
            }
        }

}
void final_calculation(int envoys,vector<int> &PlayerASteps, vector<int> &PlayerBSteps,vector<bool> &SafePoint)
{
    int catchtime=0;
    for(int i=0;i<envoys;i++)
    {
        if(SafePoint[i])
        {
            if(PlayerASteps[i]<PlayerBSteps[i])
            {
                printf("NIE\n");
                return;
            }
        }
        if(PlayerASteps[i]<PlayerBSteps[i])
            catchtime = max(catchtime,(PlayerBSteps[i]));
    }
    printf("%d\n",catchtime);
}
void dfs(vector<vector<int>  > &Diet, vector<color> &Colors, vector<int> &Level, vector<int> &Low, vector<bool> &SafePoint,
         int x)
{
    Colors[x]=grey;
    Low[x]=Level[x];
    for(int i=0;i<Diet[x].size();i++)
    {
        int y = Diet[x][i];
        if(Colors[y]==white)
        {
            Level[y]=Level[x]+1;
            dfs(Diet,Colors,Level,Low,SafePoint,y);
            if(Low[y]<=Level[x])//nie jest  mostem
            {
                SafePoint[y]=true;
                SafePoint[x]=true;
            }
            Low[x]=min(Low[x],Low[y]);        }
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
        int playerA,playerB; scanf("%d %d",&playerA, &playerB);
        playerA--;playerB--;
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
        vector<bool> SafePoint (envoys,false);
        vector<int> PlayerASteps (envoys,0);
        vector<int> PlayerBSteps (envoys,0);
        dfs(Diet,Colors,Level,Low,SafePoint,0);
        bfs(Diet,Colors,PlayerASteps,playerA,grey);
        bfs(Diet,Colors,PlayerBSteps,playerB,white);
        final_calculation(envoys,PlayerASteps,PlayerBSteps,SafePoint);
        /*for(int i=0;i<envoys;i++)
            printf("%d | ",Low[i]);
        printf("\n");
        for(int i=0;i<envoys;i++)
            printf("%d | ",Level[i]);
        printf("\n");
    for(int i=0;i<envoys;i++)
            printf("%d | ",SubtreeSize[i]);
        printf("\n");*/
    }
}

