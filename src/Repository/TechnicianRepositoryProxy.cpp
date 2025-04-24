/**
 * @file TechnicianRepositoryProxy.cpp
 * @brief Implements the TechnicianRepositoryProxy class and AccessDeniedException.
 */

#include "TechMa/Repository/TechnicianRepositoryProxy.h"

/**
 * @brief Constructs a new AccessDeniedException.
 * 
 * @param message A description of the access violation.
 */
AccessDeniedException::AccessDeniedException(const std::string &message)
    : std::runtime_error(message)
{
}

/**
 * @brief Returns the singleton instance of the TechnicianRepositoryProxy.
 * 
 * @return Reference to the singleton proxy instance.
 */
TechnicianRepositoryProxy &TechnicianRepositoryProxy::instance()
{
  static TechnicianRepositoryProxy proxy;
  return proxy;
}

/**
 * @brief Finds a technician by ID.
 * 
 * @param id The ID to look up.
 * @return Optional shared pointer to the technician, or std::nullopt if not found.
 */
std::optional<std::shared_ptr<ATechnician>>
    TechnicianRepositoryProxy::find_by_id(int id) const
{
  return TechnicianRepository::instance().find_by_id(id);
}

/**
 * @brief Retrieves all technicians in the repository.
 * 
 * @return A vector of shared pointers to all technicians.
 */
std::vector<std::shared_ptr<ATechnician>>
    TechnicianRepositoryProxy::get_all() const
{
  return TechnicianRepository::instance().get_all();
}

/**
 * @brief Provides the next unique ID for a technician.
 * 
 * @return The next available technician ID.
 */
int TechnicianRepositoryProxy::next_id()
{
  return TechnicianRepository::instance().next_id();
}

/**
 * @brief Saves a technician into the repository.
 * 
 * Only ADMIN users are authorized to perform this action.
 * 
 * @param tech The technician to save.
 * @throws AccessDeniedException if the current user is not an admin.
 */
void TechnicianRepositoryProxy::save(std::shared_ptr<ATechnician> tech)
{
  if (!AuthenticationService::instance().has_role(UserRole::ADMIN)) {
    throw AccessDeniedException(
        "Admin privileges required to save technicians"
    );
  }
  TechnicianRepository::instance().save(tech);
}

/**
 * @brief Removes a technician from the repository by ID.
 * 
 * Only ADMIN users are authorized to perform this action.
 * 
 * @param id The ID of the technician to remove.
 * @return True if the technician was successfully removed.
 * @throws AccessDeniedException if the current user is not an admin.
 */
bool TechnicianRepositoryProxy::remove_by_id(int id)
{
  if (!AuthenticationService::instance().has_role(UserRole::ADMIN)) {
    throw AccessDeniedException(
        "Admin privileges required to remove technicians"
    );
  }
  return TechnicianRepository::instance().remove_by_id(id);
}

/**
 * @brief Subscribes an observer for technician repository updates.
 * 
 * @param observer Pointer to the observer.
 */
void TechnicianRepositoryProxy::subscribe(ATechnicianObserver *observer)
{
  TechnicianRepository::instance().subscribe(observer);
}

/**
 * @brief Unsubscribes an observer from technician repository updates.
 * 
 * @param observer Pointer to the observer.
 */
void TechnicianRepositoryProxy::unsubscribe(ATechnicianObserver *observer)
{
  TechnicianRepository::instance().unsubscribe(observer);
}