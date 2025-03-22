#ifndef CUR_TEST_HPP
#define CUR_TEST_HPP

#include <QtTest/QtTest>

class CURTest : public QObject {
  Q_OBJECT
 private slots:
  void testFromData();
  void testFromFile();
  void testToPng();
  void testToBMP();
};

#endif  // CUR_TEST_HPP