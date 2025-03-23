#ifndef ANIMATED_CURSOR_HPP
#define ANIMATED_CURSOR_HPP

#include <QMap>
#include <QString>
#include <QVector>
#include <models/formats/ani.hpp>
#include <types.hpp>

class AnimatedCursor {
 public:
  static AnimatedCursor fromFile(const QString& path);
  QVector<QString> getPrev() const;
  QVector<ANIFrame> frames() const;
  QString name() const;
  QString path() const;
  QString id() const;

 private:
  AnimatedCursor(const ANI& ani);
  ANI __data;
  QString __path;
  QString __name;
  QString __id{""};
  static QMap<QString, QString> __cache;
};

#endif  // ANIMATED_CURSOR_HPP