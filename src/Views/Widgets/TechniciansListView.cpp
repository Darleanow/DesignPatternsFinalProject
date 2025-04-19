#include "TechMa/Views/Widgets/TechniciansListView.h"
#include "TechMa/Repository/TechnicianRepository.h"

#include <QStringListModel>

TechniciansListView::TechniciansListView(QWidget *parent) : QListView(parent)
{
  setup_ui();
}

TechniciansListView::~TechniciansListView()
{
  TechnicianRepository::instance().unsubscribe(this);
}

void TechniciansListView::setup_ui()
{
  m_model = new QStringListModel(this);

  setModel(m_model);

  TechnicianRepository::instance().subscribe(this);
  on_repository_updated();
}

void TechniciansListView::on_repository_updated()
{
  qDebug() << "UPDATE";

  QStringList names;
  for(auto &tech : TechnicianRepository::instance().get_all()) {
    names << QString::fromStdString(tech->get_name());
  }

  m_model->setStringList(names);
}
