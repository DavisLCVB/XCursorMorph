#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <QDataStream>
#include <QVector>
#include <types.hpp>

class Chunk {
 public:
  QString id;
  u32 size{0};
  QByteArray data;
  QVector<Chunk> children;

  Chunk() = default;

  bool read(QDataStream& stream);
  void parseSubChunks();
};

#endif  // CHUNK_HPP