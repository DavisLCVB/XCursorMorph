#include "animated-cursor.hpp"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <exceptions/xerror.hpp>
#include <models/chunk.hpp>

AnimatedCursor AnimatedCursor::fromData(const QByteArray& data) {
  return AnimatedCursor(data, "no-path");
}

AnimatedCursor AnimatedCursor::fromFile(const QString& path) {
  QFile file(path);
  if (!file.exists()) {
    throw new XError(XErrorType::FileNotFound, "File not found: " + path);
  }
  if (!file.open(QIODevice::ReadOnly)) {
    throw new XError(XErrorType::FileNotOpened, "Could not open file: " + path);
  }
  return AnimatedCursor(file.readAll(), path);
}

AnimatedCursor::AnimatedCursor(const QByteArray& data, const QString& path)
    : __data(data), __path(path) {
  __readChunks();
}

void AnimatedCursor::__readChunks() {
  auto stream = QDataStream(&__data, QIODevice::ReadOnly);
  stream.setByteOrder(QDataStream::LittleEndian);
  Chunk riff;
  if (!riff.read(stream)) {
    throw XError(XErrorType::ReadError, "Error reading RIFF chunk");
  }
  if (riff.id != "RIFF") {
    throw XError(XErrorType::InvalidData,
                 "Invalid RIFF chunk, value: " + riff.id);
  }
  riff.parseSubChunks();
  for (auto& chunk : riff.children) {
    if (chunk.id == "LIST") {
      chunk.parseSubChunks();
      for (const auto& subChunk : chunk.children) {
        auto cursor = StaticCursor::fromData(subChunk.data);
        __frames.push_back(cursor);
      }
    }
  }
}

const QVector<StaticCursor>& AnimatedCursor::frames() const {
  return __frames;
}