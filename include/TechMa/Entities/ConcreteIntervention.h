/**
 * @file ConcreteIntervention.h
 * @brief Declares the ConcreteIntervention class, a concrete implementation of AIntervention.
 */

#pragma once

#include "TechMa/Entities/AIntervention.h"

/**
 * @class ConcreteIntervention
 * @brief Concrete implementation of the AIntervention interface.
 * 
 * This class wraps an InterventionData object and exposes it through the AIntervention interface.
 */
class ConcreteIntervention : public AIntervention
{
public:
  /**
   * @brief Constructs a ConcreteIntervention with the given intervention data.
   * @param intervention_data The data representing the intervention.
   */
  explicit ConcreteIntervention(InterventionData intervention_data);

  /**
   * @brief Returns the data associated with this intervention.
   * @return A constant reference to the InterventionData object.
   */
  const InterventionData& data() const override;

private:
  InterventionData m_data;  ///< The internal data representing this intervention.
};