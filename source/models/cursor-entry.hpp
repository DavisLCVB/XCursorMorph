#ifndef ENTRY_INFO_H
#define ENTRY_INFO_H

#include <QByteArray>
#include <types.hpp>

class CursorEntry {
 public:
  u8 width{0};
  u8 height{0};
  u16 hotspotX{0};
  u16 hotspotY{0};
  u32 imgDataSize{0};
  u32 imgDataOffset{0};
  QByteArray imgData;

  CursorEntry(u8 w, u8 h, u16 hx, u16 hy, u32 size, u32 off)
      : width(w),
        height(h),
        hotspotX(hx),
        hotspotY(hy),
        imgDataSize(size),
        imgDataOffset(off) {}

  void setData(const QByteArray& data);
  void toPng() const;
};

#endif  // ENTRY_INFO_H