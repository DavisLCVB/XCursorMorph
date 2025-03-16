#include "scan-stage-controller.hpp"

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QThread>
#include <models/state.hpp>

ScanStageController::ScanStageController(ScanStageScreen* sub, QObject* parent)
    : QObject(parent), BaseController(sub) {
  connect(__sub->ScanButton(), &QPushButton::pressed, this,
          &ScanStageController::onPressScanButton);
}

void ScanStageController::onPressScanButton() {
  __sub->onScanButtonPressed();
  QPointer<ScanWorker> worker = new ScanWorker();
  QThread* scanThread = new QThread();
  worker->moveToThread(scanThread);
  connect(scanThread, &QThread::started, worker, &ScanWorker::run);
  connect(worker, &ScanWorker::finish, this,
          [=, this](const QVector<QString>& cursors) {
            scanThread->quit();
            scanThread->wait();
            __finishScan(cursors);
          });
  scanThread->start();
}

void ScanStageController::__finishScan(const QVector<QString>& cursors) {
  __sub->setCursors(cursors);
  __sub->resetScanButton();
}

ScanWorker::ScanWorker(QObject* parent) : QObject(parent) {}

void ScanWorker::run() {
  QVector<QString> paths;
  QString workingDir = State::instance().workingDirectory();
  QString buildDir = State::instance().buildDirectory();
  __scanRecursive(paths, workingDir, buildDir);
  emit finish(paths);
}

void ScanWorker::__scanRecursive(QVector<QString>& cursorPaths,
                                 const QString& currentPath,
                                 const QString& avoid) {
  if (currentPath == avoid) {
    return;
  }
  const QFileInfo fileInfo(currentPath);
  if (fileInfo.isDir()) {
    const auto files =
        QDir(currentPath)
            .entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    for (const auto& file : files) {
      __scanRecursive(cursorPaths, file.absoluteFilePath(), avoid);
    }
  } else {
    const QString suffix = fileInfo.suffix();
    if (suffix == "cur" || suffix == "ani") {
      cursorPaths.push_back(currentPath);
    }
  }
}