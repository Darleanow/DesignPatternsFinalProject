#include "TechMa/Factory/InterventionFactory.h"
#include "TechMa/Entities/ConcreteIntervention.h"

std::shared_ptr<AIntervention>
    InterventionFactory::create(const InterventionData &data)
{
  return std::make_shared<ConcreteIntervention>(data);
}
