#include "static-cursor.test.hpp"

#include <QFile>
#include <exceptions/xerror.hpp>
#include <models/formats/static-cursor.hpp>

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

void StaticCursorTest::testToPng() {
  const QString filePath = "/home/davis/Dev/XCursorMorph/cursors/pointer.cur";
  StaticCursor cursor = StaticCursor::fromPath(filePath);
  const QString outputPath = "/home/davis/Dev/XCursorMorph/cursors/pointer";
  try {

    for (const auto& entry : cursor.entries()) {
      const auto w = entry.width();
      const auto h = entry.height();
      const QString path = outputPath + QString("_%1x%2.png").arg(w).arg(h);
      entry.toPng(path);
    }
  } catch (XError& error) {
    error.printFormated();
    QVERIFY(false);
  }
}