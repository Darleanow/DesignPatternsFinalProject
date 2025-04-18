#pragma once

#include <string_view>
#include <vector>

#include "TechMa/Types/ExpertiseField.h"

class ATechnician
{
public:
  virtual ~ATechnician()                                    = default;
  virtual std::string_view            get_name() const      = 0;
  virtual int                         get_id() const        = 0;
  virtual std::vector<ExpertiseField> get_expertise() const = 0;
  virtual bool                        has_expertise(ExpertiseField) const = 0;
};
