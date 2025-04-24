/**
 * @file ParametersPage.h
 * @brief Declares the ParametersPage class, a UI component for application settings or preferences.
 */

#pragma once

#include <QWidget>

/**
 * @class ParametersPage
 * @brief A QWidget-based page used to display and manage application parameters or settings.
 * 
 * Can be extended to include various configuration options and preferences.
 */
class ParametersPage : public QWidget
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs the ParametersPage widget.
   * 
   * @param parent Optional parent QWidget.
   */
  explicit ParametersPage(QWidget *parent = nullptr);

private:
  /**
   * @brief Sets up the UI layout and widgets.
   */
  void setup_ui();

  /**
   * @brief Connects UI components to relevant logic or signals.
   */
  void setup_connects();
};