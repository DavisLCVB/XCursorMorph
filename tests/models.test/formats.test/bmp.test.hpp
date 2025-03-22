#ifndef BMP_TEST_HPP
#define BMP_TEST_HPP

#include <QtTest/QtTest>

class BMPTest : public QObject {
  Q_OBJECT
 private slots:
  void testFromData();
  void testFromFile();
  void testToPng();
};

#endif  // BMP_TEST_HPP