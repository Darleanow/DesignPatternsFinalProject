#pragma once

#include "TechMa/Entities/InterventionData.h"

#include <QDialog>
#include <optional>

class QDateEdit;
class QSpinBox;
class QComboBox;
class QLineEdit;
class QDialogButtonBox;
class TechListController;

class CreateInterventionDialog : public QDialog
{
  Q_OBJECT;

public:
  explicit CreateInterventionDialog(QWidget *parent = nullptr);
  ~CreateInterventionDialog() override;
  std::optional<InterventionData> intervention_data() const;

protected:
  void showEvent(QShowEvent *event) override;

private:
  void              setup_ui();
  void              setup_connects();
  void              clear_fields();
  void              update_ok_state();
  QIcon             tinted_icon(const QString &path, const QColor &color) const;

  QDateEdit        *m_date_input        = nullptr;
  QSpinBox         *m_duration_input    = nullptr;
  QComboBox        *m_expertise_input   = nullptr;
  QComboBox        *m_complexity_input  = nullptr;
  QComboBox        *m_type_input        = nullptr;
  QLineEdit        *m_location_input    = nullptr;
  QLineEdit        *m_notes_input       = nullptr;
  QComboBox        *m_technician_input  = nullptr;
  QDialogButtonBox *m_buttons           = nullptr;
  TechListController *m_tech_controller = nullptr;
};
