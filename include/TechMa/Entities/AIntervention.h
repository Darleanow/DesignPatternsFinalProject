/**
 * @file AIntervention.h
 * @brief Defines the abstract base class AIntervention for representing interventions.
 */

#pragma once

#include "TechMa/Entities/InterventionData.h"

/**
 * @class AIntervention
 * @brief Abstract base class representing a generic intervention.
 * 
 * This interface provides access to intervention data and ensures that all derived
 * interventions expose a consistent method for retrieving their data and ID.
 */
class AIntervention
{
public:
  /**
   * @brief Virtual destructor to ensure proper cleanup of derived classes.
   */
  virtual ~AIntervention() = default;

  /**
   * @brief Retrieves the data associated with the intervention.
   * @return A constant reference to an InterventionData object.
   */
  virtual const InterventionData& data() const = 0;

  /**
   * @brief Retrieves the intervention's ID.
   * 
   * This is a convenience method that returns the ID from the underlying data.
   * @return The intervention ID as an integer.
   */
  virtual int id() const
  {
    return data().id;
  }
};