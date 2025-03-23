#ifndef STATIC_CURSOR_TEST_HPP
#define STATIC_CURSOR_TEST_HPP

#include <QtTest/QtTest>

class StaticCursorTest : public QObject {
  Q_OBJECT

 private slots:
  void testFromFile();
  void testGetPrev();
};

#endif  // STATIC_CURSOR_TEST_HPP