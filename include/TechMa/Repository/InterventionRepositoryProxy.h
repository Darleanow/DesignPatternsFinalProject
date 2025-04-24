/**
 * @file InterventionRepositoryProxy.h
 * @brief Declares the InterventionRepositoryProxy class, a proxy to the actual intervention repository.
 */

#pragma once

#include "TechMa/Authentication/UserAuthentication.h"
#include "TechMa/Entities/AIntervention.h"
#include "TechMa/Repository/InterventionRepository.h"

#include <QObject>
#include <memory>
#include <optional>
#include <vector>

/**
 * @class InterventionRepositoryProxy
 * @brief Proxy class for the InterventionRepository with potential for access control or logging.
 * 
 * This class forwards calls to the underlying repository but provides an abstraction
 * layer that can be extended to enforce rules, permissions, or additional logic.
 */
class InterventionRepositoryProxy
{
public:
  /**
   * @brief Returns the singleton instance of the proxy.
   * @return Reference to the singleton InterventionRepositoryProxy.
   */
  static InterventionRepositoryProxy& instance();

  /**
   * @brief Finds an intervention by its ID.
   * @param id The ID to search for.
   * @return An optional containing the intervention if found.
   */
  std::optional<std::shared_ptr<AIntervention>> find_by_id(int id) const;

  /**
   * @brief Retrieves all interventions from the repository.
   * @return A vector of shared pointers to all interventions.
   */
  std::vector<std::shared_ptr<AIntervention>> get_all() const;

  /**
   * @brief Returns the next available ID for a new intervention.
   * @return The next unique intervention ID.
   */
  int next_id();

  /**
   * @brief Saves an intervention to the repository.
   * @param intervention The intervention to be saved.
   */
  void save(const std::shared_ptr<AIntervention> &intervention);

  /**
   * @brief Clears all interventions from the repository.
   */
  void clear();

  /**
   * @brief Subscribes a QObject to receive update notifications.
   * @param subscriber The QObject to subscribe.
   */
  void subscribe(QObject *subscriber);

  /**
   * @brief Unsubscribes a QObject from receiving update notifications.
   * @param subscriber The QObject to unsubscribe.
   */
  void unsubscribe(QObject *subscriber);

private:
  /**
   * @brief Private constructor for singleton enforcement.
   */
  InterventionRepositoryProxy() = default;
};