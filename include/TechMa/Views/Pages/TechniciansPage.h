#pragma once

#include <QShowEvent>
#include <QWidget>

class QPushButton;
class CreateTechnicianDialog;
class TechniciansListView;
class EntityEditorLayout;
class TechnicianEditPanel;

class TechniciansPage : public QWidget
{
  Q_OBJECT;

public:
  explicit TechniciansPage(QWidget *parent);

protected:
  void showEvent(QShowEvent *event) override;

private:
  void                    setup_ui();
  void                    setup_connects();
  void                    update_ui_for_current_role();

  QPushButton            *m_create_button;
  CreateTechnicianDialog *m_create_dialog;
  TechniciansListView    *m_list_view;

  EntityEditorLayout     *m_layout;
  TechnicianEditPanel    *m_edit_panel;

  std::optional<int>      m_selected_technician_id;
};