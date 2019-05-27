#include<cstdio>
#include<utility>
#include<vector>
#include<algorithm>
#include<math.h>
#include<iostream>

#define pi 3.141592653589793238463

using namespace std;

struct algos{
    int x,y;
};

algos lowest;

long long int det(pair<int, int> x,pair<int,int> y)
{
    return (long long)((long long)x.first*y.second-(long long)x.second*y.first);
}

void print_points(vector <algos> &Points)
{
    for(int i=0;i<Points.size();i++)
    {
        printf("%d %d\n",Points[i].x,Points[i].y);
    }
    printf("\n");
}

void input_points(vector <algos> &Points)
{
    for(int i=0;i<Points.size();i++)
    {
        scanf("%d %d",&Points[i].x,&Points[i].y);
    }
}

void find_lowest(vector <algos> &Points, algos &lowest)
{
    lowest=Points[0];
    for(int i=1;i<Points.size();i++)
    {
        if(Points[i].y<lowest.y)
            lowest=Points[i];
        else if(Points[i].y==lowest.y)
            if(Points[i].x<lowest.x)
                lowest=Points[i];
    }
}

bool operator < (algos a,algos b)
{
    if(((long long)a.x-lowest.x)*(b.y-lowest.y)>((long long)b.x-lowest.x)*(a.y-lowest.y))
        return true;
    else if(((long long)a.x-lowest.x)*(b.y-lowest.y)==((long long)b.x-lowest.x)*(a.y-lowest.y))
    {
        if((a.y-lowest.y)<(b.y-lowest.y))
            return true;
        else if((a.y-lowest.y)==(b.y-lowest.y))
        {
            if((a.x-lowest.x)<(b.x-lowest.x))
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else 
        return false;    
}

void graham(vector <algos> &Points,vector<int> &Encasement)
{
    Encasement.push_back(0);
    Encasement.push_back(1);
    for(int i=2;i<Points.size();i++)
    {
        pair<int,int>  vec_A;
        vec_A.first=Points[Encasement[Encasement.size()-2]].x-Points[Encasement[Encasement.size()-1]].x;
        vec_A.second=Points[Encasement[Encasement.size()-2]].y-Points[Encasement[Encasement.size()-1]].y;
        pair<int,int> vec_B;
        vec_B.first=Points[i].x-Points[Encasement[Encasement.size()-1]].x;
        vec_B.second=Points[i].y-Points[Encasement[Encasement.size()-1]].y;
        while(det(vec_A,vec_B)>0&&Encasement.size()>1)//sprawdzic czy dziala
            {
                //printf("x:%d\n",Encasement.back());
                Encasement.pop_back();
                if(Encasement.size()==1)
                    break;
                vec_A.first=Points[Encasement[Encasement.size()-2]].x-Points[Encasement[Encasement.size()-1]].x;
                vec_A.second=Points[Encasement[Encasement.size()-2]].y-Points[Encasement[Encasement.size()-1]].y;
                vec_B.first=Points[i].x-Points[Encasement[Encasement.size()-1]].x;
                vec_B.second=Points[i].y-Points[Encasement[Encasement.size()-1]].y;
            }
            Encasement.push_back(i);
    }
}

double dist(double Ax,double Ay, double Bx, double By)
{
    return  (double)sqrt(( double)(Ax-Bx)*(Ax-Bx)+(( double)Ay-By)*(Ay-By));
}

double calculate_encasement(vector <algos> &Points,vector<int> &A)
{
    double sum=0;
    for(unsigned int i=0;i<A.size()-1;i++)
    {
        sum+=dist(Points[A[i]].x,Points[A[i]].y,Points[A[i+1]].x,Points[A[i+1]].y);
    }
    sum+=dist(Points[A[0]].x,Points[A[0]].y,Points[A[A.size()-1]].x,Points[A[A.size()-1]].y);
    return sum;
}

int main()
{
    int ac;scanf("%d",&ac);
    while(ac--)
    {
        int amount, radius;scanf("%d %d",&amount,&radius);
        vector <algos> Points (amount);
        input_points(Points);
        
        if(amount==1)
        {
            printf("%f\n",(double)radius*2*pi);
            //cout<<(double)radius*2*pi<<endl;
        }
        else if(amount==2)
        {
            printf("%f\n",((double)dist(Points[0].x,Points[0].y,Points[1].x,Points[1].y)*2+(double)pi*2*radius));
            //cout<<(double)dist(Points[0].x,Points[0].y,Points[1].x,Points[1].y)*2+(double)pi*2*radius<<endl;
        }
        else
        {
            find_lowest(Points,lowest);
            
            sort(Points.begin(),Points.end());
            
            //print_points(Points);
            vector <int> Encasement;
            graham(Points,Encasement);
            /*for(int i=0;i<Encasement.size();i++)
            {
                printf("|%d",Encasement[i]);
            }
            printf("\n");
            printf("x");*/
            
            printf("%f\n",(double)radius*2*pi+calculate_encasement(Points,Encasement));
            //cout<<(double)radius*2*pi+calculate_encasement(Points,Encasement)<<endl;
        }
    }
    
}