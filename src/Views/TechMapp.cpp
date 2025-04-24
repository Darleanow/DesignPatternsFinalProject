/**
 * @file TechMapp.cpp
 * @brief Implements the TechMapp class, the main application window for TechMa.
 */

#include "TechMa/Views/TechMapp.h"
#include "TechMa/Authentication/UserAuthentication.h"
#include "TechMa/Views/Pages/InterventionPage.h"
#include "TechMa/Views/Pages/LoginPage.h"
#include "TechMa/Views/Pages/ParametersPage.h"
#include "TechMa/Views/Pages/TechniciansPage.h"

#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QStatusBar>
#include <QVBoxLayout>

/**
 * @brief Constructor for the main application window.
 * 
 * Initializes fonts, styles, UI layout, and connects signals.
 * 
 * @param app The QApplication instance.
 */
TechMapp::TechMapp(QApplication &app)
{
  load_stylesheet();
  setup_font(app);
  setup_ui();
  setup_connects();

  m_pages->setCurrentIndex(3);  // Show login page by default
  update_ui_for_role(UserRole::GUEST);

  show();
}

/**
 * @brief Loads and applies the Qt stylesheet to the application.
 */
void TechMapp::load_stylesheet()
{
  QFile file(":/styles/style.qss");

  if (file.open(QFile::ReadOnly | QFile::Text)) {
    QString style = file.readAll();
    qApp->setStyleSheet(style);
  }
}

/**
 * @brief Loads the RobotoMono font and applies it to the application.
 * 
 * @param app Reference to the QApplication instance.
 */
void TechMapp::setup_font(QApplication &app)
{
  int id = QFontDatabase::addApplicationFont(":/styles/fonts/RobotoMono.ttf");

  if (id == -1) {
    qWarning("Failed to load RobotoMono font.");
    return;
  }

  QStringList families = QFontDatabase::applicationFontFamilies(id);
  if (families.isEmpty()) {
    qWarning("Font loaded, but no families found.");
    return;
  }

  QFont font(families.at(0));
  font.setPointSize(12);
  font.setHintingPreference(QFont::PreferFullHinting);
  font.setStyleStrategy(QFont::PreferAntialias);
  app.setFont(font);
}

/**
 * @brief Creates and arranges the UI layout for the application.
 */
void TechMapp::setup_ui()
{
  auto *central = new QWidget(this);
  auto *vlayout = new QVBoxLayout(central);
  vlayout->setContentsMargins(0, 0, 0, 0);
  vlayout->setSpacing(0);

  auto *top_bar = new QWidget(this);
  auto *top_layout = new QHBoxLayout(top_bar);

  m_navigation_bar = new NavigationBar(this);
  top_layout->addWidget(m_navigation_bar);

  m_user_status_label = new QLabel("Guest", this);
  m_user_status_label->setStyleSheet("color: #6B6BFF; font-weight: bold; padding-right: 10px;");
  top_layout->addWidget(m_user_status_label, 0, Qt::AlignRight);

  top_bar->setLayout(top_layout);
  vlayout->addWidget(top_bar);

  m_pages = new QStackedWidget(this);
  vlayout->addWidget(m_pages);

  m_pages->addWidget(new InterventionPage(this));
  m_pages->addWidget(new TechniciansPage(this));
  m_pages->addWidget(new ParametersPage(this));
  m_login_page = new LoginPage(this);
  m_pages->addWidget(m_login_page);

  setCentralWidget(central);
  setStatusBar(new QStatusBar(this));
}

/**
 * @brief Connects internal components and UI signals to relevant handlers.
 */
void TechMapp::setup_connects()
{
  connect(m_navigation_bar, &NavigationBar::tabChanged, this, [this](int index) {
    m_pages->setCurrentIndex(index);
  });

  connect(m_login_page, &LoginPage::login_successful, this, &TechMapp::on_login_successful);
  connect(m_login_page, &LoginPage::logout_requested, this, &TechMapp::on_logout_requested);
}

/**
 * @brief Slot called when login is successful.
 * 
 * @param role Role of the logged-in user.
 */
void TechMapp::on_login_successful(UserRole role)
{
  m_current_role = role;
  update_ui_for_role(role);

  m_pages->setCurrentIndex(0);
  m_navigation_bar->setCurrentIndex(0);
}

/**
 * @brief Slot called when logout is triggered.
 */
void TechMapp::on_logout_requested()
{
  update_ui_for_role(UserRole::GUEST);
}

/**
 * @brief Updates the UI elements and role label depending on the user role.
 * 
 * @param role The current authenticated user role.
 */
void TechMapp::update_ui_for_role(UserRole role)
{
  QString role_name;
  switch (role) {
  case UserRole::ADMIN:
    role_name = "Admin";
    break;
  case UserRole::TECHNICIAN:
    role_name = "Technician";
    break;
  case UserRole::GUEST:
  default:
    role_name = "Guest";
    break;
  }

  auto user = AuthenticationService::instance().current_user();
  QString username = user ? QString::fromStdString(user->username()) : "";

  if (!username.isEmpty()) {
    m_user_status_label->setText(QString("%1 (%2)").arg(username).arg(role_name));
  } else {
    m_user_status_label->setText(role_name);
  }
}