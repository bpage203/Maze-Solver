#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>

//number of vertices
#define V 500

using namespace std;

//maybe output an ascii version of map with i++ variable
//at every vertex for start and end specification

struct vertex;  //declared so Edge can use it

struct Edge
{
    vertex *v;
    int distance;
};


//we had a struct for nodes and vertices, consolidated into only vertex
struct vertex
{
    int id;             //unique identifier for every vertex stating from 0

    //used for keeping track of original location in maze
    int row;
    int col;

    bool visited;       //flag for checking if vertex has already been visited
    string type;        //helps describe the vertex...might be obsolete
    vector<Edge> Edges; //all edges attached to vertex...might be obsolete

    // neighboring vertices
    vertex* north;
    vertex* east;
    vertex* south;
    vertex* west;
    int northDistance;
    int eastDistance;
    int southDistance;
    int westDistance;
};

class Graph
{
  public:
    //constructor
    Graph(string fileName);
    ~Graph();
    void addVertex(int sum, int row, int col);

    //adds edge from id1 to id2
    void addEdge(int id1, int id2, int direction, int distance);
    void displayEdges();
    void printDFT();
    void printBFT();
    void setAllVerticesUnvisited();
    void readFile(string fileName);           //reads text file into class variable map
    int minDistance(int dist[], bool Dset[]);
    void printMaze();
    void printAdjList();
    void storePath(int j);
    void printPath(int start);
    void printFastestPath();
    vertex* findVertex(int id);
    void resetCurrentPath();
    void findPath(int j);
    void findPath(int parent[], int j);
    int pathFinder(int id1, int id2);
    void printParentsV1(int a);
    void printParents();

    vector<int> shortestPath;
    vertex* start;
    vertex* end;

  private:

    void outliersFromArr(vector<vector<int>> map);
    vertex* findVertex(int row, int col); //overloaded
    void BFT_traversal(vertex *v);
    void DFT_traversal(vertex *v);
    bool visited(vertex* next);
    vertex* backTrack();
    int findDistance(vertex* curr, list<int> path);
    void dijkstra(int src);

    void edgesFromArr(vector<vector<int>> map);//adds vertices from map
    void verticesFromArr(vector<vector<int>> map);//adds edges from map

    // returns true if an index is a three or four way intersection
    int isIntersection(int row, int col);

    //traverses the map, along a certain path from a given index
    //until it hits another intersection.
    //returns the vertex->id that it hits
    int mapCrawler(vector<vector<int>> arr, int row, int col, int direction, int &distance);

    vector<vertex> vertices; //stores vertices
    vector<vector<int>> map; //map of the maze in integer form
    vertex* last;
    vertex* current;
    int count=0;
    int fastestDistance=0;
    int distanceGuess; //inputted guess shortest distance, used for choosing best path
    list<int> path;
    int adjList[V][V];
    list<vertex> vertexPath;
    int parentList[V];
    vertex* visitedArr[V];
    bool currentPath[V][V];
    int* fastestPath[];

};
