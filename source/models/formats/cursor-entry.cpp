#include "cursor-entry.hpp"

#include <QDir>
#include <QFileInfo>
#include <QImage>
#include <exceptions/xerror.hpp>
#include <models/structs/serializer.hpp>

void CursorEntry::setData(const QByteArray& data) {
  __imgData = data;
  __readData();
}

void CursorEntry::toPng(const QString& path) const {
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
  if (static_cast<u64>(__imgData.size()) <
      pixelDataOffset + __height * pixelRowSize) {
    throw XError(
        XErrorType::InvalidData,
        "Invalid data in cursor entry, "
        "expected more pixel data, pixelDataOffset: " +
            QString::number(pixelDataOffset) + ", expected: " +
            QString::number(pixelDataOffset + __height * pixelRowSize));
  }
  const u8* pixelData =
      reinterpret_cast<const u8*>(__imgData.data() + pixelDataOffset);
  const u64 maskOffset = pixelDataOffset + __height * pixelRowSize;
  const u64 maskRowSize = ((__width + 31) / 32) * 4;
  if (static_cast<u64>(__imgData.size()) <
      maskOffset + __height * maskRowSize) {
    throw XError(XErrorType::InvalidData,
                 "Invalid data in cursor entry, "
                 "expected more mask data, maskOffset: " +
                     QString::number(maskOffset) + ", expected: " +
                     QString::number(maskOffset + __height * maskRowSize));
  }
  const u8* maskData =
      reinterpret_cast<const u8*>(__imgData.data() + maskOffset);
  QImage image(__width, __height, QImage::Format_RGBA8888);
  for (int y = 0; y < __height; ++y) {
    int bmpY = __height - 1 - y;
    const uchar* pixelRow = pixelData + bmpY * pixelRowSize;
    const uchar* maskRow = maskData + bmpY * maskRowSize;

    for (int x = 0; x < __width; ++x) {
      uchar r, g, b, a;
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
      int byteIndex = x / 8;
      int bitIndex = 7 - (x % 8);
      uchar mask = (maskRow[byteIndex] >> bitIndex) & 1;
      if (mask == 1) {
        a = 0;
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

void CursorEntry::__readData() {
  auto [_0, w, h, _1, bpp, _2, imgSize, _3, _4, _5, _6] =
      Serializer::unpack<u32, u32, u32, u16, u16, u32, u32, u32, u32, u32, u32>(
          __imgData);
  if (__width != w || __height * 2 != h ||
      __imgDataSize - __dataHeaderSize != imgSize) {
    throw XError(XErrorType::InvalidData,
                 "Invalid data in cursor entry, "
                 "header does not match image data");
  }
  constexpr u16 magic = 0x4D42;
  const u32 fileSize = 54 + __imgDataSize;
  constexpr u32 reserved = 0;
  constexpr u32 offset = 54;
  auto newData =
      Serializer::pack(std::tuple{magic, fileSize, reserved, offset});
  newData += __imgData.mid(0);
  __imgDataSize = imgSize;
  __bitsPerPixel = bpp;
  __imgData = newData;
}

u8 CursorEntry::width() const {
  return __width;
}

u8 CursorEntry::height() const {
  return __height;
}

u16 CursorEntry::hotspotX() const {
  return __hotspotX;
}

u16 CursorEntry::hotspotY() const {
  return __hotspotY;
}

u32 CursorEntry::imgDataSize() const {
  return __imgDataSize;
}

u32 CursorEntry::imgDataOffset() const {
  return __imgDataOffset;
}

u32 CursorEntry::bytesPerPixel() const {
  return __bitsPerPixel;
}

QByteArray CursorEntry::imgData() const {
  return __imgData;
}
