/**
 * @file TechnicianEditPanel.h
 * @brief Declares the TechnicianEditPanel class, a widget to edit a technician's name and expertise fields.
 */

#pragma once

#include "TechMa/Types/ExpertiseField.h"

#include <QWidget>
#include <vector>

class QLineEdit;
class QListWidget;
class QPushButton;

/**
 * @class TechnicianEditPanel
 * @brief A QWidget-based editor for modifying technician data.
 * 
 * Provides input fields for technician name and a multi-select list for expertise fields.
 */
class TechnicianEditPanel : public QWidget
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs the edit panel and initializes the UI.
   * 
   * @param parent Optional parent widget.
   */
  explicit TechnicianEditPanel(QWidget *parent = nullptr);

  /**
   * @brief Sets the name in the input field.
   * 
   * @param name The technician's name.
   */
  void set_name(const QString &name);

  /**
   * @brief Sets the selected expertise fields in the list.
   * 
   * @param expertises A vector of expertise fields to check.
   */
  void set_expertises(const std::vector<ExpertiseField> &expertises);

  /**
   * @brief Returns the current name in the input field.
   * 
   * @return The technician name entered by the user.
   */
  QString name() const;

  /**
   * @brief Retrieves the selected expertise fields from the list.
   * 
   * @return A vector of selected expertise fields.
   */
  std::vector<ExpertiseField> selected_expertises() const;

  /**
   * @brief Provides access to the save button.
   * 
   * @return Pointer to the save QPushButton.
   */
  QPushButton *save_button() const;

  /**
   * @brief Loads a technician into the panel for editing.
   * 
   * @param id The technician's ID.
   * @param name The technician's name.
   * @param expertises The list of expertise fields.
   */
  void load_technician(
      int id,
      const QString &name,
      const std::vector<ExpertiseField> &expertises
  );

private:
  /**
   * @brief Initializes all UI components and layout.
   */
  void setup_ui();

  int          m_technician_id;     ///< ID of the currently loaded technician.
  QLineEdit   *m_name_input;        ///< Input for technician's name.
  QListWidget *m_expertise_list;    ///< Multi-select list for expertise.
  QPushButton *m_save_button;       ///< Button to save changes.
};