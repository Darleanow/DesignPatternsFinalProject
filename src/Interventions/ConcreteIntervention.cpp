/**
 * @file ConcreteIntervention.cpp
 * @brief Implements the ConcreteIntervention class.
 */

#include "TechMa/Entities/ConcreteIntervention.h"

/**
 * @brief Constructs a ConcreteIntervention with the specified intervention data.
 * 
 * @param intervention_data The data used to initialize this intervention.
 */
ConcreteIntervention::ConcreteIntervention(InterventionData intervention_data)
    : m_data(std::move(intervention_data))
{
}

/**
 * @brief Returns the data associated with this ConcreteIntervention.
 * 
 * @return A constant reference to the internal InterventionData object.
 */
const InterventionData &ConcreteIntervention::data() const
{
  return m_data;
}