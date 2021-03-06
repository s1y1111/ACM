//描述较好的：http://www.cnblogs.com/dolphin0520/archive/2011/08/26/2155202.html
//证明较好的：http://blog.csdn.net/reskip/article/details/50682436

/*
其核心思想：S中的点为已知最短路径点的集合
设所有的点为V，源点为v，已经确定最短路径的点s（也就是v-s的最短路径已知）放入S中，那么点就被分为S和V-S两类
!!!!那么在V-S中选一个s（dist[s]最小,s in V-S），那么这个v-s的最短路径值就是dist[s]，也就是未定点中dist最小的最短路径已知
为什么？这才是重点啊！！
因为dist[s]<=dist[si](si in V-S),如果经过某个si(si in V-S),那么路径总和就是v-si-s,即dist[si]+edge(si,s)>dist[si]>dist[s]
(也就是说最短路径不会经过V-S中的点，而最短路径的值是根据不断经过S中的点不断更新来的，这也是网上说的为啥最短路径一定只经过S中的点)
所以每个放进S的点最短路径都是已知的。

注意每放进一个点s进S中，要更新dist[i]=min(dist[i],dist[s]+edge(s,i))

showPath()中的点都是根据S中的点一点一点更新来的 path[i]=v表示到i的最短路径i之前紧接的点为v
*/


#include <iostream>
#include <stack>
#define M 100
#define N 100
using namespace std;

typedef struct node
{
    int matrix[N][M];      //邻接矩阵 
    int n;                 //顶点数 
    int e;                 //边数 
}MGraph; 

void DijkstraPath(MGraph g,int *dist,int *path,int v0)   //v0表示源顶点 
{
    int i,j,k;
    bool *visited=(bool *)malloc(sizeof(bool)*g.n);
    for(i=0;i<g.n;i++)     //初始化 
    {
        if(g.matrix[v0][i]>0&&i!=v0)
        {
            dist[i]=g.matrix[v0][i];
            path[i]=v0;     //path记录最短路径上从v0到i的前一个顶点 
        }
        else
        {
            dist[i]=INT_MAX;    //若i不与v0直接相邻，则权值置为无穷大 
            path[i]=-1;
        }
        visited[i]=false;
    }
    path[v0]=v0;
    dist[v0]=0;
    visited[v0]=true;
    for(i=1;i<g.n;i++)     //循环扩展n-1次 
    {
        int min=INT_MAX;
        int u;
        for(j=0;j<g.n;j++)    //寻找未被扩展的权值最小的顶点 
        {
            if(visited[j]==false&&dist[j]<min)
            {
                min=dist[j];
                u=j;        
            }
        } 
        visited[u]=true;
        for(k=0;k<g.n;k++)   //更新dist数组的值和路径的值 
        {
            //g.matrix[u][k]>0表示u,k之间有边
            if(visited[k]==false&&g.matrix[u][k]>0&&min+g.matrix[u][k]<dist[k])
            {
                dist[k]=min+g.matrix[u][k];
                path[k]=u; 
            }
        }        
    }    
}

void showPath(int *path,int v,int v0)   //打印最短路径上的各个顶点 
{
    stack<int> s;
    int u=v;
    while(v!=v0)
    {
        s.push(v);
        v=path[v];
    }
    s.push(v);
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
} 

int main(int argc, char *argv[])
{
    int n,e;     //表示输入的顶点数和边数 
    while(cin>>n>>e&&e!=0)
    {
        int i,j;
        int s,t,w;      //表示存在一条边s->t,权值为w
        MGraph g;
        int v0;
        int *dist=(int *)malloc(sizeof(int)*n);
        int *path=(int *)malloc(sizeof(int)*n);
        for(i=0;i<N;i++)
            for(j=0;j<M;j++)
                g.matrix[i][j]=0;
        g.n=n;
        g.e=e;
        for(i=0;i<e;i++)
        {
            cin>>s>>t>>w;
            g.matrix[s][t]=w;
        }
        cin>>v0;        //输入源顶点 
        DijkstraPath(g,dist,path,v0);
        for(i=0;i<n;i++)
        {
            if(i!=v0)
            {
                showPath(path,i,v0);
                cout<<dist[i]<<endl;
            }
        }
    }
    return 0;
}