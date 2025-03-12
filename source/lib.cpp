#include "lib.hpp"
#include <QApplication>
#include <QDebug>
#include <metadata/meta.hpp>

i32 XCursorMorph::run(i32 argc, c8* argv[]) {
  QApplication app(argc, argv);
  qDebug() << Meta::name;
  qDebug() << "Version: " << Meta::version;
  return app.exec();
}