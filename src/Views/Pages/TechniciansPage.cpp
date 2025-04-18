#include "TechMa/Views/Pages/TechniciansPage.h"
#include "TechMa/Views/Widgets/CreateTechnicianDialog.h"

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

  m_create_button = new QPushButton("Create Technician", this);

  top_bar->addWidget(page_name);
  top_bar->addWidget(m_create_button);
  setLayout(top_bar);

  m_create_dialog = new CreateTechnicianDialog(this);
}

void TechniciansPage::setup_connects()
{
  connect(m_create_button, &QPushButton::clicked, m_create_dialog, [this]() {
    if(m_create_dialog->exec() == QDialog::Accepted) {
      auto selected = m_create_dialog->selected_expertise();

      for(auto field : selected) {
        qDebug() << QString::fromStdString(to_string(field));
      }
    }
  });
}
