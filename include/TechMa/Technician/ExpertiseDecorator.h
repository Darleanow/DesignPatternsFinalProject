/**
 * @file ExpertiseDecorator.h
 * @brief Declares the ExpertiseDecorator class, which adds an expertise field to a technician using the Decorator pattern.
 */

#pragma once

#include "TechMa/Technician/TechnicianDecorator.h"
#include "TechMa/Types/ExpertiseField.h"

/**
 * @class ExpertiseDecorator
 * @brief A concrete decorator that adds an expertise field to a technician.
 * 
 * This class extends a technician's capabilities by adding a specific area of expertise.
 * It implements the Decorator design pattern by wrapping an existing ATechnician instance.
 */
class ExpertiseDecorator : public TechnicianDecorator
{
public:
  /**
   * @brief Constructs an ExpertiseDecorator.
   * 
   * @param base The base technician to decorate.
   * @param field The additional expertise field to add.
   */
  ExpertiseDecorator(std::shared_ptr<ATechnician> base, ExpertiseField field);

  /**
   * @brief Retrieves all expertise fields of the technician, including the added one.
   * 
   * @return A vector containing the combined expertise fields.
   */
  std::vector<ExpertiseField> get_expertise() const override;

  /**
   * @brief Checks if the technician has the specified expertise.
   * 
   * @param field The expertise field to check.
   * @return True if the field matches the added expertise or is already present in the base.
   */
  bool has_expertise(ExpertiseField field) const override;

private:
  ExpertiseField m_field; ///< The additional expertise field added by this decorator.
};