/*vector.h*/

//
// Our implementation of std::vector. Note that since vector
// is templated, there is no separate .cpp file --- the code
// must also be placed in the .h file.
//
// Prof. Joe Hummel
// Northwestern University
// CS 211
//

#pragma once

template <typename T>
class vector
{
private:
  T* A;            // ptr to underlying array
  size_t Size;     // # of elements in array
  size_t Capacity; // # of locations in array

public:
  //
  // default constructor:
  //
  vector()
    : A(new T[4]), Size(0), Capacity(4)
  { }

  //
  // destructor:
  //
  ~vector() 
  {
    delete[] A;
  }

  //
  // size:
  //
  size_t size()
  {
    return Size;
  }

  //
  // []:
  //
  T& operator[](size_t index)
  {
    return A[index];
  }

  //
  // push_back:
  //
  void push_back(T e)
  {
    if (Size == Capacity) { 
      //
      // TODO
      //

      return;
    }

    //
    // we know there's space, store e @ end:
    //
    A[Size] = e;
    Size++;
  }

};
