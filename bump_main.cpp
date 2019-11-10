/****************************************************************
 * File:    bump_main.cpp
 * Created: Oct 2019
 * Author:  Zshandi Krahn
 *
 * Reads file and assigns random priority, then gets order
 *            
 ****************************************************************/

#include "Poset.hpp"

#include <iostream>
#include <string>

#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char** argv){
  
  if(argc < 2){
    cout << "Usage:" << endl
	 << " " << argv[0] << " <file name>" << endl;
    return 0;
  }
  
  cout << "Reading poset..." << endl;
  Poset fromFile = Poset::readFromFile( argv[1] );
  
  cout << "Assigning priorities..." << endl;

  clock_t start;
  start = clock();
  
  fromFile.assignLexPriority();
  
  cout << "Ordering poset..." << endl;
  fromFile.findAndOutputOrdering();

  cout << "Time: "<<(clock()-start)/(double(CLOCKS_PER_SEC/1000))<< endl;

  return 0;
}
