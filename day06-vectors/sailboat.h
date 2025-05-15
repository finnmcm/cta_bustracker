/*sailboat.h*/

//
// Models a sailboat.
//
// Prof. Joe Hummel
// Northwestern University
// CS 211
//

#pragma once

#include <string>


class Sailboat
{
public:
  std::string name;
  double      length;

  Sailboat();
  Sailboat(std::string Name, double Length);

  double maxspeed();

  void print();
};
