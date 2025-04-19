#include "TechMa/Views/Pages/TechniciansPage.h"
#include "TechMa/Repository/TechnicianRepository.h"
#include "TechMa/Technician/BasicTechnician.h"
#include "TechMa/Technician/ExpertiseDecorator.h"
#include "TechMa/Views/Widgets/CreateTechnicianDialog.h"
#include "TechMa/Views/Widgets/TechniciansListView.h"

#include <QLabel>
#include <QPushButton>
#include <qboxlayout.h>
#include <qdialog.h>

TechniciansPage::TechniciansPage(QWidget *parent) : QWidget(parent)
{
  setup_ui();
  setup_connects();
}

void TechniciansPage::setup_ui()
{
  auto  top_bar = new QHBoxLayout(this);

  auto *page_name = new QLabel("Technicians", this);
  page_name->setObjectName("Title");

  top_bar->addWidget(page_name);

  m_create_button = new QPushButton("Create Technician", this);

  top_bar->addWidget(m_create_button);

  m_list_view = new TechniciansListView(this);
  top_bar->addWidget(m_list_view);

  setLayout(top_bar);

  m_create_dialog = new CreateTechnicianDialog(this);
}

void TechniciansPage::setup_connects()
{
  connect(m_create_button, &QPushButton::clicked, m_create_dialog, [this]() {
    if(m_create_dialog->exec() == QDialog::Accepted) {
      auto  full_name           = m_create_dialog->full_name();
      auto  selected_expertises = m_create_dialog->selected_expertise();

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
}
