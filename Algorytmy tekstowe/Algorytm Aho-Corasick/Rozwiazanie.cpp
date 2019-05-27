#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

bool iswhitespace(char c) { return (c <= ' ') ? true : false; }
void WordScan(vector<int> &Word)
{
  char c;
  int word_size=0;
  while (iswhitespace(c = getchar())) {}
  do {
    Word.push_back((int)c-48);
    word_size++;
  } while (!iswhitespace(c = getchar()));
}
enum checking
{
    free=0,
    open=1,
    done=2
};
struct Node
{
    bool accept=false;
    int Trans[2]={-1,-1};
    int fail=-1;
    //int out=-1;
};
class Trie
{
public:
    vector<Node> Tree;
    int amount;
    bool found;
    Trie(int a)
    {
        amount=a;
        found=false;
    }

    void Build()
    {
        Node temp_1;
        Tree.push_back(temp_1);
        for(int i=0;i<amount;i++)
        {
            int place=0;
            vector<int> virus;
            WordScan(virus);
            for(int j=0;j<virus.size();j++)
            {
                //printf("%d ", virus[j]);
                if(Tree[place].Trans[virus[j]]!=-1)
                    place=Tree[place].Trans[virus[j]];
                else
                {
                    Node temp_2;
                    Tree.push_back(temp_2);
                    Tree[place].Trans[virus[j]]=Tree.size()-1;
                    place=Tree.size()-1;
                }
                if(j==virus.size()-1)
                    Tree[place].accept=true;
            }
        }
    }

    void Automaton_making()
    {
        Tree[0].fail=0;
        queue<int>Nodes;
        for(int i=0;i<2;i++)
        {
            if(Tree[0].Trans[i]!=-1)
            {
                Tree[Tree[0].Trans[i]].fail=0;
                Nodes.push(Tree[0].Trans[i]);
            }
        }
        while(!Nodes.empty())
        {
            int V=Nodes.front();
            Nodes.pop();
            for(int i=0;i<2;i++)
            {
                int Y=Tree[V].Trans[i];
                if(Y!=-1)
                {
                    int K=Tree[V].fail;
                    while(K>0&&Tree[K].Trans[i]==-1)
                        K=Tree[K].fail;
                    if(Tree[K].Trans[i]!=-1)
                        K=Tree[K].Trans[i];
                    Tree[Y].fail=K;
                    Nodes.push(Y);
                }
            }
            /*int U=Tree[V].fail;
            if(Tree[U].accept==true)
                Tree[V].out=U;
            else
                Tree[V].out=Tree[U].out;*/

            if(Tree[Tree[V].fail].accept==true)
                Tree[V].accept=true;
        }
        for(int i=0;i<2;i++)
        {
            if(Tree[0].Trans[i]!=-1)
                Nodes.push(Tree[0].Trans[i]);
            else
                Tree[0].Trans[i]=0;
        }
        while(!Nodes.empty())
        {
            int V=Nodes.front();
            Nodes.pop();//printf("%d\n",V);
            for(int i=0;i<2;i++)
            {
                if(Tree[V].Trans[i]!=-1)//TESTUJ 1 1 001110001
                    Nodes.push(Tree[V].Trans[i]);//printf("%d ",Tree[Tree[4].fail].Trans[0]);

                else
                    Tree[V].Trans[i]=Tree[Tree[V].fail].Trans[i];//Show();printf(" %d %d\n",V,i);
            }
        }

    }

    void Initializing_Search()
    {
        vector<checking> Checked (Tree.size(),free);
        Search(0,Checked);
        if(found==true)
            printf("TAK\n");
        else
            printf("NIE\n");
    }

    void Search(int x,vector<checking> &Checked)
    {
        Checked[x]=open;
        for(int i=0;i<2;i++)
        {
            if(found==true)
                return;
            int y=Tree[x].Trans[i];//printf("%d %d\n",x, y);
            if(Tree[y].accept==true)
                Checked[y]=done;
            if(Checked[y]==open)
                found=true;
            if(Checked[y]==free)
                Search(y,Checked);
        }
        Checked[x]=done;
    }

    void Show()
    {
        for(int i=0;i<Tree.size();i++)
            printf("%d %d %d %d %d\n",i,Tree[i].Trans[0],Tree[i].Trans[1],Tree[i].fail,Tree[i].accept);
    }
};
int main()
{
    int sets;scanf("%d",&sets);
    while(sets--)
    {
        int viruses;scanf("%d",&viruses);
        Trie a(viruses);
        a.Build();
        a.Automaton_making();//printf("x");
        //a.Show();
        a.Initializing_Search();
    }
}