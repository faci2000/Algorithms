#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;

void entry_input(vector<int> &A)
{
    for(int i=0;i<A.size();i++)
        scanf("%d",&A[i]);
}

int Horner_Schame(vector<int> &Polynomial,int x)
{
    int sum=(Polynomial[0])%1000+1000;
    for(int i=1;i<Polynomial.size();i++)
    {
        sum=((long long)sum*x)%1000+1000;
        sum+=Polynomial[i];
    }
    sum%=1000;
    if(sum<0)
        sum+=1000;
    return sum;
}

bool check_sign(vector<int> &Polynomial,int x_value)
{
    if(x_value<0)
    {
        x_value*=-1;
        for(int i=Polynomial.size()-2;i>=0;i-=2)
            Polynomial[i]*=-1;
    }

    int rest=0;
    for(int i=Polynomial.size()-1;i>=0;i--)
    {
        if(Polynomial[i]+rest>0)
            rest=abs(Polynomial[i]+rest)/x_value;
        else
            rest=-1*ceil(abs(Polynomial[i]+rest)/x_value);
    }
    //printf("%d",rest);
    //rest*=sign;
    if(rest<0)
        return true;
    else
        return false;
}

int main()
{
    int OG;scanf("%d",&OG);
    while(OG--)
    {
        int degree, x_value;scanf("%d %d",&degree,&x_value);
        if(degree==1)
        {
            int temp;scanf("%d",&temp);
            temp=abs(temp%1000);
            if(temp<10)
                printf("00%d\n",temp);
            else if(temp<100)
                printf("0%d\n",temp);
            else
                printf("%d\n",temp);
            continue;
        }
        vector<int> Polynomial (degree);
        entry_input(Polynomial);
        if(x_value==0)
        {
            int value = Polynomial[degree-1]%1000;
            value=abs(value);
            if(value<10)
                printf("00%d\n",value);
            else if(value<100)
                printf("0%d\n",value);
            else
                printf("%d\n",value);
                continue;
        }
        int value=Horner_Schame(Polynomial,x_value);
        //printf("%d\n",check_sign(Polynomial,x_value));
        //printf("%d\n",value);
        if(check_sign(Polynomial,x_value))
            value-=1000;
        value=abs(value);
        if(value<10)
            printf("00%d\n",value);
        else if(value<100)
            printf("0%d\n",value);
        else
            printf("%d\n",value);
    }

}
