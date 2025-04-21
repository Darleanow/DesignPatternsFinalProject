#pragma once

#include "TechMa/Observer/ATechnicianObserver.h"

#include <QObject>

class QComboBox;

class TechListController : public QObject, public ATechnicianObserver
{
  Q_OBJECT;

public:
  TechListController(
      QComboBox *expertise_input, QComboBox *complexity_input,
      QComboBox *technician_input, QObject *parent = nullptr
  );
  ~TechListController() override;

  void update_technicians();

protected:
  void on_repository_updated() override;

private:
  QComboBox *m_expertise_input;
  QComboBox *m_complexity_input;
  QComboBox *m_technician_input;

  void       setup_connections();
  void       rebuild_list();
};
