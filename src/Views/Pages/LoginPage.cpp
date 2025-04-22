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

      auto *title_label = new QLabel("TechMa Login", this);
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

      btn_layout->addWidget(m_login_button);
      btn_layout->addWidget(m_guest_button);

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

      main_layout->addWidget(title_label);
      main_layout->addSpacing(20);
      main_layout->addLayout(form_layout);
      main_layout->addSpacing(10);
      main_layout->addLayout(btn_layout);
      main_layout->addWidget(m_status_label);
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

    void LoginPage::clear_fields()
    {
      m_username_input->clear();
      m_password_input->clear();
      m_status_label->clear();
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