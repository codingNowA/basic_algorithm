//first try:WA，思路出错了，详见那个状态转移方程
/*

#include<iostream>
#include<cstring>
using namespace std;
const int N=21;

int w[N][N],f[N][N];

//首先我想到距离问题本身具有最优子结构性质
//这意味着可以使用dp求解
//状态怎么设计呢？我先定义成最简单的f[i][j]
//f[i][j]:从结点i到结点j的最短哈密顿路径
//f[i][j]如何进行状态转移呢？
//最后一步是某个结点走向结点j，我们根据这个来划分
//f[i][j]=f[i][k]+w[k][j]
//但是这里有问题，因为如果f定义成哈密顿路径，
//f[a][b],无论a，b怎么变，都包含了所有的点
//也就是f[i][k]实际上也已经走了j了....
//那如果我定义f[i][j]为走i,i+1,i+2...,j-1,j这样路径的最小值呢
//answer就是f[1][n]
//思考，状态能够进行转移吗？
//f[i][j]似乎只能够由f[i][j-1]+w[j-1][j-1]转移而来
//这明显不对，因为从i到j不一定要顺序走，                               
//所以要扩张f的含义（即不限定走的顺序）,为了方便思考，令i<=j
//则f[i][j]=min(f[i][j],f[i][k]+w[k][j])   [i<=k<=j]
void dp(int n)
{
    memset(f,0x3f,sizeof f);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            for(int k=i;k<=j;k++)
            {
                f[i][j]=min(f[i][j],f[i][k]+w[k][j]);
                //这里用f[i][k]+w[k][j]进行转移
                //就跳过了k+1,k+2,...,j-1了！！！
                //这说明根本没法转移
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d",&n);

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&w[i][j]);

    dp(n);

    printf("%d",f[1][n]);
}

*/


//second try:
#include<iostream>
#include<cstring>
using namespace std;
const int N=21,M=1<<N;

int w[N][N],f[M][N];

//我看了标准答案的做法，状态表示为f[i][j]
//其中j代表从0走到j，走法为i
//i本身是一个二进制数,010111....，从右往左为第一位，到第n位
//其中第k位若为1，则代表会走k。为0则代表不走k
void dp(int n)
{
    memset(f,0x3f,sizeof f);
    f[1][1]=0; 

    for(int i=1;i<=(1<<n)-1;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if( (i>>(j-1))&1 )//能走到j
                for(int k=1;k<=n;k++)
                {
                    if( (i>>(k-1))&1 )//能走到k
                        f[i][j]=min(f[i][j],f[i-(1<<(j-1))][k]+w[k][j]);
                }
        }
    }
}

int main()
{
    int n;
    scanf("%d",&n);

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&w[i][j]);

    dp(n);

    printf("%d",f[(1<<n)-1][n]);
}
