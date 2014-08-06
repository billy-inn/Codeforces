#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=1000010;
long long c[10];
int f[maxn];
int prime[maxn];
int vis[maxn];
int d(int x)
{
	int tmp=0;
	while(x)
	{
		tmp+=x%10;
		x/=10;
	}
	return tmp<10?tmp:d(tmp);
}
void init()
{
	memset(vis,0,sizeof(vis));
	f[1]=1;
	int tot=0;
	for(int i=2;i<=1000000;i++)
	{
		if(!vis[i])
		{
			f[i]=2;
			prime[tot++]=i;
		}
		for(int j=0;j<tot;j++)
		{
			if(i*prime[j]>1000000) break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0) 
			{
				int tmp=i;
				while(tmp%prime[j]==0) tmp/=prime[j];
				f[i*prime[j]]=(f[i/tmp]+1)*f[tmp];
				break;
			}
			else f[i*prime[j]]=f[i]*f[prime[j]];
		}
	}
}
int main()
{
	init();
	int n;
	scanf("%d",&n);
	long long res=0;
	for(int i=1;i<=n;i++)
	{
		c[d(i)]++;
		res+=f[i];
	//	cout<<f[i]<<endl;
	}
	long long ans=0;
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
		{
			long long k=d(i*j),tmp;
			if(i==j) tmp=c[i]*c[i];
			else tmp=c[i]*c[j];
			ans+=tmp*c[k];
		}
	//cout<<res<<" "<<ans<<endl;
	cout<<ans-res<<endl;
	return 0;
}
