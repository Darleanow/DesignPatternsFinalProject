#pragma once

#include "TechMa/Entities/AIntervention.h"
#include "TechMa/Entities/InterventionData.h"

class InterventionFactory
{
public:
  static std::shared_ptr<AIntervention> create(const InterventionData &data);
};
