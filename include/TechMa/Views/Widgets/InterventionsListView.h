#pragma once

#include <QListView>

class QStringListModel;

class InterventionsListView : public QListView
{
  Q_OBJECT;

public:
  explicit InterventionsListView(QWidget *parent = nullptr);
  ~InterventionsListView() override;

signals:
  void intervention_selected(int id);

public slots:
  void on_repository_updated();

private:
  void              setup_ui();
  void              setup_connects();

  QStringListModel *m_model = nullptr;
};
