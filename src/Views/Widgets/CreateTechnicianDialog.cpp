#include "TechMa/Views/Widgets/CreateTechnicianDialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QListWidget>

CreateTechnicianDialog::CreateTechnicianDialog(QWidget *parent)
    : QDialog(parent)
{
  setup_ui();
  setup_connects();
}

void CreateTechnicianDialog::setup_ui()
{
  setWindowTitle("New Technician");

  auto *form = new QFormLayout(this);

  m_name_line_edit = new QLineEdit(this);
  form->addRow("Full Name", m_name_line_edit);

  m_expertise_list = new QListWidget(this);
  m_expertise_list->setSelectionMode(QAbstractItemView::MultiSelection);

  static const std::vector<ExpertiseField> all_fields = {
      ExpertiseField::ELECTRICAL, ExpertiseField::NETWORKING,
      ExpertiseField::HVAC,       ExpertiseField::PLUMBING,
      ExpertiseField::SECURITY,   ExpertiseField::SOFTWARE,
      ExpertiseField::HARDWARE,   ExpertiseField::FIRE_SAFETY,
      ExpertiseField::STRUCTURAL, ExpertiseField::GENERALIST
  };

  for(const auto &field : all_fields)
    m_expertise_list->addItem(QString::fromStdString(to_string(field)));

  form->addRow("Expertise Fields", m_expertise_list);

  m_buttons = new QDialogButtonBox(
      QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this
  );
  form->addRow(m_buttons);

  resize(700, 500);
}

void CreateTechnicianDialog::setup_connects()
{
  connect(m_buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(m_buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

std::vector<ExpertiseField> CreateTechnicianDialog::selected_expertises() const
{
  std::vector<ExpertiseField> result;

  for(QListWidgetItem *item : m_expertise_list->selectedItems()) {
    QString text = item->text();

    if(text == "Electrical")
      result.push_back(ExpertiseField::ELECTRICAL);
    else if(text == "Networking")
      result.push_back(ExpertiseField::NETWORKING);
    else if(text == "HVAC")
      result.push_back(ExpertiseField::HVAC);
    else if(text == "Plumbing")
      result.push_back(ExpertiseField::PLUMBING);
    else if(text == "Security")
      result.push_back(ExpertiseField::SECURITY);
    else if(text == "Software")
      result.push_back(ExpertiseField::SOFTWARE);
    else if(text == "Hardware")
      result.push_back(ExpertiseField::HARDWARE);
    else if(text == "Fire Safety")
      result.push_back(ExpertiseField::FIRE_SAFETY);
    else if(text == "Structural")
      result.push_back(ExpertiseField::STRUCTURAL);
    else if(text == "Generalist")
      result.push_back(ExpertiseField::GENERALIST);
  }

  return result;
}

QString CreateTechnicianDialog::full_name() const
{
  return m_name_line_edit->text();
}
