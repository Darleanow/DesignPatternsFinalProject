#pragma once

#include "TechMa/Technician/BasicTechnician.h"

#include <optional>
#include <unordered_map>
#include <vector>

class TechnicianRepository
{
public:
  static TechnicianRepository   &instance();

  void                           save(const BasicTechnician &tech);
  bool                           remove_by_id(int id);
  std::optional<BasicTechnician> find_by_id(int id) const;
  std::vector<BasicTechnician>   get_all() const;

  void                           next_id();

private:
  std::unordered_map<int, BasicTechnician> technicians;
  int                                      m_next_id = 1;

  TechnicianRepository() = default;
};
