/**
 * @file Location.h
 * @brief Defines the GPSCoords and Location structures for representing geographical locations.
 */

#pragma once

#include <string>

/**
 * @struct GPSCoords
 * @brief Represents geographical coordinates with latitude and longitude.
 */
struct GPSCoords
{
  double latitude;  ///< Latitude in decimal degrees.
  double longitude; ///< Longitude in decimal degrees.
};

/**
 * @struct Location
 * @brief Represents a physical location with an address and GPS coordinates.
 */
struct Location
{
  std::string address; ///< Human-readable address of the location.
  GPSCoords   coords;  ///< Geographical coordinates of the location.
};