/**
 * @file InterventionRepository.h
 * @brief Declares the InterventionRepository class, which manages storage and access to interventions.
 */

#pragma once

#include "TechMa/Entities/AIntervention.h"

#include <QObject>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

/**
 * @class InterventionRepository
 * @brief Singleton class that stores and manages interventions.
 * 
 * Provides methods for saving, retrieving, and managing interventions.
 * Also supports a subscription system to notify external QObject-based listeners.
 */
class InterventionRepository
{
public:
  /**
   * @brief Returns the singleton instance of the repository.
   * @return Reference to the singleton InterventionRepository.
   */
  static InterventionRepository &instance();

  /**
   * @brief Gets the next available unique intervention ID.
   * @return An integer representing the next ID.
   */
  int next_id();

  /**
   * @brief Saves a new or existing intervention in the repository.
   * @param intervention Shared pointer to the intervention to save.
   */
  void save(const std::shared_ptr<AIntervention> &intervention);

  /**
   * @brief Finds an intervention by its ID.
   * @param id The ID of the intervention to find.
   * @return An optional shared pointer to the found intervention.
   */
  std::optional<std::shared_ptr<AIntervention>> find_by_id(int id) const;

  /**
   * @brief Retrieves all interventions stored in the repository.
   * @return A vector of shared pointers to all interventions.
   */
  std::vector<std::shared_ptr<AIntervention>> get_all() const;

  /**
   * @brief Clears all stored interventions.
   */
  void clear();

  /**
   * @brief Subscribes a QObject to be notified of changes.
   * @param subscriber The QObject that wants to receive update notifications.
   */
  void subscribe(QObject *subscriber);

  /**
   * @brief Unsubscribes a QObject from notifications.
   * @param subscriber The QObject to remove from the notification list.
   */
  void unsubscribe(QObject *subscriber);

private:
  /**
   * @brief Private constructor for the singleton pattern.
   */
  InterventionRepository() = default;

  /**
   * @brief Notifies all subscribed QObjects about repository updates.
   */
  void notify_all() const;

  int m_current_id = 1; ///< Internal counter for generating unique intervention IDs.

  std::unordered_map<int, std::shared_ptr<AIntervention>> m_interventions; ///< Map of interventions indexed by ID.

  std::vector<QObject *> m_subscribers; ///< List of QObjects subscribed to repository updates.
};