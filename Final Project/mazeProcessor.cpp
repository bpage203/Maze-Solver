#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

//maybe output an ascii version of map with i++ variable at every node for start and end specification

struct node{
  string type;
  node* north;
  node* east;
  node* south;
  node* west;
  int northDistance;
  int eastDistance;
  int southDistance;
  int westDistance;
};

node* last;
node* current;
node* visited[];
int* path[];
int* fastestPath[];
int fastestDistance=0;
int distanceGuess; //inputted guess shortest distance, used for choosing best path

struct vertex;

struct Edge
{
    vertex *v;
    int distance;
};

struct vertex
{
    int id;
    bool visited;
    vector<Edge> Edges;
};

class Graph
{
  public:
    Graph();
    ~Graph();
    void addVertex(int index, int sum, bool nulls[]);
    void addEdge(int id1, int id2, int distance);
    void displayEdges();
    void printDFT();
    void printBFT();
    void setAllVerticesUnvisited();

  private:
    std::vector<vertex> vertices; //stores vertices

    vertex *findVertex(int id);
    void BFT_traversal(vertex *v);
    void DFT_traversal(vertex *v);

};

Graph::Graph(vector map){ //assuming path designated w a 1
  bool nulls[4];
  int edges[4];
  int sum;
  for(int i=0; i<map[0].size(); i++){
    for(int j=0; j<map[0][0].size(); j++){
      nulls={0,0,0,0};
      edges={map[i][j-1],map[i][j+1],map[i+1][j],map[i-1][j]};
      for(int k=0; k<4; k++){
        sum+=edges[k];
        if(edges[k]!=1) nulls[k]=1;
      }
      if(sum==3||sum==1) g.addVertex(map[i][j],sum,nulls);
    }
  }
}

Graph::~Graph(){

}

bool visited(node* next){
  list<int>::iterator i;
  for(i=visited.front(); i!=visited.end(); ++i){
    if(next==visited[i]) return true;
  }
  return false;
}

node* backTrack(int* path){
  pop(path);
  curr=last;
  return curr;
}

int findDistance(node* curr, int* path){ //curr starts as start
  int sum = 0;
  list<int>::iterator i;
  for(i=path.front(); i!=path.end(); ++i){
    switch(path[i]){
      case 1:
        sum+=curr->northDistance;
        curr=curr->north;
        break;
      case 2:
        sum+=curr->eastDistance;
        curr=curr->east;
        break;
      case 3:
        sum+=curr->southDistance;
        curr=curr->south;
        break;
      case 4:
        sum+=curr->westDistance;
        curr=curr->west;
        break;
    }
  }
  return sum;
}

vertex* Graph::findVertex(std::string name){
  vector<vertex>::iterator i;
  int counter=0;
  for(i=vertices.begin(); i!=vertices.end(); i++){
    if(i->name==name) return &vertices[counter];
    counter++;
  }
}

vector* readFile(int argc, char* argv[]){
  ifstream imageFile(argv[1]);
  string line;
  vector<vector<int>> map;
  while(getline(imageFile,line)){
    stringstream ss;
    string cell;
    vector<int> row;
    while(getline(ss,cell,',')){
      row.push_back(stoi(cell));
    }
    map.push_back(row);
  }
  return map;
}

Graph::addVertex(int index, int sum, bool nulls[]){
  vertex* newVertex = new vertex;
  newVertex->id=id;
  if(sum==3) newVertex->type="intersection";
  else if(sum==1) newVertex->type="edge";
  if(nulls[0]) newVertex->north=NULL;
  if(nulls[1]) newVertex->south=NULL;
  if(nulls[2]) newVertex->east=NULL;
  if(nulls[3]) newVertex->west=NULL;
  vertices.push_back(*newVertex);

}

void Graph::addEdge(std::string city1, std::string city2, int distance){
  Edge* newEdge = new Edge;
  vertex* first;
  vertex* second;
  first=findVertex(city1);
  second=findVertex(city2);
  newEdge->v=second;
  newEdge->distance=distance;
  first->Edges.push_back(*newEdge);
}

void Graph::displayEdges(){
  vector<vertex>::iterator i;
  vector<Edge>::iterator j;
  bool first=true;
  for(i=vertices.begin(); i!=vertices.end(); ++i){
    cout<<i->name<<"-->";
    first=true;
    for(j=i->Edges.begin(); j!=i->Edges.end(); ++j){
      if(first==true) cout<<j->v->name<<" ("<<j->distance<<" miles)";
      else cout<<"***"<<j->v->name<<" ("<<j->distance<<" miles)";
      first=false;
    }
    cout<<endl;
  }
}

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
  for(int c=0; c<vertex; c++){ //think im missing something after this line......
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

void Graph::setAllVerticesUnvisited(){
  vector<vertex>::iterator i;
  for(i=vertices.begin(); i!=vertices.end(); ++i){
    i->visited=false;
  }
}

void Graph::BFT_traversal(vertex *v){
  queue<vertex> queue;
  vertex vert=*v;
  queue.push(vert);
  vector<Edge>::iterator i;
  while(!queue.empty()){
    vert=queue.front();
    queue.pop();
    if(!findVertex(vert.name)->visited) cout<<vert.name<<endl;
    findVertex(vert.name)->visited=true;
    for(i = vert.Edges.begin(); i!=vert.Edges.end(); i++){
      if(!i->v->visited) queue.push(*(i->v));
    }
  }
}

void Graph::DFT_traversal(vertex *v){
  vector<Edge>::iterator j;
  if(v->visited==true) return;
  v->visited=true;
  cout<<v->name<<endl;
  for(j=v->Edges.begin(); j!=v->Edges.end(); j++){
    if(!j->v->visited) DFT_traversal(j->v);
  }
}

void Graph::printDFT(){
  setAllVerticesUnvisited();
  for(int i=0; i<vertices.size(); i++){
    if(!vertices[i].visited) DFT_traversal(&vertices[i]);
  }
}

void Graph::printBFT(){
  setAllVerticesUnvisited();
  for(int i=0; i<vertices.size(); i++){
    if(!vertices[i].visited) BFT_traversal(&vertices[i]);
  }
}

int main(int argc, char* argv[]){
  vector map[][]=readFile(argc, argv);
  Graph maze(map);

}
