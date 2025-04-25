/**
 * @file ExpertiseDecorator.cpp
 * @brief Implements the ExpertiseDecorator class, which extends a technician's expertise using the Decorator pattern.
 */

#include "TechMa/Technician/ExpertiseDecorator.h"
#include "TechMa/Technician/TechnicianDecorator.h"
#include "TechMa/Types/ExpertiseField.h"

/**
 * @brief Constructs an ExpertiseDecorator with a base technician and an additional expertise field.
 * 
 * @param base The base technician to decorate.
 * @param field The expertise field to add.
 */
ExpertiseDecorator::ExpertiseDecorator(
    std::shared_ptr<ATechnician> base, ExpertiseField field
)
    : TechnicianDecorator(std::move(base)),
      m_field(field)
{
}

/**
 * @brief Gets the full list of expertise fields for the decorated technician.
 * 
 * Adds the new field to the existing list from the wrapped technician.
 * 
 * @return A vector containing all expertise fields, including the one added by this decorator.
 */
std::vector<ExpertiseField> ExpertiseDecorator::get_expertise() const
{
  auto base_expertises = m_wrapped->get_expertise();
  base_expertises.push_back(m_field);

  return base_expertises;
}

/**
 * @brief Checks if the technician has the specified expertise.
 * 
 * @param field The expertise field to check.
 * @return True if the technician has the expertise via the decorator or base.
 */
bool ExpertiseDecorator::has_expertise(ExpertiseField field) const
{
  return field == m_field || m_wrapped->has_expertise(field);
}