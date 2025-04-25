/**
 * @file TechniciansPage.h
 * @brief Declares the TechniciansPage class, a QWidget for managing technician-related data in the UI.
 */

#pragma once

#include <QShowEvent>
#include <QWidget>
#include <optional>

class QPushButton;
class CreateTechnicianDialog;
class TechniciansListView;
class EntityEditorLayout;
class TechnicianEditPanel;

/**
 * @class TechniciansPage
 * @brief A QWidget page for displaying, creating, and editing technicians.
 * 
 * This page includes a list view, an editor panel, and a button for creating new technicians.
 * The content and controls adapt based on the user's role.
 */
class TechniciansPage : public QWidget
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs the TechniciansPage.
   * 
   * @param parent Optional parent widget.
   */
  explicit TechniciansPage(QWidget *parent);

protected:
  /**
   * @brief Overridden show event to update UI state when the widget is shown.
   * 
   * @param event The show event triggered by Qt.
   */
  void showEvent(QShowEvent *event) override;

private:
  /**
   * @brief Sets up the layout and UI widgets.
   */
  void setup_ui();

  /**
   * @brief Connects UI signals and slots for interaction logic.
   */
  void setup_connects();

  /**
   * @brief Updates the UI elements based on the currently logged-in user's role.
   */
  void update_ui_for_current_role();

  QPushButton            *m_create_button;             ///< Button to create a new technician.
  CreateTechnicianDialog *m_create_dialog;             ///< Dialog to input new technician data.
  TechniciansListView    *m_list_view;                 ///< View listing all technicians.
  EntityEditorLayout     *m_layout;                    ///< Container layout managing both list and panel.
  TechnicianEditPanel    *m_edit_panel;                ///< Panel for editing a selected technician.
  std::optional<int>      m_selected_technician_id;    ///< ID of the currently selected technician.
};