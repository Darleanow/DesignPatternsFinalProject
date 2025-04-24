/**
 * @file CreateInterventionDialog.cpp
 * @brief Implements the CreateInterventionDialog class for creating new interventions through a Qt dialog UI.
 */

#include "TechMa/Views/Widgets/CreateInterventionDialog.h"
#include "TechMa/Types/ExpertiseField.h"
#include "TechMa/Types/InterventionComplexity.h"
#include "TechMa/Types/InterventionStatus.h"
#include "TechMa/Types/InterventionType.h"
#include "TechMa/Views/Controllers/TechListController.h"

#include <QAbstractItemView>
#include <QColor>
#include <QComboBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QShowEvent>
#include <QSpinBox>
#include <QTimer>
#include <QVariant>

/**
 * @brief Constructs the dialog and initializes UI and connections.
 * 
 * @param parent Optional parent widget.
 */
CreateInterventionDialog::CreateInterventionDialog(QWidget *parent)
    : QDialog(parent)
{
  setup_ui();
  setup_connects();
  m_tech_controller = new TechListController(
      m_expertise_input, m_complexity_input, m_technician_input, this
  );
  clear_fields();
  update_ok_state();
}

/**
 * @brief Destructor.
 */
CreateInterventionDialog::~CreateInterventionDialog() {}

/**
 * @brief Initializes the UI components and layout of the dialog.
 */
void CreateInterventionDialog::setup_ui()
{
  setWindowTitle("New Intervention");
  auto *form = new QFormLayout(this);

  m_date_input = new QDateEdit(QDate::currentDate(), this);
  m_date_input->setCalendarPopup(true);
  form->addRow("Date *", m_date_input);

  m_duration_input = new QSpinBox(this);
  m_duration_input->setRange(1, 24);
  m_duration_input->setSuffix(" h");
  form->addRow("Duration *", m_duration_input);

  m_expertise_input = new QComboBox(this);
  m_expertise_input->addItem("Select Expertise", QVariant());
  for (auto e : {
         ExpertiseField::ELECTRICAL, ExpertiseField::NETWORKING,
         ExpertiseField::HVAC, ExpertiseField::PLUMBING, ExpertiseField::SECURITY,
         ExpertiseField::SOFTWARE, ExpertiseField::HARDWARE,
         ExpertiseField::FIRE_SAFETY, ExpertiseField::STRUCTURAL,
         ExpertiseField::GENERALIST }) {
    m_expertise_input->addItem(QString::fromStdString(to_string(e)), static_cast<int>(e));
  }
  form->addRow("Expertise *", m_expertise_input);

  m_complexity_input = new QComboBox(this);
  m_complexity_input->addItem("Select Complexity", QVariant());
  m_complexity_input->addItems({"Easy", "Medium", "Hard", "Expert"});
  form->addRow("Complexity *", m_complexity_input);

  m_type_input = new QComboBox(this);
  m_type_input->addItem("Select Type", QVariant());
  for (auto t : {
         InterventionType::MAINTENANCE, InterventionType::EMERGENCY,
         InterventionType::INSTALLATION, InterventionType::INSPECTION,
         InterventionType::DIAGNOSTIC, InterventionType::UPGRADE }) {
    m_type_input->addItem(QString::fromStdString(to_string(t)), static_cast<int>(t));
  }
  form->addRow("Type *", m_type_input);

  m_location_input = new QLineEdit(this);
  form->addRow("Location *", m_location_input);

  m_notes_input = new QLineEdit(this);
  form->addRow("Notes", m_notes_input);

  m_technician_input = new QComboBox(this);
  form->addRow("Technician", m_technician_input);

  m_buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
  form->addRow(m_buttons);
  m_buttons->button(QDialogButtonBox::Ok)->setIcon(tinted_icon(":/styles/icons/validate.svg", QColor("#6BFF6B")));
  m_buttons->button(QDialogButtonBox::Cancel)->setIcon(tinted_icon(":/styles/icons/close.svg", QColor("#FF6B6B")));

  resize(600, 400);
}

/**
 * @brief Connects signals and slots for UI interactivity and validation.
 */
void CreateInterventionDialog::setup_connects()
{
  connect(m_buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(m_buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

  auto setup_combo = [this](QComboBox *combo, auto handler) {
    combo->setEditable(false);
    connect(
        combo, QOverload<int>::of(&QComboBox::activated), this,
        [combo, handler](int) {
          combo->hidePopup();
          if (auto *view = combo->view())
            view->window()->close();
          QTimer::singleShot(0, handler);
        }
    );
  };

  setup_combo(m_expertise_input, [this] { update_ok_state(); });
  setup_combo(m_complexity_input, [this] { update_ok_state(); });
  setup_combo(m_type_input, [this] { update_ok_state(); });
  setup_combo(m_technician_input, [this] { update_ok_state(); });

  connect(m_date_input, &QDateEdit::dateChanged, this, &CreateInterventionDialog::update_ok_state);
  connect(m_duration_input, &QSpinBox::valueChanged, this, &CreateInterventionDialog::update_ok_state);
  connect(m_location_input, &QLineEdit::textChanged, this, &CreateInterventionDialog::update_ok_state);
}

/**
 * @brief Clears all fields in the form and resets the technician list.
 */
void CreateInterventionDialog::clear_fields()
{
  m_date_input->setDate(QDate::currentDate());
  m_duration_input->setValue(1);
  m_expertise_input->setCurrentIndex(0);
  m_complexity_input->setCurrentIndex(0);
  m_type_input->setCurrentIndex(0);
  m_location_input->clear();
  m_notes_input->clear();
  m_technician_input->clear();
  m_technician_input->addItem("— None Selected —", QVariant());
  m_tech_controller->update_technicians();
}

/**
 * @brief Enables or disables the OK button depending on form completeness.
 */
void CreateInterventionDialog::update_ok_state()
{
  bool ok = m_date_input->date().isValid() &&
            m_duration_input->value() > 0 &&
            m_expertise_input->currentIndex() > 0 &&
            m_complexity_input->currentIndex() > 0 &&
            m_type_input->currentIndex() > 0 &&
            !m_location_input->text().isEmpty();

  m_buttons->button(QDialogButtonBox::Ok)->setEnabled(ok);
}

/**
 * @brief Called when the dialog is shown; clears fields and resets UI.
 * 
 * @param event The Qt show event.
 */
void CreateInterventionDialog::showEvent(QShowEvent *event)
{
  clear_fields();
  QDialog::showEvent(event);
}

/**
 * @brief Collects all data from the form into an InterventionData structure.
 * 
 * @return A filled InterventionData instance if the form is valid, otherwise std::nullopt.
 */
std::optional<InterventionData> CreateInterventionDialog::intervention_data() const
{
  if (!m_buttons->button(QDialogButtonBox::Ok)->isEnabled())
    return std::nullopt;

  InterventionData data;
  auto d = m_date_input->date();
  data.date = std::chrono::year{d.year()} / unsigned(d.month()) / unsigned(d.day());
  data.anticipated_duration = std::chrono::hours{m_duration_input->value()};
  data.expertise_required = static_cast<ExpertiseField>(m_expertise_input->currentData().toInt());
  data.complexity = static_cast<InterventionComplexity>(m_complexity_input->currentIndex() - 1);
  data.type = static_cast<InterventionType>(m_type_input->currentData().toInt());
  data.status = InterventionStatus::PENDING;
  data.location = Location{
    m_location_input->text().toStdString(),
    {0, 0} // Default GPS coords
  };
  data.notes = m_notes_input->text().toStdString();
  QVariant v = m_technician_input->currentData();
  data.technician_id = v.isValid() ? std::optional{v.toInt()} : std::nullopt;

  return data;
}

/**
 * @brief Tints an icon with a given color.
 * 
 * @param path File path to the icon.
 * @param color The tint color to apply.
 * @return A QIcon with the specified tint.
 */
QIcon CreateInterventionDialog::tinted_icon(const QString &path, const QColor &color) const
{
  QPixmap src(path);
  QPixmap dst(src.size());
  dst.fill(Qt::transparent);
  QPainter p(&dst);
  p.setCompositionMode(QPainter::CompositionMode_Source);
  p.drawPixmap(0, 0, src);
  p.setCompositionMode(QPainter::CompositionMode_SourceIn);
  p.fillRect(dst.rect(), color);
  p.end();
  return QIcon(dst);
}