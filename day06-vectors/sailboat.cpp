/*sailboat.cpp*/

//
// Models a sailboat.
//
// Prof. Joe Hummel
// Northwestern University
// CS 211
//

#include <iostream>
#include <cmath>

#include "sailboat.h"

using namespace std;

//
// default constructor:
// 
Sailboat::Sailboat()
  : name(""), length(0.0)
{ }

//
// parameterized constructor:
//
Sailboat::Sailboat(string Name, double Length)
  : name(Name), length(Length)
{ }

//
// maxspeed:
//
double Sailboat::maxspeed()
{
  return 1.3 * sqrt(length);
}

//
// print:
//
void Sailboat::print()
{
  cout << name << ":" << endl;
  cout << " length: " << length << " ft" << endl;
  cout << " Max speed: " << maxspeed() << " kts" << endl;
}
