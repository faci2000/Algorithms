#include<cstdio>
#include<vector>
#define duzo 1000000009;
using namespace std;

void print_matrix(vector<vector<int> > &Matrix)
{
    for(int i=0;i<Matrix.size();i++)
    {
        for(int j=0;j<Matrix[0].size();j++)
            printf("%d ",Matrix[i][j]);
        printf("\n");
    }

}

void matrix_multiplication(vector<vector<int> > &Matrix_A,
                           vector<vector<int> > &Matrix_B)
{
    vector<vector<int> > Final_matrix (Matrix_A.size(),vector<int>(Matrix_A.size(),0));
    for(int i=0;i<Matrix_A.size();i++)
        for(int j=0;j<Matrix_A.size();j++)
            for(int k=0;k<Matrix_A.size();k++)
            {
                Final_matrix[i][j]%=duzo;
                Matrix_A[i][k]%=duzo;
                Matrix_B[k][j]%=duzo;
                Final_matrix[i][j]+=((long long)Matrix_A[i][k]*Matrix_B[k][j])%duzo;
                Final_matrix[i][j]%=duzo;
            }
    Matrix_A=Final_matrix;
}

void matrix_powering(vector<vector<int> > &Matrix,
                     vector<vector<int> > &Original,
                     int power)
{
    if(power%2==0)
    {
        matrix_powering(Matrix,Original,power/2);
        matrix_multiplication(Matrix,Matrix);
        return;
    }
    else if(power>1)
    {
        matrix_powering(Matrix,Original,power-1);
        matrix_multiplication(Matrix,Original);
        return;
    }
    else
        return;
}

void neighborhood_input(vector<vector<int> > &Neighborhood,int amount)
{
    for(int i=0;i<amount;i++)
    {
        int temp_1,temp_2;scanf("%d %d", &temp_1,&temp_2);
        Neighborhood[temp_1-1][temp_2-1]= 1;
        Neighborhood[temp_2-1][temp_1-1]=1;
    }
}

void copying(vector<vector<int> > &Copy,vector<vector<int> > &Original,int mask)
{
    for(int i=0;i<Original.size();i++)
    {
        for(int j=0;j<Original.size();j++)
        {
            if((mask&(1<<i))>0||(mask&(1<<j))>0)
            {
                //printf("->%d %d %d\n",mask,i,j);
                Copy[i][j]=0;
            }
            else
            {
                Copy[i][j]=Original[i][j];
                //printf("%d %d %d\n",mask,i,j);
            }
        }
    }
}

long long int matrix_sum(vector<vector<int> > &Matrix)
{
    long long int sum=0;
    for(int i=0;i<Matrix.size();i++)
        for(int j=0;j<Matrix.size();j++)
        {
            sum%=duzo;
            Matrix[i][j]%=duzo;
            sum+=Matrix[i][j];
            sum%=duzo;
        }
    return sum;
}

void includ_exclude_calculation(vector<vector<int> > &Original,int power, int amount)
{
    vector<vector<int> > Copy (Original.size(),vector<int>(Original.size(),0));
    vector<vector<int> > Copyv2 (Original.size(),vector<int>(Original.size(),0));
    long long int final_sum=0;
    for(int i=0;i<(1<<amount);i++)
    {
        //printf("|%d|\n",i);
        copying(Copy,Original,i);
        //print_matrix(Copy);
        Copyv2=Copy;
        matrix_powering(Copy,Copyv2,power);
        //print_matrix(Copy);
        if(__builtin_popcount(i)%2==0)
        {
            final_sum%=duzo;
            final_sum+=(matrix_sum(Copy))%duzo;
            final_sum%=duzo;
        }
        else
        {
            final_sum%=duzo;
            //if(final_sum<matrix_sum(Copy))
              //  printf("X");
            final_sum-=(matrix_sum(Copy))%duzo;
            if(final_sum<0)
                final_sum+=duzo;
            final_sum%=duzo;
        }

    }
    printf("%lld\n",final_sum);
}

int main()
{
    int matma;scanf("%d",&matma);
    while(matma--)
    {
        int cities,routes,fav_cities,trip_length;
        scanf("%d %d %d %d",&cities,&routes,&fav_cities,&trip_length);
        vector<vector<int> > Neighborhood (cities,vector<int>(cities,0));
        neighborhood_input(Neighborhood, routes);
        if(routes==0&&trip_length>1)
        {
            printf("0\n");
            continue;
        }
        if(fav_cities==1&&trip_length==1)
        {
            printf("1\n");
            continue;
        }
        if(trip_length<fav_cities)
        {
            printf("0\n");
            continue;
        }
        includ_exclude_calculation(Neighborhood,trip_length-1,fav_cities);
    }
}
