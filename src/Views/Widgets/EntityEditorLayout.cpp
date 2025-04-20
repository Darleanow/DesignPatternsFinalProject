#include "TechMa/Views/Widgets/EntityEditorLayout.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

EntityEditorLayout::EntityEditorLayout(
    const QString &title, const QString &actionText, QWidget *parent
)
    : QWidget(parent),
      m_title_text(title),
      m_action_text(actionText)
{
  setup_ui();
}

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

void EntityEditorLayout::set_left_widget(QWidget *widget)
{
  if(m_left_widget)
    m_main_layout->removeWidget(m_left_widget);
  m_left_widget = widget;
  m_main_layout->insertWidget(0, widget, 1);
}

void EntityEditorLayout::set_right_widget(QWidget *widget)
{
  if(m_right_widget)
    m_main_layout->removeWidget(m_right_widget);
  m_right_widget = widget;
  m_main_layout->addWidget(widget, 2);
}

QPushButton *EntityEditorLayout::action_button() const
{
  return m_action_button;
}
