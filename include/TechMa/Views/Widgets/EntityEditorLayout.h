/**
 * @file EntityEditorLayout.h
 * @brief Declares the EntityEditorLayout class, a custom QWidget layout for editing entities with a left/right pane design.
 */

#pragma once

#include <QWidget>

class QLabel;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

/**
 * @class EntityEditorLayout
 * @brief A UI layout widget that provides a reusable interface structure with a header, action button, and split pane for content.
 * 
 * This layout is typically used for pages that involve displaying a list of items on the left,
 * and an editor or detail view on the right.
 */
class EntityEditorLayout : public QWidget
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs the layout with a title and an action button label.
   * 
   * @param title Text to display in the header.
   * @param actionText Text for the main action button.
   * @param parent Optional parent QWidget.
   */
  explicit EntityEditorLayout(
      const QString &title, const QString &actionText, QWidget *parent = nullptr
  );

  /**
   * @brief Sets the widget that will appear on the left side of the main content area.
   * 
   * @param widget The widget to embed on the left.
   */
  void set_left_widget(QWidget *widget);

  /**
   * @brief Sets the widget that will appear on the right side of the main content area.
   * 
   * @param widget The widget to embed on the right.
   */
  void set_right_widget(QWidget *widget);

  /**
   * @brief Returns a pointer to the action button.
   * 
   * Useful for connecting signals to trigger actions like "Create", "Add", etc.
   * 
   * @return QPushButton* Pointer to the action button.
   */
  QPushButton *action_button() const;

private:
  /**
   * @brief Builds the initial UI layout and components.
   */
  void setup_ui();

  QString m_title_text;        ///< Text displayed in the title label.
  QString m_action_text;       ///< Text displayed on the action button.

  QLabel      *m_title;        ///< The label used to display the title at the top.
  QPushButton *m_action_button;///< The main action button (e.g. "Create").
  QWidget     *m_left_widget;  ///< Widget shown on the left side of the layout.
  QWidget     *m_right_widget; ///< Widget shown on the right side of the layout.

  QHBoxLayout *m_topbar_layout;///< Horizontal layout for the title and button.
  QHBoxLayout *m_main_layout;  ///< Horizontal layout for the main content split.
  QVBoxLayout *m_global_layout;///< Global vertical layout combining topbar and main content.
};