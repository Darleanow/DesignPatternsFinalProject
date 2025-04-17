#include "TechMa/Views/TechMapp.h"

#include <QApplication>
#include <QFile>
#include <QPushButton>

TechMapp::TechMapp(QApplication &app)
{
  load_stylesheet();

  QFont font("Roboto");
  font.setHintingPreference(QFont::PreferFullHinting);
  font.setStyleStrategy(QFont::PreferAntialias);
  app.setFont(font);

  QPushButton *button = new QPushButton("Hello from Qt + stylesheet!", this);
  button->resize(200, 100);
  button->show();
}

void TechMapp::load_stylesheet()
{
  QFile file(":/styles/style.qss");

  if(file.open(QFile::ReadOnly | QFile::Text)) {
    QString style = file.readAll();
    qApp->setStyleSheet(style);
  }
}
