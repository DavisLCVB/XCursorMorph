#include <QtTest/QtTest>
#include "models.test/formats.test/ani.test.hpp"
#include "models.test/formats.test/bmp.test.hpp"
#include "models.test/formats.test/cur-ico.test.hpp"
#include "models.test/static-cursor.test.hpp"

int main(int argc, char** argv) {
  int status = 0;
  {
    CURTest curTest;
    status |= QTest::qExec(&curTest, argc, argv);
  }
  {
    BMPTest bmpTest;
    status |= QTest::qExec(&bmpTest, argc, argv);
  }
  {
    ANITest aniTest;
    status |= QTest::qExec(&aniTest, argc, argv);
  }
  {
    StaticCursorTest staticCursorTest;
    status |= QTest::qExec(&staticCursorTest, argc, argv);
  }
  return status;
}
