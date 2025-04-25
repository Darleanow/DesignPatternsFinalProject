/**
 * @file LoginPage.h
 * @brief Declares the LoginPage class, the user interface component for login and authentication.
 */

#pragma once

#include "TechMa/Authentication/UserAuthentication.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QShowEvent>
#include <QWidget>

/**
 * @class LoginPage
 * @brief A QWidget-based login page that handles user authentication and role-based access.
 * 
 * Provides UI controls for logging in, logging out, or entering as a guest.
 * Communicates with the AuthenticationService and emits signals on login state changes.
 */
class LoginPage : public QWidget
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs the login page UI.
   * 
   * @param parent Optional parent widget.
   */
  explicit LoginPage(QWidget *parent = nullptr);

signals:
  /**
   * @brief Emitted when a user has successfully logged in.
   * 
   * @param role The role of the logged-in user.
   */
  void login_successful(UserRole role);

  /**
   * @brief Emitted when the user requests to log out.
   */
  void logout_requested();

private slots:
  /**
   * @brief Attempts to log in with the provided username and password.
   */
  void attempt_login();

  /**
   * @brief Logs in as a guest (no credentials required).
   */
  void login_as_guest();

  /**
   * @brief Logs out the current user.
   */
  void logout();

private:
  /**
   * @brief Initializes and arranges the UI components.
   */
  void setup_ui();

  /**
   * @brief Connects UI elements to their respective slots.
   */
  void setup_connects();

  /**
   * @brief Clears the login input fields.
   */
  void clear_fields();

  /**
   * @brief Applies a tint to an icon loaded from the given path.
   * 
   * @param path File path of the icon.
   * @param color Tint color.
   * @return A tinted QIcon.
   */
  QIcon tinted_icon(const QString &path, const QColor &color) const;

  /**
   * @brief Updates the UI to reflect the state of a logged-in user.
   * 
   * @param user The currently logged-in user.
   */
  void update_ui_for_logged_in_user(std::shared_ptr<User> user);

  /**
   * @brief Resets the UI to the logged-out state.
   */
  void update_ui_for_logged_out();

protected:
  /**
   * @brief Called when the widget is shown, used to reset or update UI state.
   * 
   * @param event The show event.
   */
  void showEvent(QShowEvent *event) override;

private:
  QLineEdit   *m_username_input;   ///< Input field for username.
  QLineEdit   *m_password_input;   ///< Input field for password.
  QPushButton *m_login_button;     ///< Button to attempt login.
  QPushButton *m_guest_button;     ///< Button to login as guest.
  QPushButton *m_logout_button;    ///< Button to log out.
  QLabel      *m_status_label;     ///< Label showing login status messages.
  QLabel      *m_user_info;        ///< Label showing logged-in user info.
};