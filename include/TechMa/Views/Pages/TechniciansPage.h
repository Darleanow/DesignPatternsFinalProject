#pragma once

#include <QWidget>

class TechniciansPage : public QWidget
{
  Q_OBJECT;

public:
  explicit TechniciansPage(QWidget *parent);

private:
  void setup_ui();
  void setup_connects();
};
