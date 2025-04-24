/**
 * @file InterventionCreatorFacade.cpp
 * @brief Implements the InterventionCreatorFacade class.
 */

#include "TechMa/Facade/InterventionCreatorFacade.h"
#include "TechMa/Factory/InterventionFactory.h"

/**
 * @brief Delegates the creation of an intervention to the InterventionFactory.
 * 
 * @param data The input data for the intervention.
 * @return A shared pointer to the newly created AIntervention object.
 */
std::shared_ptr<AIntervention>
    InterventionCreatorFacade::create_intervention(const InterventionData &data)
{
  return InterventionFactory::create(data);
}