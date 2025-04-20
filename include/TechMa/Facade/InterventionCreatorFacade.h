#pragma once

#include "TechMa/Entities/AIntervention.h"
#include "TechMa/Entities/InterventionData.h"

#include <memory>

class InterventionCreatorFacade
{
public:
  static std::shared_ptr<AIntervention>
      create_intervention(const InterventionData &data);
};
