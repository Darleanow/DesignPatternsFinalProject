#include "TechMa/Views/Pages/TechniciansPage.h"
#include "TechMa/Repository/TechnicianRepository.h"
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
#include <QPushButton>

TechniciansPage::TechniciansPage(QWidget *parent) : QWidget(parent)
{
  setup_ui();
  setup_connects();
}

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

void TechniciansPage::setup_connects()
{
  connect(m_create_button, &QPushButton::clicked, m_create_dialog, [this]() {
    if(m_create_dialog->exec() == QDialog::Accepted) {
      auto  full_name           = m_create_dialog->full_name();
      auto  selected_expertises = m_create_dialog->selected_expertises();

      auto &technician_repository = TechnicianRepository::instance();

      std::shared_ptr<ATechnician> technician =
          std::make_shared<BasicTechnician>(
              technician_repository.next_id(), full_name.toStdString()
          );

      for(const auto &expertise : selected_expertises) {
        technician =
            std::make_shared<ExpertiseDecorator>(technician, expertise);
      }

      technician_repository.save(technician);
    }
  });

  connect(
      m_list_view, &TechniciansListView::technician_selected, this,
      [this](int id) {
        m_selected_technician_id = id;

        const auto tech = TechnicianRepository::instance().find_by_id(id);
        if(!tech)
          return;

        m_edit_panel->load_technician(
            tech->get()->get_id(),
            QString::fromStdString(tech->get()->get_name()),
            tech->get()->get_expertise()
        );

        m_edit_panel->setVisible(true);
      }
  );

  connect(m_edit_panel->save_button(), &QPushButton::clicked, this, [this]() {
    if(!m_selected_technician_id.has_value())
      return;

    const auto id         = *m_selected_technician_id;
    const auto name       = m_edit_panel->name().toStdString();
    const auto expertises = m_edit_panel->selected_expertises();

    std::shared_ptr<ATechnician> technician =
        std::make_shared<BasicTechnician>(id, name);

    for(const auto &exp : expertises)
      technician = std::make_shared<ExpertiseDecorator>(technician, exp);

    TechnicianRepository::instance().save(technician);
  });
}
