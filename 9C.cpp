#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	int ans=1;
	for(int i=1;i<10;i++)
	{
		int tmp;
		for(int j=0;j<(1<<i);j++)
		{
			tmp=1;
			for(int k=0;k<i;k++)
				tmp=tmp*10+((j&(1<<k))?1:0);
			if(tmp<=n) 
				ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
