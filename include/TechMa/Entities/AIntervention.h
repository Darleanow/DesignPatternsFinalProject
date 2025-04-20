#pragma once

#include "TechMa/Entities/InterventionData.h"

class AIntervention
{
public:
  virtual ~AIntervention() = default;

  virtual const InterventionData &data() const = 0;
  virtual int                     id() const
  {
    return data().id;
  }
};
