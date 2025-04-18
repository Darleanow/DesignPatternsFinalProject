#include "TechMa/Views/Pages/InterventionPage.h"

#include <QLabel>

InterventionPage::InterventionPage(QWidget *parent) : QWidget(parent)
{
  setup_ui();
  setup_connects();
}

void InterventionPage::setup_ui()
{
  auto *page_name = new QLabel("Interventions", this);
  page_name->setObjectName("Title");
}

void InterventionPage::setup_connects() {}
