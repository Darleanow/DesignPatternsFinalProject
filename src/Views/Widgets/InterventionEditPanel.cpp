/**
 * @file InterventionEditPanel.cpp
 * @brief Implements the InterventionEditPanel class, a QWidget for editing intervention data.
 */

#include "TechMa/Views/Widgets/InterventionEditPanel.h"
#include "TechMa/Types/ExpertiseField.h"
#include "TechMa/Types/InterventionComplexity.h"
#include "TechMa/Types/InterventionStatus.h"
#include "TechMa/Types/InterventionType.h"
#include "TechMa/Views/Controllers/TechListController.h"

#include <QAbstractItemView>
#include <QComboBox>
#include <QDateEdit>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

/**
 * @brief Constructor. Initializes UI and controller.
 * 
 * @param parent Optional parent QWidget.
 */
InterventionEditPanel::InterventionEditPanel(QWidget *parent) : QWidget(parent)
{
  setup_ui();
  setup_connects();
  m_tech_controller = new TechListController(
      m_expertise_input, m_complexity_input, m_technician_input, this
  );
  setVisible(false);
}

/**
 * @brief Destructor.
 */
InterventionEditPanel::~InterventionEditPanel() {}

/**
 * @brief Builds and lays out the form inputs for editing interventions.
 */
void InterventionEditPanel::setup_ui()
{
  auto *layout = new QFormLayout(this);

  m_date_input = new QDateEdit(QDate::currentDate(), this);
  m_date_input->setCalendarPopup(true);
  layout->addRow("Date", m_date_input);

  m_duration_input = new QSpinBox(this);
  m_duration_input->setRange(1, 24);
  m_duration_input->setSuffix(" h");
  layout->addRow("Duration", m_duration_input);

  m_expertise_input = new QComboBox(this);
  for (auto e : {
         ExpertiseField::ELECTRICAL, ExpertiseField::NETWORKING,
         ExpertiseField::HVAC, ExpertiseField::PLUMBING, ExpertiseField::SECURITY,
         ExpertiseField::SOFTWARE, ExpertiseField::HARDWARE,
         ExpertiseField::FIRE_SAFETY, ExpertiseField::STRUCTURAL,
         ExpertiseField::GENERALIST }) {
    m_expertise_input->addItem(QString::fromStdString(to_string(e)), static_cast<int>(e));
  }
  layout->addRow("Expertise", m_expertise_input);

  m_complexity_input = new QComboBox(this);
  m_complexity_input->addItems({"Easy", "Medium", "Hard", "Expert"});
  layout->addRow("Complexity", m_complexity_input);

  m_type_input = new QComboBox(this);
  for (auto t : {
         InterventionType::MAINTENANCE, InterventionType::EMERGENCY,
         InterventionType::INSTALLATION, InterventionType::INSPECTION,
         InterventionType::DIAGNOSTIC, InterventionType::UPGRADE }) {
    m_type_input->addItem(QString::fromStdString(to_string(t)), static_cast<int>(t));
  }
  layout->addRow("Type", m_type_input);

  m_status_input = new QComboBox(this);
  for (auto s : {
         InterventionStatus::PENDING, InterventionStatus::IN_PROGRESS,
         InterventionStatus::COMPLETED, InterventionStatus::CANCELLED,
         InterventionStatus::ON_HOLD, InterventionStatus::RESCHEDULED }) {
    m_status_input->addItem(QString::fromStdString(to_string(s)), static_cast<int>(s));
  }
  layout->addRow("Status", m_status_input);

  m_location_input = new QLineEdit(this);
  layout->addRow("Location", m_location_input);

  m_notes_input = new QLineEdit(this);
  layout->addRow("Notes", m_notes_input);

  m_technician_input = new QComboBox(this);
  layout->addRow("Technician", m_technician_input);

  m_save_button = new QPushButton("Save Changes", this);
  layout->addRow("", m_save_button);

  layout->setVerticalSpacing(12);
  layout->setContentsMargins(8, 8, 8, 8);
}

/**
 * @brief Sets up signal/slot connections for combo behavior.
 */
void InterventionEditPanel::setup_connects()
{
  auto setup_combo = [this](QComboBox *combo) {
    combo->setEditable(false);
    connect(
        combo, QOverload<int>::of(&QComboBox::activated), combo,
        [combo](int) {
          combo->hidePopup();
          if (auto *v = combo->view())
            v->window()->close();
        }
    );
  };

  setup_combo(m_expertise_input);
  setup_combo(m_complexity_input);
  setup_combo(m_type_input);
  setup_combo(m_status_input);
  setup_combo(m_technician_input);
}

/**
 * @brief Loads existing data into the form for editing.
 * 
 * @param d The intervention data to populate the form with.
 */
void InterventionEditPanel::load(const InterventionData &d)
{
  m_id = d.id;
  QDate qd(
      int(d.date.year()), int(static_cast<unsigned>(d.date.month())),
      int(static_cast<unsigned>(d.date.day()))
  );
  m_date_input->setDate(qd);
  m_duration_input->setValue(int(d.anticipated_duration.count()));
  m_expertise_input->setCurrentIndex(int(d.expertise_required));
  m_complexity_input->setCurrentIndex(int(d.complexity));
  m_type_input->setCurrentIndex(int(d.type));
  m_status_input->setCurrentIndex(int(d.status));
  m_location_input->setText(QString::fromStdString(d.location.address));
  m_notes_input->setText(QString::fromStdString(d.notes));

  m_tech_controller->update_technicians();
  int idx = 0;
  if (d.technician_id) {
    for (int i = 1; i < m_technician_input->count(); ++i) {
      if (m_technician_input->itemData(i).toInt() == *d.technician_id) {
        idx = i;
        break;
      }
    }
  }
  m_technician_input->setCurrentIndex(idx);
  setVisible(true);
}

/**
 * @brief Reimplemented to handle widget visibility updates.
 * 
 * @param ev Qt show event.
 */
void InterventionEditPanel::showEvent(QShowEvent *ev)
{
  QWidget::showEvent(ev);
}

/**
 * @brief Collects and returns the current form data as a new InterventionData structure.
 * 
 * @return The updated InterventionData.
 */
InterventionData InterventionEditPanel::to_data() const
{
  InterventionData data;
  data.id = m_id;
  auto date = m_date_input->date();
  data.date = std::chrono::year{date.year()} / unsigned(date.month()) / unsigned(date.day());
  data.anticipated_duration = std::chrono::hours{m_duration_input->value()};
  data.expertise_required = static_cast<ExpertiseField>(m_expertise_input->currentIndex());
  data.complexity = static_cast<InterventionComplexity>(m_complexity_input->currentIndex());
  data.type = static_cast<InterventionType>(m_type_input->currentIndex());
  data.status = static_cast<InterventionStatus>(m_status_input->currentIndex());
  data.location = Location{
      m_location_input->text().toStdString(),
      {0, 0}
  };
  data.notes = m_notes_input->text().toStdString();
  QVariant v = m_technician_input->currentData();
  data.technician_id = v.isValid() ? std::optional{v.toInt()} : std::nullopt;
  data.completed = false;
  return data;
}

/**
 * @brief Accessor for the "Save Changes" button.
 * 
 * @return QPushButton* Pointer to the save button.
 */
QPushButton *InterventionEditPanel::save_button() const
{
  return m_save_button;
}