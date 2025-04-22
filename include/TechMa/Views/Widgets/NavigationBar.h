#pragma once

#include <QPixmap>
#include <QString>
#include <QTabBar>

class NavigationBar : public QTabBar
{
  Q_OBJECT;

public:
  explicit NavigationBar(QWidget *parent = nullptr);
  QPixmap paint_svg(const QString &path) const;

signals:
  void tabChanged(int index);

private:
  void setup_ui();
  void setup_connects();
};