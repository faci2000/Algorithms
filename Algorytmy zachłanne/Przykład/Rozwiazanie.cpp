#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
    int TOEFL;scanf("%d",&TOEFL);
    while(TOEFL--)
    {
        int width,height;
        scanf("%d %d",&height,&width);
        height--;width--;
        int Horizontal[height]={};
        int Vertical[width]={};
        for(int i=0;i<height;i++)
            scanf("%d",&Horizontal[i]);
        for(int i=0;i<width;i++)
            scanf("%d",&Vertical[i]);
        sort(Horizontal,Horizontal+height);
        sort(Vertical,Vertical+width);
        int vert_multi=1,hor_multi=1;
        int h=height-1,v=width-1;
        long long    int sum=0;
        while(h>=0&&v>=0)
        {

            if(Horizontal[h]>=Vertical[v])
            {
                sum+=Horizontal[h]*hor_multi;
                h--;
                vert_multi++;
            }
            else
            {
                sum+=Vertical[v]*vert_multi;
                v--;
                hor_multi++;
            }
            //printf("%d ||",sum);
        }
        if(h>=0)
        {
            while(h>=0)
            {
                sum+=Horizontal[h]*hor_multi;
                h--;
                //printf("%d ||",sum);
            }
        }
        if(v>=0)
        {
            while(v>=0)
            {
                sum+=Vertical[v]*vert_multi;
                v--;
                //printf("%d ||",sum);
            }
        }
        printf("%lld\n",sum);
    }

}
