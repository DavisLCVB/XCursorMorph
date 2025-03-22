#include "chunk.hpp"

#include <QBuffer>
#include <QDebug>
#include <QIODevice>
#include <exceptions/xerror.hpp>

bool Chunk::read(QDataStream& stream) {
  c8 header[4];
  if (stream.readRawData(header, 4) != 4) {
    return false;
  }
  id = QString::fromLatin1(header, 4);
  stream >> size;
  if (stream.status() != QDataStream::Ok) {
    return false;
  }
  data.resize(size);
  if (stream.readRawData(data.data(), size) != size) {
    return false;
  }
  if (size % 2 == 1) {
    if (stream.skipRawData(1) != 1) {
      return false;
    }
  }
  return true;
}

void Chunk::parseSubChunks(const QString& headerId) {
  if (data.size() <= 4) {
    return;
  }
  QString chunkHeaderId = QString::fromLatin1(data.data(), 4);
  if (headerId != "--none" && chunkHeaderId != headerId) {
    throw XError(XErrorType::InvalidData,
                 "Invalid subchunk header: " + headerId);
  }
  QByteArray subData = data.mid(4);
  QBuffer buffer(&subData);
  buffer.open(QIODevice::ReadOnly);
  QDataStream stream(&buffer);
  stream.setByteOrder(QDataStream::LittleEndian);
  while (!stream.atEnd()) {
    Chunk chunk;
    if (!chunk.read(stream)) {
      break;
    }
    children.append(chunk);
  }
}