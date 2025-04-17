#pragma once

#include <QMainWindow>

class QApplication;

class TechMapp : public QMainWindow
{
  Q_OBJECT

public:
  explicit TechMapp(QApplication &app);

private:
  void load_stylesheet();
};
