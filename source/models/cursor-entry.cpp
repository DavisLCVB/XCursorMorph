#include "cursor-entry.hpp"

void CursorEntry::setData(const QByteArray& data) {
  imgData = data;
}

void CursorEntry::toPng() const {}