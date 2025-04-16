#pragma once

#include <string>

#include "TechMa/Entities/ATechnician.h"
#include "TechMa/Types/ExpertiseField.h"

class BasicTechnician : public ATechnician
{
public:
  explicit BasicTechnician(std::string name);

  std::string_view            get_name() const override;
  std::vector<ExpertiseField> get_expertise() const override;
  bool                        has_expertise(ExpertiseField) const override;

private:
  std::string m_name;
};
