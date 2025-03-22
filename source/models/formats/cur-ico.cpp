#include "cur-ico.hpp"

#include <QDataStream>
#include <QFile>
#include <exceptions/xerror.hpp>
#include <models/formats/bmp.hpp>
#include <models/structs/serializer.hpp>
#include <types.hpp>

void CUR_ICOEntry::setDimension(const QPair<u8, u8>& dimension) {
  __dimension = dimension;
}

void CUR_ICOEntry::setColorCount(u8 colorCount) {
  __colorCount = colorCount;
}

void CUR_ICOEntry::setHotspot(const QPair<u16, u16>& hotspot) {
  __hotspot = hotspot;
}

void CUR_ICOEntry::setSize(u32 size) {
  __size = size;
}

void CUR_ICOEntry::setOffset(u32 offset) {
  __offset = offset;
}

QPair<u8, u8> CUR_ICOEntry::dimension() const {
  return __dimension;
}

u8 CUR_ICOEntry::colorCount() const {
  return __colorCount;
}

QPair<u16, u16> CUR_ICOEntry::hotspot() const {
  return __hotspot;
}

u32 CUR_ICOEntry::size() const {
  return __size;
}

u32 CUR_ICOEntry::offset() const {
  return __offset;
}

void CUR_ICOEntry::setData(const QByteArray& data) {
  __data = data;
}

QByteArray CUR_ICOEntry::data() const {
  return __data;
}

void CUR_ICOEntry::toPng(const QString& path) {
  __rebuildBMPHeader();
  BMP bmp = BMP::fromData(__data);
  bmp.toPng(path);
}

void CUR_ICOEntry::toBMP(const QString& path) {
  __rebuildBMPHeader();
  BMP bmp = BMP::fromData(__data);
  bmp.save(path);
}

void CUR_ICOEntry::__rebuildBMPHeader() {
  const u16 signature = 0x4D42;
  const u32 fileSize = __BMP_HEADER_SIZE_BYTES + __size;
  const u32 reserved = 0;
  const u32 offset = __BMP_HEADER_SIZE_BYTES + __BMP_INFO_HEADER_SIZE_BYTES;
  auto newData =
      Serializer::pack(std::tuple{signature, fileSize, reserved, offset});
  __data = newData + __data;
}

CUR_ICO CUR_ICO::fromData(const QByteArray& data) {
  CUR_ICO cur(data);
  cur.__readHeader();
  cur.__fillEntries();
  return cur;
}

CUR_ICO CUR_ICO::fromFile(const QString& path) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    throw XError(XErrorType::FileNotOpened, "Failed to open file " + path);
  }
  QByteArray data = file.readAll();
  return CUR_ICO::fromData(data);
}

CUR_ICO::CUR_ICO(const QByteArray& data) : __data(data) {}

void CUR_ICO::__readHeader() {
  const auto header = Serializer::unpack<u16, u16, u16>(__data);
  const auto [res, type, num] = header;
  if (res != 0) {
    throw XError::invalidData("reserved bytes value", QString::number(res), 0);
  }
  if (type != 2 && type != 1) {
    throw XError::invalidData("File type", QString::number(type), " 1 | 2");
  }
  if (num == 0) {
    throw XError::invalidData("Number of images", QString::number(num),
                              "1-65535");
  }
  if (type == 1) {
    __isIco = true;
  }
  __imagesCount = num;
}

void CUR_ICO::__fillEntries() {
  const auto entriesData = __data.mid(__HEADER_SIZE_BYTES);
  for (u16 i{0}; i < __imagesCount; ++i) {
    auto entryData = Serializer::unpack<u8, u8, u8, u8, u16, u16, u32, u32>(
        entriesData.mid(i * __ENTRY_SIZE_BYTES));
    const auto [width, height, colorCount, reserved, xHotspot, yHotspot, size,
                offset] = entryData;
    if (reserved != 0) {
      throw XError::invalidData(
          "reserved bytes value in entry #" + QString::number(i),
          QString::number(reserved), "0");
    }
    CUR_ICOEntry entry;
    entry.setDimension({width, height});
    entry.setColorCount(colorCount);
    entry.setSize(size);
    entry.setOffset(offset);
    entry.setData(__data.mid(offset, size));
    if (__isIco) {
      entry.setHotspot({0, 0});
    } else {
      entry.setHotspot({xHotspot, yHotspot});
    }
    __entries.append(entry);
  }
}

QVector<CUR_ICOEntry> CUR_ICO::entries() const {
  return __entries;
}