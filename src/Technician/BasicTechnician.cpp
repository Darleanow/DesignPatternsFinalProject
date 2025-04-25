/**
 * @file BasicTechnician.cpp
 * @brief Implements the BasicTechnician class.
 */

#include "TechMa/Technician/BasicTechnician.h"
#include "TechMa/Types/ExpertiseField.h"

/**
 * @brief Constructs a BasicTechnician with a specified ID and name.
 * 
 * @param id Unique identifier for the technician.
 * @param name Name of the technician.
 */
BasicTechnician::BasicTechnician(int id, std::string name)
    : m_id(id),
      m_name(std::move(name))
{
}

/**
 * @brief Gets the technician's ID.
 * 
 * @return The unique ID of the technician.
 */
int BasicTechnician::get_id() const
{
  return m_id;
}

/**
 * @brief Gets the technician's name.
 * 
 * @return The name of the technician.
 */
std::string BasicTechnician::get_name() const
{
  return m_name;
}

/**
 * @brief Returns the list of expertise fields.
 * 
 * @return An empty vector, as BasicTechnician has no specific expertise by default.
 */
std::vector<ExpertiseField> BasicTechnician::get_expertise() const
{
  return {}; // None by default
}

/**
 * @brief Checks whether the technician has a specific expertise.
 * 
 * @param field The expertise field to check.
 * @return Always false for BasicTechnician.
 */
bool BasicTechnician::has_expertise(ExpertiseField) const
{
  return false;
}