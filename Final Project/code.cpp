#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
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

node* traverseBrute(node* curr){  //replaced w dijekstra
  int distance;
  while(curr!=start){
    visited.end()=curr;
    if(curr->type=="finish"){
      distance=findDistance(curr, path);
      if(distance<fastestDistance||fastestDistance==0){
        fastestDistance=distance;
        fastestPath=path;
      }
      curr=backTrack(curr);
    }
    if(curr->type=="edge"){
      curr=backTrack(path);
    }
    for(int i=1; i<5; i++){
      switch(i){
        case 1:
          if(curr->north!=NULL&&!visited(curr->north)){
            curr=curr->north;
            path.end()=1;
            curr=traverseBrute(curr);
          }
          break;
        case 2:
          if(curr->east!=NULL&&!visited(curr->east)){
            curr=curr->east;
            path.end()=2;
            curr=traverseBrute(curr);
          }
          break;
        case 3:
          if(curr->south!=NULL&&!visited(curr->south)){
            curr=curr->south;
            path.end()=3;
            curr=traverseBrute(curr);
          }
          break;
        case 4:
          if(curr->west!=NULL&&!visited(curr->west)){
            curr=curr->west;
            path.end()=4;
            curr=traverseBrute(curr);
          }
          break;
      }
    }
    curr->type="edge";
    curr=   backtrack(path);
  }
  return curr;
}

int main(int argc, char* argv[]){
  readin;

  node* curr;


}
