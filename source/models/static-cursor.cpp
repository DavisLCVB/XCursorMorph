#include "static-cursor.hpp"

#include <QFileInfo>
#include <QUuid>
#include <exceptions/xerror.hpp>
#include <models/state.hpp>
#include <types.hpp>

QMap<QString, QString> StaticCursor::__cache;

StaticCursor StaticCursor::fromFile(const QString& path) {
  CUR_ICO curIco = CUR_ICO::fromFile(path);
  auto sCur = StaticCursor(curIco);
  sCur.__name = QFileInfo(path).fileName().split('.').first();
  sCur.__path = path;
  if (!__cache.contains(path)) {
    sCur.__id = QUuid::createUuid().toString().remove("{").remove("}");
    __cache[path] = sCur.__id;
  } else {
    sCur.__id = __cache[path];
  }
  return sCur;
}

StaticCursor::StaticCursor(const CUR_ICO& curIco) : __data(curIco) {}

QString StaticCursor::getPrev() {
  if (__path.isEmpty()) {
    throw XError::invalidData("path", "Not empty");
  }
  if (__id.isEmpty() || !__cache.contains(__path)) {
    __id = QUuid::createUuid().toString();
    __cache[__path] = __id;
  }
  auto entry = __data.entries().back();
  const QString path =
      State::instance().cacheDirectory() + "/" + __cache[__path] + ".png";
  if (QFileInfo(path).exists()) {
    return path;
  }
  entry.toPng(path);
  return path;
}

CUR_ICO StaticCursor::data() const {
  return __data;
}

QVector<CUR_ICOEntry> StaticCursor::entries() const {
  return __data.entries();
}

QString StaticCursor::name() const {
  return __name;
}

QString StaticCursor::path() const {
  return __path;
}

QString StaticCursor::id() const {
  return __id;
}

QMap<QString, QString> StaticCursor::cache() {
  return __cache;
}

void StaticCursor::setCache(const QMap<QString, QString>& cache) {
  __cache = cache;
}

void StaticCursor::clearCache() {
  __cache.clear();
}