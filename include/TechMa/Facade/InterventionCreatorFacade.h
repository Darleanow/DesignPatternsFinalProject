/**
 * @file InterventionCreatorFacade.h
 * @brief Declares the InterventionCreatorFacade class, which provides a simplified interface for creating interventions.
 */

#pragma once

#include "TechMa/Entities/AIntervention.h"
#include "TechMa/Entities/InterventionData.h"

#include <memory>

/**
 * @class InterventionCreatorFacade
 * @brief Facade class that simplifies the creation of AIntervention objects.
 * 
 * This class hides the complexity of the underlying factory logic and provides a single point of access
 * for creating new interventions based on provided data.
 */
class InterventionCreatorFacade
{
public:
  /**
   * @brief Creates a new intervention instance using the provided data.
   * 
   * @param data The data used to configure the intervention.
   * @return A shared pointer to the created AIntervention.
   */
  static std::shared_ptr<AIntervention> create_intervention(const InterventionData &data);
};