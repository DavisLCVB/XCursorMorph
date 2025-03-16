#ifndef XSTATIC_CURSOR_HPP
#define XSTATIC_CURSOR_HPP

#include <QByteArray>
#include <QString>
#include <QVector>
#include <models/formats/cursor-entry.hpp>
#include <types.hpp>

class StaticCursor {
 public:
  static StaticCursor fromData(const QByteArray& data);
  static StaticCursor fromPath(const QString& path);
  const QVector<CursorEntry>& entries() const;

 private:
  explicit StaticCursor(const QString& path, const QByteArray& data);
  void __readHeader();
  void __readEntries();
  QString __path;
  QByteArray __data;
  u16 __entryCount;
  QVector<CursorEntry> __entries;
  constexpr static u16 __headerSize{6};
  constexpr static u16 __entrySize{16};
  constexpr static u16 __headerReservedValue{0};
  constexpr static u16 __headerTypeValue{2};
};

#endif  // XSTATIC_CURSOR_HPP