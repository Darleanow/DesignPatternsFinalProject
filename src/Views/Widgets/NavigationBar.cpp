/**
 * @file NavigationBar.cpp
 * @brief Implements the NavigationBar class, a custom tab bar with icon rendering and navigation support.
 */

#include "TechMa/Views/Widgets/NavigationBar.h"
#include <QIcon>
#include <QPainter>

/**
 * @brief Constructs the navigation bar and initializes its UI.
 * 
 * @param parent Optional parent QWidget.
 */
NavigationBar::NavigationBar(QWidget *parent) : QTabBar(parent)
{
  setup_ui();
  setup_connects();
}

/**
 * @brief Configures the navigation bar appearance and populates tabs with icons and labels.
 */
void NavigationBar::setup_ui()
{
  const std::vector<QString> labels = {
      "Interventions", "Technicians", "Parameters", "Account"
  };

  const std::vector<QString> icons = {
      ":/styles/icons/navigation_bar/interventions.svg",
      ":/styles/icons/navigation_bar/technicians.svg",
      ":/styles/icons/navigation_bar/settings.svg",
      ":/styles/icons/navigation_bar/log-in.svg"
  };

  setExpanding(false);
  setUsesScrollButtons(false);
  setDocumentMode(true);
  setDrawBase(false);
  setElideMode(Qt::ElideNone);
  setFocusPolicy(Qt::NoFocus);

  for (int i = 0; i < static_cast<int>(labels.size()); ++i)
    addTab(QIcon(paint_svg(icons[i])), labels[i]);
}

/**
 * @brief Connects the tab selection signal to the custom tabChanged signal.
 */
void NavigationBar::setup_connects()
{
  connect(this, &QTabBar::currentChanged, this, &NavigationBar::tabChanged);
}

/**
 * @brief Applies a custom fill color to an SVG icon and returns it as a QPixmap.
 * 
 * @param path The resource path to the SVG file.
 * @return QPixmap The colored icon rendered from the SVG.
 */
QPixmap NavigationBar::paint_svg(const QString &path) const
{
  QPixmap source(path);
  QPixmap result = source;
  QPainter painter(&result);
  painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
  painter.fillRect(result.rect(), QColor("#6B6BFF"));
  painter.end();
  return result;
}