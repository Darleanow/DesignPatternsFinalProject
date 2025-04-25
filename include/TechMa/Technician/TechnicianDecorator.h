/**
 * @file TechnicianDecorator.h
 * @brief Declares the TechnicianDecorator abstract class used to extend technician functionality.
 */

#pragma once

#include "TechMa/Entities/ATechnician.h"
#include "TechMa/Types/ExpertiseField.h"

#include <memory>

/**
 * @class TechnicianDecorator
 * @brief Abstract base class for decorating ATechnician instances with additional behaviors.
 * 
 * Implements the Decorator design pattern by wrapping another ATechnician object and forwarding calls.
 * Subclasses can override specific behaviors (e.g., expertise, permissions).
 */
class TechnicianDecorator : public ATechnician
{
public:
  /**
   * @brief Constructs a TechnicianDecorator wrapping a given technician.
   * 
   * @param base The technician instance to wrap.
   */
  explicit TechnicianDecorator(std::shared_ptr<ATechnician> base);

  /**
   * @brief Retrieves the ID of the wrapped technician.
   * 
   * @return The technician ID.
   */
  int get_id() const override;

  /**
   * @brief Retrieves the name of the wrapped technician.
   * 
   * @return The technician's name.
   */
  std::string get_name() const override;

  /**
   * @brief Retrieves the expertise fields of the wrapped technician.
   * 
   * @return A vector of expertise fields.
   */
  std::vector<ExpertiseField> get_expertise() const override;

  /**
   * @brief Checks if the technician has the specified expertise.
   * 
   * @param field The expertise field to check.
   * @return True if the technician has the expertise.
   */
  bool has_expertise(ExpertiseField field) const override;

protected:
  std::shared_ptr<ATechnician> m_wrapped; ///< The technician being decorated.
};