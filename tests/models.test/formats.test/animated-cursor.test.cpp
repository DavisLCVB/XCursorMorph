#include "animated-cursor.test.hpp"

#include <QFile>
#include <exceptions/xerror.hpp>
#include <models/formats/animated-cursor.hpp>

void AnimatedCursorTest::testFromData() {
  QString path = "/home/davis/Dev/XCursorMorph/cursors/busy.ani";
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    throw XError("Failed to open file: " + path);
  }
  try {
    auto data = file.readAll();
    auto cursor = AnimatedCursor::fromData(data);
    QVERIFY(cursor.frames().size() > 0);
  } catch (XError& e) {
    e.printFormated();
    QVERIFY(false);
  }
}

void AnimatedCursorTest::testFromPath() {
  try {
    QString path = "/home/davis/Dev/XCursorMorph/cursors/busy.ani";
    auto cursor = AnimatedCursor::fromPath(path);
    QVERIFY(cursor.frames().size() > 0);
  } catch (XError& e) {
    e.printFormated();
    QVERIFY(false);
  }
}

void AnimatedCursorTest::testToPng() {
  try {
    QString path = "/home/davis/Dev/XCursorMorph/cursors/busy.ani";
    auto cursor = AnimatedCursor::fromPath(path);
    auto frames = cursor.frames();
    u64 index{0};
    for (auto& frame : frames) {
      auto entries = frame.entries();
      for (auto& entry : entries) {
        const QString outputPath =
            "/home/davis/Dev/XCursorMorph/cursors/busy-" +
            QString::number(index) + "/busy_" + QString::number(entry.width()) +
            "x" + QString::number(entry.height()) + ".png";
        entry.toPng(outputPath);
      }
      index++;
    }
  } catch (XError& e) {
    e.printFormated();
    QVERIFY(false);
  }
}