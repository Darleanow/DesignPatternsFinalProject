#include "TechMa/Views/Pages/ParametersPage.h"

#include <QLabel>

ParametersPage::ParametersPage(QWidget *parent) : QWidget(parent)
{
  setup_ui();
  setup_connects();
}

void ParametersPage::setup_ui()
{
  auto *page_name = new QLabel("Parameters", this);
  page_name->setObjectName("Title");
}

void ParametersPage::setup_connects() {}
