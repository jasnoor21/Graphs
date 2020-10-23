#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <limits.h>

int r=0;
int e=0;

typedef struct Stack{
	unsigned int cap;
	int top;
	int*arr;
}STACK;

int a=0,b=0;

STACK* makeStack(unsigned int cap){
	STACK* stack=(STACK*)malloc(sizeof(STACK));
	stack->cap=cap;
	stack->top=-1;
	stack->arr=(int*)malloc(stack->cap*sizeof(int));
	return stack;
}

typedef struct Queue{
	unsigned int cap;
	int start,end,size;
	int*brr;
}QUEUE;

QUEUE* makeQueue(unsigned int cap){
	QUEUE* queue=(QUEUE*)malloc(sizeof(QUEUE));
	queue->cap=cap;
	queue->start=0;
	queue->end=cap-1;
	queue->size=0;
	queue->brr=(int*)malloc(queue->cap*sizeof(int));
	return queue;
}
//stack functions

int SisEmpty(STACK*stack){
	if(stack->top==-1)return 1;
	else{return 0;}
}

int SisFull(STACK*stack){
	if(stack->top==stack->cap-1)return 1;
	else{return 0;}
}

void push(STACK*stack, int data){
	if(stack->top==stack->cap-1){printf("Error ");return;}
	stack->arr[++stack->top]=data;a++;return;

}

int pop(STACK*stack){
	if(stack->top==-1){return 0;}
	int k=stack->arr[stack->top--];a--;return k;
}

int Ssize(STACK*stack){
	return a;
}

//queue functions

int QisFull(QUEUE* queue){
	if(queue->size == queue->cap)return 1;
	else{return 0;}
}

int QisEmpty(QUEUE* queue){
	if(queue->size == 0)return 1;
	else{return 0;}
}

int Qsize(QUEUE*queue){
	return(queue->size);
}

void enqueue(QUEUE* queue, int data)
{
    if (queue->size == queue->cap)
        return ;
    queue->end = (queue->end + 1)%queue->cap;
    queue->brr[queue->end] = data;
    queue->size = queue->size + 1;

}


int dequeue(QUEUE* queue)
{
    if (queue->size == 0)
        return 0;
    int item = queue->brr[queue->start];
    queue->start = (queue->start + 1)%queue->cap;
    queue->size = queue->size - 1;
    //printf("%d ",item);
    return item;
}


// adjcency list funtions
struct Edge
{
    int src, dest, weight;
};

struct Graph
{
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
    return graph;
}


//BFS for undirected graph function
void BFSud(int*arr,int n,int S){
	int s=S-1;
	QUEUE*qu=makeQueue(n);
	char color[n];
	//int dist[n];
	for(int i=0;i<n;i++){
		color[i]='w';
		//dist[i]=0;
	}
	enqueue(qu,s);
	color[s]='g';
	int c1=0;
	int c2=0;
	int c3=0;
	int u;
	while(!QisEmpty(qu)){
		u=dequeue(qu);
		c1=0;
		for(int f=0;f<n;f++){
			if(*(arr+u*n+f)){
				if(color[f]=='w'){
					color[f]='g';
					c1++;c2++;
					enqueue(qu, f);
				}

			}
			color[u]='b';
		}
		if(c1){printf("%d ",c1 );}
	}
	color[s]='b';
	printf("%d %d ",0,c2);
	for(int p=1;p<n;p++){
		for(int z=0;z<p;z++){
			if(*(arr+p*n+z)){
				c3++;
			}
		}
	}
	printf("%d\n",(c3-c2));
}

// BFS for directed graph

void BFSd(int*arr,int n,int S){
	int s=S-1;
	QUEUE*qu=makeQueue(n);
	char color[n];
	int par[n];
	for(int i=0;i<n;i++){
		color[i]='w';
		par[i]=-1;
	}
	enqueue(qu,s);
	color[s]='g';
	int c1=0;
	int c2=0;
	int c3=0;
	int c4=0;
	int back=0;
	int cross=0;
	int u;
	while(!QisEmpty(qu)){
		u=dequeue(qu);
		c1=0;
		for(int f=0;f<n;f++){
			if(*(arr+u*n+f)){
				c3++;
				if(color[f]=='w'){
					color[f]='g';
					par[f]=u;
					c1++;c2++;
					enqueue(qu, f);
					*(arr+u*n+f)=0;
				}
				if(color[f]=='g')back++;
				if(color[f]=='b')back++;
			}
			color[u]='b';
		}
		if(c1){printf("%d ",c1 );}
	}

	int count =0;int g,h;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(*(arr+i*n+j)){
				int y=par[i];
				while(par[y]>-2){
					count++;g= j;h=i;
					if(y==j){c4++;break;}
					if(y==-1){break;}
					y=par[y];
				}
			}
		}
	}
	printf("0 %d %d 0 %d \n",c2,c4,c3-c2-c4);
	/*
	printf("%d %d %d\n",c2, c3, c4 );
	printf("%d %d %d %d\n%d %d %d\n",par[0],par[1],par[2],par[par[3]], count,h,g );*/
	
}

//dijkastra algorithm

void DIJ(struct Graph* graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];
    int i,j;
    for (i = 0; i < V; i++)
        {dist[i]   = 999999;}
    dist[src] = 0;
    for (i = 1; i <= V-1; i++)
    {
        for (j = 0; j < E; j++)
        {

            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] + weight < dist[v])
                {dist[v] = dist[u] + weight;}
        }
    }
    for (i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] + weight < dist[v]){
            //printf("-1");
            return;
        }
    }
    for(int i=0;i<V;i++){
        printf("%d ",dist[i]);
    }
   	printf("\n");
    return;
}

//DFS Undireceted

void DFS(int*arr,int n,int S,int D){
	int s=S-1;
	int color[n];
	int par[n];
	int disc[n];
	int fin[n];
	int c1=0;
	int c2=0;
	for(int i=0;i<n;i++){
		color[i]=0;
		par[i]=-1;
		disc[i]=99999;
		fin[i]=99999;
	}
	int time=0;
	DFSVis(arr,n,s,color,par,disc,fin,&time,&c1,&c2);
	/*for(int i=0;i<n;i++){
		printf("%d ",disc[i]);
	}
	printf("\n");
	for(int i=0;i<n;i++){
		printf("%d ",fin[i]);
	}
	printf("\n" );*/

	int tree=r;
	int fwd=0;
	int back=0;
	int cross=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(*(arr+(n*i)+j)){
			if(disc[i]+1 <disc[j] && fin[j]+1 <fin[i]  )fwd++;
			if(disc[i] >disc[j] && fin[j] >fin[i])back++;
			if(fin[i]<disc[j] )cross++;
			}
		}
	}
	//printf("%d\n",e/2 );
	if(!D)printf("%d %d %d\n",fin[s],tree,(e/2)-tree);
	if(D)printf("%d %d %d %d %d\n",fin[s],tree,back,fwd,cross);r=0;
}

void DFSVis(int*arr,int n,int s,int *color,int *par,int *disc,int *fin,int *time,int *c1,int *c2){
	(*(color+s))=1;
	(*time)++;
	(*(disc+s))=*time;
	//printf(" t=%d  ",*time);
	for(int j=0;j<n;j++){
            //int a=*s;
			
			if(*(arr+(n*s)+j)){
				//printf(" col %d \n", *(color+j));
				if(*(color+j)==0){
					//printf("jasn\n");
					*(par+j)=s;r++;
					//printf("r %d\n",r );
					DFSVis(arr,n,j,color,par,disc,fin,time,&c1,&c2);
				}
				else{(*c2)++;}
			}
		}
	*(color+s)=2;
	(*time)++;
	*(fin+s)=*time;
}

//DFS Directed

/*void DFSd(int*arr, int n,int S){
	int s=S-1;
	char color[n];
	int par[n];
	int disc[n];
	int fin[n];
	for(int i=0;i<n;i++){
		color[i]='b';
		par[i]=-1;
		disc[i]=99999;
		fin[i]=99999;
	}

}*/

//Topological sorting
void topo(int*arr,int n){
	int ind[n];
	int c1;
	for(int i=0;i<n;i++){
		c1=0;
		for(int j=0;j<n;j++){
			if(*(arr+n*j+i)){c1++;}
		}
		ind[i]=c1;
	}
	int min=0;
	int k=0;
	for(int j=0;j<n;j++){
		min=ind[0];
		k=0;
		for(int i=0;i<n;i++){
			if(ind[i]<min){min=ind[i];k=i;}
		}
		printf("%d ",k+1);
		ind[k]=99999;
	}
	printf("\n");
	return;
}



//Bellman ford

void BellmanFord(struct Graph* graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];
    int i,j;
    int c1=0;
    int c2=0;
    for (i = 0; i < V; i++)
        {dist[i]   = 999999;}
    dist[src] = 0;
    for (i = 1; i <= V-1; i++)
    {
        for (j = 0; j < E; j++)
        {
            c1++;
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] + weight < dist[v])
                {dist[v] = dist[u] + weight;c2++;}
        }
    }
    for (i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] + weight < dist[v]){
            printf("-1");return;
        }
    }
    for(int i=0;i<V;i++){
        printf("%d ",dist[i]);
    }
    printf("%d %d\n",c1,c2);
    return;
}










int main(){
int t;
struct Graph* graph;
scanf("%d",&t);
int N,D,s,q;
for(int i=0;i<t;i++){
	scanf("%d",&q);

		if(q==1){
			scanf("%d %d %d",&N,&D,&s);
			int arr[N][N];
		    for(int i=0;i<N;i++){
		        for(int j=0;j<N;j++){
		    scanf("%d",&arr[i][j]);
		    }}
		    if(D==0){BFSud(arr,N,s);}
		    if(D==1){BFSd(arr,N,s);}
			}

		else if(q==2){
			scanf("%d %d %d",&N,&D,&s);
			int brr[N][N];
		    for(int i=0;i<N;i++){
		        for(int j=0;j<N;j++){
		    scanf("%d",&brr[i][j]);
		    if(brr[i][j])e++;
		    }}
		    DFS(brr,N,s,D);
		    e=0;
		   // if(D==0){DFSd();}
		//    if(D==0){DFSud(brr,N,s);}
		}



		else if(q==3){
			scanf("%d",&N);
			int crr[N][N];
		    for(int i=0;i<N;i++){
		        for(int j=0;j<N;j++){
                    scanf("%d",&crr[i][j]);
		    }}
		    topo(crr,N);
			}




        else if(q==4){
			int N,D,s;
			scanf("%d %d %d",&N,&D,&s);
            s--;
			int x;
			int c=0;
			int error1=0;
			//temporary array
			int arr[N][N];
			for(int i=0;i<N;i++){
		        for(int j=0;j<N;j++){
                    scanf("%d",&arr[i][j]);
                    x=arr[i][j];
                    if(x<0){error1++;}
                    if(x!= 0 && x!= 999999 ){c++;}
		    		}
				}
		    	graph = createGraph(N, c);

		    	c=0;
		    	for(int i=0;i<N;i++){
		        	for(int j=0;j<N;j++){
                        x=arr[i][j];
		        		if(!(x== 0 || x== 999999 || x==-999999)){
		        			graph->edge[c].src=i ;
        					graph->edge[c].dest= j;
        					graph->edge[c].weight= arr[i][j];
        					c++;
		        		}
		        	}
		        }
                //printf("singh %d\n",c);
        		if(!error1)DIJ(graph, s);
        		if(error1){printf("%d \n",-1);}

			}


		else if(q==5){
			int z,D,s;
			//printf("jasn\n");
			scanf("%d %d %d",&z,&D,&s);
            s--;
			int x;
			int c=0;
			//temporary array
			int arr[z][z];
			for(int i=0;i<z;i++){
		        for(int j=0;j<z;j++){
                    scanf("%d",&arr[i][j]);
                    x=arr[i][j];
                    if(x!= 0 && x!= 999999 && x!=-999999){c++;}
		    		}
				}
               //	printf("jasnoor %d\n",c );
		    	graph = createGraph(z, c);
		    	//printf("singh\n");
		    	c=0;
		    	for(int i=0;i<z;i++){
		        	for(int j=0;j<z;j++){
                        x=arr[i][j];
		        		if(!(x== 0 || x== 999999 || x==-999999)){
		        			graph->edge[c].src=i ;
        					graph->edge[c].dest= j;
        					graph->edge[c].weight= arr[i][j];
        					c++;
		        		}
		        	}
		        }
              //  printf("narang %d\n",c);
       			BellmanFord(graph, 0);

			}

		else{printf("%d",-1);}

	}
	return 0;
}









