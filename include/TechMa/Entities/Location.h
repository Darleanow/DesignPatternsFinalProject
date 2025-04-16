#pragma once

#include <string>

struct GPSCoords
{
  double latitude;
  double longitude;
};

struct Location
{
  std::string address;
  GPSCoords   coords;
};
