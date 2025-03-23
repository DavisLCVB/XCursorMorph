#include "animated-cursor.hpp"

#include <QFileInfo>
#include <QUuid>
#include <models/state.hpp>

QMap<QString, QString> AnimatedCursor::__cache;

AnimatedCursor AnimatedCursor::fromFile(const QString& path) {
  ANI ani = ANI::fromFile(path);
  auto aniCur = AnimatedCursor(ani);
  aniCur.__name = QFileInfo(path).fileName().split('.').first();
  aniCur.__path = path;
  if (!__cache.contains(path)) {
    aniCur.__id = QUuid::createUuid().toString().remove("{").remove("}");
    __cache[path] = aniCur.__id;
  } else {
    aniCur.__id = __cache[path];
  }
  return aniCur;
}

AnimatedCursor::AnimatedCursor(const ANI& ani) : __data(ani) {}

QVector<QString> AnimatedCursor::getPrev() const {
  QVector<QString> paths;
  const QString prefix = State::instance().cacheDirectory() + "/" +
                         __cache[__path] + "/" + __cache[__path] + "-";
  for (const auto& frame : __data.frames()) {
    const QString path = prefix + QString::number(frame.sequence()) + ".png";
    paths.push_back(path);
    if (QFileInfo(path).exists()) {
      continue;
    }
    frame.entries().back().toPng(path);
  }
  return paths;
}

QVector<ANIFrame> AnimatedCursor::frames() const {
  return __data.frames();
}

QString AnimatedCursor::name() const {
  return __name;
}

QString AnimatedCursor::path() const {
  return __path;
}

QString AnimatedCursor::id() const {
  return __id;
}

QMap<QString, QString> AnimatedCursor::cache() {
  return __cache;
}

void AnimatedCursor::setCache(const QMap<QString, QString>& cache) {
  __cache = cache;
}

void AnimatedCursor::clearCache() {
  __cache.clear();
}