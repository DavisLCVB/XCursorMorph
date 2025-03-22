#ifndef CUR_HPP
#define CUR_HPP

#include <QByteArray>
#include <QPair>
#include <QVector>
#include <models/formats/ientry.hpp>
#include <types.hpp>

class CUR_ICOEntry final : public IEntry {
 public:
  void setDimension(const QPair<u8, u8>& dimension);
  void setColorCount(u8 colorCount);
  void setHotspot(const QPair<u16, u16>& hotspot);
  void setSize(u32 size);
  void setOffset(u32 offset);
  void setData(const QByteArray& data);
  QPair<u8, u8> dimension() const;
  u8 colorCount() const;
  QPair<u16, u16> hotspot() const;
  u32 size() const;
  u32 offset() const;
  QByteArray data() const;
  CUR_ICOEntry() = default;
  ~CUR_ICOEntry() = default;
  void toPng(const QString& path) override;
  void toBMP(const QString& path);

 private:
  QPair<u8, u8> __dimension;
  u8 __colorCount;
  QPair<u16, u16> __hotspot;
  u32 __size;
  u32 __offset;
  QByteArray __data;
  static const u32 __BMP_HEADER_SIZE_BYTES = 14;
  static const u32 __BMP_INFO_HEADER_SIZE_BYTES = 40;
  void __rebuildBMPHeader();
};

class CUR_ICO {
 public:
  static CUR_ICO fromData(const QByteArray& data);
  static CUR_ICO fromFile(const QString& path);
  QVector<CUR_ICOEntry> entries() const;
  ~CUR_ICO() = default;

 private:
  CUR_ICO(const QByteArray& data);
  void __readHeader();
  void __fillEntries();

  QByteArray __data;
  u16 __imagesCount;
  QVector<CUR_ICOEntry> __entries;
  bool __isIco{false};
  static const u16 __HEADER_SIZE_BYTES = 6;
  static const u16 __ENTRY_SIZE_BYTES = 16;
};
#endif  // CUR_HPP