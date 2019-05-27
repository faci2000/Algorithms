#include<iostream>
#include<vector>
using namespace std;
void set_perm(vector<vector<int> >&Perm,int x)
{
    while(x>0)
    {
        for(int i=0;i<8;i++)
        {
            Perm[x].push_back(Perm[2*x][Perm[2*x+1][i]]);
        }

        x--;
    }
}
void change(vector<vector<int> >&Perm,int x)
{
    while(x>0)
    {
        for(int i=0;i<8;i++)
            Perm[x][i]=Perm[2*x][Perm[2*x+1][i]];
        x/=2;
    }
}
int main()
{
    int wires; cin>>wires;
    int m=1;
    while(m<wires)
        m*=2;
    vector<vector<int> > Perm (m*2);
    for(int i=m;i<2*m;i++)
    {
        if(i<m+wires)
            for(int j=0;j<8;j++)
                {
                    int buff;cin>>buff;
                    Perm[i].push_back(buff-1);
                }
        else
            for(int j=0;j<8;j++)
                Perm[i].push_back(j);
    }
    set_perm(Perm,m-1);

    int perms;cin>>perms;
    for(int i=0;i<perms;i++)
    {
        int x;cin>>x;
        for(int j=0;j<8;j++)
        {
            int buff;cin>>buff;
            Perm[m+x-1][j]=buff-1;
        }
        change(Perm,(m+x-1)/2);
        for(int j=0;j<8;j++)
            cout<<Perm[1][j]+1<<" ";
        cout<<endl;
    }
}