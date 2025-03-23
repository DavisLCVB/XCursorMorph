#include "static-cursor.test.hpp"

#include <exceptions/xerror.hpp>
#include <models/static-cursor.hpp>

void StaticCursorTest::testFromFile() {
  try {
    const QString path = "/home/davis/Dev/XCursorMorph/input.test/pointer.cur";
    StaticCursor cursor = StaticCursor::fromFile(path);
  } catch (XError& e) {
    e.printFormated();
    QVERIFY(false);
  }
}

void StaticCursorTest::testGetPrev() {
  try {

    const QString path = "/home/davis/Dev/XCursorMorph/input.test/pointer.cur";
    StaticCursor cursor = StaticCursor::fromFile(path);
    const auto prevPath = QFileInfo(cursor.getPrev()).absoluteFilePath();
    qDebug() << prevPath;
    QVERIFY(prevPath ==
            "/home/davis/Dev/XCursorMorph/.xcursor-morph/_static_0.png");
  } catch (XError& e) {
    e.printFormated();
    QVERIFY(false);
  }
}