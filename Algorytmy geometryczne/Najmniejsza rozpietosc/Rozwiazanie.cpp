#include<cstdio>
#include<utility>
#include<vector>
#include<algorithm>
#include<math.h>
//#include<iostream>
using namespace std;

struct point{
    int x,y;
};

point lowest;

long long int det(pair<int, int> x,pair<int,int> y)
{
    return (long long)((long long)x.first*y.second-(long long)x.second*y.first);
}

void input_points(vector <point> &Points)
{
    for(int i=0;i<Points.size();i++)
    {
        scanf("%d %d",&Points[i].x,&Points[i].y);
    }
}

void find_lowest(vector <point> &Points, point &lowest)
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

bool operator < (point a,point b)
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

void graham(vector <point> &Points,vector<int> &Encasement)
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
        while(det(vec_A,vec_B)>=0&&Encasement.size()>1)//sprawdzic czy dziala
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

void print_points(vector <point> &Points)
{
    for(int i=0;i<Points.size();i++)
    {
        printf("%d %d\n",Points[i].x,Points[i].y);
    }
    printf("\n");
}

int find_k_point(vector <point> &Points,vector<int> &Hull, int base_1, int base_2)
{
    // for (int &i : Hull) {
    //     printf("%d ", i);
    // } printf("\n");
    int j=base_1+Hull.size(),i=base_2;
    //int double_check=0;
    
    while(i<j)
    {
        int middle=(i+j)/2;
        // printf("i: %d j: %d\n",i,j);
        // printf("middle: %d\n", middle);
        // printf("x:%d , y:%d\n", Points[Hull[middle%Hull.size()]].x, Points[Hull[middle%Hull.size()]].y);

        if(det(make_pair<int,int> ((Points[Hull[base_1]].x-Points[Hull[middle%Hull.size()]].x),(Points[Hull[base_1]].y-Points[Hull[middle%Hull.size()]].y)),      //psrawdzam czy wyskość middle jest 
            make_pair<int,int> ((Points[Hull[base_2]].x-Points[Hull[middle%Hull.size()]].x),(Points[Hull[base_2]].y-Points[Hull[middle%Hull.size()]].y)))>        //wieksza niż z prawej strony
            det(make_pair<int,int> ((Points[Hull[base_1]].x-Points[Hull[(middle+1)%Hull.size()]].x),(Points[Hull[base_1]].y-Points[Hull[(middle+1)%Hull.size()]].y)),
            make_pair<int,int> ((Points[Hull[base_2]].x-Points[Hull[(middle+1)%Hull.size()]].x),(Points[Hull[base_2]].y-Points[Hull[(middle+1)%Hull.size()]].y))))
        {
            j=middle;
            //printf("a\n");
        }
        else if(det(make_pair<int,int> ((Points[Hull[base_1]].x-Points[Hull[middle%Hull.size()]].x),(Points[Hull[base_1]].y-Points[Hull[middle%Hull.size()]].y)),      //psrawdzam czy wyskość middle jest 
            make_pair<int,int> ((Points[Hull[base_2]].x-Points[Hull[middle%Hull.size()]].x),(Points[Hull[base_2]].y-Points[Hull[middle%Hull.size()]].y)))<        //mniejsza niż z prawej strony
            det(make_pair<int,int> ((Points[Hull[base_1]].x-Points[Hull[(middle+1)%Hull.size()]].x),(Points[Hull[base_1]].y-Points[Hull[(middle+1)%Hull.size()]].y)),
            make_pair<int,int> ((Points[Hull[base_2]].x-Points[Hull[(middle+1)%Hull.size()]].x),(Points[Hull[base_2]].y-Points[Hull[(middle+1)%Hull.size()]].y))))
        {
            i=middle+1;
           //printf("B\n");
        }
        else if(det(make_pair<int,int> ((Points[Hull[base_1]].x-Points[Hull[middle%Hull.size()]].x),(Points[Hull[base_1]].y-Points[Hull[middle%Hull.size()]].y)),       //psrawdzam czy wyskość middle jest 
            make_pair<int,int> ((Points[Hull[base_2]].x-Points[Hull[middle%Hull.size()]].x),(Points[Hull[base_2]].y-Points[Hull[middle%Hull.size()]].y)))>              //wieksza niż z lewej strony
            det(make_pair<int,int> ((Points[Hull[base_1]].x-Points[Hull[(middle-1+Hull.size())%Hull.size()]].x),(Points[Hull[base_1]].y-Points[Hull[(middle-1+Hull.size())%Hull.size()]].y)),
            make_pair<int,int> ((Points[Hull[base_2]].x-Points[Hull[(middle-1+Hull.size())%Hull.size()]].x),(Points[Hull[base_2]].y-Points[Hull[(middle-1+Hull.size())%Hull.size()]].y))))
        {
            i=middle+1;
            //printf("c\n");
        }
        else
        {
            j=middle;
           //printf("d\n");
        }
    }
    return i%Hull.size();
}

double dist(double Ax,double Ay, double Bx, double By)
{
    return  (double)sqrt(( double)(Ax-Bx)*(Ax-Bx)+(( double)Ay-By)*(Ay-By));
}

double finding_lowest_distant(vector <point> &Points,vector<int> &Hull)
{
    int g= find_k_point(Points,Hull,0,1);
    double minn=(double)det(make_pair<int,int> ((Points[Hull[0]].x-Points[Hull[g]].x),(Points[Hull[0]].y-Points[Hull[g]].y)), 
            make_pair<int,int> ((Points[Hull[1]].x-Points[Hull[g]].x),(Points[Hull[1]].y-Points[Hull[g]].y)))/
            dist(Points[Hull[0]].x,Points[Hull[0]].y,Points[Hull[1]].x,Points[Hull[1]].y);
    //printf("%d :%d - %f\n",1,g,minn);
    for(int i=1;i<Hull.size();i++)
    {
        int k=find_k_point(Points,Hull,i,(i+1)%Hull.size());
        double height = (double)det(make_pair<int,int> ((Points[Hull[i]].x-Points[Hull[k]].x),(Points[Hull[i]].y-Points[Hull[k]].y)), 
            make_pair<int,int> ((Points[Hull[(i+1)%Hull.size()]].x-Points[Hull[k]].x),(Points[Hull[(i+1)%Hull.size()]].y-Points[Hull[k]].y)))/
            dist(Points[Hull[i]].x,Points[Hull[i]].y,Points[Hull[(i+1)%Hull.size()]].x,Points[Hull[(i+1)%Hull.size()]].y);
        //printf("%d :%d - %f\n",i+1,k,height);
        if(height<minn)
            minn=height;
    }
    return minn;
}

int main()
{
    int matura;scanf("%d",&matura);
    while(matura--)
    {
        int amount; scanf("%d",&amount);
        vector<point> Points (amount);
        input_points(Points);
        if(amount==1)
        {
            printf("0\n");
        }
        else if(amount==2)
        {
            printf("%f\n",dist(Points[0].x,Points[0].y,Points[1].x,Points[1].y));
        }
        else
        {
            find_lowest(Points,lowest);
            sort(Points.begin(),Points.end());
            vector<int> Hull;
            graham(Points,Hull);
            // printf("%d\n",Hull.size());
            // for(int i=0;i<Hull.size();i++)
            // {
            //     printf("%d %d\n",Points[Hull[i]].x,Points[Hull[i]].y);
            // }
            double marker =finding_lowest_distant(Points,Hull);
            printf("%f\n",marker);
        }
        
    }
    
}