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

struct InterventionData
{
  int                                 id;
  std::chrono::year_month_day         date;
  std::chrono::hours                  anticipated_duration;
  std::optional<std::chrono::minutes> actual_duration;
  std::shared_ptr<ATechnician>        technician;
  ExpertiseField                      expertise_required;
  InterventionComplexity              complexity;
  InterventionType                    type;
  InterventionStatus                  status;
  Location                            location;
  std::string                         notes;
  std::optional<int>                  technician_id;

  bool                                completed = false;
};
