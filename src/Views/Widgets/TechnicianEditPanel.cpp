/**
 * @file TechnicianEditPanel.cpp
 * @brief Implements the TechnicianEditPanel class, providing a UI panel for editing technician data.
 */

#include "TechMa/Views/Widgets/TechnicianEditPanel.h"
#include "TechMa/Types/ExpertiseField.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

/**
 * @brief Constructor. Sets up the UI layout and widgets.
 * 
 * @param parent Optional parent widget.
 */
TechnicianEditPanel::TechnicianEditPanel(QWidget *parent) : QWidget(parent)
{
  setup_ui();
}

/**
 * @brief Initializes the UI components for the panel.
 */
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

  for (const auto &field : all_fields)
    m_expertise_list->addItem(QString::fromStdString(to_string(field)));

  layout->addRow("Expertise Fields", m_expertise_list);

  m_save_button = new QPushButton("Save Changes", this);
  layout->addRow("", m_save_button);

  layout->setVerticalSpacing(12);
  layout->setContentsMargins(8, 8, 8, 8);

  setVisible(false);
}

/**
 * @brief Sets the technician name in the input field.
 * 
 * @param name The technician's name.
 */
void TechnicianEditPanel::set_name(const QString &name)
{
  m_name_input->setText(name);
}

/**
 * @brief Gets the name from the input field.
 * 
 * @return The technician name.
 */
QString TechnicianEditPanel::name() const
{
  return m_name_input->text();
}

/**
 * @brief Sets the expertise fields as selected in the list.
 * 
 * @param expertises The list of fields to select.
 */
void TechnicianEditPanel::set_expertises(const std::vector<ExpertiseField> &expertises)
{
  for (int i = 0; i < m_expertise_list->count(); ++i) {
    auto *item = m_expertise_list->item(i);
    item->setSelected(false);
    for (const auto &field : expertises) {
      if (item->text() == QString::fromStdString(to_string(field)))
        item->setSelected(true);
    }
  }
}

/**
 * @brief Loads a technician's ID, name, and expertise into the panel.
 * 
 * @param id Technician ID.
 * @param name Technician name.
 * @param expertises List of expertise fields.
 */
void TechnicianEditPanel::load_technician(
    int id, const QString &name, const std::vector<ExpertiseField> &expertises
)
{
  m_technician_id = id;
  set_name(name);
  set_expertises(expertises);
}

/**
 * @brief Returns the selected expertise fields.
 * 
 * @return A vector of selected ExpertiseField enums.
 */
std::vector<ExpertiseField> TechnicianEditPanel::selected_expertises() const
{
  std::vector<ExpertiseField> result;

  for (QListWidgetItem *item : m_expertise_list->selectedItems()) {
    const QString text = item->text();

    if (text == "Electrical")
      result.push_back(ExpertiseField::ELECTRICAL);
    else if (text == "Networking")
      result.push_back(ExpertiseField::NETWORKING);
    else if (text == "HVAC")
      result.push_back(ExpertiseField::HVAC);
    else if (text == "Plumbing")
      result.push_back(ExpertiseField::PLUMBING);
    else if (text == "Security")
      result.push_back(ExpertiseField::SECURITY);
    else if (text == "Software")
      result.push_back(ExpertiseField::SOFTWARE);
    else if (text == "Hardware")
      result.push_back(ExpertiseField::HARDWARE);
    else if (text == "Fire Safety")
      result.push_back(ExpertiseField::FIRE_SAFETY);
    else if (text == "Structural")
      result.push_back(ExpertiseField::STRUCTURAL);
    else if (text == "Generalist")
      result.push_back(ExpertiseField::GENERALIST);
  }

  return result;
}

/**
 * @brief Returns the save button.
 * 
 * @return QPushButton pointer to the "Save Changes" button.
 */
QPushButton *TechnicianEditPanel::save_button() const
{
  return m_save_button;
}