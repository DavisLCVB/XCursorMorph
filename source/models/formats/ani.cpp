#include "ani.hpp"

#include <QDataStream>
#include <QFile>
#include <exceptions/xerror.hpp>
#include <models/structs/serializer.hpp>
#include <types.hpp>

ANIFrame::ANIFrame(const CUR_ICO& entry) : __frameData(entry) {}

void ANIFrame::setFrameData(const CUR_ICO& data) {
  __frameData = data;
}

void ANIFrame::setRate(const u32 rate) {
  __rate = rate;
}

void ANIFrame::setSequence(const u32 sequence) {
  __sequence = sequence;
}

u32 ANIFrame::rate() const {
  return __rate;
}

u32 ANIFrame::sequence() const {
  return __sequence;
}

CUR_ICO ANIFrame::frameData() const {
  return __frameData;
}

ANI ANI::fromData(const QByteArray& data) {
  return ANI(data);
}

ANI ANI::fromFile(const QString& path) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    throw XError(XErrorType::FileNotOpened, "Failed to open file, " + path);
  }
  return ANI(file.readAll());
}

ANI::ANI(const QByteArray& data) : __data(data) {
  __readRiffChunk();
}

void ANI::__readRiffChunk() {
  QDataStream stream(__data);
  stream.setByteOrder(QDataStream::LittleEndian);
  Chunk riff = Chunk();
  riff.read(stream);
  if (riff.id != "RIFF") {
    throw XError::invalidData("RIFF chunk id", riff.id, "RIFF");
  }
  riff.parseSubChunks("ACON");
  for (auto& chunk : riff.children) {
    if (chunk.id == "LIST") {
      __readListChunk(chunk);
    }
    if (chunk.id == "anih") {
      __readAnihChunk(chunk);
    }
    if (chunk.id == "seq ") {
      __readSeqChunk(chunk);
    }
    if (chunk.id == "rate") {
      __readRateChunk(chunk);
    }
  }
}

void ANI::__readListChunk(Chunk& chunk) {
  chunk.parseSubChunks("fram");
  for (const auto& subChunk : chunk.children) {
    auto cursor = CUR_ICO::fromData(subChunk.data);
    __framesData.push_back(cursor);
  }
}

void ANI::__readAnihChunk(Chunk& chunk) {
  QByteArray data = chunk.data;
  QDataStream stream(&data, QIODevice::ReadOnly);
  stream.setByteOrder(QDataStream::LittleEndian);
  const auto [headerSize, numFrames, numSteps, _0, _1, bitCount, _2,
              displayRate, flags] =
      Serializer::unpack<u32, u32, u32, u32, u32, u32, u32, u32, u32>(data);
  if (headerSize != 36) {
    throw XError::invalidData("anih header size", QString::number(headerSize),
                              "36");
  }
  if (__framesData.size() > 0 && numFrames != __framesData.size()) {
    throw XError::invalidData("anih numFrames", QString::number(numFrames),
                              QString::number(__framesData.size()));
  }
  __numSteps = numSteps;
  __anihChunkFound = true;
  __bpp = bitCount;
  __displayRate = displayRate;
  __flags = flags;
  if ((flags & 0x1) == 0) {
    throw XError::notSupported("Raw data in animated cursor");
  }
}

void ANI::__readSeqChunk(Chunk& chunk) {
  QByteArray data = chunk.data;
  QDataStream stream(&data, QIODevice::ReadOnly);
  stream.setByteOrder(QDataStream::LittleEndian);
  for (u32 i{0}; i < __numSteps; i++) {
    u32 seq;
    stream >> seq;
    __seq.push_back(seq);
  }
  __seqChunkFound = true;
}

void ANI::__readRateChunk(Chunk& chunk) {
  QByteArray data = chunk.data;
  QDataStream stream(&data, QIODevice::ReadOnly);
  stream.setByteOrder(QDataStream::LittleEndian);
  for (u32 i{0}; i < __numSteps; i++) {
    u32 rate;
    stream >> rate;
    __rate.push_back(rate);
  }
  __rateChunkFound = true;
}

QVector<ANIFrame> ANI::frames() const {
  QVector<ANIFrame> frames;
  for (i64 i = 0; i < __framesData.size(); ++i) {
    const auto& frame = __framesData[i];
    auto aniFrame = ANIFrame(frame);
    if (__rateChunkFound) {
      const auto& rate = __rate[i];
      aniFrame.setRate(rate);
    } else {
      aniFrame.setRate(75);
    }
    if (__seqChunkFound) {
      const auto& seq = __seq[i];
      aniFrame.setSequence(seq);
    } else {
      aniFrame.setSequence(i);
    }
    aniFrame.setFrameData(frame);
    frames.push_back(aniFrame);
  }
  std::sort(frames.begin(), frames.end(),
            [](const ANIFrame& a, const ANIFrame& b) {
              return a.sequence() < b.sequence();
            });
  return frames;
}

QVector<CUR_ICOEntry> ANIFrame::entries() const {
  return __frameData.entries();
}