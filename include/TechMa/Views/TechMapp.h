/**
 * @file TechMapp.h
 * @brief Declares the TechMapp class, the main application window for the TechMa system.
 */

#pragma once

#include "TechMa/Authentication/UserAuthentication.h"
#include "TechMa/Views/Widgets/NavigationBar.h"

#include <QLabel>
#include <QMainWindow>

class QApplication;
class NavigationBar;
class QStackedWidget;
class LoginPage;

/**
 * @class TechMapp
 * @brief Main window controller for the TechMa application.
 * 
 * Handles authentication state, UI navigation, and layout setup. Reacts to login/logout events
 * and adapts the UI according to the user role.
 */
class TechMapp : public QMainWindow
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs the main application window.
   * 
   * @param app Reference to the running QApplication, used to apply fonts and styles.
   */
  explicit TechMapp(QApplication &app);

private slots:
  /**
   * @brief Called when a login is successful.
   * 
   * @param role The role of the authenticated user.
   */
  void on_login_successful(UserRole role);

  /**
   * @brief Called when a logout is requested by the user.
   */
  void on_logout_requested();

private:
  /**
   * @brief Loads and applies the global stylesheet to the application.
   */
  void load_stylesheet();

  /**
   * @brief Configures and applies the application font.
   * 
   * @param app Reference to the application instance.
   */
  void setup_font(QApplication &app);

  /**
   * @brief Sets up the main UI layout and widgets.
   */
  void setup_ui();

  /**
   * @brief Connects internal signals and slots for UI and authentication handling.
   */
  void setup_connects();

  /**
   * @brief Updates the UI components based on the user's role.
   * 
   * @param role The current user role.
   */
  void update_ui_for_role(UserRole role);

  NavigationBar  *m_navigation_bar;      ///< Navigation bar for tab-based page switching.
  QStackedWidget *m_pages;               ///< Container for all main pages of the application.
  LoginPage      *m_login_page;          ///< Login page widget.
  QLabel         *m_user_status_label;   ///< Displays current user info/status.
  UserRole        m_current_role = UserRole::GUEST; ///< Currently logged-in user's role.
};