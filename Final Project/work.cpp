#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
using namespace std;

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

void createGrid(int x, int y){
  bool isPath[x][y];
  for(int i=0; i<x; i++){
    for(int j=0; j<y; j++){
      if(isWhite) isPath[i][j]=true;
      else isPath[i][j]=false;
    }
  }
}
