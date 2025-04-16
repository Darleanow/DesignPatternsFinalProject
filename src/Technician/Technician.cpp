#include "TechMa/Technician/BasicTechnician.h"
#include "TechMa/Types/ExpertiseField.h"

BasicTechnician::BasicTechnician(std::string name) : m_name(std::move(name)) {}

std::string_view BasicTechnician::get_name() const
{
  return m_name;
}

std::vector<ExpertiseField> BasicTechnician::get_expertise() const
{
  return {}; // None by default
}

bool BasicTechnician::has_expertise(ExpertiseField) const
{
  return false;
}
