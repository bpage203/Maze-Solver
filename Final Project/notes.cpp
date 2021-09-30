#include <iostream>
#include <climits>
using namespace std;
#define vertex 7 //total number of vertices in Graph
int minDist(int dist[], bool Dset[]){
  int min=INT_MAX,index;
  for(int v=0; v<vertex;v++){
    if(Dset[v]==false&&dist[v]<=min){
      min=dist[v];
      index=v;
    }
  }
  return index;
}

void dijkstra(int graph[vertex][vertex],int src){ //using matrix is inefficient cuz its sparce, find another way
  int dist[vertex];
  bool Dset[vertex];
  for(int i=0;i<v;i++){
    Dset[i]=false;
  }
  dist[src]=0;
  for(int c=0; c<vertex; c++){ //think im missing something after this line
    for(int u=0; u<vertex; u++){
      if(!Dset[v]&&graph[u][v]&&dist[u]!=INT_MAX&&dist[u]+graph[u][v]<min) dist[v]=dist[u]+graph[u][v];
    }
  }
  cout<<"Vertex\t\tDistance from source"<<endl;
  for(int i=0;i<vertex;i++){
  char c=65+i;
  cout<<c<<"\t\t"<<dist[i]<<endl;
  }
}


int main(){
  int graph[vertex][vertex]={{},{},{},{}};
  dijkstra(graph,0);
  return 0;
}
