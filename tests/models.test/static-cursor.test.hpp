#ifndef STATIC_CURSOR_TEST_H
#define STATIC_CURSOR_TEST_H

#include <QtTest/QtTest>

class StaticCursorTest final : public QObject {
  Q_OBJECT
 private slots:
  void testFromData();
  void testFromPath();
};

#endif  // STATIC_CURSOR_TEST_H