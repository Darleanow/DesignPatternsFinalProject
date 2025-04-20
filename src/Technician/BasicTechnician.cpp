#include "TechMa/Technician/BasicTechnician.h"
#include "TechMa/Types/ExpertiseField.h"

BasicTechnician::BasicTechnician(int id, std::string name)
    : m_id(id),
      m_name(std::move(name))
{
}

int BasicTechnician::get_id() const
{
  return m_id;
}

std::string BasicTechnician::get_name() const
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
