#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
struct env
{
	int w,h,id;
	bool operator<(const env& tmp) const
	{
		return w<tmp.w;
	}
} e[5010];
int dp[5010];
int dir[5010];
int vis[5010];
int n,w,h,m=0;
int dfs(int u)
{
	if(vis[u]) return dp[u];
	vis[u]=1;
	dp[u]=1;
	dir[u]=-1;
	for(int i=u+1;i<m;i++) if(e[i].w > e[u].w && e[i].h > e[u].h)
	{
		int tmp=dfs(i);
		if(dp[u]<tmp+1)
		{
			dp[u]=tmp+1;
			dir[u]=i;
		}
	}
	return dp[u];
}
int main()
{
	scanf("%d%d%d",&n,&w,&h);
	for(int i=0;i<n;i++)
	{
		scanf("%d%d",&e[m].w,&e[m].h);
		e[m].id=i+1;
		if(e[m].w <= w || e[m].h <= h) continue;
		m++;
	}
	sort(e,e+m);
	memset(vis,0,sizeof(vis));
	int ans=0,p;
	for(int i=0;i<m;i++)
	{
		int tmp=dfs(i);
		if(ans<tmp)
		{
			ans=tmp;
			p=i;
		}
	}
	if(ans==0) puts("0");
	else
	{
		printf("%d\n",ans);
		while(p!=-1)
		{
			printf("%d ",e[p].id);
			p=dir[p];
		}
		puts("");
	}
	return 0;
}
