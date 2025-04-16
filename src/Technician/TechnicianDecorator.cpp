#include "TechMa/Technician/TechnicianDecorator.h"
#include "TechMa/Types/ExpertiseField.h"

TechnicianDecorator::TechnicianDecorator(std::shared_ptr<ATechnician> base)
    : m_wrapped(std::move(base))
{
}

std::string_view TechnicianDecorator::get_name() const
{
  return m_wrapped->get_name();
}

std::vector<ExpertiseField> TechnicianDecorator::get_expertise() const
{
  return m_wrapped->get_expertise();
}

bool TechnicianDecorator::has_expertise(ExpertiseField field) const
{
  return m_wrapped->has_expertise(field);
}
