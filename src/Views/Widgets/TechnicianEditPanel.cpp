#include "TechMa/Views/Widgets/TechnicianEditPanel.h"
#include "TechMa/Repository/TechnicianRepository.h"
#include "TechMa/Types/ExpertiseField.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <qpushbutton.h>

TechnicianEditPanel::TechnicianEditPanel(QWidget *parent) : QWidget(parent)
{
  setup_ui();
}

void TechnicianEditPanel::setup_ui()
{
  auto *layout = new QFormLayout(this);

  m_name_input = new QLineEdit(this);
  layout->addRow("Full Name", m_name_input);

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

  layout->addRow("Expertise Fields", m_expertise_list);

  m_save_button = new QPushButton("Save Changes", this);
  layout->addRow("", m_save_button);

  layout->setVerticalSpacing(12);
  layout->setContentsMargins(8, 8, 8, 8);

  setVisible(false);
}

void TechnicianEditPanel::set_name(const QString &name)
{
  m_name_input->setText(name);
}

QString TechnicianEditPanel::name() const
{
  return m_name_input->text();
}

void TechnicianEditPanel::set_expertises(
    const std::vector<ExpertiseField> &expertises
)
{
  for(int i = 0; i < m_expertise_list->count(); ++i) {
    auto *item = m_expertise_list->item(i);
    item->setSelected(false);
    for(const auto &field : expertises) {
      if(item->text() == QString::fromStdString(to_string(field)))
        item->setSelected(true);
    }
  }
}

void TechnicianEditPanel::load_technician(
    int id, const QString &name, const std::vector<ExpertiseField> &expertises
)
{
  m_technician_id = id;
  set_name(name);
  set_expertises(expertises);
}

std::vector<ExpertiseField> TechnicianEditPanel::selected_expertises() const
{
  std::vector<ExpertiseField> result;

  for(QListWidgetItem *item : m_expertise_list->selectedItems()) {
    const QString text = item->text();

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

QPushButton *TechnicianEditPanel::save_button() const
{
  return m_save_button;
}
