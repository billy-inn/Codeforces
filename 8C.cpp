#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf=0x3fffffff;
typedef pair<int,int> pii;
struct point
{
	int x,y;
	point(int x=0,int y=0):x(x),y(y){}
};
int dp[1<<24],n;
pii dir[1<<24];
int all;
point o,p[50];
int dis(point a,point b){return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}
int dfs(int st)
{
	if(st==all) return 0;
	if(dp[st]!=-1) return dp[st];
	int& ans=dp[st];
	ans=inf;
	int u,st0;
	for(int i=0;i<n;i++)
		if(((1<<i)&st)==0)
		{
			u=i;
			st0=st|(1<<i);
			break;
		}
	for(int i=0;i<n;i++)
		if(((1<<i)&st0)==0)
		{
			int tmp=dfs(st0|(1<<i))+dis(p[i],p[u]);
			if(tmp<ans)
			{
				ans=tmp;
				dir[st]=make_pair(u,i);
			}
		}
	int tmp=dfs(st0)+dis(p[u],o);
	if(tmp<ans)
	{
		ans=tmp;
		dir[st]=make_pair(u,-1);
	}
	return ans;
}
void print(int st)
{
	if(st==all) return;
	int u=dir[st].first,v=dir[st].second;
	printf("%d %d ",u+1,v+1);
	if(v+1!=0) printf("0 ");
	st|=(1<<u);
	if(v!=-1) st|=(1<<v);
	print(st);
}
int main()
{
	memset(dp,-1,sizeof(dp));
	scanf("%d%d",&o.x,&o.y);
	scanf("%d",&n);
	int ans=0;
	for(int i=0;i<n;i++)
	{
		scanf("%d%d",&p[i].x,&p[i].y);
		ans+=dis(o,p[i]);
	}
	all=(1<<n)-1;
	ans+=dfs(0);
	printf("%d\n",ans);
	printf("0 ");
	print(0);
	puts("");
	return 0;
}
