/**
 * @file ATechnician.h
 * @brief Defines the abstract base class ATechnician representing a technician entity.
 */

#pragma once

#include <string>
#include <vector>

#include "TechMa/Types/ExpertiseField.h"

/**
 * @class ATechnician
 * @brief Abstract base class that represents a technician and their expertise.
 * 
 * This interface is used to define the essential attributes and behaviors of any technician entity,
 * such as retrieving their name, ID, and area of expertise.
 */
class ATechnician
{
public:
  /**
   * @brief Virtual destructor to ensure proper destruction of derived classes.
   */
  virtual ~ATechnician() = default;

  /**
   * @brief Gets the technician's full name.
   * @return The name of the technician as a string.
   */
  virtual std::string get_name() const = 0;

  /**
   * @brief Gets the technician's unique ID.
   * @return An integer representing the technician's ID.
   */
  virtual int get_id() const = 0;

  /**
   * @brief Retrieves the technician's areas of expertise.
   * @return A vector of ExpertiseField representing the technician's skills.
   */
  virtual std::vector<ExpertiseField> get_expertise() const = 0;

  /**
   * @brief Checks whether the technician possesses a specific area of expertise.
   * @param field The expertise field to check.
   * @return True if the technician has the expertise, false otherwise.
   */
  virtual bool has_expertise(ExpertiseField field) const = 0;
};