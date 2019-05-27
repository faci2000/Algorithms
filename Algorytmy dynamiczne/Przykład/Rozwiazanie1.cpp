#include<cstdio>
#include<vector>
using namespace std;
class Pizza_Game
{
public:
      vector<int> Pizza;
      int pizza_size;
      vector<vector<int> > First;
      vector<vector<int> > Second;
      Pizza_Game(int s)
      {
              pizza_size = s;
              Pizza.resize(pizza_size, 0);
              First.resize(pizza_size, Pizza);
              Second.resize(pizza_size, Pizza);
      }
      void build()
      {
              for (int i = 0; i < pizza_size; i++)
              {
                      int temp; scanf("%d", &temp);
                      Pizza[i] = temp;
                      First[i][i] = temp;
                      //Second[i][i] = temp;
              }
      }
      void write()
      {
              //for (int i = 0; i < pizza_size; i++)
                      //printf("%d ", Pizza[i]);
              //printf("\n");
              for (int i = 0; i < pizza_size; i++)
              {
                      for (int j = 0; j < pizza_size; j++)
                              printf("%d ", First[i][j]);
                      printf("\n");
              }
      }
      void calculate()
      {
              for (int d = 1; d < pizza_size - 1; d++)
              {
                      for (int i = 0; i < pizza_size; i++)
                      {
                              int j = i + d;
                              if(Pizza[i% pizza_size] + Second[(i + 1) % pizza_size][j% pizza_size]>=Pizza[j% pizza_size] + Second[i% pizza_size][(j - 1) % pizza_size])
                {
                    First[i% pizza_size][j% pizza_size] = Pizza[i% pizza_size] + Second[(i + 1) % pizza_size][j% pizza_size];
                    Second[i% pizza_size][j% pizza_size] = First[(i + 1) % pizza_size][j% pizza_size];
                }
                else
                {
                    First[i% pizza_size][j% pizza_size] = Pizza[j% pizza_size] + Second[i% pizza_size][(j - 1) % pizza_size];
                    Second[i% pizza_size][j% pizza_size] = First[i% pizza_size][(j - 1) % pizza_size];
                }
                      }
              }
      }
      void look_for_Tbw()
      {
              int Tbw = 0;
              for (int i = 1; i < pizza_size; i++)
              {
                      if (Pizza[Tbw % pizza_size] + Second[(Tbw + 1) % pizza_size][(Tbw - 1 + pizza_size) % pizza_size] < Pizza[i % pizza_size] + Second[(i + 1) % pizza_size][(i - 1 + pizza_size) % pizza_size])
                              Tbw = i;
              }
              printf("%d %d\n",Pizza[Tbw % pizza_size] + Second[(Tbw + 1) % pizza_size][(Tbw - 1 + pizza_size) % pizza_size], First[(Tbw + 1) % pizza_size][(Tbw - 1 + pizza_size) % pizza_size]);
      }
};
int main()
{
    int I_will_win_OM;scanf("%d",&I_will_win_OM);
    while(I_will_win_OM--)
    {
        int pizza_size; scanf("%d", &pizza_size);
        Pizza_Game A(pizza_size);
        A.build();
        A.calculate();
        /*printf("\n");
        A.write();
        printf("\n");*/
        A.look_for_Tbw();
    }
}