#ifndef XANIMATED_CURSOR_HPP
#define XANIMATED_CURSOR_HPP

#include <QByteArray>
#include <QString>
#include <QVector>
#include <models/formats/static-cursor.hpp>

class AnimatedCursor {
 public:
  static AnimatedCursor fromData(const QByteArray& data);
  static AnimatedCursor fromPath(const QString& path);
  const QVector<StaticCursor>& frames() const;

 private:
  AnimatedCursor(const QByteArray& data, const QString& path);
  QByteArray __data;
  QString __path;
  QVector<StaticCursor> __frames;
  void __readChunks();
};

#endif  // XANIMATED_CURSOR_HPP