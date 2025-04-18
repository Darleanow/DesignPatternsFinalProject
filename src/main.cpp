#include "TechMa/Views/TechMapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  TechMapp     techmapp(app);

  return app.exec();
}
