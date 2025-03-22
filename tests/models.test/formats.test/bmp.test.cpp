#include "bmp.test.hpp"

#include <exceptions/xerror.hpp>
#include <models/formats/bmp.hpp>

void BMPTest::testFromData() {
  try {
    QString path = "/home/davis/Dev/XCursorMorph/input.test/pointer.bmp";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
      throw XError(XErrorType::FileNotOpened, "Failed to open file " + path);
    }
    QByteArray data = file.readAll();
    BMP bmp = BMP::fromData(data);
  } catch (XError& err) {
    err.printFormated();
    QFAIL("Failed");
  }
}

void BMPTest::testFromFile() {
  try {
    QString path = "/home/davis/Dev/XCursorMorph/input.test/pointer.bmp";
    BMP bmp = BMP::fromFile(path);
  } catch (XError& err) {
    err.printFormated();
    QFAIL("Failed");
  }
}

void BMPTest::testToPng() {
  try {
    QString path = "/home/davis/Dev/XCursorMorph/input.test/pointer.bmp";
    BMP bmp = BMP::fromFile(path);
    bmp.toPng("/home/davis/Dev/XCursorMorph/output.test/pointer-bmp.png");
  } catch (XError& err) {
    err.printFormated();
    QFAIL("Failed");
  }
}