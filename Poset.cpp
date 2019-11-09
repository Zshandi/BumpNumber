/****************************************************************
 * File:    Poset.cpp
 * Created: Oct 2019
 * Author:  Zshandi Krahn
 *
 * Class for handling posets
 *            
 ****************************************************************/

#include "Poset.hpp"

#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

Poset::Poset(int size){
  this->size = size;

  if(size == 0) return;
  
  nodes = new Node[size];
  for(int i = 0; i < size; i++){
    nodes[i].init(i);
  }
}

Poset::~Poset(){
  if(size != 0) delete [] nodes;
}

void Poset::addUpper(int node, int upperNode){
  nodes[node].addUpper(upperNode);
  nodes[upperNode].addLower(node);
}

int Poset::getSize(){
  return size;
}

Poset Poset::readFromFile(const char* filename){
  ifstream file;
  int u,v, n;
   
  file.open(filename);
  if (!file) { 
    cerr << "File not openable. " << endl;
    throw 0;
  }
  file >> n;

  // Init poset to size n
  Poset fromFile(n);
  
  cout << "Reading " << n <<  " nodes..." << endl;
  if (n>100000) { // arbitrary
    cerr<<"n too large: "<<n<<endl; throw 0;
  }

  file >> u;

  while (u < n && file) {
    file >> v; 
    while (v < n && file) {

      fromFile.addUpper(u, v);
      
      file >> v;
    }

    file >> u;
  }

  file.close();

  return fromFile;
}

void Poset::saveToFile(const char* filename){
  ofstream out;

  out.open(filename);

  out << size << endl;

  for (int u=0; u<size; u++) {
    out << u;

    cout << nodes[u].allUpper();

    out << " " << size << endl;
  }

  out << size << endl;

  out.close();
}


void Poset::assignPriority(int node, int p){

  nodes[node].setPriority(p);
}

class NodeWrapper{
public:
  Node* node;
  NodeWrapper(Node* n){
    node = n;
  }
  bool operator < (const NodeWrapper &other) const{
    return (*node) < ( *(other.node) );
  }
};

void Poset::findAndOutputOrdering(){

  priority_queue<NodeWrapper> myNodeQ;

  for(int i = 0; i < size; i++){
    if(nodes[i].getLowerCount() == 0){
      myNodeQ.push( NodeWrapper(nodes+i) );
    }
  }

  while( !myNodeQ.empty() ){
    Node* node = myNodeQ.top().node;
    myNodeQ.pop();

    node->beginTraverse();
    
    while ( node->hasNextUpper() ) {
      int upperNode = node->nextUpper();

      if( nodes[upperNode].decrLower() ){
	myNodeQ.push( NodeWrapper(nodes+upperNode) );
      }
    }

    cout << node->getID() << " ";
  }

  cout << endl
       << "Priorities: " << endl;
  for(int i = 0; i < size; i++){
    cout << nodes[i].getPriority() << " ";
  }
  cout << endl;
}
