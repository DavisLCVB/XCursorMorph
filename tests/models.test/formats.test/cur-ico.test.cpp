#include "cur-ico.test.hpp"

#include <QFile>
#include <exceptions/xerror.hpp>
#include <models/formats/cur-ico.hpp>
#include <types.hpp>

void CURTest::testFromData() {
  try {
    QString path = "/home/davis/Dev/XCursorMorph/input.test/pointer.cur";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
      throw XError(XErrorType::FileNotOpened, "Failed to open file " + path);
    }
    QByteArray data = file.readAll();
    CUR_ICO cur = CUR_ICO::fromData(data);
  } catch (XError& err) {
    err.printFormated();
    QFAIL("Failed");
  }
}

void CURTest::testFromFile() {
  try {
    QString path = "/home/davis/Dev/XCursorMorph/input.test/pointer.cur";
    CUR_ICO cur = CUR_ICO::fromFile(path);
  } catch (XError& err) {
    err.printFormated();
    QFAIL("Failed");
  }
}

void CURTest::testToPng() {
  try {
    QString path = "/home/davis/Dev/XCursorMorph/input.test/text.cur";
    CUR_ICO cur = CUR_ICO::fromFile(path);
    QVector<CUR_ICOEntry> entries = cur.entries();
    u16 index{0};
    for (auto& entry : entries) {
      entry.toPng("/home/davis/Dev/XCursorMorph/output.test/text" +
                  QString::number(index) + ".png");
      ++index;
    }
  } catch (XError& err) {
    err.printFormated();
    QFAIL("Failed");
  }
}

void CURTest::testToBMP() {
  try {
    QString path = "/home/davis/Dev/XCursorMorph/input.test/pointer.cur";
    CUR_ICO cur = CUR_ICO::fromFile(path);
    QVector<CUR_ICOEntry> entries = cur.entries();
    u16 index{0};
    for (auto& entry : entries) {
      entry.toBMP("/home/davis/Dev/XCursorMorph/output.test/pointer" +
                  QString::number(index) + ".bmp");
      ++index;
    }
  } catch (XError& err) {
    err.printFormated();
    QFAIL("Failed");
  }
}