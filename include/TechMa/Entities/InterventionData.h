/**
 * @file InterventionData.h
 * @brief Defines the InterventionData structure which holds all information related to an intervention.
 */

#pragma once

#include "TechMa/Entities/ATechnician.h"
#include "TechMa/Entities/Location.h"
#include "TechMa/Types/ExpertiseField.h"
#include "TechMa/Types/InterventionComplexity.h"
#include "TechMa/Types/InterventionStatus.h"
#include "TechMa/Types/InterventionType.h"

#include <chrono>
#include <memory>
#include <optional>
#include <string>

/**
 * @struct InterventionData
 * @brief Data structure containing all relevant details of an intervention.
 * 
 * This struct is used to describe the full context and metadata of an intervention,
 * including timing, technician, type, complexity, location, and current status.
 */
struct InterventionData
{
  int id; ///< Unique identifier of the intervention.

  std::chrono::year_month_day date; ///< Scheduled date of the intervention.

  std::chrono::hours anticipated_duration; ///< Expected duration of the intervention.

  std::optional<std::chrono::minutes> actual_duration; ///< Actual duration, if completed.

  std::shared_ptr<ATechnician> technician; ///< Pointer to the assigned technician.

  ExpertiseField expertise_required; ///< Expertise required to perform the intervention.

  InterventionComplexity complexity; ///< Complexity level of the intervention.

  InterventionType type; ///< Type/category of the intervention.

  InterventionStatus status; ///< Current status of the intervention (e.g., pending, completed).

  Location location; ///< Location where the intervention will take place.

  std::string notes; ///< Additional notes or comments.

  std::optional<int> technician_id; ///< Technician ID if directly referenced (fallback/legacy).

  bool completed = false; ///< Flag indicating whether the intervention has been completed.
};