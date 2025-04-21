#include "TechMa/Facade/InterventionCreatorFacade.h"
#include "TechMa/Factory/InterventionFactory.h"

std::shared_ptr<AIntervention>
    InterventionCreatorFacade::create_intervention(const InterventionData &data)
{
  return InterventionFactory::create(data);
}
