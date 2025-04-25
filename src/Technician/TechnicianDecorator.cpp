/**
 * @file TechnicianDecorator.cpp
 * @brief Implements the TechnicianDecorator abstract class, which delegates functionality to a wrapped ATechnician.
 */

#include "TechMa/Technician/TechnicianDecorator.h"
#include "TechMa/Types/ExpertiseField.h"

/**
 * @brief Constructs a TechnicianDecorator that wraps another ATechnician instance.
 * 
 * @param base The technician to decorate.
 */
TechnicianDecorator::TechnicianDecorator(std::shared_ptr<ATechnician> base)
    : m_wrapped(std::move(base))
{
}

/**
 * @brief Forwards the get_id call to the wrapped technician.
 * 
 * @return The ID of the wrapped technician.
 */
int TechnicianDecorator::get_id() const
{
  return m_wrapped->get_id();
}

/**
 * @brief Forwards the get_name call to the wrapped technician.
 * 
 * @return The name of the wrapped technician.
 */
std::string TechnicianDecorator::get_name() const
{
  return m_wrapped->get_name();
}

/**
 * @brief Forwards the get_expertise call to the wrapped technician.
 * 
 * @return A vector of the wrapped technician's expertise fields.
 */
std::vector<ExpertiseField> TechnicianDecorator::get_expertise() const
{
  return m_wrapped->get_expertise();
}

/**
 * @brief Forwards the has_expertise call to the wrapped technician.
 * 
 * @param field The field to check for.
 * @return True if the technician has the specified expertise.
 */
bool TechnicianDecorator::has_expertise(ExpertiseField field) const
{
  return m_wrapped->has_expertise(field);
}