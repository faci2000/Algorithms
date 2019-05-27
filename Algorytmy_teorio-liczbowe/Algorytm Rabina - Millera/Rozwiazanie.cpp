#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
long long peasant(long long x, long long y, long long p)
{
    long long sum=0;
    while (y>0)
    {
         if (y&1)
             sum=(sum+x)%p;
        x=x<<1;
        x%=p;
        y=y>>1;
        sum%=p;
     }
     return sum;
}

long long exponentiation(long long a, long long power,long long p)
{
  long long result=1;
  while (power)
  {
    if (power%2==1)
    {
        result=peasant(result,a,p)%p;
    }
    power/=2;
    a=peasant(a,a,p)%p;
  }
  return result%p;
}

bool witness(long long number,long long a, long long t, long long d)
{
    long long x1,x2;
    //printf("%lld %lld",a,d);
    x1=exponentiation(a,d,number);
    //printf("x");
    for(int i=0;i<t;i++)
    {
        x2=peasant(x1,x1,number)%number;
        if(x2==1&&x1!=1&&x1!=number-1)
            return true;
        x1=x2;
    }
    if(x2!=1)
        return true;
    return false;
}

bool Miller_Rabin(long long number,long long precision,long long t, long long d)
{

    for(long long i=0;i<precision;i++)
    {
        long long random = rand()%(number-2)+1;
        //printf(" %lld %lld ",i, precision);
        if(witness(number,random,t,d))
            return false;
    }
    return true;
}

int main()
{
    int glhf;scanf("%d",&glhf);
    while(glhf--)
    {
        //printf("%lld ",peasant(5311748275137519,2,1000000000000000000));
        srand (time(NULL));
        long long number;scanf("%lld",&number);
        //printf("%lld",number);
        long long t=0;
        long long  d=(number-1);
        while(d%2==0)
        {
            t++;
            d/=2;
        }
        //printf("%lld %lld %lld",number-1,t,d);
        if(number==0||number==1)
            printf("NIE\n");
        else if(number==2)
            printf("TAK\n");
        else if(Miller_Rabin(number,50,t,d))
            printf("TAK\n");
        else
            printf("NIE\n");
    }

}
