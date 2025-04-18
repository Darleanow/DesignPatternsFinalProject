#include "TechMa/Repository/TechnicianRepository.h"

TechnicianRepository &TechnicianRepository::instance()
{
  static TechnicianRepository instance;
  return instance;
}

void TechnicianRepository::save(const BasicTechnician &tech)
{
  technicians[tech.get_id()] = tech;
}

bool TechnicianRepository::remove_by_id(int id)
{
  return technicians.erase(id) > 0;
}

std::optional<BasicTechnician> TechnicianRepository::find_by_id(int id) const
{
  if(auto it = technicians.find(id); it != technicians.end()) {
    return it->second;
  }
  return std::nullopt;
}

std::vector<BasicTechnician> TechnicianRepository::get_all() const
{
  std::vector<BasicTechnician> result;
  for(const auto &[_, tech] : technicians) {
    result.push_back(tech);
  }
  return result;
}

void TechnicianRepository::next_id()
{
  m_next_id++;
}
