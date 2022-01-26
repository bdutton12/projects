#include "vehicle.h"
#include <tuple>
#include <stdexcept>

Vehicle::Vehicle(char a) {
  ve_char = a;
  coordinates = std::make_tuple(0, 0);
}

void Vehicle::SetBearing(char dir) {
  if (dir == 'N' || dir == 'E' || dir == 'S' || dir == 'W') {
    bearing = dir;
  } else {
    throw(std::invalid_argument("Error"));
  }
}

void Vehicle::MoveForward(int spaces = 1) {
  int curr_coord;

  switch (bearing) {
    case 'N':
      curr_coord = std::get<0>(coordinates);
      curr_coord -= spaces;
      coordinates = std::make_tuple(curr_coord, std::get<1>(coordinates));
      break;
    case 'S':
      curr_coord = std::get<0>(coordinates);
      curr_coord += spaces;
      coordinates = std::make_tuple(curr_coord, std::get<1>(coordinates));
      break;
    case 'E':
      curr_coord = std::get<1>(coordinates);
      curr_coord += spaces;
      coordinates = std::make_tuple(std::get<0>(coordinates), curr_coord);
      break;
    case 'W':
      curr_coord = std::get<1>(coordinates);
      curr_coord -= spaces;
      coordinates = std::make_tuple(std::get<0>(coordinates), curr_coord);
      break;
  }
}

void Vehicle::TurnRight() {
  switch (bearing) {
    case 'N':
      bearing = 'E';
      break;
    case 'S':
      bearing = 'W';
      break;
    case 'E':
      bearing = 'S';
      break;
    case 'W':
      bearing = 'N';
      break;
  }
}

void Vehicle::TurnLeft() {
  switch (bearing) {
    case 'N':
      bearing = 'W';
      break;
    case 'S':
      bearing = 'E';
      break;
    case 'E':
      bearing = 'N';
      break;
    case 'W':
      bearing = 'S';
      break;
  }
}

std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
  os << vehicle.ve_char;
  return os;
}

bool operator<(const Vehicle& lhs, const Vehicle& rhs) {
  return lhs.ve_char < rhs.ve_char;
}

bool operator==(const Vehicle& lhs, const Vehicle& rhs) {
  return lhs.ve_char == rhs.ve_char;
}