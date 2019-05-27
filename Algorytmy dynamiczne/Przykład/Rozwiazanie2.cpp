#include<cstdio>
#include<vector>
#include<algorithm>
//2147483647
using namespace std;
class Roads
{
	int map_size;
	vector<vector<long long int> > Map;
	vector<long long int> Cost;
	vector<bool> Check;
	vector<long long int> Order;
	vector<long long int> With;
	vector<long long int> Without;
	vector<bool>Take;
	public:
		Roads(int s)
		{
			map_size=s;
			Map.resize(map_size);
			Cost.resize(map_size);
			Check.resize(map_size,false);
			Take.resize(map_size,false);
			With.resize(map_size,0);
			Without.resize(map_size,0);
		}
		void input()
		{
			for(int i=0;i<map_size;i++)
			{
				 int temp;scanf("%d",&temp);
				Cost[i]=temp;
			}
			for(int i =0;i<map_size-1;i++)
			{
				int temp_1,temp_2;scanf("%d %d",&temp_1,&temp_2);
				Map[temp_1-1].push_back(temp_2-1);
				Map[temp_2-1].push_back(temp_1-1);
			}
		}
		void dfs_right(int x)
      	{
        	Check[x]=true;
       		for(int i=0;i<Map[x].size();i++)
       	   	{
            	if(Check[Map[x][i]]==false)
                	dfs_right(Map[x][i]);
          	}
          	Order.push_back(x);
      	}
      	void order()
      	{
          	for(int i=0;i<map_size;i++)
        	{
              if(Check[i]==false)
                dfs_right(i);
          	}
      	}
      	void calculate()
      	{
      		for(int i=0;i<map_size;i++)
      		{
	      		int current=Order[i];
				long long int with=Cost[current];
				long long int without=0;
				for(long long j=0;j<Map[current].size();j++)
				{
					without=(long long int)((long long int)With[Map[current][j]]+(long long int)without);
					with=(long long int)((long long int)with+(long long int)min((long long int)With[Map[current][j]],(long long int)Without[Map[current][j]]));
				}
				With[current]=(long long int)with;
				Without[current]=(long long int)without;
			}
			//printf("|%d %d %d|",current,With[current],Without[current]);
	  	}
	  	void which(int x)
	  	{
	  	    Check[x]=false;
	  	    if(Take[x]==true)
            {
                for(int i=0;i<Map[x].size();i++)
                {
                    if(Check[Map[x][i]]==true)
                    {
                        if(With[Map[x][i]]<Without[Map[x][i]])
                            Take[Map[x][i]]=true;
                        which(Map[x][i]);
                    }

                }
            }
            else
                for(int i=0;i<Map[x].size();i++)
                {
                    if(Check[Map[x][i]]==true)
                    {
                       Take[Map[x][i]]=true;
                        which(Map[x][i]);
                    }

                }
	  	}
	  	void chose()
	  	{
	  	    if(With[Order[map_size-1]]<Without[Order[map_size-1]])
                Take[Order[map_size-1]]=true;
            which(Order[map_size-1]);
	  	}
		void write()
		{
			printf("%lld\n",min(With[Order[map_size-1]],Without[Order[map_size-1]]));
			for(int i=0;i<map_size;i++)
            {
                if(Take[i]==true)
                    printf("1");
                else
                    printf("0");
            }
            printf("\n");
		}
};
int main()
{
    int  g;scanf("%d",&g);
    while(g--)
    {
        int large;scanf("%d",&large);
        Roads X = Roads(large);
        X.input();
        X.order();
        X.calculate();
        X.chose();
        X.write();
    }

}
