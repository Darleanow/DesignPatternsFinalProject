#pragma once

#include "TechMa/Authentication/UserAuthentication.h"
#include "TechMa/Views/Widgets/NavigationBar.h"

#include <QLabel>
#include <QMainWindow>

class QApplication;
class NavigationBar;
class QStackedWidget;
class LoginPage;

class TechMapp : public QMainWindow
{
  Q_OBJECT;

public:
  explicit TechMapp(QApplication &app);

private slots:
  void on_login_successful(UserRole role);
  void on_logout_requested();

private:
  void            load_stylesheet();
  void            setup_font(QApplication &app);
  void            setup_ui();
  void            setup_connects();
  void            update_ui_for_role(UserRole role);

  NavigationBar  *m_navigation_bar;
  QStackedWidget *m_pages;
  LoginPage      *m_login_page;
  QLabel         *m_user_status_label;
  UserRole        m_current_role = UserRole::GUEST;
};