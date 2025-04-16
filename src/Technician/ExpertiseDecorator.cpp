#include "TechMa/Technician/ExpertiseDecorator.h"
#include "TechMa/Technician/TechnicianDecorator.h"
#include "TechMa/Types/ExpertiseField.h"

ExpertiseDecorator::ExpertiseDecorator(
    std::shared_ptr<ATechnician> base, ExpertiseField field
)
    : TechnicianDecorator(std::move(base)),
      m_field(field)
{
}

std::vector<ExpertiseField> ExpertiseDecorator::get_expertise() const
{
  auto base_expertises = m_wrapped->get_expertise();
  base_expertises.push_back(m_field);

  return base_expertises;
}

bool ExpertiseDecorator::has_expertise(ExpertiseField field) const
{
  return field == m_field || m_wrapped->has_expertise(field);
}
