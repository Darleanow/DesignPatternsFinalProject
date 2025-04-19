#pragma once

#include <string>

enum class ExpertiseField
{
  ELECTRICAL,  // Circuits, panels, power systems
  NETWORKING,  // Router, switches, cabling
  HVAC,        // Heating, ventilation, air conditioning
  PLUMBING,    // Water systems, pipes, leakage
  SECURITY,    // Cameras, access control, alarms
  SOFTWARE,    // OS Maintenance, scripts, diagnosis
  HARDWARE,    // Physical server repairs, BIOS, components
  FIRE_SAFETY, // Detectors, sprinklers, inspections
  STRUCTURAL,  // Building-related (doors, windows, ceilings)
  GENERALIST,  // Can handle basic tasks in every domain (complexity < medium)
};

inline std::string to_string(ExpertiseField expertise_field)
{
  switch(expertise_field) {
  case ExpertiseField::ELECTRICAL:
    return "Electrical";
  case ExpertiseField::NETWORKING:
    return "Networking";
  case ExpertiseField::HVAC:
    return "HVAC";
  case ExpertiseField::PLUMBING:
    return "Plumbing";
  case ExpertiseField::SECURITY:
    return "Security";
  case ExpertiseField::SOFTWARE:
    return "Software";
  case ExpertiseField::HARDWARE:
    return "Hardware";
  case ExpertiseField::FIRE_SAFETY:
    return "Fire Safety";
  case ExpertiseField::STRUCTURAL:
    return "Structural";
  case ExpertiseField::GENERALIST:
    return "Generalist";
  default:
    return "Not Found";
  }
}
