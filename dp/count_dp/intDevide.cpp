
/***********first try:WA********** */
//错的原因在于，我这样做会有大量的重复
//比如 2，2，1，1 可以由f[4]*f[2],f[5]*f[1]....得到，无法处理重复值
/*

#include<iostream>
using namespace std;
const int mol=1e9+7,N=1010;

int f[N];

void dp(int n)
{
    //分析:f[n]代表整数n的划分方法
    //f[n]怎么去由小状态转移过来呢
    //(1,n-1),(2,n-2),(3,n-3)....
    //(1,1,n-2),(1,2,n-3).....
    //组合是在是太多了
    //我在想(3,n-3)和(1,2,n-3)的联系
    //即f[3]+f[n-3]和f[1]+f[2]+f[n-3]的关系。貌似没什么关系
    //所以我在想改变下状态表示，->f[k][n]:整数n划分为k个数
    //好像也行不通.....
    //f[k]+f[n-k]和f[v]+f[l]+f[p]....+f[n-k]
    //v,l,p.....只是k的一种划分方式，也就是f[k]包含前者
    
    for(int i=0;i<=n;i++) f[i]=1;

    //(0,n)(1,n-1),(2,n-2),(3,n-3)......(n-3,3),(n-2,2),(n-1,1),(n,0)
    //会有重复
    //0,1, 2 ,3,4  i/2
    //0,1,2 ,3,4,5 i/2
    for(int i=1;i<=n;i++)
    {
        for(int k=0;k<=i/2&&i-k>=0;k++)
        {
            //有问题
            if(k==i-k) f[i]+=(f[k]*f[k]-1);
            else f[i]+=(f[k]*f[i-k]);
        }
        f[i]-=1;
    }
}


int main()
{
    int n;
    scanf("%d",&n);

    dp(n);

    printf("%d",f[n]);
    return 0;
}

*/


/*******second try:***** */
#include<iostream>
using namespace std;
const int N=1010,mol=1e9+7;

//看成完全背包问题，f[i][j]选前i个物品，体积为j，存储总的划分状态
int f[N][N];

void dp(int n)
{   
    for(int i=0;i<=n;i++) f[i][0]=1;
    
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(j>=i) f[i][j]=(f[i-1][j]+f[i][j-i])%mol;
            else f[i][j]=f[i-1][j]%mol;
        }
    }

    return;
}

int main()
{
    int n;
    scanf("%d",&n);

    dp(n);

    printf("%d",f[n][n]);
}