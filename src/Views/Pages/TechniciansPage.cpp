#include "TechMa/Views/Pages/TechniciansPage.h"

#include <QLabel>

TechniciansPage::TechniciansPage(QWidget *parent) : QWidget(parent)
{
  setup_ui();
  setup_connects();
}

void TechniciansPage::setup_ui()
{
  auto *page_name = new QLabel("Technicians", this);
  page_name->setObjectName("Title");
}

void TechniciansPage::setup_connects() {}
