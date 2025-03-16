#ifndef STATE_HPP
#define STATE_HPP

#include <QObject>
#include <QPointer>

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

 private:
  static QPointer<State> __instance;
  State() = default;
  ~State() = default;
  QString __workingDirectory;
  QString __buildDirectory;
};

#endif  // STATE_HPP