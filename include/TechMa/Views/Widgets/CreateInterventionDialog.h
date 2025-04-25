/**
 * @file CreateInterventionDialog.h
 * @brief Declares the CreateInterventionDialog class, a QDialog used to create new interventions.
 */

#pragma once

#include "TechMa/Entities/InterventionData.h"

#include <QDialog>
#include <optional>

class QDateEdit;
class QSpinBox;
class QComboBox;
class QLineEdit;
class QDialogButtonBox;
class TechListController;

/**
 * @class CreateInterventionDialog
 * @brief A modal dialog that allows users to input data for a new intervention.
 * 
 * Includes fields for date, duration, expertise, complexity, type, location, notes, and technician.
 */
class CreateInterventionDialog : public QDialog
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs the dialog.
   * 
   * @param parent Optional parent widget.
   */
  explicit CreateInterventionDialog(QWidget *parent = nullptr);

  /**
   * @brief Destructor.
   */
  ~CreateInterventionDialog() override;

  /**
   * @brief Retrieves the data entered by the user as an InterventionData object.
   * 
   * @return An optional InterventionData if the fields are valid and complete.
   */
  std::optional<InterventionData> intervention_data() const;

protected:
  /**
   * @brief Handles the show event to prepare or reset the dialog.
   * 
   * @param event The show event triggered by Qt.
   */
  void showEvent(QShowEvent *event) override;

private:
  /**
   * @brief Initializes and arranges all UI components.
   */
  void setup_ui();

  /**
   * @brief Connects UI components to their corresponding signals and slots.
   */
  void setup_connects();

  /**
   * @brief Clears all input fields in the form.
   */
  void clear_fields();

  /**
   * @brief Enables or disables the OK button based on form validity.
   */
  void update_ok_state();

  /**
   * @brief Tints a given icon with a specific color.
   * 
   * @param path Path to the icon file.
   * @param color The color to tint the icon with.
   * @return A QIcon with the specified tint.
   */
  QIcon tinted_icon(const QString &path, const QColor &color) const;

  QDateEdit         *m_date_input        = nullptr; ///< Date selection input.
  QSpinBox          *m_duration_input    = nullptr; ///< Expected duration input (in hours).
  QComboBox         *m_expertise_input   = nullptr; ///< Required expertise field selection.
  QComboBox         *m_complexity_input  = nullptr; ///< Intervention complexity selection.
  QComboBox         *m_type_input        = nullptr; ///< Type of intervention.
  QLineEdit         *m_location_input    = nullptr; ///< Location address input.
  QLineEdit         *m_notes_input       = nullptr; ///< Additional notes input.
  QComboBox         *m_technician_input  = nullptr; ///< Assigned technician selection.
  QDialogButtonBox  *m_buttons           = nullptr; ///< Dialog buttons (OK/Cancel).
  TechListController *m_tech_controller  = nullptr; ///< Controller to manage technician list based on inputs.
};