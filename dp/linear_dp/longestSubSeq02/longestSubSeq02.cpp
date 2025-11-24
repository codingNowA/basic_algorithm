#include<iostream>
using namespace std;
const int N=1e5+10;

int a[N],f[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);


    return 0;
}



/*template code*/
/*
#include<iostream>
using namespace std;
const int N=1e5+10;
int a[N],f[N];

int b_search(int l, int r,int c)//找第一个大于a[i]的位置
{
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(f[mid]>=c) r=mid;
        else l=mid+1;  
    }

    return l; 
}

int main()
{
    int n;
    scanf("%d",&n);

    for(int i=1;i<=n;i++) scanf("%d",&a[i]);

    int cnt=0;
    f[0]=-2e9;
    for(int i=1;i<=n;i++)
    {
        if(f[cnt]<a[i]) f[++cnt]=a[i];
        else
        {
            int p=b_search(1,cnt,a[i]);
            f[p]=a[i];
        }
    }

    printf("%d",cnt);
    return 0;
}

*/