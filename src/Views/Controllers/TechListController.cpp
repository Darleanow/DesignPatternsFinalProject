/**
 * @file TechListController.cpp
 * @brief Implements the TechListController class, which manages technician-related combo boxes and observes repository updates.
 */

#include "TechMa/Views/Controllers/TechListController.h"
#include "TechMa/Repository/TechnicianRepository.h"
#include "TechMa/Types/InterventionComplexity.h"

#include <QComboBox>
#include <QVariant>

/**
 * @brief Constructs the controller and sets up connections between UI and logic.
 * 
 * Also subscribes the controller to the TechnicianRepository to listen for updates.
 * 
 * @param expertise_input Pointer to the expertise QComboBox.
 * @param complexity_input Pointer to the complexity QComboBox.
 * @param technician_input Pointer to the technician selection QComboBox.
 * @param parent Optional Qt parent.
 */
TechListController::TechListController(
    QComboBox *expertise_input, QComboBox *complexity_input,
    QComboBox *technician_input, QObject *parent
)
    : QObject(parent),
      m_expertise_input(expertise_input),
      m_complexity_input(complexity_input),
      m_technician_input(technician_input)
{
  setup_connections();
  TechnicianRepository::instance().subscribe(this);
  update_technicians();
}

/**
 * @brief Destructor that unsubscribes from the TechnicianRepository.
 */
TechListController::~TechListController()
{
  TechnicianRepository::instance().unsubscribe(this);
}

/**
 * @brief Connects UI combo boxes to the update logic.
 * 
 * When a user changes the selected expertise or complexity, the technician list is rebuilt.
 */
void TechListController::setup_connections()
{
  connect(
      m_expertise_input, QOverload<int>::of(&QComboBox::activated), this,
      [this](int) { update_technicians(); }
  );
  connect(
      m_complexity_input, QOverload<int>::of(&QComboBox::activated), this,
      [this](int) { update_technicians(); }
  );
}

/**
 * @brief Triggers a rebuild of the technician list based on current selections.
 */
void TechListController::update_technicians()
{
  rebuild_list();
}

/**
 * @brief Reacts to updates in the technician repository by refreshing the list.
 */
void TechListController::on_repository_updated()
{
  update_technicians();
}

/**
 * @brief Rebuilds the technician combo box list based on selected filters.
 * 
 * Filters technicians by selected expertise and complexity.
 * Includes generalists for tasks of medium complexity or below.
 */
void TechListController::rebuild_list()
{
  QVariant prev    = m_technician_input->currentData();
  int      prev_id = prev.isValid() ? prev.toInt() : -1;

  m_technician_input->clear();
  m_technician_input->addItem("— Aucun —", QVariant());

  bool    has_expertise = m_expertise_input->currentData().isValid();
  QString first_txt     = m_complexity_input->itemText(0);
  bool    placeholder   = first_txt.contains("Select", Qt::CaseInsensitive);
  bool    has_complexity =
      placeholder ? m_complexity_input->currentIndex() > 0 : true;
  if (!has_expertise || !has_complexity) {
    m_technician_input->setEnabled(false);
    return;
  }

  auto required =
      static_cast<ExpertiseField>(m_expertise_input->currentData().toInt());
  int  cidx      = placeholder ? m_complexity_input->currentIndex() - 1
                               : m_complexity_input->currentIndex();
  auto comp      = static_cast<InterventionComplexity>(cidx);
  bool allow_gen = comp <= InterventionComplexity::MEDIUM;

  for (auto tech : TechnicianRepository::instance().get_all()) {
    if (tech->has_expertise(required) ||
        (allow_gen && tech->has_expertise(ExpertiseField::GENERALIST))) {
      m_technician_input->addItem(
          QString::fromStdString(tech->get_name()), tech->get_id()
      );
    }
  }

  int to_select = 0;
  if (prev_id >= 0) {
    for (int i = 1; i < m_technician_input->count(); ++i) {
      if (m_technician_input->itemData(i).toInt() == prev_id) {
        to_select = i;
        break;
      }
    }
  }
  m_technician_input->setCurrentIndex(to_select);
  m_technician_input->setEnabled(true);
}