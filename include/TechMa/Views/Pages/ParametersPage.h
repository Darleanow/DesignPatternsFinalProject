#pragma once

#include <QWidget>

class ParametersPage : public QWidget
{
  Q_OBJECT;

public:
  explicit ParametersPage(QWidget *parent = nullptr);

private:
  void setup_ui();
  void setup_connects();
};
