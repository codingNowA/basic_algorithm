/************WA********* */
/*
#include<iostream>
#include<cstring>
using namespace std;
const int N=1010,M=N;
const int MAX=1000;//f的最大可能值

char a[N],b[M];
int f[N][M];

void dp(int n,int m)
{   
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            f[i][j]=MAX;
            if(i==0) f[i][j]=j;
            else if(j==0) f[i][j]=i;  
        }
    }


    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
        //1. f[i+1][j],是f[i][j]插入a[i+1]再进行操作,f[i][j]+1=f[i+1][j]
        //2. f[i-1][j],是f[i][j]删除a[i]再进行操作,f[i][j]+1=f[i-1][j],f[i-1][j]+2=f[i+1][j]
        //f[i+1][j]=min(f[i][j]+1,f[i-1][j]+2)
        //3. f[i-1][j-1]是f[i][j]删除a[i],b[j]再进行操作
        //对于3中，删除b[j]是非法的，该怎么办呢?
        //关注f[i-1][j-1]到f[i][j]的实际意义
        //f[i-1][j-1]到f[i][j]不需要进行插入b[j]的操作
        //我们只需要比较a[i]和b[j]就行了,
        //若a[i]!=b[j],则可以通过一次替换来进行转移
        //若a[i]==b[j],则不需要任何操作.
        //对于1,2。还要考虑能不能进行转移，
        //我的初步想法是全都初始化为很大，这样就不影响了，都认为能够转移，最后看合理的值
            
            //f[i][j]=min(f[i-2][j]+1,f[i-1][j]+2);
            if(i-1>=0) f[i][j]=min(f[i][j],f[i-1][j]+2);
            if(i-2>=0) f[i][j]=min(f[i][j],f[i-2][j]+1);
            if(i-1>=0&&j-1>=0&&a[i]!=b[j]) f[i][j]=min(f[i][j],f[i-1][j-1]+1);
        }
    }
}

int main()
{
    int n,m;
    scanf("%d",&n);
    scanf("%s",a+1);//从1开始存
    scanf("%d",&m);
    scanf("%s",b+1);

    dp(n,m);    

    printf("%d",f[n][m]);
    return 0;
}

*/


#include<iostream>
using namespace std;
const int N=1010,M=N;
const int MAX=1000;//f的最大可能值

char a[N],b[M];
int f[N][M];

void dp(int n,int m)
{   
    for(int i=0;i<=n;i++) f[i][0]=i;
    for(int j=0;j<=m;j++) f[0][j]=j;
    
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            //f[i][j]表示a前i个匹配b前j个字符
            //我们要如何去转移成更小状态呢
            //更小状态:f[i-k][j-t]
            //先考虑f[i-k][j],显然 删除a[i]+f[i-1][j]可以得到f[i][j]，显然这是可传递的
            //再考虑f[i][j-t],插入b[j]+f[i][j-1]可以得到f[i][j]，这也是可传递的
            //在考虑f[i-k][j-t]
            //若a[i]==b[j],f[i-1][j-1]==f[i][j]
            //若a[i]!=b[j],替换a[i]为b[j]+f[i-1][j-1]可以得到f[i][j],这个也可传递
            //大问题到小问题 左、上，左上，所以我们只要初始化最边上两条边就行了
            /* 1 2 3 4 5 6 ... n
            1
            2
            3
            4
            5               \
            6                \  ^
            :                 \ |
            n              <——(n,n) 
            */
            f[i][j]=min(f[i-1][j],f[i][j-1])+1;
            if(a[i]==b[j]) f[i][j]=min(f[i][j],f[i-1][j-1]);
            else f[i][j]=min(f[i][j],f[i-1][j-1]+1);
            
        }
    }
}

int main()
{
    int n,m;
    scanf("%d",&n);
    scanf("%s",a+1);//从1开始存
    scanf("%d",&m);
    scanf("%s",b+1);

    dp(n,m);    

    printf("%d",f[n][m]);
    return 0;
}