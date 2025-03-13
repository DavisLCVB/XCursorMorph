#include "static-cursor.test.hpp"

#include <QFile>
#include <exceptions/xerror.hpp>
#include <models/static-cursor.hpp>

void StaticCursorTest::testFromData() {
  const QString filePath = "/home/davis/Dev/XCursorMorph/cursors/pointer.cur";
  QFile file(filePath);
  QVERIFY(file.exists());
  QVERIFY(file.open(QIODevice::ReadOnly));
  const QByteArray data = file.readAll();
  try {
    StaticCursor cursor = StaticCursor::fromData(data);
    QVERIFY(cursor.entries().size() > 0);
  } catch (XError& error) {
    error.printFormated();
    QVERIFY(false);
  }
}

void StaticCursorTest::testFromPath() {
  const QString filePath = "/home/davis/Dev/XCursorMorph/cursors/pointer.cur";
  StaticCursor cursor = StaticCursor::fromPath(filePath);
  QVERIFY(cursor.entries().size() > 0);
}