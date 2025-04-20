#pragma once

#include "TechMa/Types/ExpertiseField.h"

#include <QDialog>

class QWidget;
class QDialogButtonBox;
class QListWidget;
class QLineEdit;

class CreateTechnicianDialog : public QDialog
{
  Q_OBJECT;

public:
  explicit CreateTechnicianDialog(QWidget *parent = nullptr);

  std::vector<ExpertiseField> selected_expertises() const;

  QString                     full_name() const;

private:
  QDialogButtonBox *m_buttons;
  QListWidget      *m_expertise_list;
  QLineEdit        *m_name_line_edit;

  void              setup_ui();
  void              setup_connects();
};
