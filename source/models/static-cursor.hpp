#ifndef STATIC_CURSOR_HPP
#define STATIC_CURSOR_HPP

#include <QMap>
#include <QString>
#include <models/formats/cur-ico.hpp>
#include <types.hpp>

class StaticCursor {
 public:
  static StaticCursor fromFile(const QString& path);
  QString getPrev();
  CUR_ICO data() const;
  QVector<CUR_ICOEntry> entries() const;
  QString name() const;
  QString path() const;
  QString id() const;
  static QMap<QString, QString> cache();
  static void setCache(const QMap<QString, QString>& cache);
  static void clearCache();

 private:
  StaticCursor(const CUR_ICO& curIco);
  CUR_ICO __data;
  QString __name;
  QString __path;
  QString __id{""};
  static QMap<QString, QString> __cache;
};

#endif  // STATIC_CURSOR_HPP
