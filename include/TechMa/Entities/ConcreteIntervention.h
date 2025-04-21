#pragma once

#include "TechMa/Entities/AIntervention.h"

class ConcreteIntervention : public AIntervention
{
public:
  explicit ConcreteIntervention(InterventionData intervention_data);
  const InterventionData &data() const override;

private:
  InterventionData m_data;
};
