#include<iostream>
#include<utility>
#include<vector>
#include<math.h>

using namespace std;

long long int det(pair<int, int> x,pair<int,int> y)
{
    return (long long)((long long)x.first*y.second-(long long)x.second*y.first);
}

int NWD(int a, int b)
{
    while(b)
    {
        int temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}

void input(vector<pair<int,int> > &Figure)
{

    for(int i=0;i<Figure.size();i++)
    {//printf("%d\n", Figure.size());
        scanf("%d %d",&Figure[i].first,&Figure[i].second);
    }
}

long long int square_count(vector<pair<int,int> > &Figure)
{
    long long int square=0;
    for(int i=1;i<Figure.size()-1;i++)
    {
        pair<int,int> vect1;
        vect1.first=(Figure[i].first-Figure[0].first);
        vect1.second=(Figure[i].second-Figure[0].second);

        pair<int,int> vect2;
        vect2.first=(Figure[i+1].first-Figure[0].first);
        vect2.second=(Figure[i+1].second-Figure[0].second);

        square+=det(vect1,vect2);
    }
    return abs(square)/2;
}

long long int edge_points_count(vector<pair<int,int> > &Figure)
{
    long long int points=0;
    for(int i=0;i<Figure.size();i++)
    {
        points+=NWD(abs(Figure[i].first-Figure[(i+1)%Figure.size()].first),
                    abs(Figure[i].second-Figure[(i+1)%Figure.size()].second));
    }
    return points;
}

int main()
{
    int lamp;scanf("%d",&lamp);
    while(lamp--)
    {
        int vert;scanf("%d",&vert);
        vector<pair<int,int> > Figure (vert);
        input(Figure);
        long long int square=square_count(Figure);
        //printf("%d ",square);
        long long int edge_points=edge_points_count(Figure);
        //printf("%d ",edge_points);
        printf("%lld\n",(square-(edge_points/2)+1));
    }


}
