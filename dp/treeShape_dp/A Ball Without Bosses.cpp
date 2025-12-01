//first try:WA
//错误原因：元素和元素之间是互相有联系的
//我在状态转移时只考虑到了因新元素的加入导致部分元素的退出
//没有考虑到部分元素退出还可能导致部分元素可加入
//这说明加入一个元素的影响是递归影响的，而非线性的
//那我这样就实现不了了
/*

#include<iostream>
#include<cstring>
using namespace std;
const int N=6010,INF=1e9;

int happy[N];
int h[N],e[N],ne[N],idx;
int f[N];

void add_edge(int a,int b)//a->b,a为上司，我想记录一个人有多少下属
{
    e[idx]=b;
    ne[idx]=h[a];
    h[a]=idx++;
}

//计算因为i号职员加入，导致的人员退出，造成的快乐指数变化
int driveAway(int number)
{
    int delta=0;
    for(int i=h[number];i!=-1;i=ne[i])
    {
        int j=e[i];
        int t=happy[j];
        delta+=t;
    }

    return -delta;
}

void dp(int n)
{
    for(int i=1;i<=n;i++) f[i]=-INF;
    f[0]=0;

    for(int i=1;i<=n;i++)
    {
        int delta=driveAway(i);
        f[i]=max(f[i-1],f[i-1]+happy[i]+delta);
    }
}

int main()
{
    memset(h,-1,sizeof h);
    int n;
    scanf("%d",&n);

    for(int i=1;i<=n;i++) scanf("%d",&happy[i]);
    for(int i=1;i<=n;i++)
    {
        int L,K;
        scanf("%d%d",&L,&K);
        add_edge(K,L);
    }

    dp(n);

    printf("%d",f[n]);
    return 0;
}

*/

#include<iostream>
#include<cstring>
using namespace std;
const int N=6010,INF=1e9;

int happy[N];
int h[N],e[N],ne[N],idx;

//如何去使用结点的递归影响关系呢？
//一个人加入不仅会逼退一些人，还会给一些人加入的可能
//这个关系是当前结点影响了子节点，子节点又影响了它的子节点导致的
//这种递归关系容易联想到树的dfs
//假如状态设为f[N],则f[i]以i为根节点的树的最大happy值
//如果i选了，则f[k](k为i的邻接点)，肯定本身就不包含k的happy值
//如果i没选，则f[k]可能包含自身的happy值，也可能不包含自身的happy值
//为了方便描述选没选，我们可以引入第二个维度，来表示
//int f[N][2]
//f[i][0],表示没选i;f[i][1],表示选了i

int f[N][2];//那么答案就是max(f[root][0],f[root][1]);
bool has_parent[N];//用于找root

void add_edge(int a,int b)//a->b,a为上司，我想记录一个人有多少下属
{
    e[idx]=b;
    ne[idx]=h[a];
    h[a]=idx++;
}

void dfs(int r,int n)
{
    f[r][1]=happy[r];
    f[r][0]=0;

    for(int i=h[r];i!=-1;i=ne[i])
    {
        int s=e[i];
        dfs(s,n);

        f[r][1]+=f[s][0];
        f[r][0]+=max(f[s][0],f[s][1]);   
    }
}

int main()
{
    memset(h,-1,sizeof h);
    int n;
    scanf("%d",&n);

    for(int i=1;i<=n;i++) scanf("%d",&happy[i]);
    for(int i=1;i<n;i++)
    {
        int L,K;
        scanf("%d%d",&L,&K);
        add_edge(K,L);
        has_parent[L]=true;
    }

    int root=0;
    for(int i=1;i<=n;i++)
    {
        if(!has_parent[i])
        {
            root=i;
            break;
        }
    }

    dfs(root,n);

    int res=max(f[root][0],f[root][1]);
    printf("%d",res);
    return 0;
}