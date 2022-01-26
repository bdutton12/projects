#include "course.h"
#include "vehicle.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <tuple>

Course::Course(std::string _layout) {
  std::stringstream ss(_layout);

  // For each line, if line is blank -> skip, if line has characters -> remove
  // whitespace and add trailing newline
  for (std::string line; std::getline(ss, line);) {
    std::string temp;

    if (line.empty()) {
      continue;
    } else {
      for (auto i : line) {
        if (isspace(i)) {
          continue;
        } else {
          temp.push_back(i);
        }
      }
    }
    track_width = temp.size();
    layout.push_back(temp);
  }

  // Find location of start and finish
  int x = 0;
  for (auto line : layout) {
    int y = 0;
    for (auto c : line) {
      if (c == 'S') {
        startCoords = std::make_tuple(x, y);
      }
      if (c == 'F') {
        finCoords = std::make_tuple(x, y);
      }
      y++;
    }
    x++;
  }

  layout_veh = layout;
}

Course::Course(Course& c) {
  layout = c.layout;
  layout_veh = c.layout;
  track_width = c.track_width;
}

void Course::operator=(Course& c) {
  layout = c.layout;
  layout_veh = c.layout_veh;
  vehicles = c.vehicles;
  startCoords = c.startCoords;
  finCoords = c.finCoords;
  track_width = c.track_width;

  c.layout_veh = c.layout;
  std::vector<Vehicle*> temp;
  c.vehicles = temp;
}

void Course::UpdatePositions() {
  for (auto veh : vehicles) {
    layout_veh[std::get<0>(veh->coordinates)][std::get<1>(veh->coordinates)] =
        veh->ve_char;
  }
}

// Add pluses, update vehicle positions and output layout
std::ostream& operator<<(std::ostream& os, Course& course) {
  for (int i = 0; i < course.track_width + 2; i++) {
    os << "+";
  }
  os << "\n";

  course.layout_veh = course.layout;

  // Update course with vehicles to new vehicle positions
  course.UpdatePositions();

  for (auto line : course.layout_veh) {
    os << "+" << line << "+\n";
  }

  for (int i = 0; i < course.track_width + 2; i++) {
    os << "+";
  }
  os << "\n";

  return os;
}

// Add vehicle to vector of all vehicles and set coords to start
void Course::AddVehicleToStart(Vehicle* vehicle) {
  vehicle->coordinates = startCoords;
  vehicles.push_back(vehicle);
}

// If vehicle is not on track, move vehicle to start
int Course::ReturnOffTrackVehiclesToStart() {
  int num_moved = 0;

  for (auto veh : vehicles) {
    char track_state =
        layout[std::get<0>(veh->coordinates)][std::get<1>(veh->coordinates)];
    if (track_state != 'S' && track_state != '*' && track_state != 'F') {
      veh->coordinates = startCoords;
      num_moved++;
    }
  }

  return num_moved;
}

std::set<Vehicle> Course::VehiclesAtFinish() {
  std::set<Vehicle> finished_vehicles;

  for (auto veh : vehicles) {
    if (veh->coordinates == finCoords) {
      finished_vehicles.insert(*veh);
    }
  }

  return finished_vehicles;
}
