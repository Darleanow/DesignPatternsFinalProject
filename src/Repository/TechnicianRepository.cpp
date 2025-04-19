#include "TechMa/Repository/TechnicianRepository.h"
#include "TechMa/Observer/ATechnicianObserver.h"

TechnicianRepository &TechnicianRepository::instance()
{
  static TechnicianRepository repo;
  return repo;
}

void TechnicianRepository::save(std::shared_ptr<ATechnician> tech)
{
  technicians[tech->get_id()] = std::move(tech);
  notify_all();
}

bool TechnicianRepository::remove_by_id(int id)
{
  auto found = technicians.erase(id) > 0;

  if(found) {
    notify_all();
  }

  return found;
}

std::optional<std::shared_ptr<ATechnician>>
    TechnicianRepository::find_by_id(int id) const
{
  if(auto it = technicians.find(id); it != technicians.end()) {
    return it->second;
  }
  return std::nullopt;
}

std::vector<std::shared_ptr<ATechnician>> TechnicianRepository::get_all() const
{
  std::vector<std::shared_ptr<ATechnician>> result;
  for(const auto &[_, tech] : technicians) {
    result.push_back(tech);
  }
  return result;
}

int TechnicianRepository::next_id()
{
  return m_next_id++;
}

void TechnicianRepository::subscribe(ATechnicianObserver *observer)
{
  m_observers.push_back(observer);
}

void TechnicianRepository::unsubscribe(ATechnicianObserver *observer)
{
  std::erase(m_observers, observer);
}

void TechnicianRepository::notify_all()
{
  for(auto *observer : m_observers) {
    if(observer) {
      observer->on_repository_updated();
    }
  }
}
