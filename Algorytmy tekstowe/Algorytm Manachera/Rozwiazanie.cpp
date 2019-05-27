#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
string modify(string word)
{
    string mod_word="@";
    for(int i=0;i<word.size();i++)
    {
        mod_word+=word[i];
        if(i!=word.size()-1)
            mod_word+='#';
    }
    return mod_word+'$';
}
void Manacher(string word,int* Tab)
{
    int the_longest=0;
    for(int i=1;i<=word.size()-1;i++)
    {
        if(i<=the_longest+Tab[the_longest])
            Tab[i]=min(the_longest+Tab[the_longest]-i,Tab[the_longest-(i-the_longest)]);
        if(i+Tab[i]>=Tab[the_longest]+the_longest)
            while(word[i+Tab[i]+1]==word[i-Tab[i]-1])
                Tab[i]++;
        if(Tab[i]+i>the_longest+Tab[the_longest])
            the_longest=i;
    }
}
void check(int left, int right, int* Tab)
{
    left*=2;right*=2;
    int middle=(left+right)/2;
    if(middle+Tab[middle-1]>=right)
        cout<<"TAK"<<endl;
    else
        cout<<"NIE"<<endl;
}
int main()
{
    int g;scanf("%d",&g);
    while(g--)
    {
        string word;cin>>word;
        word=modify(word);
        int Tab[word.size()]={};
        Manacher(word,Tab);
        int checks;scanf("%d",&checks);
        for(int i=0;i<checks;i++)
        {
            int left,right;scanf("%d %d",&left,&right);
            check(left,right,Tab);
        }
    }

}