#pragma once

#include <string>

enum class InterventionStatus
{
  PENDING,
  IN_PROGRESS,
  COMPLETED,
  CANCELLED,
  ON_HOLD,
  RESCHEDULED
};

inline std::string to_string(InterventionStatus expertise_field)
{
  switch(expertise_field) {
  case InterventionStatus::PENDING:
    return "Pending";
  case InterventionStatus::IN_PROGRESS:
    return "In Progress";
  case InterventionStatus::COMPLETED:
    return "Completed";
  case InterventionStatus::CANCELLED:
    return "Cancelled";
  case InterventionStatus::ON_HOLD:
    return "On Hold";
  case InterventionStatus::RESCHEDULED:
    return "Rescheduled";
  default:
    return "Not Found";
  }
}
