#include<cstdio>
#include<cmath>
#include<map>
using namespace std;

struct A_type{
int j,aj;
};

int powering(int a, int power,int p)
{
  int result=1;
  while (power)
  {
    if (power%2==1)
    {
        result=((long long)result*a)%p;
    }
    power/=2;
    a=((long long)a*a)%p;
  }
  return result%p;
}

int fill_A_table(map<int,int> &A_table,int a, int m, int p, int b)
{
    for(int j=0;j<m;j++)
    {
        int aj= powering(a,j,p);
        A_table[aj]=j;
        if(aj%p==b)
            return j;
        //printf("%d\n",aj);
    }
    return m+1;
}

void extended_euklidean(int a, int b,int &ma, int &mb)
{
	if(b!=0)
	{
		extended_euklidean(b, a%b,ma,mb);//printf("%d %d ",ma,mb);
		int temp = ma;
		ma = mb  - a/b*ma;
		mb = temp;

	}
}

int negative_factor(int a,int p)
{
    int ma=0,mp=1;
    extended_euklidean(a,p,ma,mp);
    return ((long long)mp+p)%p;
}

void discrete_logarithm(int a,int b,int m,int p, map<int,int> A_table)
{
    for(int i=1;i<m;i++)
    {
        int check = powering(a,i,p);
        check=((long long)check*b)%p;
        //printf("%d | ",check);
        if(A_table.find(check)!=A_table.end())
        {
            printf("%d \n", (i*m+A_table[check])%p);
            return;
        }
    }
    printf("-1\n");
    return;
}

int main()
{
    int deadline; scanf("%d",&deadline);
    while(deadline--)
    {
        int a,b,p;scanf("%d %d %d",&a,&b,&p);
        int m = ceil(sqrt(p));
        //printf("m== %d\n",m);
        map<int,int> A_table;
        int filling_check=fill_A_table(A_table,a,m,p,b);
        if(filling_check==m+1)
        {
            int negative_a = negative_factor(a,p);
            //printf("a^-1 = %d ",negative_a);
            negative_a=powering(negative_a,m,p);
            //printf("a^-m = %d\n",negative_a);
            discrete_logarithm(negative_a,b,m,p,A_table);
        }
        else
            printf("%d\n",filling_check);
        /*printf("%d",negative_factor(3214512,1321));*/
    }

}
