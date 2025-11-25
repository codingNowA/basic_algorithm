//******first try:WA*******/
/*主要是状态转移想错了，f[i][j]还可以由f[i][k]+a[k+1],f[k+1][j]这类转移而来*/
//而且这三个合并的时候，上面这个式子不对，in fact:f[i][j]=左+右+（左+中+右）=左+右+S[i]-S[j]
//其中S为前缀数组

/*
#include<iostream>
using namespace std;
const int N=310;

int f[N][N],a[N];

void dp(int n)
{
    //f分析可得，去初始化主对角线的位置就行
    for(int i=1;i<=n;i++) f[i][i]=a[i];
    
    // for(int i=1;i<=n;i++)
    // {
    //     for(int j=i+1;j<=n;j++)//j的范围存疑
    //     {
    //         f[i][j]=min(f[i+1][j]+a[i],f[i][j-1]+a[j]);
    //     }
    // }
    //这里错的原因，是因为小问题转移为大问题的方向不对
    //应该按主对角线方向一步步进行初始化 j-i=0,1,2,3,....n-1,一共n条对角线
    for(int k=0;k<n;k++)
    {
        for(int i=1;i<n&&i+k<=n;i++)
        {
            f[i][i+k]=min(f[i+1][i+k]+a[i],f[i][i+k-1]+a[i+k]);       
        }
    }
    
}

int main()
{
    int n;
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);//从1开始存
    
    
    dp(n);
    
    printf("%d\n",f[1][n]);
    return 0;
}

*/

#include<iostream>
using namespace std;
const int N=310,INF=1e9;

int f[N][N],S[N];

void dp(int n)
{
    //只有一个石头的情况下没有合并代价，所以初始化为0
    
    for(int len=1;len<=n-1;len++)
    {
        for(int i=1;i<=n;i++)
        {
            int j=i+len;
            if(j>n) break;//这里要记得检查，j不要超出范围
            
            f[i][j]=INF;
            for(int k=i;k<j;k++)//这里应该是取i~j-1,这样可以包含所有情况
            {
                f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]+S[j]-S[i-1]);
            }
        }
    }
    
}

int main()
{
    int n;
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++) 
    {
        int t;
        scanf("%d",&t);
        S[i]=S[i-1]+t;
    }
    
    dp(n);
    
    printf("%d\n",f[1][n]);
    return 0;
}