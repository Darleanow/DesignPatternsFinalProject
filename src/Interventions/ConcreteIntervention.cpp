#include "TechMa/Entities/ConcreteIntervention.h"

ConcreteIntervention::ConcreteIntervention(InterventionData intervention_data)
    : m_data(std::move(intervention_data))
{
}

const InterventionData &ConcreteIntervention::data() const
{
  return m_data;
}
