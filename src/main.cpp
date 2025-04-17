#include "TechMa/Views/TechMapp.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  TechMapp     techmapp(app); // pas de dérivation, juste un contrôleur

  return app.exec();
}
