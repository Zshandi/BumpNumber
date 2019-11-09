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

// returns whether or not there are any left
bool Node::decrUpper(){
  upperCount--;
  return upperCount <= 0;
}

// returns whether or not there are any left
bool Node::decrLower(){
  lowerCount--;
  return lowerCount <= 0;
}

int Node::getLowerCount(){
  return lowerCount;
}

int Node::getUpperCount(){
  return upperCount;
}

void Node::addLex(int lex){
  lexLabel->push_front(lex);
}

string Node::allUpper(){
  stringstream s("");
  for(int i = 0; i < upper->size(); i++){
    s << " " << (*upper)[i];
  }
  return s.str();
}

bool Node::operator < (const Node &other) const{

  if(priority == -1){
    return lexLabel > other.lexLabel;
  }else{
    return priority < other.priority;
  }
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
