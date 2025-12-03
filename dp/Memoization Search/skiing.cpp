//first try
/*

#include<iostream>
#include<algorithm>
using namespace std;
const int N=310;
typedef pair<int,int> PII;

int h[N][N],f[N][N];
PII ds[4]={{0,-1},{0,1},{-1,0},{1,0}};//上下左右方向

int dp(int r,int c)
{
    //每个状态需要由上下左右四个方向转移而来
    //我很难去初始化f，感觉没法初始化所有需要的状态
    //而且考虑相邻的两个格子，他们的状态按我的逻辑是相互依赖的...
    //所以虽然状态之间存在关系，但是我们
    //找不到方法可以做到初始化部分状态去递推出所有状态
    //但是我们可以利用状态转移的关系，
    //对于已经确定的状态直接使用，对于不确定的状态进行dfs
    //这样相较于直接所有点都进行dfs，少算了大量重复的状态

    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            for(int move=1;move<=4;move++)
            {
                int dx=ds[move].first;
                int dy=ds[move].second;
                if(h[i][j]<h[i+dx][i+dy])
                    f[i][j]=max(f[i][j],f[i+dx][i+dy]+1);
            }
        }
    }
}

int main()
{
    int r,c;
    scanf("%d%d",&r,&c);

    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
            scanf("%d",&h[i][j]),f[i][j]=1;

    int res=dp(r,c);
    
    printf("%d",res);
    return 0;
}

*/

//second try
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=310;
typedef pair<int,int> PII;

int h[N][N],f[N][N],res;
bool st[N][N];//用于标识f[i][j]是否为最优值
PII ds[4]={{0,-1},{0,1},{-1,0},{1,0}};//上下左右方向

void dfs(int x,int y,int r,int c)
{
    for(int move=0;move<=3;move++)
    {
        int new_x=x+ds[move].first;
        int new_y=y+ds[move].second;
        
        if(new_x<=0||new_x>r||new_y<=0||new_y>c) continue;
        else if(h[x][y]<=h[new_x][new_y]) continue;
        else if(h[x][y]>h[new_x][new_y])
        {
            if(!st[new_x][new_y])
            {
                dfs(new_x,new_y,r,c);
            }

            f[x][y]=max(f[x][y],f[new_x][new_y]+1);
        }

    }

    st[x][y]=true;
    return;
   
}

int dp(int r,int c)
{
    //每个状态需要由上下左右四个方向转移而来
    //我很难去初始化f，感觉没法初始化所有需要的状态
    //而且考虑相邻的两个格子，他们的状态按我的逻辑是相互依赖的...
    //所以虽然状态之间存在关系，但是我们
    //找不到方法可以做到初始化部分状态去递推出所有状态
    //但是我们可以利用状态转移的关系，
    //对于已经确定的状态直接使用，对于不确定的状态进行dfs
    //这样相较于直接所有点都进行dfs，少算了大量重复的状态

    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
             dfs(i,j,r,c);
             if(f[i][j]>res) res=f[i][j];
        }
    }
}

int main()
{
    int r,c;
    scanf("%d%d",&r,&c);

    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
            scanf("%d",&h[i][j]),f[i][j]=1;

    dp(r,c);
    
    printf("%d",res);
    return 0;
}