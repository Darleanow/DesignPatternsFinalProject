/**
 * @file InterventionFactory.h
 * @brief Declares the InterventionFactory class responsible for creating intervention instances.
 */

#pragma once

#include "TechMa/Entities/AIntervention.h"
#include "TechMa/Entities/InterventionData.h"

#include <memory>

/**
 * @class InterventionFactory
 * @brief Factory class responsible for creating AIntervention objects.
 * 
 * This class encapsulates the logic required to construct different types of interventions.
 */
class InterventionFactory
{
public:
  /**
   * @brief Creates a new intervention based on the provided data.
   * 
   * @param data The data used to initialize the intervention.
   * @return A shared pointer to the created AIntervention instance.
   */
  static std::shared_ptr<AIntervention> create(const InterventionData &data);
};