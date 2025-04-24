/**
 * @file InterventionStatus.h
 * @brief Declares the InterventionStatus enum and its string conversion function.
 */

#pragma once

#include <string>

/**
 * @enum InterventionStatus
 * @brief Represents the current status of an intervention throughout its lifecycle.
 */
enum class InterventionStatus
{
  PENDING,      ///< The intervention is scheduled but not yet started.
  IN_PROGRESS,  ///< The intervention is currently underway.
  COMPLETED,    ///< The intervention has been successfully completed.
  CANCELLED,    ///< The intervention was cancelled before completion.
  ON_HOLD,      ///< The intervention is paused or delayed.
  RESCHEDULED   ///< The intervention has been postponed and rescheduled.
};

/**
 * @brief Converts an InterventionStatus value to its human-readable string equivalent.
 * 
 * @param expertise_field The InterventionStatus enum value.
 * @return A string representation of the status.
 */
inline std::string to_string(InterventionStatus expertise_field)
{
  switch(expertise_field) {
    case InterventionStatus::PENDING:      return "Pending";
    case InterventionStatus::IN_PROGRESS:  return "In Progress";
    case InterventionStatus::COMPLETED:    return "Completed";
    case InterventionStatus::CANCELLED:    return "Cancelled";
    case InterventionStatus::ON_HOLD:      return "On Hold";
    case InterventionStatus::RESCHEDULED:  return "Rescheduled";
    default:                               return "Not Found";
  }
}