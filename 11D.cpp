#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
LL dp[1<<19][19];
int vis[1<<19][19],n,m;
int g[19][19];
LL dfs(int st,int cur,int u)
{
	if(vis[st][u]) return dp[st][u];
	vis[st][u]=1;
	LL &ans=dp[st][u];
	ans=0;
	for(int v=cur;v<n;v++)
		if(g[u][v])
		{
			if(v==cur && st!=((1<<v)|(1<<u))) ans++;
			else if(v!=cur && ((st&(1<<v))==0)) ans+=dfs(st^(1<<v),cur,v);
		}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&n,&m);
	while(m--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		u--;v--;
		g[u][v]=g[v][u]=1;
	}
	LL ans=0;
	for(int i=0;i<n;i++) ans+=dfs((1<<i),i,i);
	cout<<ans/2<<"\n";
	return 0;
}
