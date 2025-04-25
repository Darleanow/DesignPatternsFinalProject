/**
 * @file ATechnicianObserver.h
 * @brief Declares the ATechnicianObserver interface used for observing technician-related changes.
 */

#pragma once

/**
 * @class ATechnicianObserver
 * @brief Interface for classes that need to observe changes in the technician repository.
 * 
 * This abstract observer is typically used in the Observer design pattern to be notified
 * when a repository of technicians is updated.
 */
class ATechnicianObserver
{
public:
  /**
   * @brief Virtual destructor for safe deletion through a base class pointer.
   */
  virtual ~ATechnicianObserver() = default;

  /**
   * @brief Called when the technician repository is updated.
   * 
   * Implement this method to define how an observer should react to changes.
   */
  virtual void on_repository_updated() = 0;
};