#include "Project.hpp"
using namespace std;

//maybe output an ascii version of map with i++ variable at every node for start and end specification

Graph::Graph(string fileName){ //assuming path designated w/ a 1
  this->count = 0;
  readFile(fileName);
  verticesFromArr(map);
  edgesFromArr(map);
  resetCurrentPath();

}

Graph::~Graph(){

}

void Graph::resetCurrentPath(){
  for(int i = 0; i<V;i++)
    for(int j = 0; j<V;j++)
      currentPath[i][j] = 0;
}

void Graph::printAdjList(){
  for (int i = 0; i<count; i++){
    for(int j = 0; j<count; j++){
      cout<<setfill('0')<<setw(3)<<adjList[i][j]<<" ";
    }
    cout<<endl;
  }
}

//used to be in constructor
void Graph::verticesFromArr(vector<vector<int>> map){
  int edges[4] = {0,0,0,0};
  int sum;
  for(int i=1; i<map.size()-1; i++){
    for(int j=1; j<map[0].size()-1; j++){
      if(map[i][j]==1) sum=isIntersection(i,j);
      if(sum==1) this->addVertex(sum,i,j);
      else if(sum==3) this->addVertex(sum,i,j);
      else if(sum==4) this->addVertex(sum,i,j);
      sum=0;
    }
  }
  outliersFromArr(map);
}

void Graph::outliersFromArr(vector<vector<int>> map){
  int edges[3] = {0,0,0};
  int sum=0;

  if(map[0][0]==1){
    sum+=map[0][1];
    sum+=map[1][0];
    if(sum==1) this->addVertex(sum,0,0);
    sum=0;
  }
  if(map[0][map[0].size()-1]){
    sum+=map[0][map[0].size()-2];
    sum+=map[1][map[0].size()-1];
    if(sum==1) this->addVertex(sum,0,map[0].size()-1);
    sum=0;
  }
  if(map[map.size()-1][0]){
    sum+=map[map.size()-1][1];
    sum+=map[map.size()-2][0];
    if(sum==1) this->addVertex(sum,map.size()-1,0);
    sum=0;
  }
  if(map[map.size()-1][map[0].size()-1]){
    sum+=map[map.size()-2][map[0].size()-1];
    sum+=map[map.size()-1][map[0].size()-2];
    if(sum==1) this->addVertex(sum,map.size()-1,map[0].size()-1);
    sum=0;
  }

  int j;
  for(int i=1; i<map.size()-1; i++){
    if(map[i][0]==1){
      j=0;
      sum+=map[i][j+1];
      sum+=map[i-1][j];
      sum+=map[i+1][j];
      if(sum==1) this->addVertex(sum,i,j);
      else if(sum==3) this->addVertex(sum,i,j);
      sum=0;
    }
    if(map[i][map[0].size()-1]==1){
      j=map[0].size()-1;
      sum+=map[i][j-1];
      sum+=map[i-1][j];
      sum+=map[i+1][j];
      if(sum==1) this->addVertex(sum,i,j);
      else if(sum==3) this->addVertex(sum,i,j);
      sum=0;
    }
  }

  int i;
  for(int j=1; j<map[0].size()-1; j++){
    if(map[0][j]==1){
      i=0;
      sum+=map[i+1][j];
      sum+=map[i][j-1];
      sum+=map[i][j+1];
      if(sum==1) this->addVertex(sum,i,j);
      else if(sum==3) this->addVertex(sum,i,j);
      sum=0;
    }
    if(map[map.size()-1][j]==1){
      i=map.size()-1;
      sum+=map[i-1][j];
      sum+=map[i][j-1];
      sum+=map[i][j+1];
      if(sum==1) this->addVertex(sum,i,j);
      else if(sum==3) this->addVertex(sum,i,j);
      sum=0;
    }
  }
}

void Graph::edgesFromArr(vector<vector<int>> map){
  int row, col, distanceToNode;
  int temp;
  int currVertId;

  for(int i = 0; i<vertices.size(); i++){
    row = vertices[i].row;
    col = vertices[i].col;
    currVertId = vertices[i].id;
    for(int j = 0; j<4; j++){
      temp = mapCrawler(map,row,col,j,distanceToNode);
      if(temp>0){
        addEdge(currVertId, temp, j, distanceToNode);
      }

    }
  }
}

void Graph::setAllVerticesUnvisited(){
  vector<vertex>::iterator i;
  for(i=vertices.begin(); i!=vertices.end(); ++i){
    i->visited=false;
  }
}


int Graph::isIntersection(int row, int col){
  int pathTotal = 0;
  if(map[row+1][col] == 1)//assuming path is marked by a "1"
    pathTotal++;

  if(map[row][col+1] == 1)
    pathTotal++;

  if(map[row-1][col] == 1)
    pathTotal++;

  if(map[row][col-1] == 1)
    pathTotal++;

  return pathTotal;
}


int Graph::mapCrawler(vector<vector<int>> arr, int row, int col, int direction, int &distance){
  int backwards = (direction+2)%4;
  if(direction == 0){
    if( arr[row-1][col] == 0)
      return -1;
    else
      row--;
  }else if(direction == 1){
    if( arr[row][col+1] == 0)
      return -1;
    else
      col++;
  }else if(direction == 2){
    if( arr[row+1][col] == 0)
      return -1;
    else
      row++;
  }else if(direction == 3){
    if( arr[row][col-1] == 0)
      return -1;
    else
      col--;
  }
  int dist = 1;

  //moves in a direction that is not backwards.
  //stops at intersections
  while(isIntersection(row, col)<3){//<-isIntersection doesnt exist yet
    if(backwards!=0 && arr[row-1][col] == 1){//assuming path is marked by a "1"
      row--;
      backwards = 2;
    }else if(backwards!=1 && arr[row][col+1] == 1){
      col++;
      backwards = 3;
    }else if(backwards!=2 && arr[row+1][col] == 1){
      row++;
      backwards = 0;
    }else if(backwards!=3 && arr[row][col-1] == 1){
      col--;
      backwards = 1;
    }else{ // this means a deadend has been hit
      break;
    }
    dist++;

  }
  distance = dist;
  return findVertex(row,col)->id;
}

void Graph::findPath( int j){
  findPath(parentList,j);
}

void Graph::findPath(int parent[], int j){//ending node

    // Base Case : If j is source
    for(int i = 1; i<shortestPath.size(); i++){
      pathFinder(shortestPath[i-1],shortestPath[i]);
    }

    // for(int i = 0; i<map.size(); i++){
    //   for(int j = 0; j<map[0].size(); j++){
    //     cout<<currentPath[i][j];
    //   }
    //   cout<<endl;
    // }

}

int Graph::pathFinder(int id1, int id2){
  int direction;
  if(findVertex(id1)->north!=NULL)
    if(findVertex(id1)->north->id == id2)
      direction = 0;
  if(findVertex(id1)->east!=NULL)
    if(findVertex(id1)->east->id == id2)
      direction = 1;
  if(findVertex(id1)->south!=NULL)
    if(findVertex(id1)->south->id == id2)
      direction = 2;
  if(findVertex(id1)->west!=NULL)
    if(findVertex(id1)->west->id == id2)
      direction = 3;




  int row = findVertex(id1)->row;
  int col = findVertex(id1)->col;
  currentPath[row][col] = 1;

  int backwards = (direction+2)%4;

  if(direction == 0){
    if( map[row-1][col] == 0)
      return -1;
    else
      row--;
  }else if(direction == 1){
    if( map[row][col+1] == 0)
      return -1;
    else
      col++;
  }else if(direction == 2){
    if( map[row+1][col] == 0)
      return -1;
    else
      row++;
  }else if(direction == 3){
    if( map[row][col-1] == 0)
      return -1;
    else
      col--;
  }
  currentPath[row][col] = 1;

  //moves in a direction that is not backwards.
  //stops at intersections
  while(isIntersection(row, col)<3){//<-isIntersection doesnt exist yet
    if(backwards!=0 && map[row-1][col] == 1){//assuming path is marked by a "1"
      row--;
      backwards = 2;
    }else if(backwards!=1 && map[row][col+1] == 1){
      col++;
      backwards = 3;
    }else if(backwards!=2 && map[row+1][col] == 1){
      row++;
      backwards = 0;
    }else if(backwards!=3 && map[row][col-1] == 1){
      col--;
      backwards = 1;
    }else{ // this means a deadend has been hit
      break;
    }
    currentPath[row][col] = 1;

  }

  return findVertex(row,col)->id;
}

bool Graph::visited(vertex* next){

  for(int i = 0; i<count; i++){//g++ doesnt like the iterator
    if(visitedArr[i] == next) return true;
  }
  return false;
}

vertex* Graph::backTrack(){
  int temp = path.size();
  temp=temp-3;  //changed this so that the last variable is updated as well
  vertexPath.pop_front();
  current=&vertexPath.front();
  vertexPath.pop_front();
  last=&vertexPath.front();
  vertexPath.push_front(*current);
  path.pop_front();
  return current;
}



int Graph::findDistance(vertex* curr, list<int> path){ //curr starts as start
  int sum = 0;
  list<int>::iterator i;
  for(i=path.begin(); i!=path.end(); ++i){
    switch(*i){
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

vertex* Graph::findVertex(int id){
  vector<vertex>::iterator i;
  int counter=0;
  for(i=vertices.begin(); i!=vertices.end(); i++){
    if(i->id==id) return &vertices[counter];
    counter++;
  }
}

vertex* Graph::findVertex(int row, int col){
  vector<vertex>::iterator i;
  int counter=0;
  for(i=vertices.begin(); i!=vertices.end(); i++){
    if(i->row == row && i->col == col) return &vertices[counter];
    counter++;
  }
}

void Graph::readFile(string fileName){
  ifstream imageFile(fileName);
  string line;
  while(getline(imageFile,line)){
    stringstream ss;
    ss<<line;
    string cell;
    vector<int> row;
    while(getline(ss,cell,',')){
      row.push_back(stoi(cell));
    }
    map.push_back(row);
  }
  // for(int i=0; i<map.size(); i++){     //for fixing edge cases, add edges of 0s
  //   for(int j=0; j<map[0].size(); j++){
  //     map[j].push_back(0);
  //     map[j].push_front(0);
  //   }
  // }
}

void Graph::printMaze(){
  int scale;
  if(vertices.size()>999) scale = 3;
  else if(vertices.size()>99) scale = 2;
  else if(vertices.size()>9) scale = 1;
  else scale = 0;

  bool inter;
  int counter=0;
  int xs[vertices.size()];
  int ys[vertices.size()];

  for(int i=0; i<vertices.size(); i++) xs[i]=vertices[i].row;
  for(int i=0; i<vertices.size(); i++) ys[i]=vertices[i].col;

  for(int i=0; i<map.size(); i++){
    for(int j=0; j<map[0].size(); j++){
      for(int k=0; k<vertices.size(); k++){
        if(i==xs[k]&&j==ys[k]){ //vertices
          switch(scale){
            case 1:
            if(counter<10) cout<<"0";
            break;
            case 2:
            if(counter<10) cout<<"00";
            else if(counter<100) cout<<"0";
            break;
            case 3:
            if(counter<10) cout<<"000";
            else if(counter<100) cout<<"00";
            else if(counter<1000) cout<<"0";
            break;
          }
          cout<<vertices[counter].id;
          counter++;
          inter=true;
        }
      }
      if(inter==true) inter=false;
      else if(map[i][j]==0){ //walls
        switch(scale){
          case 1:
          cout<<char(178);
          break;
          case 2:
          cout<<char(178)<<char(178);
          break;
          case 3:
          cout<<char(178)<<char(178)<<char(178);
        }
        cout<<char(178);
      }
      else if(map[i][j]==1){  //path
        switch(scale){
          case 1:
          cout<<char(32);
          break;
          case 2:
          cout<<char(32)<<char(32);
          break;
          case 3:
          cout<<char(32)<<char(32)<<char(32);
        }
        cout<<char(32);
      }
    }
    cout<<endl;
  }
}

void Graph::addVertex(int sum, int row, int col){
  vertex* newVertex = new vertex;
  newVertex->id=count++;
  if(sum==3){
    newVertex->type="inter";
  }else if(sum==1){
    newVertex->type="dead";
  }

  newVertex->north = NULL;
  newVertex->east = NULL;
  newVertex->south = NULL;
  newVertex->west = NULL;

  newVertex->northDistance = -1;
  newVertex->eastDistance  = -1;
  newVertex->southDistance = -1;
  newVertex->westDistance  = -1;

  newVertex->row = row;
  newVertex->col = col;

  vertices.push_back(*newVertex);

}


// adds undirected edge betwenn two vertices
//direction is the direction between id1 and id2
void Graph::addEdge(int id1, int id2, int direction, int distance){
  Edge* newEdge = new Edge;
  vertex* first = findVertex(id1);
  vertex* second = findVertex(id2);

  adjList[id1][id2] = distance;

  newEdge->v=second;
  newEdge->distance=distance;

  if(direction == 0){
    first->north = second;
  }else if(direction == 1){
    first->east = second;
  }else if(direction == 2){
    first->south = second;
  }else if(direction == 3){
    first->west = second;
  }

  first->Edges.push_back(*newEdge);
}

void Graph::displayEdges(){
  vector<vertex>::iterator i;
  vector<Edge>::iterator j;
  bool first=true;
  for(i=vertices.begin(); i!=vertices.end(); ++i){
    cout<<i->id<<"-->";
    first=true;
    for(j=i->Edges.begin(); j!=i->Edges.end(); ++j){
      if(first==true) cout<<j->v->id<<" ("<<j->distance<<" pixels)";
      else cout<<"***"<<j->v->id<<" ("<<j->distance<<" pixels)";
      first=false;
    }
    cout<<endl;
  }
}

int Graph::minDistance(int dist[], bool Dset[]){
  int min=INT_MAX,index;
  for(int v=0; v<count; v++){
    if(Dset[v]==false&&dist[v]<=min){
      min=dist[v];
      index=v;
    }
  }
  return index;
}

void Graph::storePath(int j)
{

    // Base Case : If j is source
    if (parentList[j] == - 1)
        return;

    storePath(parentList[j]);

    shortestPath.push_back(j);

}

void printPath(int parent[], int j){

    // Base Case : If j is source
    if (parent[j] == - 1)
        return;
    printPath(parent, parent[j]);

    printf("%d ", j);

}

int printSolution(int dist[], int n, int parent[]){
    int src = 0;
    printf("Vertex\t Distance\tPath");
    for (int i = 1; i < n; ++i)
    {
        printf("\n%d -> %d \t\t %d\t\t%d ",
                      src, i, dist[i], src);
        printPath(parent, i);
        cout<<endl;
        if(i==n-1)
          break;
    }
}

void Graph::dijkstra(int src){
   int dist[500];

   bool sptSet[500];

   int parent[500];

   for (int i = 0; i < this->count; i++)
      dist[i] = INT_MAX, sptSet[i] = false, parent[0] = -1;

   dist[src] = 0;

   for (int c = 0; c < count-1; c++)
   {

     int u = minDistance(dist, sptSet);

     sptSet[u] = true;

     for (int v = 0; v < count; v++){

       if (!sptSet[v] && adjList[u][v] && dist[u] != INT_MAX
                                     && dist[u]+adjList[u][v] < dist[v]){
         parent[v] = u;
         dist[v] = dist[u] + adjList[u][v];
        }
      }
   }

  //printSolution(dist,count,parent);
  for (int z = 0; z<count; z++){
    parentList[z] = parent[z];
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
    if(!findVertex(vert.id)->visited) cout<<vert.id<<endl;
    findVertex(vert.id)->visited=true;
    for(i = vert.Edges.begin(); i!=vert.Edges.end(); i++){
      if(!i->v->visited) queue.push(*(i->v));
    }
  }
}

void Graph::DFT_traversal(vertex *v){
  vector<Edge>::iterator j;
  if(v->visited==true) return;
  v->visited=true;
  cout<<v->id<<endl;
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

void Graph::printPath(int start){
  dijkstra(start);
}

void Graph::printParentsV1(int a){
  storePath(a);
  for(int i = 0; i <shortestPath.size(); i++)
    cout<<shortestPath[i]<<endl;
}

void Graph::printParents(){
  cout<<"parents: "<<endl;
  for(int i = 0; i<count;i++)
    cout <<i<<" "<< parentList[i]<<" "<<endl;
}

void Graph::printFastestPath(){ //get from djiekstra
  bool isPath;
  for(int i=0; i<map.size(); i++){
    for(int j=0; j<map[0].size(); j++){
      if(currentPath[i][j]) isPath=true;
      if(isPath==true) cout<<":"<<")";
      else if(map[i][j]==1) cout<<char(32)<<char(32);
      else if(map[i][j]==0) cout<<char(178)<<char(178);
      isPath=false;
    }
    cout<<endl;
  }
}


int main(int argc, char* argv[]){
  int decision;
  Graph maze(argv[1]);
  while(decision!=-1){
    maze.printMaze();
    cout<<"Choose at which node you'd like to start."<<endl;
    cin>>decision;
    maze.start=maze.findVertex(0);
    maze.shortestPath.push_back(maze.start->id);
    cout<<"Choose at which node you'd like to finish."<<endl;
    cin>>decision;
    maze.end=maze.findVertex(decision);
    maze.printPath(maze.start->id);
    maze.storePath(maze.end->id);
    maze.findPath(maze.end->id);
    maze.printFastestPath();
    maze.resetCurrentPath();
    maze.shortestPath.clear();
    cout<<"Enter '-1' to exit or 0 to continue."<<endl;
    cin>>decision;
  }
}
