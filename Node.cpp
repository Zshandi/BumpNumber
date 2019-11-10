/****************************************************************
 * File:    Node.cpp
 * Created: Nov 2019
 * Author:  Zshandi Krahn
 *
 * A node within a Poset
 *            
 ****************************************************************/

#include "Node.hpp"
#include "Poset.hpp"

#include <sstream>

using namespace std;

Node::Node(){
  id = 0;

  upper = new vector<int>;
  lower = new vector<int>;
  lexLabel = new deque<int>;

  priority = -1;

  upperCount = 0;
  lowerCount = 0;
}

Node::~Node(){
  delete upper;
  delete lower;
  delete lexLabel;
}

void Node::init(int id){
  this->id = id;
}

int Node::getID(){
  return id;
}

void Node::addUpper(int upperNode){
  upper->push_back(upperNode);
  upperCount++;
}

void Node::addLower(int lowerNode){
  lower->push_back(lowerNode);
  lowerCount++;
}

void Node::setPriority(int p){
  priority = p;
}

int Node::getPriority(){
  return priority;
}

// returns true if there are none left, false otherwise
bool Node::decrUpper(){
  return --upperCount <= 0;
}

// returns true if there are none left, false otherwise
bool Node::decrLower(){
  return --lowerCount <= 0;
}

int Node::getLowerCount(){
  return lowerCount;
}

int Node::getUpperCount(){
  return upperCount;
}

void Node::resetCounts(){
  upperCount = upper->size();
  lowerCount = lower->size();
}

void Node::addLex(int lex){
  lexLabel->push_front(lex);
}

// Functions for traversing upper or lower

void Node::beginTraverse(){
  nextUpper_i = nextLower_i = 0;
}

bool Node::hasNextUpper(){
  return nextUpper_i < upper->size();
}
bool Node::hasNextLower(){
  return nextLower_i < lower->size();
}
  

int Node::nextUpper(){
  return (*upper)[nextUpper_i++];
}
int Node::nextLower(){
  return (*lower)[nextLower_i++];
}

// Orderings

bool Node::OrderByPriority::operator() ( Node* a, Node* b ){
  return a->priority < b->priority;
}

bool Node::OrderByLex::operator() ( Node* a, Node* b ){
  return *(a->lexLabel) > *(b->lexLabel);
}

// Insertion op

ostream& operator << (ostream &out, const Node &node){
  out << node.id << "(" << node.priority << ")";
  return out;
}
