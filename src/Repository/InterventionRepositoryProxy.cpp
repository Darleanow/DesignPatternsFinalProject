/**
 * @file InterventionRepositoryProxy.cpp
 * @brief Implements the InterventionRepositoryProxy class, a secure proxy to the InterventionRepository.
 */

#include "TechMa/Repository/InterventionRepositoryProxy.h"
#include "TechMa/Repository/TechnicianRepositoryProxy.h"

/**
 * @brief Returns the singleton instance of the proxy.
 * 
 * @return Reference to the unique instance of InterventionRepositoryProxy.
 */
InterventionRepositoryProxy &InterventionRepositoryProxy::instance()
{
  static InterventionRepositoryProxy proxy;
  return proxy;
}

/**
 * @brief Finds an intervention by ID through the underlying repository.
 * 
 * @param id The ID of the intervention to retrieve.
 * @return An optional shared pointer to the intervention if found.
 */
std::optional<std::shared_ptr<AIntervention>>
    InterventionRepositoryProxy::find_by_id(int id) const
{
  return InterventionRepository::instance().find_by_id(id);
}

/**
 * @brief Retrieves all interventions through the underlying repository.
 * 
 * @return A vector containing shared pointers to all interventions.
 */
std::vector<std::shared_ptr<AIntervention>>
    InterventionRepositoryProxy::get_all() const
{
  return InterventionRepository::instance().get_all();
}

/**
 * @brief Gets the next available ID for a new intervention.
 * 
 * @return The next unique intervention ID.
 */
int InterventionRepositoryProxy::next_id()
{
  return InterventionRepository::instance().next_id();
}

/**
 * @brief Saves an intervention, enforcing a technician-level access check.
 * 
 * @param intervention The intervention to save.
 * @throws AccessDeniedException if the user does not have TECHNICIAN privileges.
 */
void InterventionRepositoryProxy::save(
    const std::shared_ptr<AIntervention> &intervention
)
{
  if (!AuthenticationService::instance().has_role(UserRole::TECHNICIAN)) {
    throw AccessDeniedException(
        "You must be at least a member to save interventions"
    );
  }
  InterventionRepository::instance().save(intervention);
}

/**
 * @brief Clears the intervention repository, restricted to admin users.
 * 
 * @throws AccessDeniedException if the user does not have ADMIN privileges.
 */
void InterventionRepositoryProxy::clear()
{
  if (!AuthenticationService::instance().has_role(UserRole::ADMIN)) {
    throw AccessDeniedException(
        "Admin privileges required to clear interventions"
    );
  }
  InterventionRepository::instance().clear();
}

/**
 * @brief Subscribes a QObject to repository update notifications.
 * 
 * @param subscriber The QObject to subscribe.
 */
void InterventionRepositoryProxy::subscribe(QObject *subscriber)
{
  InterventionRepository::instance().subscribe(subscriber);
}

/**
 * @brief Unsubscribes a QObject from repository update notifications.
 * 
 * @param subscriber The QObject to unsubscribe.
 */
void InterventionRepositoryProxy::unsubscribe(QObject *subscriber)
{
  InterventionRepository::instance().unsubscribe(subscriber);
}