#ifndef ANIMATED_CURSOR_H
#define ANIMATED_CURSOR_H

#include <QObject>
#include <QtTest/QtTest>

class AnimatedCursorTest final : public QObject {
  Q_OBJECT
 private slots:
  void testFromData();
  void testFromPath();
  void testToPng();
};

#endif  // ANIMATED_CURSOR_H