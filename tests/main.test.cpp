#include <QtTest/QtTest>
#include "models.test/animated-cursor.test.hpp"
#include "models.test/static-cursor.test.hpp"

int main(int argc, char** argv) {
  int status = 0;
  {
    StaticCursorTest test;
    status |= QTest::qExec(&test, argc, argv);
  }
  {
    AnimatedCursorTest test;
    status |= QTest::qExec(&test, argc, argv);
  }
  return status;
}
