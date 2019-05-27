#include<cstdio>
#include<vector>
using namespace std;
void wyp(vector<vector<bool> > &Tab,int cities/*,int a, int b*/)
{
   // printf("%d %d\n",a,b);
    for(int i=0;i<(1<<cities);i++)
    {
        for(int j=0;j<cities;j++)
        {
            if(Tab[i][j]==true)
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
    printf("\n");
}
int main()
{
    int f;scanf("%d",&f);
    while(f--)
    {
        int cities, routes;scanf("%d %d",&cities,&routes);
        vector<vector<bool> > Connections (cities+1,(vector<bool> (cities+1,false)));
        for(int i=0;i<routes;i++)
        {
            int temp_1, temp_2;scanf("%d %d",&temp_1,&temp_2);
            Connections[temp_1][temp_2]=true;
            Connections[temp_2][temp_1]=true;
        }
        vector<vector<bool> > Tab ((1<<cities),(vector<bool> (cities,false)));
        for(int s=0;s<(1<<cities);s++)
        {
            for(int x=0;x<cities;x++)
            {
                if((s&(1<<x))!=0)
                    Tab[s][x]=true;
            }
        }

        for(int s=0;s<(1<<cities);s++)
        {
            for(int x=0;x<cities;x++)
            {
                if((s&(1<<x))!=0)
                {
                    Tab[s][x]=false;
                    if(s==(1<<x)&&Connections[0][x+1]==true)
                         Tab[s][x]=true;
                    for(int y=0;y<cities;y++)
                    {
                        if((y!=x)&&(s&(1<<y))&&(Connections[x+1][y+1]==true)&&(Tab[s-(1<<x)][y]==true))
                            Tab[s][x]=true;
                    }
                }

            }
        }
        //wyp(Tab,cities);
        int a=-1,b=0;
        for(int i=0;i<cities;i++)
        {
            if(Tab[(1<<cities)-1][i]==true&&Connections[0][i+1]==true)
            {
                printf("TAK\n");
                a=((1<<cities)-(1<<i));
                b=i;
                printf("%d ",i+1);
                break;
            }
        }
        if(a==-1)
            printf("NIE\n");
        while(a>1)
        {
            for(int i=0;i<cities;i++)
            {
                if(Tab[a-1][i]==true&&Connections[b+1][i+1])
                {
                    a=(a-(1<<i));
                    b=i;
                    printf("%d ",i+1);
                    break;
                }
            }
        }
        if(a!=-1)
            printf("\n");
    }

}
