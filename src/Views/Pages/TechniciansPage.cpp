/**
 * @file TechniciansPage.cpp
 * @brief Implements the TechniciansPage class, managing the technician creation and edition UI.
 */

#include "TechMa/Views/Pages/TechniciansPage.h"
#include "TechMa/Authentication/UserAuthentication.h"
#include "TechMa/Repository/TechnicianRepositoryProxy.h"
#include "TechMa/Technician/BasicTechnician.h"
#include "TechMa/Technician/ExpertiseDecorator.h"
#include "TechMa/Views/Widgets/CreateTechnicianDialog.h"
#include "TechMa/Views/Widgets/EntityEditorLayout.h"
#include "TechMa/Views/Widgets/TechnicianEditPanel.h"
#include "TechMa/Views/Widgets/TechniciansListView.h"

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QFormLayout>

/**
 * @brief Constructs the TechniciansPage and initializes the UI.
 * 
 * @param parent Optional parent widget.
 */
TechniciansPage::TechniciansPage(QWidget *parent) : QWidget(parent)
{
  setup_ui();
  setup_connects();

  update_ui_for_current_role();
}

/**
 * @brief Initializes all UI components and layout.
 */
void TechniciansPage::setup_ui()
{
  m_layout = new EntityEditorLayout("Technicians", "Create Technician", this);
  m_create_button = m_layout->action_button();

  m_list_view = new TechniciansListView(this);
  m_layout->set_left_widget(m_list_view);

  m_edit_panel = new TechnicianEditPanel(this);
  m_layout->set_right_widget(m_edit_panel);

  auto *wrapper_layout = new QVBoxLayout(this);
  wrapper_layout->addWidget(m_layout);
  setLayout(wrapper_layout);

  m_create_dialog = new CreateTechnicianDialog(this);
}

/**
 * @brief Connects user actions (buttons, selection) to their respective logic.
 */
void TechniciansPage::setup_connects()
{
  connect(m_create_button, &QPushButton::clicked, m_create_dialog, [this]() {
    try {
      if (m_create_dialog->exec() == QDialog::Accepted) {
        auto full_name = m_create_dialog->full_name();
        auto selected_expertises = m_create_dialog->selected_expertises();

        auto &technician_repository = TechnicianRepositoryProxy::instance();

        std::shared_ptr<ATechnician> technician =
            std::make_shared<BasicTechnician>(
                technician_repository.next_id(), full_name.toStdString()
            );

        for (const auto &expertise : selected_expertises) {
          technician = std::make_shared<ExpertiseDecorator>(technician, expertise);
        }

        technician_repository.save(technician);
      }
    } catch (const AccessDeniedException &e) {
      QMessageBox::warning(
          this, "Access Denied", QString::fromStdString(e.what())
      );
    }
  });

  connect(
      m_list_view, &TechniciansListView::technician_selected, this,
      [this](int id) {
        m_selected_technician_id = id;

        const auto tech = TechnicianRepositoryProxy::instance().find_by_id(id);
        if (!tech)
          return;

        m_edit_panel->load_technician(
            tech->get()->get_id(),
            QString::fromStdString(tech->get()->get_name()),
            tech->get()->get_expertise()
        );

        m_edit_panel->setVisible(true);

        update_ui_for_current_role();
      }
  );

  connect(m_edit_panel->save_button(), &QPushButton::clicked, this, [this]() {
    if (!m_selected_technician_id.has_value())
      return;

    try {
      const auto id = *m_selected_technician_id;
      const auto name = m_edit_panel->name().toStdString();
      const auto expertises = m_edit_panel->selected_expertises();

      std::shared_ptr<ATechnician> technician =
          std::make_shared<BasicTechnician>(id, name);

      for (const auto &exp : expertises)
        technician = std::make_shared<ExpertiseDecorator>(technician, exp);

      TechnicianRepositoryProxy::instance().save(technician);
    } catch (const AccessDeniedException &e) {
      QMessageBox::warning(
          this, "Access Denied", QString::fromStdString(e.what())
      );
    }
  });
}

/**
 * @brief Updates UI elements according to the user's role.
 */
void TechniciansPage::update_ui_for_current_role()
{
  bool is_admin = AuthenticationService::instance().has_role(UserRole::ADMIN);

  m_create_button->setEnabled(is_admin);
  m_create_button->setVisible(is_admin);

  if (m_edit_panel) {
    m_edit_panel->save_button()->setEnabled(is_admin);

    if (!is_admin && m_edit_panel->isVisible()) {
      QLabel *warning = new QLabel(
          "View only mode. Admin access required to edit.", m_edit_panel
      );
      warning->setStyleSheet("color: red;");

      QFormLayout *layout = qobject_cast<QFormLayout *>(m_edit_panel->layout());
      if (layout) {
        layout->addRow("", warning);
      }
    }
  }
}

/**
 * @brief Handles the show event and refreshes UI based on current permissions.
 * 
 * @param event The Qt show event.
 */
void TechniciansPage::showEvent(QShowEvent *event)
{
  QWidget::showEvent(event);
  update_ui_for_current_role();
}