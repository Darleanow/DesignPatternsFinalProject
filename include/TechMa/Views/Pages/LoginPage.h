#pragma once

#include "TechMa/Authentication/UserAuthentication.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class LoginPage : public QWidget
{
  Q_OBJECT;

public:
  explicit LoginPage(QWidget *parent = nullptr);

signals:
  void login_successful(UserRole role);
  void logout_requested();

private slots:
  void attempt_login();
  void login_as_guest();

private:
  void         setup_ui();
  void         setup_connects();
  void         clear_fields();
  QIcon        tinted_icon(const QString &path, const QColor &color) const;

  QLineEdit   *m_username_input;
  QLineEdit   *m_password_input;
  QPushButton *m_login_button;
  QPushButton *m_guest_button;
  QLabel      *m_status_label;
};