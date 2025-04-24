/**
 * @file main.cpp
 * @brief Entry point for the TechMa application.
 * 
 * Initializes the QApplication instance and launches the main window.
 */

#include "TechMa/Views/TechMapp.h"

#include <QApplication>

/**
 * @brief Main entry point of the application.
 * 
 * Initializes the Qt application and displays the main TechMa window.
 * 
 * @param argc Argument count from command-line.
 * @param argv Argument vector from command-line.
 * @return Exit status code from the Qt event loop.
 */
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  TechMapp techmapp(app);

  return app.exec();
}