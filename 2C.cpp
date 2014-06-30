#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
const double eps=1e-8;
int dcmp(double x)
{
	if(fabs(x)<eps) return 0;
	else return x<0?-1:1;
}
struct point
{
	double x,y;
	point(double x=0,double y=0):x(x),y(y){}
};
point operator+(point a,point b){return point(a.x+b.x,a.y+b.y);}
point operator-(point a,point b){return point(a.x-b.x,a.y-b.y);}
point operator*(point a,double p){return point(a.x*p,a.y*p);}
bool operator==(point a,point b)
{
	return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}
double dot(point a,point b){return a.x*b.x+a.y*b.y;}
double length(point a){return sqrt(dot(a,a));}
double cross(point a,point b){return a.x*b.y-a.y*b.x;}
point normal(point a)
{
	double L=length(a);
	return point(-a.y/L,a.x/L);
}
point getlineinter(point p,point v,point q,point w)
{
	point u=p-q;
	double t=cross(w,u)/cross(v,w);
	return p+v*t;
}
struct circle
{
	point c;
	double r;
	circle(point c=point(0,0),double r=0):c(c),r(r){}
	point getpoint(double a)
	{
		return point(c.x+cos(a)*r,c.y+sin(a)*r);
	}
};
double angle(point v){return atan2(v.y,v.x);}
int getlinecircleinter(point p,point v,circle C,double& t1,double& t2,vector<point>& sol)
{
	double a=v.x,b=p.x-C.c.x,c=v.y,d=p.y-C.c.y;
	double e=a*a+c*c,f=2*(a*b+c*d),g=b*b+d*d-C.r*C.r;
	double delta=f*f-4*e*g;
	if(dcmp(delta)<0) return 0;
	if(dcmp(delta)==0)
	{
		t1=t2=-f/(2*e);
		sol.push_back(p+v*t1);
		return 1;
	}
	t1=(-f-sqrt(delta))/(2*e);sol.push_back(p+v*t1);
	t2=(-f+sqrt(delta))/(2*e);sol.push_back(p+v*t2);
	return 2;
}
int getcircleinter(circle C1,circle C2,vector<point>& sol)
{
	double d=length(C1.c-C2.c);
	if(dcmp(d)==0)
	{
		if(dcmp(C1.r-C2.r)==0) return -1;
		return 0;
	}
	if(dcmp(C1.r+C2.r-d)<0) return 0;
	if(dcmp(fabs(C1.r-C2.r)-d)>0) return 0;

	double a=angle(C2.c-C1.c);
	double da=acos((C1.r*C1.r+d*d-C2.r*C2.r)/(2*C1.r*d));
	point p1=C1.getpoint(a-da),p2=C1.getpoint(a+da);
	sol.push_back(p1);
	if(p1==p2) return 1;
	sol.push_back(p2);
	return 2;
}
int get(double r1,double r2,double x1,double x2,double y1,double y2,circle& CC)
{
	double A=(2*x1*r2*r2-2*x2*r1*r1)/(r2*r2-r1*r1);
	double B=(2*y1*r2*r2-2*y2*r1*r1)/(r2*r2-r1*r1);
	double C=(r2*r2*(x1*x1+y1*y1)-r1*r1*(x2*x2+y2*y2))/(r2*r2-r1*r1);
	double D=A*A/4+B*B/4-C;
	if(dcmp(D)<0) return 0;
	
	CC.c.x=A/2;CC.c.y=B/2;
	CC.r=sqrt(D);

	return 1;
}
int main()
{
	int r[3],x[3],y[3];
	point p[3];
	vector<point> sol;
	for(int i=0;i<3;i++) 
	{
		scanf("%d%d%d",&x[i],&y[i],&r[i]);
		p[i]=point(x[i],y[i]);
	}
	if(r[0]==r[1] && r[1]==r[2])
	{
		point v1=p[0]-p[1],v2=p[1]-p[2];
		point n1=normal(v1),n2=normal(v2);
		point m1=(p[0]+p[1])*0.5,m2=(p[1]+p[2])*0.5;
		point ans=getlineinter(m1,n1,m2,n2);
		printf("%.5f %.5f\n",ans.x,ans.y);
	}
	else if(r[0]==r[1])
	{
		circle C;
		if(get(r[0],r[2],x[0],x[2],y[0],y[2],C))
		{
			point v=p[0]-p[1];
			point n=normal(v);
			point m=(p[0]+p[1])*0.5;
			double t1,t2;
			getlinecircleinter(m,n,C,t1,t2,sol);
			double maxangle=0;
			int ans =-1;
			for(int i=0;i<sol.size();i++)
			{
				point P=sol[i]-r[0];
				double tmp=r[0]/length(P);
				double ang=2*asin(tmp);
				if(dcmp(maxangle-ang)<0)
				{
					maxangle=ang;
					ans=i;
				}
			}
			if(ans!=-1) printf("%.5f %.5f\n",sol[ans].x,sol[ans].y);
		}
	}
	else if(r[0]==r[2])
	{
		circle C;
		if(get(r[0],r[1],x[0],x[1],y[0],y[1],C))
		{
			point v=p[0]-p[2];
			point n=normal(v);
			point m=(p[0]+p[2])*0.5;
			double t1,t2;
			getlinecircleinter(m,n,C,t1,t2,sol);
			double maxangle=0;
			int ans =-1;
			for(int i=0;i<sol.size();i++)
			{
				point P=sol[i]-r[0];
				double tmp=r[0]/length(P);
				double ang=2*asin(tmp);
				if(dcmp(maxangle-ang)<0)
				{
					maxangle=ang;
					ans=i;
				}
			}
			if(ans!=-1) printf("%.5f %.5f\n",sol[ans].x,sol[ans].y);
		}
	}
	else if(r[1]==r[2])
	{
		circle C;
		if(get(r[0],r[2],x[0],x[2],y[0],y[2],C))
		{
			point v=p[2]-p[1];
			point n=normal(v);
			point m=(p[2]+p[1])*0.5;
			double t1,t2;
			getlinecircleinter(m,n,C,t1,t2,sol);
			double maxangle=0;
			int ans =-1;
			for(int i=0;i<sol.size();i++)
			{
				point P=sol[i]-r[0];
				double tmp=r[0]/length(P);
				double ang=2*asin(tmp);
				if(dcmp(maxangle-ang)<0)
				{
					maxangle=ang;
					ans=i;
				}
			}
			if(ans!=-1) printf("%.5f %.5f\n",sol[ans].x,sol[ans].y);
		}
	}
	else
	{
		circle C1,C2;
		if(get(r[0],r[1],x[0],x[1],y[0],y[1],C1) && get(r[0],r[2],x[0],x[2],y[0],y[2],C2))
		{
			getcircleinter(C1,C2,sol);
			double maxangle=0;
			int ans=-1;
			for(int i=0;i<sol.size();i++)
			{
				point P=sol[i]-r[0];
				double tmp=r[0]/length(P);
				double ang=2*asin(tmp);
				if(dcmp(maxangle-ang)<0)
				{
					maxangle=ang;
					ans=i;
				}
			}
			if(ans!=-1) printf("%.5f %.5f\n",sol[ans].x,sol[ans].y);
		}
	}
	return 0;
}
