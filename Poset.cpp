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

    Node * node = &nodes[u];

    node->beginTraverse();
    while( node->hasNextUpper() ){
      cout << " " << node->nextUpper();
    }

    out << " " << size << endl;
  }

  out << size << endl;

  out.close();
}


void Poset::assignPriority(int node, int p){

  nodes[node].setPriority(p);
}

void Poset::findAndOutputOrdering(){

  for(int i = 0; i < size; i++){
    nodes[i].resetCounts();
  }

  PriorityOrderQ myQ;

  for(int i = 0; i < size; i++){
    if(nodes[i].getLowerCount() == 0){
      myQ.push( &nodes[i] );
    }
  }

  Node* node = myQ.top();
  myQ.pop();

  Node* nextNode = NULL;

  bool bump = false;
  int bumpNum = 0;

  while( !myQ.empty() || (node != NULL) ){

    if( !myQ.empty() ){
      nextNode = myQ.top();
      myQ.pop();
    }else if(node->getUpperCount() != 0){
      bump = true;
      bumpNum++;
    }

    if(node != NULL){
      
      cout << *node;
      
      if(bump){
	cout << "--";
	bump = false;
      }else{
	cout << "  ";
      }
      
      node->beginTraverse();
    
      while ( node->hasNextUpper() ) {
	int upperNode = node->nextUpper();

	if( nodes[upperNode].decrLower() ){
	  myQ.push( &nodes[upperNode] );
	}
      }
    }

    node = nextNode;
    nextNode = NULL;
  }

  cout << endl
       << "bump number is " << bumpNum << endl;
}

void Poset::assignLexPriority(){

  LexOrderQ myQ;

  for(int i = 0; i < size; i++){
    if(nodes[i].getUpperCount() == 0){
      myQ.push( &nodes[i] );
    }
  }

  int currentPriority = 0;
  
  while( !myQ.empty() ){
    Node * node = myQ.top();
    myQ.pop();

    node->setPriority(currentPriority++);

    node->beginTraverse();

    while( node->hasNextLower() ){
      int lowerID = node->nextLower();

      Node* lowerNode = &nodes[lowerID];

      lowerNode->addLex( node->getPriority() );

      if( lowerNode->decrUpper() ){
	myQ.push(lowerNode);
      }
    }
  }
      
}




