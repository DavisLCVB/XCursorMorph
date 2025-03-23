#ifndef ANI_HPP
#define ANI_HPP

#include <QByteArray>
#include <QString>
#include <models/formats/cur-ico.hpp>
#include <models/structs/chunk.hpp>

class ANIFrame {
 public:
  ANIFrame(const CUR_ICO& entry);
  ~ANIFrame() = default;
  void setFrameData(const CUR_ICO& data);
  void setRate(const u32 rate);
  void setSequence(const u32 sequence);
  u32 rate() const;
  u32 sequence() const;
  CUR_ICO frameData() const;
  QVector<CUR_ICOEntry> entries() const;

 private:
  u32 __rate{0};
  u32 __sequence{0};
  CUR_ICO __frameData;
};

class ANI {
 public:
  static ANI fromData(const QByteArray& data);
  static ANI fromFile(const QString& path);
  QVector<ANIFrame> frames() const;

 private:
  ANI(const QByteArray& data);
  void __readRiffChunk();
  void __readListChunk(Chunk& chunk);
  void __readAnihChunk(Chunk& chunk);
  void __readSeqChunk(Chunk& chunk);
  void __readRateChunk(Chunk& chunk);
  QByteArray __data;
  QVector<CUR_ICO> __framesData;
  u32 __numSteps = 0;
  u32 __bpp = 0;
  u32 __displayRate = 0;
  u32 __flags = 0;
  bool __anihChunkFound = false;
  bool __seqChunkFound = false;
  bool __rateChunkFound = false;
  QVector<u32> __seq;
  QVector<u32> __rate;
};

#endif  // ANI_HPP