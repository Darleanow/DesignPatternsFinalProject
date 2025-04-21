#pragma once

#include <QWidget>
#include <optional>

class EntityEditorLayout;
class QPushButton;
class InterventionEditPanel;
class InterventionsListView;
class CreateInterventionDialog;

class InterventionPage : public QWidget
{
  Q_OBJECT;

public:
  explicit InterventionPage(QWidget *parent = nullptr);

private:
  void                      setup_ui();
  void                      setup_connects();

  EntityEditorLayout       *m_layout;
  QPushButton              *m_create_button;
  InterventionsListView    *m_list_view;
  InterventionEditPanel    *m_edit_panel;
  CreateInterventionDialog *m_create_dialog;

  std::optional<int>        m_selected_intervention_id;
};
