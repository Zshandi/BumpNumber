/****************************************************************
 * File:    Poset.hpp
 * Created: Oct 2019
 * Author:  Zshandi Krahn
 *
 * Class for handling posets
 *            
 ****************************************************************/

#ifndef POSET_HPP
#define POSET_HPP

#include "Node.hpp"

#include <vector>

class Poset{

protected:
  int size;

  Node* nodes;
  
public:
  Poset(int size=0);
  ~Poset();
  
  void addUpper(int node, int upper);
  
  int getSize();
  
  static Poset readFromFile(const char* filename);
  void saveToFile(const char* filename);

  void assignPriority(int node, int p);

  void findAndOutputOrdering();

  void assignLexPriority();
};

#endif
