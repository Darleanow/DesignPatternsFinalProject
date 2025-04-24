/**
 * @file InterventionPage.cpp
 * @brief Implements the InterventionPage class, a QWidget handling intervention-related UI and interactions.
 */

#include "TechMa/Views/Pages/InterventionPage.h"
#include "TechMa/Authentication/UserAuthentication.h"
#include "TechMa/Facade/InterventionCreatorFacade.h"
#include "TechMa/Repository/InterventionRepositoryProxy.h"
#include "TechMa/Views/Widgets/CreateInterventionDialog.h"
#include "TechMa/Views/Widgets/EntityEditorLayout.h"
#include "TechMa/Views/Widgets/InterventionEditPanel.h"
#include "TechMa/Views/Widgets/InterventionsListView.h"
#include "TechMa/Repository/TechnicianRepositoryProxy.h"

#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>

/**
 * @brief Constructor that initializes and connects all UI components.
 * 
 * @param parent Optional parent QWidget.
 */
InterventionPage::InterventionPage(QWidget *parent) : QWidget(parent)
{
  setup_ui();
  setup_connects();

  update_ui_for_current_role();
}

/**
 * @brief Sets up the main layout and initializes widgets.
 */
void InterventionPage::setup_ui()
{
  m_layout =
      new EntityEditorLayout("Interventions", "Create Intervention", this);
  m_create_button = m_layout->action_button();

  m_list_view = new InterventionsListView(this);
  m_layout->set_left_widget(m_list_view);

  m_edit_panel = new InterventionEditPanel(this);
  m_layout->set_right_widget(m_edit_panel);
  m_edit_panel->setVisible(false);

  auto *wrapper_layout = new QVBoxLayout(this);
  wrapper_layout->addWidget(m_layout);
  setLayout(wrapper_layout);

  m_create_dialog = new CreateInterventionDialog(this);
}

/**
 * @brief Connects UI signals and slots to handle creation and editing of interventions.
 */
void InterventionPage::setup_connects()
{
  connect(m_create_button, &QPushButton::clicked, this, [this]() {
    try {
      if (m_create_dialog->exec() == QDialog::Accepted) {
        auto data = m_create_dialog->intervention_data();
        if (data.has_value()) {
          data->id = InterventionRepositoryProxy::instance().next_id();
          auto intervention =
              InterventionCreatorFacade::create_intervention(data.value());
          InterventionRepositoryProxy::instance().save(intervention);
        }
      }
    } catch (const AccessDeniedException &e) {
      QMessageBox::warning(
          this, "Access Denied", QString::fromStdString(e.what())
      );
    }
  });

  connect(
      m_list_view, &InterventionsListView::intervention_selected, this,
      [this](int id) {
        m_selected_intervention_id = id;
        auto opt = InterventionRepositoryProxy::instance().find_by_id(id);
        if (opt.has_value()) {
          const auto &intervention = opt.value();
          m_edit_panel->load(intervention->data());
        }

        update_ui_for_current_role();
      }
  );

  connect(m_edit_panel->save_button(), &QPushButton::clicked, this, [this]() {
    if (!m_selected_intervention_id.has_value())
      return;

    try {
      auto data    = m_edit_panel->to_data();
      data.id      = *m_selected_intervention_id;
      auto updated = InterventionCreatorFacade::create_intervention(data);
      InterventionRepositoryProxy::instance().save(updated);
    } catch (const AccessDeniedException &e) {
      QMessageBox::warning(
          this, "Access Denied", QString::fromStdString(e.what())
      );
    }
  });
}

/**
 * @brief Updates the UI components according to the current user's role.
 */
void InterventionPage::update_ui_for_current_role()
{
  bool can_edit =
      AuthenticationService::instance().has_role(UserRole::TECHNICIAN);

  m_create_button->setEnabled(can_edit);

  if (m_edit_panel) {
    m_edit_panel->save_button()->setEnabled(can_edit);

    if (!can_edit && m_edit_panel->isVisible()) {
      QLabel *warning =
          new QLabel("View only mode. Please log in to edit.", m_edit_panel);
      warning->setStyleSheet("color: red;");

      QFormLayout *layout = qobject_cast<QFormLayout *>(m_edit_panel->layout());
      if (layout) {
        layout->addRow("", warning);
      }
    }
  }
}

/**
 * @brief Overridden Qt event triggered when the widget is shown.
 * 
 * Updates the UI to reflect user permissions.
 * 
 * @param event The Qt show event.
 */
void InterventionPage::showEvent(QShowEvent *event)
{
  QWidget::showEvent(event);

  update_ui_for_current_role();
}