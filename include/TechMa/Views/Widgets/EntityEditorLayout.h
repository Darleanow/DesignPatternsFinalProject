#pragma once

#include <QWidget>

class QLabel;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

class EntityEditorLayout : public QWidget
{
  Q_OBJECT;

public:
  explicit EntityEditorLayout(
      const QString &title, const QString &actionText, QWidget *parent = nullptr
  );

  void         set_left_widget(QWidget *widget);
  void         set_right_widget(QWidget *widget);
  QPushButton *action_button() const;

private:
  void         setup_ui();

  QString      m_title_text;
  QString      m_action_text;

  QLabel      *m_title;
  QPushButton *m_action_button;
  QWidget     *m_left_widget;
  QWidget     *m_right_widget;

  QHBoxLayout *m_topbar_layout;
  QHBoxLayout *m_main_layout;
  QVBoxLayout *m_global_layout;
};
