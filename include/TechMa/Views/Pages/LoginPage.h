#pragma once

#include "TechMa/Authentication/UserAuthentication.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QShowEvent>
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
  void logout();

private:
  void  setup_ui();
  void  setup_connects();
  void  clear_fields();
  QIcon tinted_icon(const QString &path, const QColor &color) const;
  void  update_ui_for_logged_in_user(std::shared_ptr<User> user);
  void  update_ui_for_logged_out();

protected:
  void showEvent(QShowEvent *event) override;

private:
  QLineEdit   *m_username_input;
  QLineEdit   *m_password_input;
  QPushButton *m_login_button;
  QPushButton *m_guest_button;
  QPushButton *m_logout_button;
  QLabel      *m_status_label;
  QLabel      *m_user_info;
};