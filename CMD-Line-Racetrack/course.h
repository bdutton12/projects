#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <tuple>

class Vehicle;

class Course {
  std::vector<std::string> layout;
  std::vector<std::string> layout_veh;
  std::tuple<int, int> startCoords;
  std::tuple<int, int> finCoords;
  std::vector<Vehicle*> vehicles;
  friend class Vehicle;
  int track_width;

  void UpdatePositions();

 public:
  Course(std::string);
  Course(Course&);
  void operator=(Course&);
  friend std::ostream& operator<<(std::ostream&, Course&);
  void AddVehicleToStart(Vehicle*);
  int ReturnOffTrackVehiclesToStart();
  std::set<Vehicle> VehiclesAtFinish();
};

#endif