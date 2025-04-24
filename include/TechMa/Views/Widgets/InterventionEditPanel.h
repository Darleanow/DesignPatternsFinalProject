/**
 * @file InterventionEditPanel.h
 * @brief Declares the InterventionEditPanel class, a QWidget for editing existing intervention data.
 */

#pragma once

#include "TechMa/Entities/InterventionData.h"

#include <QWidget>

class QDateEdit;
class QSpinBox;
class QComboBox;
class QLineEdit;
class QPushButton;
class TechListController;

/**
 * @class InterventionEditPanel
 * @brief A QWidget-based panel for editing an existing intervention.
 * 
 * Provides UI elements to modify and save all properties of an InterventionData instance.
 */
class InterventionEditPanel : public QWidget
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs the panel and initializes UI components.
   * 
   * @param parent Optional parent QWidget.
   */
  explicit InterventionEditPanel(QWidget *parent = nullptr);

  /**
   * @brief Destructor.
   */
  ~InterventionEditPanel() override;

  /**
   * @brief Loads intervention data into the form for editing.
   * 
   * @param data The intervention data to load into the UI.
   */
  void load(const InterventionData &data);

  /**
   * @brief Extracts the modified data from the form.
   * 
   * @return The updated InterventionData based on user inputs.
   */
  InterventionData to_data() const;

  /**
   * @brief Provides access to the Save button.
   * 
   * @return Pointer to the save QPushButton.
   */
  QPushButton *save_button() const;

protected:
  /**
   * @brief Triggered when the widget is shown. Used to initialize controller state.
   * 
   * @param event The Qt show event.
   */
  void showEvent(QShowEvent *event) override;

private:
  /**
   * @brief Sets up all UI components and layout.
   */
  void setup_ui();

  /**
   * @brief Connects signals and slots for interactive behavior.
   */
  void setup_connects();

  int                 m_id;                    ///< ID of the currently loaded intervention.
  QDateEdit          *m_date_input       = nullptr; ///< Date input field.
  QSpinBox           *m_duration_input   = nullptr; ///< Duration in hours.
  QComboBox          *m_expertise_input  = nullptr; ///< Expertise required.
  QComboBox          *m_complexity_input = nullptr; ///< Intervention complexity.
  QComboBox          *m_type_input       = nullptr; ///< Type of intervention.
  QComboBox          *m_status_input     = nullptr; ///< Current status.
  QLineEdit          *m_location_input   = nullptr; ///< Address/location string.
  QLineEdit          *m_notes_input      = nullptr; ///< Optional notes.
  QComboBox          *m_technician_input = nullptr; ///< Assigned technician (if any).
  QPushButton        *m_save_button      = nullptr; ///< Save button to confirm changes.
  TechListController *m_tech_controller  = nullptr; ///< Controls the tech dropdown content.
};