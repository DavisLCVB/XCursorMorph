#include "lib.hpp"
#include <QApplication>
#include <QDebug>
#include <metadata/meta.hpp>
#include <models/static-cursor.hpp>
#include <mutex>

#include <views/main-window.hpp>

std::unique_ptr<XCursorMorph> XCursorMorph::__instance = nullptr;

XCursorMorph& XCursorMorph::instance() {
  static std::once_flag __once;
  std::call_once(__once, []() { __instance.reset(new XCursorMorph()); });
  return *__instance;
}

i32 XCursorMorph::run(i32 argc, c8* argv[]) {
  __loadResources();
  QApplication app(argc, argv);
  app.setApplicationName(Meta::name);
  app.setApplicationVersion(Meta::version);
  MainWindow window;
  window.show();
  return app.exec();
}

void XCursorMorph::__loadResources() {
  Q_INIT_RESOURCE(assets);
}