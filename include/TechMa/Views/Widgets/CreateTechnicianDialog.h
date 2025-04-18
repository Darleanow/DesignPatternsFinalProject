#pragma once

#include "TechMa/Types/ExpertiseField.h"

#include <QDialog>

class QWidget;
class QDialogButtonBox;
class QListWidget;

class CreateTechnicianDialog : public QDialog
{
  Q_OBJECT;

public:
  explicit CreateTechnicianDialog(QWidget *parent = nullptr);

  std::vector<ExpertiseField> selected_expertise() const;

private:
  QDialogButtonBox *m_buttons;
  QListWidget      *m_expertise_list;

  void              setup_ui();
  void              setup_connects();
};
