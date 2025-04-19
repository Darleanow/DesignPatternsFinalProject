#pragma once

#include <string>

#include "TechMa/Entities/ATechnician.h"
#include "TechMa/Types/ExpertiseField.h"

class BasicTechnician : public ATechnician
{
public:
  BasicTechnician(int id, std::string name);

  int                         get_id() const override;
  std::string                 get_name() const override;
  std::vector<ExpertiseField> get_expertise() const override;
  bool                        has_expertise(ExpertiseField) const override;

private:
  int         m_id;
  std::string m_name;
};
