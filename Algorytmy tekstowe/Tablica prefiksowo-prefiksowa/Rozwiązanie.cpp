#include<cstdio>
#include<vector>
using namespace std;
bool iswhitespace(char c) { return (c <= ' ') ? true : false; }
int WordScan(vector<char> &Word)
{
  char c;
  int word_size=0;
  while (iswhitespace(c = getchar())) {}
  do {
    Word.push_back(c);
    word_size++;
  } while (!iswhitespace(c = getchar()));
  Word.push_back('$');
  return word_size+1;
}
void PrefPref(vector<char> &Word,int *Z,int word_size)
{
    int k=0;
    for(int i=1;i<word_size;i++)
    {
        if(i<=k+Z[k])//
            Z[i]=min(Z[i-k],k+Z[k]-i);//
        while(Word[i+Z[i]]==Word[Z[i]])//
            Z[i]++;
        if(i+Z[i]>k+Z[k])
            k=i;
    }
}
int main()
{
    int g;scanf("%d",&g);
    while(g--)
    {
    vector<char> Word;
    int word_size=WordScan(Word);
    //for(int i=0;i<word_size;i++)
        //printf("%c",Word[i]);
    int Z[word_size]={};
    PrefPref(Word,Z,word_size);
    for(int i=0;i<word_size-1;i++)
        printf("%d ",Z[i]);
    printf("\n");
    }

}