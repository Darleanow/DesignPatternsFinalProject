/**
 * @file InterventionFactory.cpp
 * @brief Implements the InterventionFactory class.
 */

#include "TechMa/Factory/InterventionFactory.h"
#include "TechMa/Entities/ConcreteIntervention.h"

/**
 * @brief Creates a ConcreteIntervention using the provided data.
 * 
 * @param data The intervention data.
 * @return A shared pointer to the new ConcreteIntervention.
 */
std::shared_ptr<AIntervention>
    InterventionFactory::create(const InterventionData &data)
{
  return std::make_shared<ConcreteIntervention>(data);
}