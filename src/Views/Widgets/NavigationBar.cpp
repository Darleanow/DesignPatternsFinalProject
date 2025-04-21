#include "TechMa/Views/Widgets/NavigationBar.h"
#include <QIcon>
#include <QPainter>

NavigationBar::NavigationBar(QWidget *parent) : QTabBar(parent)
{
  setup_ui();
  setup_connects();
}

void NavigationBar::setup_ui()
{
  const std::vector<QString> labels = {
      "Interventions", "Technicians", "Parameters", "Connexion / Roles"
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

  for(int i = 0; i < static_cast<int>(labels.size()); ++i)
    addTab(QIcon(paint_svg(icons[i])), labels[i]);
}

void NavigationBar::setup_connects()
{
  connect(this, &QTabBar::currentChanged, this, &NavigationBar::tabChanged);
}

QPixmap NavigationBar::paint_svg(const QString &path) const
{
  QPixmap  source(path);
  QPixmap  result = source;
  QPainter painter(&result);
  painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
  painter.fillRect(result.rect(), QColor("#6B6BFF"));
  painter.end();
  return result;
}
