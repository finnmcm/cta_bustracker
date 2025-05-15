/*main.cpp*/

//
// Program to input, sort, and output sailboat objects
// by their maxspeed.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
//

#include <iostream>
#include <fstream>
#include <string>

#include <algorithm>

#include "sailboat.h"

#include <vector>
//#include "vector.h"


//
// inputBoats:
//
bool inputBoats(std::string filename, std::vector<Sailboat>& boats)
{
  std::ifstream file;

  file.open(filename);

  if (file.fail())
    return false;

  while (true) {

    std::string name;
    double length;

    file >> name;
    file >> length;
        
    if (file.fail())
      break;

    Sailboat s(name, length);

    boats.push_back(s);
  }

  return true;
}


//
// outputBoats:
//
void outputBoats(std::vector<Sailboat>& boats)
{
  for (size_t i=0; i < boats.size(); i++)
    boats[i].print();

  return;
}


//
// main:
//
int main()
{
  std::vector<Sailboat> boats;
  bool success;

  success = inputBoats("boats.txt", boats);

  if (!success) {
    std::cout << "**Error: input file not found?" << std::endl;
    return 0;
  }

  std::cout << "# of boats: " << boats.size() << std::endl;
  std::cout << std::endl;

  outputBoats(boats);

  return 0;
}
