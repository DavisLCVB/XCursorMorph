#ifndef ANI_TEST_HPP
#define ANI_TEST_HPP

#include <QObject>
#include <QtTest/QtTest>

class ANITest : public QObject {
  Q_OBJECT
 private slots:
  void testFromData();
  void testFromPath();
  void testToPng();
};

#endif  // ANI_TEST_HPP