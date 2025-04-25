/**
 * @file TechniciansListView.cpp
 * @brief Implements the TechniciansListView class, which displays a list of technicians and handles selection events.
 */

#include "TechMa/Views/Widgets/TechniciansListView.h"
#include "TechMa/Repository/TechnicianRepository.h"

#include <QStringListModel>

/**
 * @brief Constructs the list view, sets up UI components, and connects signals.
 * 
 * @param parent Optional parent QWidget.
 */
TechniciansListView::TechniciansListView(QWidget *parent) : QListView(parent)
{
  setup_ui();
  setup_connects();
}

/**
 * @brief Destructor. Unsubscribes from the technician repository to stop receiving updates.
 */
TechniciansListView::~TechniciansListView()
{
  TechnicianRepository::instance().unsubscribe(this);
}

/**
 * @brief Initializes the internal model and subscribes to repository updates.
 */
void TechniciansListView::setup_ui()
{
  m_model = new QStringListModel(this);

  setEditTriggers(QAbstractItemView::NoEditTriggers);
  setModel(m_model);

  TechnicianRepository::instance().subscribe(this);
  on_repository_updated();
}

/**
 * @brief Connects click events to the signal emitting the selected technician ID.
 */
void TechniciansListView::setup_connects()
{
  connect(this, &QListView::clicked, this, [this](const QModelIndex &index) {
    const int row = index.row();

    auto all = TechnicianRepository::instance().get_all();
    if (row >= 0 && row < static_cast<int>(all.size())) {
      int id = static_cast<int>(all.at(row)->get_id());
      emit technician_selected(id);
    }
  });
}

/**
 * @brief Updates the displayed list of technicians based on the current repository data.
 */
void TechniciansListView::on_repository_updated()
{
  QStringList names;
  for (auto &tech : TechnicianRepository::instance().get_all()) {
    names << QString::fromStdString(tech->get_name());
  }

  m_model->setStringList(names);
}