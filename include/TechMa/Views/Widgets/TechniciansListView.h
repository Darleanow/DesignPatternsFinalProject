#pragma once

#include "TechMa/Observer/ATechnicianObserver.h"

#include <QListView>

class QWidget;
class QStringListModel;

class TechniciansListView : public QListView, public ATechnicianObserver
{
  Q_OBJECT;

public:
  explicit TechniciansListView(QWidget *parent = nullptr);
  ~TechniciansListView();

  void on_repository_updated() override;

private:
  QStringListModel *m_model;

  void              setup_ui();
};
