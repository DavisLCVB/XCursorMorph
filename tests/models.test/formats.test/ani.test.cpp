#include "ani.test.hpp"

#include <QFile>
#include <exceptions/xerror.hpp>
#include <models/formats/ani.hpp>

void ANITest::testFromData() {
  try {
    const QString path = "/home/davis/Dev/XCursorMorph/input.test/busy.ani";
    QFile file(path);
    QVERIFY(file.open(QIODevice::ReadOnly));
    ANI ani = ANI::fromData(file.readAll());
    QVERIFY(ani.frames().size() > 0);
  } catch (XError& e) {
    e.printFormated();
    QVERIFY(false);
  }
}

void ANITest::testFromPath() {
  try {
    const QString path = "/home/davis/Dev/XCursorMorph/input.test/busy.ani";
    ANI ani = ANI::fromPath(path);
    QVERIFY(ani.frames().size() > 0);
  } catch (XError& e) {
    e.printFormated();
    QVERIFY(false);
  }
}

void ANITest::testToPng() {
  try {
    const QString path = "/home/davis/Dev/XCursorMorph/input.test/busy.ani";
    ANI ani = ANI::fromPath(path);
    QVERIFY(ani.frames().size() > 0);
    const QString prefix = "/home/davis/Dev/XCursorMorph/output.test/busy";
    i64 i{0};
    for (const auto& frame : ani.frames()) {
      const QString framePrefix = prefix + QString::number(i);
      for (auto entry : frame.entries()) {
        const QString name = framePrefix + "_" +
                             QString::number(entry.dimension().first) + "x" +
                             QString::number(entry.dimension().second) + ".png";
        entry.toPng(name);
      }
      ++i;
    }
  } catch (XError& e) {
    e.printFormated();
    QVERIFY(false);
  }
}
