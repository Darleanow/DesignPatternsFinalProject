/**
 * @file InterventionType.h
 * @brief Declares the InterventionType enum class and a string conversion utility.
 */

#pragma once

#include <string>

/**
 * @enum InterventionType
 * @brief Represents the category or nature of an intervention.
 */
enum class InterventionType
{
  MAINTENANCE,   ///< Routine maintenance tasks.
  EMERGENCY,     ///< Urgent interventions requiring immediate attention.
  INSTALLATION,  ///< Setting up new hardware or software.
  INSPECTION,    ///< Scheduled inspections and system checks.
  DIAGNOSTIC,    ///< Troubleshooting and diagnostics.
  UPGRADE        ///< System or component upgrades.
};

/**
 * @brief Converts an InterventionType value to a human-readable string.
 * 
 * @param expertise_field The InterventionType enum value.
 * @return A string representing the type.
 */
inline std::string to_string(InterventionType expertise_field)
{
  switch(expertise_field) {
    case InterventionType::MAINTENANCE:   return "Maintenance";
    case InterventionType::EMERGENCY:     return "Emergency";
    case InterventionType::INSTALLATION:  return "Installation";
    case InterventionType::INSPECTION:    return "Inspection";
    case InterventionType::DIAGNOSTIC:    return "Diagnostic";
    case InterventionType::UPGRADE:       return "Upgrade";
    default:                              return "Not Found";
  }
}