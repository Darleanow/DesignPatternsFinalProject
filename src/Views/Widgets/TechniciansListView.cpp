#include "TechMa/Views/Widgets/TechniciansListView.h"
#include "TechMa/Repository/TechnicianRepository.h"

#include <QStringListModel>

TechniciansListView::TechniciansListView(QWidget *parent) : QListView(parent)
{
  setup_ui();
  setup_connects();
}

TechniciansListView::~TechniciansListView()
{
  TechnicianRepository::instance().unsubscribe(this);
}

void TechniciansListView::setup_ui()
{
  m_model = new QStringListModel(this);

  setEditTriggers(QAbstractItemView::NoEditTriggers);

  setModel(m_model);

  TechnicianRepository::instance().subscribe(this);
  on_repository_updated();
}

void TechniciansListView::setup_connects()
{
  connect(this, &QListView::clicked, this, [this](const QModelIndex &index) {
    const int row = index.row();

    auto      all = TechnicianRepository::instance().get_all();
    if(row >= 0 && row < static_cast<int>(all.size())) {
      int  id = static_cast<int>(all.at(row)->get_id());
      emit technician_selected(id);
    }
  });
}

void TechniciansListView::on_repository_updated()
{
  QStringList names;
  for(auto &tech : TechnicianRepository::instance().get_all()) {
    names << QString::fromStdString(tech->get_name());
  }

  m_model->setStringList(names);
}
