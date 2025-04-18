#pragma once

#include "TechMa/Views/Widgets/NavigationBar.h"

#include <QMainWindow>

class QApplication;
class NavigationBar;
class QStackedWidget;

class TechMapp : public QMainWindow
{
  Q_OBJECT;

public:
  explicit TechMapp(QApplication &app);

private:
  void            load_stylesheet();
  void            setup_font(QApplication &app);
  void            setup_ui();
  void            setup_connects();

  NavigationBar  *m_navigation_bar;
  QStackedWidget *m_pages;
};
