#pragma once

#include "TechMa/Types/ExpertiseField.h"

#include <QWidget>
#include <vector>

class QLineEdit;
class QListWidget;
class QPushButton;

class TechnicianEditPanel : public QWidget
{
  Q_OBJECT;

public:
  explicit TechnicianEditPanel(QWidget *parent = nullptr);

  void    set_name(const QString &name);
  void    set_expertises(const std::vector<ExpertiseField> &expertises);

  QString name() const;
  std::vector<ExpertiseField> selected_expertises() const;

  QPushButton                *save_button() const;

  void                        load_technician(
                             int id, const QString &name, const std::vector<ExpertiseField> &expertises
                         );

private:
  void         setup_ui();

  int          m_technician_id;
  QLineEdit   *m_name_input;
  QListWidget *m_expertise_list;
  QPushButton *m_save_button;
};
