/****************************************************************
 * File:    Node.hpp
 * Created: Nov 2019
 * Author:  Zshandi Krahn
 *
 * A node within a Poset
 *            
 ****************************************************************/

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <deque>

#include <string>

class Poset;

class Node{

protected:
  int id;
  
  std::vector<int>* upper;
  std::vector<int>* lower;
  std::deque<int>* lexLabel;
  
  int priority;

  int upperCount;
  int lowerCount;

  //Poset* pos;

  int nextUpper_i;
  int nextLower_i;
  
public:
  Node();
  ~Node();

  void init(int id);

  int getID();
  
  void addUpper(int upper);
  void addLower(int lower);
  
  void setPriority(int p);
  int getPriority();

  // returns whether there are any left
  bool decrUpper();
  bool decrLower();

  int getLowerCount();
  int getUpperCount();

  //void resetCounts();

  void addLex(int lex);

  std::string allUpper();

  bool operator < (const Node &other) const;

  // Functions for traversing upper or lower

  void beginTraverse();

  bool hasNextUpper();
  bool hasNextLower();

  int nextUpper();
  int nextLower();
};

#endif
