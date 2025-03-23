#include "bmp.hpp"

#include <QDir>
#include <QFileInfo>
#include <QImage>
#include <QString>
#include <exceptions/xerror.hpp>
#include <models/structs/serializer.hpp>
#include <types.hpp>

BMP BMP::fromData(const QByteArray& data) {
  return BMP(data);
}

BMP BMP::fromFile(const QString& path) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    throw XError(XErrorType::FileNotOpened, "Failed to open file " + path);
  }
  return BMP(file.readAll());
}

BMP::BMP(const QByteArray& data) : __data(data) {
  __readHeader();
  __readInfoHeader();
}

void BMP::__readHeader() {
  auto header =
      Serializer::unpack<u16, u32, u32, u32>(__data.left(__HEADER_SIZE_BYTES));
  auto [signature, fileSize, res, dataOffset] = header;
  if (signature != 0x4D42) {
    throw XError::invalidData("BMP signature",
                              QString::fromLatin1(__data.left(2)), "BM");
  }
  if (res != 0) {
    throw XError::invalidData("BMP reserved", QString::number(res), "0");
  }
  __fileSize = fileSize;
  __dataOffset = dataOffset;
}

void BMP::__readInfoHeader() {
  auto header =
      Serializer::unpack<u32, u32, u32, u16, u16, u32, u32, u32, u32, u32, u32>(
          __data.mid(__HEADER_SIZE_BYTES, __INFO_HEADER_SIZE_BYTES));
  auto [infoHeaderSize, width, height, _0, bitCount, compression, sizeImage, _1,
        _2, _3, _4] = header;
  if (infoHeaderSize != __INFO_HEADER_SIZE_BYTES) {
    throw XError::invalidData("BMP info header size",
                              QString::number(infoHeaderSize),
                              QString::number(__INFO_HEADER_SIZE_BYTES));
  }
  if (height != 2 * width) {
    throw XError::invalidData("BMP height", QString::number(height),
                              QString::number(2 * width));
  }
  if (bitCount != 32 && bitCount != 24) {
    throw XError::notSupported("BMP bit count with value " +
                               QString::number(bitCount));
  }
  if (compression != 0) {
    throw XError::notSupported("BMP compression with value " +
                               QString::number(compression));
  }
  if (sizeImage == 0) {
    throw XError::invalidData("BMP size image", QString::number(sizeImage),
                              "0");
  }
  __bitsPerPixel = bitCount;
  __imageSize = sizeImage;
  __width = width;
  __height = height / 2;  // img + mask
}

void BMP::toPng(const QString& path) const {
  u32 pixelRowSize = 0;
  if (__bitsPerPixel == 32) {
    pixelRowSize = __width * 4;
  } else if (__bitsPerPixel == 24) {
    pixelRowSize = ((__width * 3 + 3) / 4) * 4;
  } else {
    QString message =
        QString("Unsupported bits per pixel: %1").arg(__bitsPerPixel);
    throw XError(XErrorType::NotSupported, message);
  }
  const u64 pixelDataOffset = __dataOffset;
  if (static_cast<u64>(__data.size()) <
      pixelDataOffset + __height * pixelRowSize) {
    throw XError(
        XErrorType::InvalidData,
        "Invalid data in cursor entry, "
        "expected more pixel data, pixelDataOffset: " +
            QString::number(pixelDataOffset) + ", expected: " +
            QString::number(pixelDataOffset + __height * pixelRowSize));
  }
  const u8* pixelData =
      reinterpret_cast<const u8*>(__data.data() + pixelDataOffset);
  const u64 maskOffset = pixelDataOffset + __height * pixelRowSize;
  const u64 maskRowSize = ((__width + 31) / 32) * 4;
  if (static_cast<u64>(__data.size()) < maskOffset + __height * maskRowSize) {
    throw XError(XErrorType::InvalidData,
                 "Invalid data in cursor entry, "
                 "expected more mask data, maskOffset: " +
                     QString::number(maskOffset) + ", expected: " +
                     QString::number(maskOffset + __height * maskRowSize));
  }
  const u8* maskData = reinterpret_cast<const u8*>(__data.data() + maskOffset);
  QImage image(__width, __height, QImage::Format_RGBA8888);
  for (i32 y = 0; y < __height; ++y) {
    i32 bmpY = __height - 1 - y;
    const u8* pixelRow = pixelData + bmpY * pixelRowSize;
    const u8* maskRow = maskData + bmpY * maskRowSize;

    for (i32 x = 0; x < __width; ++x) {
      u8 r, g, b, a;
      if (__bitsPerPixel == 24) {
        b = pixelRow[x * 3];
        g = pixelRow[x * 3 + 1];
        r = pixelRow[x * 3 + 2];
        a = 255;
      } else {  // 32 bpp
        b = pixelRow[x * 4];
        g = pixelRow[x * 4 + 1];
        r = pixelRow[x * 4 + 2];
        a = pixelRow[x * 4 + 3];
      }
      i32 byteIndex = x / 8;
      i32 bitIndex = 7 - (x % 8);
      u8 mask = (maskRow[byteIndex] >> bitIndex) & 1;
      if (mask == 1) {
        bool inverseXOR = false;
        if (__bitsPerPixel == 24) {
          inverseXOR = (pixelRow[x * 3] > 128);
        } else {
          inverseXOR = (pixelRow[x * 4] > 128);
        }
        if (inverseXOR) {
          r = 255 - r;
          g = 255 - g;
          b = 255 - b;
          a = 255;
        } else {
          a = 0;
        }
      }
      image.setPixel(x, y, qRgba(r, g, b, a));
    }
  }
  QFileInfo fileInfo(path);
  QDir dir = fileInfo.absoluteDir();
  if (!dir.exists()) {
    if (!dir.mkpath(".")) {
      throw XError(XErrorType::CreationFailed,
                   "Failed to create directory " + dir.path());
    }
  }
  if (!image.save(path, "PNG")) {
    throw XError(XErrorType::CreationFailed, "Failed to save image to " + path);
  }
}

void BMP::save(const QString& path) const {
  QFile file(path);
  if (!file.open(QIODevice::WriteOnly)) {
    throw XError(XErrorType::CreationFailed, "Failed to open file " + path);
  }
  if (file.write(__data) == -1) {
    throw XError(XErrorType::CreationFailed, "Failed to write to file " + path);
  }
  file.close();
}

u32 BMP::bitsPerPixel() const {
  return __bitsPerPixel;
}