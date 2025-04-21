#pragma once

#include <string>

enum class InterventionType
{
  MAINTENANCE,
  EMERGENCY,
  INSTALLATION,
  INSPECTION,
  DIAGNOSTIC,
  UPGRADE
};

inline std::string to_string(InterventionType expertise_field)
{
  switch(expertise_field) {
  case InterventionType::MAINTENANCE:
    return "Maintenance";
  case InterventionType::EMERGENCY:
    return "Emergency";
  case InterventionType::INSTALLATION:
    return "Installation";
  case InterventionType::INSPECTION:
    return "Inspection";
  case InterventionType::DIAGNOSTIC:
    return "Diagnostic";
  case InterventionType::UPGRADE:
    return "Upgrade";
  default:
    return "Not Found";
  }
}
