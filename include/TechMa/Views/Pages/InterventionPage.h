/**
 * @file InterventionPage.h
 * @brief Declares the InterventionPage class, the main widget for managing interventions in the UI.
 */

#pragma once

#include <QShowEvent>
#include <QWidget>
#include <optional>

class EntityEditorLayout;
class QPushButton;
class InterventionEditPanel;
class InterventionsListView;
class CreateInterventionDialog;

/**
 * @class InterventionPage
 * @brief Main QWidget that displays and manages all intervention-related UI components.
 * 
 * Includes a list of interventions, a panel for editing, and a dialog for creation.
 * Also handles role-based UI updates and user interactions.
 */
class InterventionPage : public QWidget
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs the InterventionPage widget.
   * 
   * @param parent Optional parent QWidget.
   */
  explicit InterventionPage(QWidget *parent = nullptr);

protected:
  /**
   * @brief Handles the show event to trigger UI updates when the widget is shown.
   * 
   * @param event The show event.
   */
  void showEvent(QShowEvent *event) override;

private:
  /**
   * @brief Initializes and arranges all UI elements.
   */
  void setup_ui();

  /**
   * @brief Connects internal signals and slots.
   */
  void setup_connects();

  /**
   * @brief Updates UI visibility and behavior based on the user's role.
   */
  void update_ui_for_current_role();

  EntityEditorLayout       *m_layout;                  ///< Main layout container.
  QPushButton              *m_create_button;           ///< Button to create a new intervention.
  InterventionsListView    *m_list_view;               ///< View listing existing interventions.
  InterventionEditPanel    *m_edit_panel;              ///< Panel for editing selected intervention.
  CreateInterventionDialog *m_create_dialog;           ///< Dialog window for creating new intervention.

  std::optional<int>        m_selected_intervention_id; ///< ID of the currently selected intervention, if any.
};