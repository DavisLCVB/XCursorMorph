#ifndef BMP_HPP
#define BMP_HPP

#include <QByteArray>
#include <QString>
#include <types.hpp>

class BMP {
 public:
  static BMP fromData(const QByteArray& data);
  static BMP fromFile(const QString& path);
  u32 bitsPerPixel() const;
  void toPng(const QString& path) const;
  void save(const QString& path) const;
  ~BMP() = default;

 private:
  BMP(const QByteArray& data);
  void __readHeader();
  void __readInfoHeader();
  QByteArray __data;
  u32 __fileSize;
  u32 __dataOffset;
  u32 __bitsPerPixel;
  u32 __imageSize;
  u16 __width;
  u16 __height;
  static const u16 __HEADER_SIZE_BYTES = 14;
  static const u16 __INFO_HEADER_SIZE_BYTES = 40;
};

#endif  // BMP_HPP