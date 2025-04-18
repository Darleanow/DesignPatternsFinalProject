#include "TechMa/Views/TechMapp.h"
#include "TechMa/Views/Pages/InterventionPage.h"
#include "TechMa/Views/Pages/ParametersPage.h"
#include "TechMa/Views/Pages/TechniciansPage.h"

#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

TechMapp::TechMapp(QApplication &app)
{
  load_stylesheet();
  setup_font(app);
  setup_ui();
  setup_connects();

  show();
}

void TechMapp::load_stylesheet()
{
  QFile file(":/styles/style.qss");

  if(file.open(QFile::ReadOnly | QFile::Text)) {
    QString style = file.readAll();
    qApp->setStyleSheet(style);
  }
}

void TechMapp::setup_font(QApplication &app)
{
  int id = QFontDatabase::addApplicationFont(":/styles/fonts/RobotoMono.ttf");

  if(id == -1) {
    qWarning("Failed to load RobotoMono font.");
    return;
  }

  QStringList families = QFontDatabase::applicationFontFamilies(id);
  if(families.isEmpty()) {
    qWarning("Font loaded, but no families found.");
    return;
  }

  QFont font(families.at(0));
  font.setPointSize(12);
  font.setHintingPreference(QFont::PreferFullHinting);
  font.setStyleStrategy(QFont::PreferAntialias);
  app.setFont(font);
}

void TechMapp::setup_ui()
{
  auto *central = new QWidget(this);
  auto *vlayout = new QVBoxLayout(central);
  vlayout->setContentsMargins(0, 0, 0, 0);
  vlayout->setSpacing(0);

  m_navigation_bar = new NavigationBar(this);
  vlayout->addWidget(m_navigation_bar);

  m_pages = new QStackedWidget(this);
  vlayout->addWidget(m_pages);

  m_pages->addWidget(new InterventionPage(this));
  m_pages->addWidget(new TechniciansPage(this));
  m_pages->addWidget(new ParametersPage(this));

  setCentralWidget(central);
}

void TechMapp::setup_connects()
{
  connect(
      m_navigation_bar, &NavigationBar::tabChanged, m_pages,
      &QStackedWidget::setCurrentIndex
  );
}
