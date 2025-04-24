/**
 * @file InterventionRepository.cpp
 * @brief Implements the InterventionRepository singleton class.
 */

#include "TechMa/Repository/InterventionRepository.h"

/**
 * @brief Returns the singleton instance of the InterventionRepository.
 * 
 * This method ensures that only one instance of the repository exists.
 * @return Reference to the singleton instance.
 */
InterventionRepository &InterventionRepository::instance()
{
  static InterventionRepository repository;
  return repository;
}

/**
 * @brief Returns the next available unique ID and increments the counter.
 * 
 * @return The next intervention ID.
 */
int InterventionRepository::next_id()
{
  return m_current_id++;
}

/**
 * @brief Saves an intervention in the repository and notifies subscribers.
 * 
 * @param intervention The intervention to be stored.
 */
void InterventionRepository::save(
    const std::shared_ptr<AIntervention> &intervention
)
{
  m_interventions[intervention->id()] = intervention;
  notify_all();
}

/**
 * @brief Searches for an intervention by its ID.
 * 
 * @param id The ID of the intervention to find.
 * @return An optional containing the intervention if found, std::nullopt otherwise.
 */
std::optional<std::shared_ptr<AIntervention>>
    InterventionRepository::find_by_id(int id) const
{
  auto it = m_interventions.find(id);
  if (it != m_interventions.end())
    return it->second;
  return std::nullopt;
}

/**
 * @brief Retrieves a list of all stored interventions.
 * 
 * @return A vector containing shared pointers to all interventions.
 */
std::vector<std::shared_ptr<AIntervention>>
    InterventionRepository::get_all() const
{
  std::vector<std::shared_ptr<AIntervention>> result;
  for (const auto &[_, intervention] : m_interventions)
    result.push_back(intervention);
  return result;
}

/**
 * @brief Clears the intervention repository and notifies all subscribers.
 */
void InterventionRepository::clear()
{
  m_interventions.clear();
  notify_all();
}

/**
 * @brief Subscribes a QObject to be notified on repository updates.
 * 
 * @param subscriber The QObject to be added as a subscriber.
 */
void InterventionRepository::subscribe(QObject *subscriber)
{
  if (!subscriber)
    return;
  m_subscribers.push_back(subscriber);
}

/**
 * @brief Unsubscribes a QObject from repository updates.
 * 
 * @param subscriber The QObject to be removed from the subscriber list.
 */
void InterventionRepository::unsubscribe(QObject *subscriber)
{
  m_subscribers.erase(
      std::remove(m_subscribers.begin(), m_subscribers.end(), subscriber),
      m_subscribers.end()
  );
}

/**
 * @brief Notifies all subscribed QObjects by invoking their update method.
 */
void InterventionRepository::notify_all() const
{
  for (auto *sub : m_subscribers) {
    QMetaObject::invokeMethod(
        sub, "on_repository_updated", Qt::QueuedConnection
    );
  }
}