#ifndef STATE_HPP
#define STATE_HPP

#include <QObject>
#include <QPointer>
#include <QString>
#include <QVector>
#include <models/formats/animated-cursor.hpp>
#include <models/formats/static-cursor.hpp>

enum class FolderType {
  CurFolder,
  AniFolder,
  PngFolder,
  BaseFolder,
};

class State final : public QObject {
  Q_OBJECT
 public:
  static State& instance();

  State(const State&) = delete;
  State& operator=(const State&) = delete;

  State(State&&) = delete;
  State& operator=(State&&) = delete;

  void setWorkingDirectory(const QString& workingDirectory);
  QString workingDirectory() const;
  QString buildDirectory() const;
  QString cacheDirectory() const;
  QString staticCursorsFolder(FolderType folderType) const;
  QString animatedCursorsFolder(FolderType folderType) const;
  void setCursors(const QVector<QString>& cursors);

 private:
  static QPointer<State> __instance;
  State() = default;
  ~State() = default;
  QString __workingDirectory;
  QString __buildDirectory;
  QVector<StaticCursor> __staticCursors;
  QVector<AnimatedCursor> __animatedCursors;
};

#endif  // STATE_HPP