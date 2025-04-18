#pragma once

#include <QWidget>

class QPushButton;
class CreateTechnicianDialog;

class TechniciansPage : public QWidget
{
  Q_OBJECT;

public:
  explicit TechniciansPage(QWidget *parent);

private:
  void                    setup_ui();
  void                    setup_connects();

  QPushButton            *m_create_button;
  CreateTechnicianDialog *m_create_dialog;
};
