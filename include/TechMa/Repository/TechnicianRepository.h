#pragma once

#include "TechMa/Entities/ATechnician.h"
#include "TechMa/Observer/ATechnicianObserver.h"

#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

class TechnicianRepository
{
public:
  static TechnicianRepository &instance();

  void                         save(std::shared_ptr<ATechnician> tech);
  bool                         remove_by_id(int id);
  std::optional<std::shared_ptr<ATechnician>> find_by_id(int id) const;
  std::vector<std::shared_ptr<ATechnician>>   get_all() const;

  int                                         next_id();


  void subscribe(ATechnicianObserver *observer);
  void unsubscribe(ATechnicianObserver *observer);

private:
  std::unordered_map<int, std::shared_ptr<ATechnician>> technicians;
  int                                                   m_next_id = 1;
  std::vector<ATechnicianObserver *>                    m_observers;

  TechnicianRepository() = default;
  void notify_all();
};
