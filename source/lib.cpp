#include "lib.hpp"
#include <QApplication>
#include <QDebug>
#include <metadata/meta.hpp>

int XCursorMorph::run(int argc, char* argv[]) {
  QApplication app(argc, argv);
  qDebug() << Meta::name;
  qDebug() << "Version: " << Meta::version;
  return app.exec();
}