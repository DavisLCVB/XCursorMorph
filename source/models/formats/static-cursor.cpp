#include "static-cursor.hpp"

#include <QDebug>
#include <QFile>
#include <exceptions/xerror.hpp>
#include <models/structs/serializer.hpp>

StaticCursor StaticCursor::fromData(const QByteArray& data) {
  return StaticCursor("no-path", data);
}

StaticCursor StaticCursor::fromPath(const QString& path) {
  QFile file(path);
  if (!file.exists()) {
    throw XError(XErrorType::FileNotFound, "File not found: " + path);
  }
  if (!file.open(QIODevice::ReadOnly)) {
    throw XError(XErrorType::FileNotOpened, "Failed to open file: " + path);
  }
  return StaticCursor(path, file.readAll());
}

const QVector<CursorEntry>& StaticCursor::entries() const {
  return __entries;
}

StaticCursor::StaticCursor(const QString& path, const QByteArray& data)
    : __path(path), __data(data) {
  __readHeader();
  __readEntries();
}

void StaticCursor::__readHeader() {
  const QByteArray header = __data.left(__headerSize);
  auto [res, type, num] = Serializer::unpack<u16, u16, u16>(header);
  if (res != __headerReservedValue) {
    const QString message =
        QString("Invalid header, reserverd must be %1, value: %2 - %3")
            .arg(__headerReservedValue)
            .arg(res)
            .arg(__path);
    throw XError(XErrorType::InvalidData, message);
  }
  if (type != __headerTypeValue) {
    const QString message =
        QString("Invalid byte of type, must be %1, value: %2 - %3")
            .arg(__headerTypeValue)
            .arg(type)
            .arg(__path);
    throw XError(XErrorType::InvalidData, message);
  }
  __entryCount = num;
}

void StaticCursor::__readEntries() {
  for (u16 index{0}; index < __entryCount; ++index) {
    const u64 start = __headerSize + __entrySize * index;
    auto [w, h, _, res, hx, hy, size, off] =
        Serializer::unpack<u8, u8, u8, u8, u16, u16, u32, u32>(
            __data.mid(start, __entrySize));
    auto entry = CursorEntry{w, h, hx, hy, size, off};
    entry.setData(__data.mid(off, size));
    __entries.append(entry);
  }
}
