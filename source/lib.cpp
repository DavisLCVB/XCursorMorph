#include "lib.hpp"
#include <QApplication>
#include <QDebug>
#include <metadata/meta.hpp>
#include <mutex>

XCursorMorph& XCursorMorph::instance() {
  static std::once_flag __once;
  std::call_once(__once, []() { __instance.reset(new XCursorMorph()); });
  return *__instance;
}

i32 XCursorMorph::run(i32 argc, c8* argv[]) {
  QApplication app(argc, argv);
  qDebug() << Meta::name;
  qDebug() << "Version: " << Meta::version;
  return app.exec();
}