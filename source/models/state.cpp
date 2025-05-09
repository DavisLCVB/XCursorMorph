#include "state.hpp"
#include <QPointer>
#include <mutex>

QPointer<State> State::__instance = nullptr;

State& State::instance() {
  static std::once_flag flag;
  std::call_once(flag, []() { __instance = new State(); });
  return *__instance;
}

void State::setWorkingDirectory(const QString& workingDirectory) {
  __workingDirectory = workingDirectory;
  __buildDirectory = workingDirectory + "/Build";
}

QString State::workingDirectory() const {
  return __workingDirectory;
}

QString State::buildDirectory() const {
  return __buildDirectory;
}

QString State::cacheDirectory() const {
  return __buildDirectory + "/.xcursor-morph";
}

QString State::staticCursorsFolder(FolderType folderType) const {
  switch (folderType) {
    case FolderType::CurFolder:
      return __buildDirectory + "/Static/cur";
    case FolderType::PngFolder:
      return __buildDirectory + "/Static/png";
    case FolderType::BaseFolder:
      return __buildDirectory + "/Static";
    default:
      return "";
  }
}

QString State::animatedCursorsFolder(FolderType folderType) const {
  switch (folderType) {
    case FolderType::PngFolder:
      return __buildDirectory + "/Animated/png";
    case FolderType::AniFolder:
      return __buildDirectory + "/Animated/ani";
    case FolderType::BaseFolder:
      return __buildDirectory + "/Animated";
    default:
      return "";
  }
}

void State::setCursors(const QVector<QString>& cursors) {
  __staticCursors.clear();
  __animatedCursors.clear();
  for (const auto& cursor : cursors) {
    if (cursor.endsWith(".cur")) {
      __staticCursors.push_back(StaticCursor::fromFile(cursor));
    } else if (cursor.endsWith(".ani")) {
      __animatedCursors.push_back(AnimatedCursor::fromFile(cursor));
    }
  }
}

void State::setPhase(StatePhases phase) {
  __currentPhase = phase;
}

StatePhases State::phase() const {
  return __currentPhase;
}

QString State::phaseString() const {
  switch (__currentPhase) {
    case StatePhases::Scan:
      return "scan";
    case StatePhases::Extract:
      return "extract";
    case StatePhases::Edit:
      return "edit";
    default:
      return "";
  }
}

QVector<StaticCursor> State::staticCursors() const {
  return __staticCursors;
}

QVector<AnimatedCursor> State::animatedCursors() const {
  return __animatedCursors;
}