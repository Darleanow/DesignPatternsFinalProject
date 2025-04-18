#pragma once

#include "TechMa/Entities/ATechnician.h"
#include "TechMa/Types/ExpertiseField.h"

#include <memory>

class TechnicianDecorator : public ATechnician
{
public:
  explicit TechnicianDecorator(std::shared_ptr<ATechnician> base);

  int                         get_id() const override;
  std::string_view            get_name() const override;
  std::vector<ExpertiseField> get_expertise() const override;
  bool                        has_expertise(ExpertiseField) const override;

protected:
  std::shared_ptr<ATechnician> m_wrapped;
};
