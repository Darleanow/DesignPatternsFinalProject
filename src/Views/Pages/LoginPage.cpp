#include "TechMa/Views/Pages/LoginPage.h"
#include "TechMa/Authentication/UserAuthentication.h"

#include <QColor>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

LoginPage::LoginPage(QWidget *parent) : QWidget(parent)
{
  setup_ui();
  setup_connects();
}

void LoginPage::setup_ui()
{
  auto *main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignCenter);

  auto *title_label = new QLabel("TechMa Account", this);
  title_label->setObjectName("Title");
  title_label->setAlignment(Qt::AlignCenter);

  auto *form_layout = new QFormLayout();

  m_username_input = new QLineEdit(this);
  m_username_input->setPlaceholderText("Username");
  form_layout->addRow("Username:", m_username_input);

  m_password_input = new QLineEdit(this);
  m_password_input->setPlaceholderText("Password");
  m_password_input->setEchoMode(QLineEdit::Password);
  form_layout->addRow("Password:", m_password_input);

  auto *btn_layout = new QHBoxLayout();

  m_login_button = new QPushButton("Login", this);
  m_login_button->setIcon(
      tinted_icon(":/styles/icons/log-in.svg", QColor("#6B6BFF"))
  );

  m_guest_button = new QPushButton("Continue as Guest", this);

  m_logout_button = new QPushButton("Logout", this);
  m_logout_button->setIcon(
      tinted_icon(":/styles/icons/log-out.svg", QColor("#FF6B6B"))
  );
  m_logout_button->setVisible(false);

  btn_layout->addWidget(m_login_button);
  btn_layout->addWidget(m_guest_button);
  btn_layout->addWidget(m_logout_button);

  m_status_label = new QLabel(this);
  m_status_label->setStyleSheet("color: red;");
  m_status_label->setAlignment(Qt::AlignCenter);

  auto *hints_label = new QLabel(this);
  hints_label->setText("Available accounts for demo:\n"
                       "- Username: admin, Password: admin123 (Admin)\n"
                       "- Username: tech, Password: tech123 (Technician)\n"
                       "- Username: guest, Password: guest123 (Guest)");
  hints_label->setStyleSheet("color: #666; font-size: 10pt;");
  hints_label->setAlignment(Qt::AlignCenter);

  m_user_info = new QLabel(this);
  m_user_info->setStyleSheet("color: #6B6BFF; font-weight: bold;");
  m_user_info->setAlignment(Qt::AlignCenter);
  m_user_info->setVisible(false);

  main_layout->addWidget(title_label);
  main_layout->addSpacing(20);
  main_layout->addLayout(form_layout);
  main_layout->addSpacing(10);
  main_layout->addLayout(btn_layout);
  main_layout->addWidget(m_status_label);
  main_layout->addWidget(m_user_info);
  main_layout->addSpacing(30);
  main_layout->addWidget(hints_label);

  setLayout(main_layout);
}

void LoginPage::setup_connects()
{
  connect(
      m_login_button, &QPushButton::clicked, this, &LoginPage::attempt_login
  );
  connect(
      m_guest_button, &QPushButton::clicked, this, &LoginPage::login_as_guest
  );
  connect(m_logout_button, &QPushButton::clicked, this, &LoginPage::logout);

  connect(
      m_username_input, &QLineEdit::returnPressed, this,
      &LoginPage::attempt_login
  );
  connect(
      m_password_input, &QLineEdit::returnPressed, this,
      &LoginPage::attempt_login
  );

  auto update_login_button = [this]() {
    m_login_button->setEnabled(
        !m_username_input->text().isEmpty() &&
        !m_password_input->text().isEmpty()
    );
  };

  connect(m_username_input, &QLineEdit::textChanged, this, update_login_button);
  connect(m_password_input, &QLineEdit::textChanged, this, update_login_button);

  update_login_button();
}

void LoginPage::attempt_login()
{
  QString username = m_username_input->text();
  QString password = m_password_input->text();

  if(AuthenticationService::instance().login(
         username.toStdString(), hash_password(password.toStdString())
     )) {
    auto current_user = AuthenticationService::instance().current_user();
    update_ui_for_logged_in_user(current_user);
    emit login_successful(current_user->role());
    clear_fields();
  } else {
    m_status_label->setText("Invalid username or password");
    QTimer::singleShot(3000, m_status_label, &QLabel::clear);
  }
}

void LoginPage::login_as_guest()
{
  AuthenticationService::instance().logout();
  emit login_successful(UserRole::GUEST);
  clear_fields();
}

void LoginPage::logout()
{
  AuthenticationService::instance().logout();
  update_ui_for_logged_out();
  emit logout_requested();
}

void LoginPage::update_ui_for_logged_in_user(std::shared_ptr<User> user)
{
  if(!user)
    return;

  m_username_input->setVisible(false);
  m_password_input->setVisible(false);
  m_login_button->setVisible(false);
  m_guest_button->setVisible(false);

  QString role_name;
  switch(user->role()) {
  case UserRole::ADMIN:
    role_name = "Admin";
    break;
  case UserRole::TECHNICIAN:
    role_name = "Technician";
    break;
  case UserRole::GUEST:
    role_name = "Guest";
    break;
  }

  m_user_info->setText(QString("Logged in as: %1 (%2)")
                           .arg(QString::fromStdString(user->username()))
                           .arg(role_name));
  m_user_info->setVisible(true);
  m_logout_button->setVisible(true);
}

void LoginPage::update_ui_for_logged_out()
{
  m_username_input->setVisible(true);
  m_password_input->setVisible(true);
  m_login_button->setVisible(true);
  m_guest_button->setVisible(true);

  m_user_info->setVisible(false);
  m_logout_button->setVisible(false);
}

void LoginPage::clear_fields()
{
  m_username_input->clear();
  m_password_input->clear();
  m_status_label->clear();
}

void LoginPage::showEvent(QShowEvent *event)
{
  QWidget::showEvent(event);

  auto current_user = AuthenticationService::instance().current_user();
  if(current_user) {
    update_ui_for_logged_in_user(current_user);
  } else {
    update_ui_for_logged_out();
  }
}

QIcon LoginPage::tinted_icon(const QString &path, const QColor &color) const
{
  QPixmap src(path);
  QPixmap dst(src.size());
  dst.fill(Qt::transparent);
  QPainter p(&dst);
  p.setCompositionMode(QPainter::CompositionMode_Source);
  p.drawPixmap(0, 0, src);
  p.setCompositionMode(QPainter::CompositionMode_SourceIn);
  p.fillRect(dst.rect(), color);
  p.end();
  return QIcon(dst);
}