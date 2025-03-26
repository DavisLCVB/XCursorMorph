#include "extract-stage-controller.hpp"

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QPointer>
#include <QThread>
#include <models/state.hpp>

ExtractStageController::ExtractStageController(ExtractStageScreen* sub,
                                               QObject* parent)
    : QObject(parent), BaseController(sub) {
  connect(__sub->ExtractButton(), &QPushButton::pressed, this,
          &ExtractStageController::onPressExtractButton);
}

void ExtractStageController::onPressExtractButton() {
  QPointer<ExtractWorker> worker = new ExtractWorker();
  QThread* extractThread = new QThread();
  worker->moveToThread(extractThread);
  connect(extractThread, &QThread::started, worker, &ExtractWorker::run);
  connect(worker, &ExtractWorker::finish, this, [=, this](bool result) {
    extractThread->quit();
    extractThread->wait();
    __finishExtract(result);
  });
  extractThread->start();
}

void ExtractStageController::__finishExtract(bool result) {
  __sub->setResult(result);
  emit finishExtract();
}

ExtractWorker::ExtractWorker(QObject* parent) : QObject(parent) {}

void ExtractWorker::run() {
  try {
    auto& state = State::instance();
    const auto sCursors = state.staticCursors();
    const auto aCursors = state.animatedCursors();
    for (const auto& cursor : sCursors) {
      const auto pngPath = state.staticCursorsFolder(FolderType::PngFolder) +
                           "/" + cursor.name();
      for (auto& entry : cursor.entries()) {
        const auto fullPngPath = pngPath + QString("_%1x%2.png")
                                               .arg(entry.dimension().first)
                                               .arg(entry.dimension().second);
        entry.toPng(fullPngPath);
      }
    }
    for (const auto& cursor : aCursors) {
      const auto pngPath = state.animatedCursorsFolder(FolderType::PngFolder) +
                           "/" + cursor.name() + "/" + cursor.name();
      for (auto& frame : cursor.frames()) {
        const auto partialPngPath =
            pngPath + QString("_%1").arg(frame.sequence()) + "/" +
            cursor.name() + QString("_%1").arg(frame.sequence());
        for (auto& entry : frame.entries()) {
          const auto fullPngPath =
              partialPngPath + QString("_%1x%2.png")
                                   .arg(entry.dimension().first)
                                   .arg(entry.dimension().second);
          entry.toPng(fullPngPath);
        }
      }
    }
    emit finish(true);
  } catch (...) {
    emit finish(false);
  }
}