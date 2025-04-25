/**
 * @file CreateTechnicianDialog.h
 * @brief Declares the CreateTechnicianDialog class, a dialog for inputting new technician information.
 */

#pragma once

#include "TechMa/Types/ExpertiseField.h"

#include <QDialog>
#include <vector>

class QWidget;
class QDialogButtonBox;
class QListWidget;
class QLineEdit;

/**
 * @class CreateTechnicianDialog
 * @brief A dialog UI for creating a new technician, allowing input of name and selection of expertise fields.
 */
class CreateTechnicianDialog : public QDialog
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs the dialog and initializes the UI.
   * 
   * @param parent Optional parent widget.
   */
  explicit CreateTechnicianDialog(QWidget *parent = nullptr);

  /**
   * @brief Returns the list of selected expertises from the list widget.
   * 
   * @return A vector of selected ExpertiseField enums.
   */
  std::vector<ExpertiseField> selected_expertises() const;

  /**
   * @brief Retrieves the full name entered by the user.
   * 
   * @return A QString containing the technician's name.
   */
  QString full_name() const;

private:
  QDialogButtonBox *m_buttons;           ///< Dialog button box (OK/Cancel).
  QListWidget      *m_expertise_list;    ///< List of selectable expertise fields.
  QLineEdit        *m_name_line_edit;    ///< Input field for the technician's name.

  /**
   * @brief Builds and arranges the dialog's UI components.
   */
  void setup_ui();

  /**
   * @brief Connects UI events to their respective handlers.
   */
  void setup_connects();
};