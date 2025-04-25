/**
 * @file TechnicianRepositoryProxy.h
 * @brief Declares the TechnicianRepositoryProxy class and the AccessDeniedException.
 */

#pragma once

#include "TechMa/Authentication/UserAuthentication.h"
#include "TechMa/Entities/ATechnician.h"
#include "TechMa/Observer/ATechnicianObserver.h"
#include "TechMa/Repository/TechnicianRepository.h"

#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @class AccessDeniedException
 * @brief Exception thrown when a user attempts an operation without sufficient privileges.
 */
class AccessDeniedException : public std::runtime_error
{
public:
  /**
   * @brief Constructs a new AccessDeniedException.
   * 
   * @param message Explanation of the access denial.
   */
  AccessDeniedException(const std::string &message);
};

/**
 * @class TechnicianRepositoryProxy
 * @brief Proxy class for TechnicianRepository, providing access control and observer delegation.
 * 
 * This proxy enforces role-based access control on technician operations.
 */
class TechnicianRepositoryProxy
{
public:
  /**
   * @brief Returns the singleton instance of the TechnicianRepositoryProxy.
   * 
   * @return Reference to the global instance.
   */
  static TechnicianRepositoryProxy &instance();

  /**
   * @brief Finds a technician by ID.
   * 
   * @param id Technician ID.
   * @return Optional shared pointer to the technician, or std::nullopt if not found.
   */
  std::optional<std::shared_ptr<ATechnician>> find_by_id(int id) const;

  /**
   * @brief Retrieves all technicians from the repository.
   * 
   * @return A vector of shared pointers to all technicians.
   */
  std::vector<std::shared_ptr<ATechnician>> get_all() const;

  /**
   * @brief Gets the next available technician ID.
   * 
   * @return The next unique ID.
   */
  int next_id();

  /**
   * @brief Saves a technician in the repository.
   * 
   * Requires TECHNICIAN role or higher.
   * 
   * @param tech Shared pointer to the technician.
   * @throws AccessDeniedException if current user lacks permission.
   */
  void save(std::shared_ptr<ATechnician> tech);

  /**
   * @brief Removes a technician by ID.
   * 
   * Requires ADMIN role.
   * 
   * @param id ID of the technician to remove.
   * @return True if removal was successful.
   * @throws AccessDeniedException if current user lacks permission.
   */
  bool remove_by_id(int id);

  /**
   * @brief Subscribes an observer for technician repository updates.
   * 
   * @param observer Pointer to the observer.
   */
  void subscribe(ATechnicianObserver *observer);

  /**
   * @brief Unsubscribes an observer from updates.
   * 
   * @param observer Pointer to the observer to remove.
   */
  void unsubscribe(ATechnicianObserver *observer);

private:
  /**
   * @brief Private constructor for singleton pattern.
   */
  TechnicianRepositoryProxy() = default;
};