#pragma once

#include "TechMa/Entities/InterventionData.h"
#include <QWidget>

class QDateEdit;
class QSpinBox;
class QComboBox;
class QLineEdit;
class QPushButton;
class TechListController;

class InterventionEditPanel : public QWidget {
  Q_OBJECT

public:
  explicit InterventionEditPanel(QWidget* parent = nullptr);
  ~InterventionEditPanel() override;
  void load(const InterventionData& data);
  InterventionData to_data() const;
  QPushButton* save_button() const;

protected:
  void showEvent(QShowEvent* event) override;

private:
  void setup_ui();
  void setup_connects();

  int m_id;
  QDateEdit* m_date_input       = nullptr;
  QSpinBox*  m_duration_input   = nullptr;
  QComboBox* m_expertise_input  = nullptr;
  QComboBox* m_complexity_input = nullptr;
  QLineEdit* m_location_input   = nullptr;
  QLineEdit* m_notes_input      = nullptr;
  QComboBox* m_technician_input = nullptr;
  QPushButton* m_save_button    = nullptr;
  TechListController* m_tech_controller = nullptr;
};
