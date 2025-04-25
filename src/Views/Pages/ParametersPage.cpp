/**
 * @file ParametersPage.cpp
 * @brief Implements the ParametersPage class, which displays basic application parameters UI.
 */

#include "TechMa/Views/Pages/ParametersPage.h"

#include <QLabel>

/**
 * @brief Constructs the ParametersPage and sets up its UI components.
 * 
 * @param parent Optional parent QWidget.
 */
ParametersPage::ParametersPage(QWidget *parent) : QWidget(parent)
{
  setup_ui();
  setup_connects();
}

/**
 * @brief Sets up the static UI layout for the parameters page.
 */
void ParametersPage::setup_ui()
{
  auto *page_name = new QLabel("Parameters", this);
  page_name->setObjectName("Title");
}

/**
 * @brief Placeholder for setting up signal-slot connections.
 * 
 * Currently empty — extend this as functionality is added.
 */
void ParametersPage::setup_connects() {}