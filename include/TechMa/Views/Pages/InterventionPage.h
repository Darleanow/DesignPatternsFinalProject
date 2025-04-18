#pragma once

#include <QWidget>

class InterventionPage : public QWidget
{
  Q_OBJECT;

public:
  explicit InterventionPage(QWidget *parent = nullptr);

private:
  void setup_ui();
  void setup_connects();
};
