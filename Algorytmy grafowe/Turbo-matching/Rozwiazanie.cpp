#include<cstdio>
#include <vector>
#include<stack>
using namespace std;

class Matching
{
    private:
    vector< vector<int>> Connections;
    vector<int> Connected_A;//already in matching princes
    vector<int> Connected_B;//already in matching princess
    bool changes = true;

    public: Matching(int plants, int rules)
    {
        Connections.resize(plants);
        for(int i=0;i<rules;i++)
        {
            int temp_1,temp_2;
            scanf("%d %d",&temp_1,&temp_2);
            Connections[temp_1-1].push_back(temp_2-1);
        }
        Connected_A.resize(plants,-1);
        Connected_B.resize(plants,-1);
    }

    void find_augumenting_path(stack<int> &New_path,int x,vector<bool> &Visited_A, vector<bool> &Visited_B, bool is_A)
    {
        if(changes)
            return;
        if(!is_A)
        {
            int y=Connected_B[x];
            if(!Visited_A[y])
            {
                Visited_A[y]=true;
                New_path.push(y);
                find_augumenting_path(New_path,y,Visited_A,Visited_B,true);
            }
            if(changes)
                return;
        }
        else if(is_A)
        {
            for(int i=0;i<Connections[x].size();i++)
            {
                int y=Connections[x][i];
                if(!Visited_B[y])
                {
                    Visited_B[y]=true;
                    New_path.push(y);
                    if(Connected_B[y]==-1)
                    {
                        changes=true;
                        return;//the augumenting path is found
                    }
                    find_augumenting_path(New_path,y,Visited_A,Visited_B,false);
                }
                if(changes)
                    return;
            }
        }
        if(changes)
            return;
        New_path.pop();
    }

    void overwrite_matching(stack<int> &Path)
    {
        while(!Path.empty())
        {
            int temp = Path.top();
            Path.pop();
            Connected_A[Path.top()]=temp;
            Connected_B[temp]=Path.top();
            Path.pop();
        }
    }

    void the_best_matching()
    {
        bool changed =true;
        while(changed)
        { changed=false;
            for(int i=0;i<Connected_A.size();i++)
            {
                changes=false;
                if(-1==Connected_A[i])
                {
                    stack<int> Temp;
                    vector<bool> Visited_A;// visited in dfs
                    vector<bool> Visited_B;// visitied in dfs
                    Visited_A.resize(Connected_A.size(),false);
                    Visited_B.resize(Connected_B.size(),false);
                    Visited_A[i]=true;
                    Temp.push(i);
                    find_augumenting_path(Temp,i,Visited_A,Visited_B,true);
                    overwrite_matching(Temp);
                }
                if(changes)
                    changed=true;
            }
        }
    }

    void print()
    {
        for(int i=0;i<Connected_A.size();i++)
        {
            if(Connected_A[i]==-1)
                {
                    printf("NIE\n");
                    return;
                }
        }
        printf("TAK\n");
    }
};

int main()
{
    int UJ;scanf("%d",&UJ);
    while(UJ--)
    {
        int plants,rules;
        scanf("%d %d",&plants,&rules);
        Matching A(plants,rules);
        A.the_best_matching();
        A.print();
    }
}
