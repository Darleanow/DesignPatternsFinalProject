/**
 * @file NavigationBar.h
 * @brief Declares the NavigationBar class, a custom QTabBar with SVG icon rendering.
 */

#pragma once

#include <QPixmap>
#include <QString>
#include <QTabBar>

/**
 * @class NavigationBar
 * @brief Custom navigation bar based on QTabBar, designed to support tab switching and SVG icon rendering.
 * 
 * Emits a signal when the selected tab changes, and provides a utility method to load and paint SVG icons.
 */
class NavigationBar : public QTabBar
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs the NavigationBar and sets up UI elements.
   * 
   * @param parent Optional parent QWidget.
   */
  explicit NavigationBar(QWidget *parent = nullptr);

  /**
   * @brief Renders an SVG file into a QPixmap.
   * 
   * @param path The file path to the SVG asset.
   * @return QPixmap The rendered SVG as a pixmap.
   */
  QPixmap paint_svg(const QString &path) const;

signals:
  /**
   * @brief Emitted when a new tab is selected.
   * 
   * @param index The index of the newly selected tab.
   */
  void tabChanged(int index);

private:
  /**
   * @brief Initializes the tab bar UI and appearance.
   */
  void setup_ui();

  /**
   * @brief Connects signals and slots for tab interaction.
   */
  void setup_connects();
};