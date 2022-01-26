#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <tuple>
#include "course.h"

class Vehicle {
  char ve_char;
  char bearing;
  std::tuple<int, int> coordinates;
  friend class Course;

 public:
  Vehicle(char a);
  friend std::ostream& operator<<(std::ostream&, const Vehicle&);
  friend bool operator<(const Vehicle&, const Vehicle&);
  friend bool operator==(const Vehicle&, const Vehicle&);
  void SetBearing(char);
  void MoveForward(int);
  void TurnRight();
  void TurnLeft();
};

#endif