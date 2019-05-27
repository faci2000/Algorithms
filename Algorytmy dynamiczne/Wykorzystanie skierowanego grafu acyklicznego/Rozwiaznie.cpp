#include<cstdio>
#include<vector>
using namespace std;
class Game
{
  int board_size;
  vector<vector<int> > Board;
  vector<int> Order;
  vector<bool> Check_or_State;
  public:
      Game (int s)
      {
          board_size=s;
          Board.resize(board_size);
          Check_or_State.resize(board_size,false);
      }
      void input()
      {
          for(int i=0;i<board_size;i++)
          {
              int amount;scanf("%d",&amount);
              for(int j=0;j<amount;j++)
              {
                  int temp;scanf("%d",&temp);
                  Board[i].push_back(temp);
              }
          }
      }
      void dfs_right(int x)
      {
          Check_or_State[x]=true;
          for(int i=0;i<Board[x].size();i++)
          {
              if(Check_or_State[Board[x][i]]==false)
                dfs_right(Board[x][i]);
          }
          Order.push_back(x);
      }
      void order()
      {
          for(int i=0;i<board_size;i++)
          {
              if(Check_or_State[i]==false)
                dfs_right(i);
          }
      }
      void calculate()
      {
          for(int i=0;i<board_size;i++)
          {
              int current=Order[i];
              if(Board[current].size()==0)
                Check_or_State[current]=false;
              else
              {
                  bool state=false;
                  for(int j=0;j<Board[current].size();j++)
                      if(Check_or_State[Board[current][j]]==false)
                        state=true;
                  Check_or_State[current]=state;
              }
          }
      }
      void write()
      {
          for(int i=0;i<board_size;i++)
          {
              if(Check_or_State[i])
                printf("W");
              else
                printf("P");
          }
          printf("\n");
      }
};
int main()
{
    int I;scanf("%d",&I);
    while(I--)
    {
        int large;scanf("%d",&large);
        Game x =  Game(large);
        x.input();
        x.order();
        x.calculate();
        x.write();
    }

}