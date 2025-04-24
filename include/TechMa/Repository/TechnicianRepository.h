/**
 * @file TechnicianRepository.h
 * @brief Declares the TechnicianRepository class, responsible for storing and managing technicians.
 */

#pragma once

#include "TechMa/Entities/ATechnician.h"
#include "TechMa/Observer/ATechnicianObserver.h"

#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

/**
 * @class TechnicianRepository
 * @brief Singleton repository for storing and accessing ATechnician instances.
 * 
 * Supports basic CRUD operations and implements an observer pattern to notify subscribers when changes occur.
 */
class TechnicianRepository
{
public:
  /**
   * @brief Returns the singleton instance of the repository.
   * 
   * @return Reference to the global TechnicianRepository instance.
   */
  static TechnicianRepository &instance();

  /**
   * @brief Saves or updates a technician in the repository.
   * 
   * @param tech Shared pointer to the technician to save.
   */
  void save(std::shared_ptr<ATechnician> tech);

  /**
   * @brief Removes a technician by their ID.
   * 
   * @param id The ID of the technician to remove.
   * @return True if a technician was removed, false otherwise.
   */
  bool remove_by_id(int id);

  /**
   * @brief Retrieves a technician by their ID.
   * 
   * @param id The ID to look up.
   * @return Optional shared pointer to the technician, or std::nullopt if not found.
   */
  std::optional<std::shared_ptr<ATechnician>> find_by_id(int id) const;

  /**
   * @brief Retrieves all technicians in the repository.
   * 
   * @return A vector of shared pointers to all stored technicians.
   */
  std::vector<std::shared_ptr<ATechnician>> get_all() const;

  /**
   * @brief Generates the next available unique technician ID.
   * 
   * @return The next ID as an integer.
   */
  int next_id();

  /**
   * @brief Subscribes an observer to be notified on repository changes.
   * 
   * @param observer Pointer to an observer implementing ATechnicianObserver.
   */
  void subscribe(ATechnicianObserver *observer);

  /**
   * @brief Unsubscribes an observer from notifications.
   * 
   * @param observer Pointer to the observer to remove.
   */
  void unsubscribe(ATechnicianObserver *observer);

private:
  std::unordered_map<int, std::shared_ptr<ATechnician>> technicians; ///< Storage map of technicians.
  int m_next_id = 1; ///< Counter for generating unique IDs.
  std::vector<ATechnicianObserver *> m_observers; ///< List of subscribed observers.

  /**
   * @brief Private constructor for singleton pattern.
   */
  TechnicianRepository() = default;

  /**
   * @brief Notifies all subscribed observers of repository changes.
   */
  void notify_all();
};