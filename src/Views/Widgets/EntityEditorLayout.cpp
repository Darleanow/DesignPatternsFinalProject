/**
 * @file EntityEditorLayout.cpp
 * @brief Implements the EntityEditorLayout class, a reusable two-panel UI layout with a title and action button.
 */

#include "TechMa/Views/Widgets/EntityEditorLayout.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

/**
 * @brief Constructs the layout with a title and an action button label.
 * 
 * @param title The title displayed at the top of the layout.
 * @param actionText The text displayed on the action button.
 * @param parent Optional parent QWidget.
 */
EntityEditorLayout::EntityEditorLayout(
    const QString &title, const QString &actionText, QWidget *parent
)
    : QWidget(parent),
      m_title_text(title),
      m_action_text(actionText)
{
  setup_ui();
}

/**
 * @brief Sets up the internal layout with a top bar and a main two-panel area.
 */
void EntityEditorLayout::setup_ui()
{
  m_title = new QLabel(m_title_text, this);
  m_title->setObjectName("Title");

  m_action_button = new QPushButton(m_action_text, this);

  m_topbar_layout = new QHBoxLayout();
  m_topbar_layout->addWidget(m_title);
  m_topbar_layout->addStretch();
  m_topbar_layout->addWidget(m_action_button);

  m_main_layout = new QHBoxLayout();
  m_main_layout->setSpacing(24);
  m_main_layout->setContentsMargins(0, 0, 0, 0);

  m_global_layout = new QVBoxLayout(this);
  m_global_layout->addLayout(m_topbar_layout);
  m_global_layout->addLayout(m_main_layout);

  setLayout(m_global_layout);
}

/**
 * @brief Inserts or replaces the widget shown on the left side of the main layout.
 * 
 * @param widget The widget to place on the left.
 */
void EntityEditorLayout::set_left_widget(QWidget *widget)
{
  if (m_left_widget)
    m_main_layout->removeWidget(m_left_widget);
  m_left_widget = widget;
  m_main_layout->insertWidget(0, widget, 1);
}

/**
 * @brief Inserts or replaces the widget shown on the right side of the main layout.
 * 
 * @param widget The widget to place on the right.
 */
void EntityEditorLayout::set_right_widget(QWidget *widget)
{
  if (m_right_widget)
    m_main_layout->removeWidget(m_right_widget);
  m_right_widget = widget;
  m_main_layout->addWidget(widget, 2);
}

/**
 * @brief Returns a pointer to the main action button.
 * 
 * Useful for connecting to UI signals (e.g. clicked()).
 * 
 * @return QPushButton* Pointer to the action button.
 */
QPushButton *EntityEditorLayout::action_button() const
{
  return m_action_button;
}