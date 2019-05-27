#include<iostream>
#include<string>
using namespace std;
void KMP(string A,int *Tab)
{
    int k=0;
    for(int i=2;i<A.size();i++)
    {
        while(k>0&&A[k+1]!=A[i])
            k=Tab[k];
        if(A[k+1]==A[i])
            k++;
        Tab[i]=k;
    }
}
int calc_verse(int *Tab, int length)
{
     for(int i=1;i<length;i++)
     {
         if(length%i==0)
         {
             int j=i*2;
             while(Tab[j]%i==0&&Tab[j]!=0)
             {
                 if(j==length)
                    return length/i;
                 j+=i;
             }
         }
     }
     return 1;
}
int main()
{
    int g;cin>>g;
    while(g--)
    {
        string anthem;cin>>anthem;
        anthem='0'+anthem;
        int PI[anthem.size()]={};
        KMP(anthem,PI);
        cout<<calc_verse(PI,anthem.size()-1)<<endl;
    }
}