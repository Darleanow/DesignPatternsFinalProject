/**
 * @file TechnicianRepository.cpp
 * @brief Implements the TechnicianRepository class responsible for managing technician records and notifying observers.
 */

#include "TechMa/Repository/TechnicianRepository.h"
#include "TechMa/Observer/ATechnicianObserver.h"

/**
 * @brief Retrieves the singleton instance of the TechnicianRepository.
 * 
 * @return Reference to the global instance.
 */
TechnicianRepository &TechnicianRepository::instance()
{
  static TechnicianRepository repo;
  return repo;
}

/**
 * @brief Saves or updates a technician in the repository.
 * 
 * @param tech Shared pointer to the technician.
 */
void TechnicianRepository::save(std::shared_ptr<ATechnician> tech)
{
  technicians[tech->get_id()] = std::move(tech);
  notify_all();
}

/**
 * @brief Removes a technician by ID.
 * 
 * @param id The ID of the technician to remove.
 * @return True if the technician was successfully removed, false otherwise.
 */
bool TechnicianRepository::remove_by_id(int id)
{
  auto found = technicians.erase(id) > 0;

  if (found) {
    notify_all();
  }

  return found;
}

/**
 * @brief Finds a technician by their ID.
 * 
 * @param id The ID of the technician.
 * @return Optional containing the technician if found, or std::nullopt.
 */
std::optional<std::shared_ptr<ATechnician>>
    TechnicianRepository::find_by_id(int id) const
{
  if (auto it = technicians.find(id); it != technicians.end()) {
    return it->second;
  }
  return std::nullopt;
}

/**
 * @brief Retrieves all stored technicians.
 * 
 * @return A vector of shared pointers to technicians.
 */
std::vector<std::shared_ptr<ATechnician>> TechnicianRepository::get_all() const
{
  std::vector<std::shared_ptr<ATechnician>> result;
  for (const auto &[_, tech] : technicians) {
    result.push_back(tech);
  }
  return result;
}

/**
 * @brief Generates and returns the next available technician ID.
 * 
 * @return A unique integer ID.
 */
int TechnicianRepository::next_id()
{
  return m_next_id++;
}

/**
 * @brief Subscribes an observer to be notified of repository updates.
 * 
 * @param observer Pointer to the observer.
 */
void TechnicianRepository::subscribe(ATechnicianObserver *observer)
{
  m_observers.push_back(observer);
}

/**
 * @brief Unsubscribes an observer from receiving notifications.
 * 
 * @param observer Pointer to the observer to remove.
 */
void TechnicianRepository::unsubscribe(ATechnicianObserver *observer)
{
  std::erase(m_observers, observer);
}

/**
 * @brief Notifies all subscribed observers that the repository has been updated.
 */
void TechnicianRepository::notify_all()
{
  for (auto *observer : m_observers) {
    if (observer) {
      observer->on_repository_updated();
    }
  }
}