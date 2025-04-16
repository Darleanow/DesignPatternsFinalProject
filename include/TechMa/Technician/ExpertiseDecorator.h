#pragma once

#include "TechMa/Technician/TechnicianDecorator.h"
#include "TechMa/Types/ExpertiseField.h"

class ExpertiseDecorator : public TechnicianDecorator
{
public:
  ExpertiseDecorator(std::shared_ptr<ATechnician> base, ExpertiseField field);

  std::vector<ExpertiseField> get_expertise() const override;
  bool                        has_expertise(ExpertiseField) const override;

private:
  ExpertiseField m_field;
};
