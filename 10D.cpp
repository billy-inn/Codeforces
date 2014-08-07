#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 510;
int n,m;
int a[maxn],b[maxn];
int dp[maxn][maxn];
int path[maxn][maxn];
void print(int i,int j,int pre)
{
	if(path[i][j]==0) 
	{
		if(j!=pre) printf("%d ",b[j]);
		return;
	}
	print(i-1,path[i][j],j);
	if(j!=pre) printf("%d ",b[j]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	memset(dp,0,sizeof(dp));
	memset(path,0,sizeof(path));
	for(int i=1;i<=n;i++)
	{
		int tmp=0,k=0;
		for(int j=1;j<=m;j++)
		{
			dp[i][j]=dp[i-1][j];
			path[i][j]=j;
			if(a[i]>b[j] && tmp<dp[i-1][j]) 
			{
				tmp=dp[i-1][j];
				k=j;
			}
			if(a[i]==b[j]) 
			{
				dp[i][j]=tmp+1;
				path[i][j]=k;
			}
		}
	}
	int ans=0,p=0;
	for(int i=1;i<=m;i++)
		if(ans<dp[n][i])
		{
			ans=dp[n][i];
			p=i;
		}
	printf("%d\n",ans);
	print(n,p,0);
	puts("");
	return 0;
}
