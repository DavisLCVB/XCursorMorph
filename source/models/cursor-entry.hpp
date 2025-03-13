#ifndef ENTRY_INFO_H
#define ENTRY_INFO_H

#include <QByteArray>
#include <types.hpp>

class CursorEntry {
 public:
  CursorEntry(u8 w, u8 h, u16 hx, u16 hy, u32 size, u32 off)
      : __width(w),
        __height(h),
        __hotspotX(hx),
        __hotspotY(hy),
        __imgDataSize(size),
        __imgDataOffset(off) {}

  void setData(const QByteArray& data);
  void toPng(const QString& path) const;

  u8 width() const;
  u8 height() const;
  u16 hotspotX() const;
  u16 hotspotY() const;
  u32 imgDataSize() const;
  u32 imgDataOffset() const;
  u32 bytesPerPixel() const;
  QByteArray imgData() const;

 private:
  u8 __width{0};
  u8 __height{0};
  u16 __hotspotX{0};
  u16 __hotspotY{0};
  u32 __imgDataSize{0};
  u32 __imgDataOffset{0};
  u32 __bitsPerPixel{0};
  QByteArray __imgData;

  void __readData();
  constexpr static u32 __dataHeaderSize{40};
  constexpr static u32 __headerEnd{14};
  constexpr static u32 __dataOffset{54};
};

#endif  // ENTRY_INFO_H