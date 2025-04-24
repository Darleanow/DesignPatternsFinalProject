/**
 * @file BasicTechnician.h
 * @brief Declares the BasicTechnician class, a simple implementation of the ATechnician interface.
 */

#pragma once

#include <string>

#include "TechMa/Entities/ATechnician.h"
#include "TechMa/Types/ExpertiseField.h"

/**
 * @class BasicTechnician
 * @brief A basic implementation of the ATechnician interface.
 * 
 * Represents a technician with a name and an ID, but no specific expertise fields by default.
 */
class BasicTechnician : public ATechnician
{
public:
  /**
   * @brief Constructs a BasicTechnician with a given ID and name.
   * 
   * @param id Unique identifier for the technician.
   * @param name Name of the technician.
   */
  BasicTechnician(int id, std::string name);

  /**
   * @brief Retrieves the technician's ID.
   * 
   * @return An integer representing the ID.
   */
  int get_id() const override;

  /**
   * @brief Retrieves the technician's name.
   * 
   * @return The technician's name as a string.
   */
  std::string get_name() const override;

  /**
   * @brief Retrieves the technician's areas of expertise.
   * 
   * @return A vector of expertise fields (empty for BasicTechnician).
   */
  std::vector<ExpertiseField> get_expertise() const override;

  /**
   * @brief Checks whether the technician has a specific expertise.
   * 
   * @param field The expertise field to check.
   * @return False for BasicTechnician, which has no specific expertise.
   */
  bool has_expertise(ExpertiseField field) const override;

private:
  int         m_id;   ///< Unique ID of the technician.
  std::string m_name; ///< Name of the technician.
};