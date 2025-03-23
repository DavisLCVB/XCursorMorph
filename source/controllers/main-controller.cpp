#include "main-controller.hpp"

#include <QFile>
#include <QJsonDocument>
#include <controllers/stages/scan-stage-controller.hpp>
#include <metadata/meta.hpp>
#include <models/animated-cursor.hpp>
#include <models/state.hpp>
#include <models/static-cursor.hpp>

MainController::MainController(MainWindow* sub, QObject* parent)
    : QObject(parent), __sub(sub) {
  __selectFolderController = new SelectFolderController(__sub->SelectFolder());
  connect(__selectFolderController, &SelectFolderController::folderSelected,
          this, &MainController::onFolderSelected);
  __sub->Header()->setTitle(Meta::name + "  -  v" + Meta::version);
  __initStages();
}

void MainController::onFolderSelected() {
  __sub->ContentStack()->setCurrentIndex(1);
  State::instance().setPhase(StatePhases::Scan);
  __sub->MainContent()->setStageButtonState(1, StageButtonState::Current);
  __loadState();
}

void MainController::__initStages() {
  auto scanStageController =
      new ScanStageController(__sub->MainContent()->Stage1Screen());
  __stagesControllers["Scan"] = scanStageController;
  connect(scanStageController, &ScanStageController::finishScan, this,
          &MainController::onFinishScan);
}

void MainController::onFinishScan() {
  State::instance().setPhase(StatePhases::Extract);
  __sub->MainContent()->setStageButtonState(2, StageButtonState::Current);
  __saveState();
}

void MainController::__saveState() {
  QJsonDocument doc;
  auto staticMap = StaticCursor::cache();
  auto animatedMap = AnimatedCursor::cache();
  QJsonObject cache;
  for (const auto& [key, value] : staticMap.asKeyValueRange()) {
    cache[key] = value;
  }
  for (const auto& [key, value] : animatedMap.asKeyValueRange()) {
    cache[key] = value;
  }
  QJsonObject root;
  root["cache"] = cache;
  root["current_state"] = State::instance().phaseString();
  doc.setObject(root);
  const QString cacheJsonPath =
      State::instance().cacheDirectory() + "/xcursor-morph.cache.json";
  QFile file(cacheJsonPath);
  if (file.open(QIODevice::WriteOnly)) {
    file.write(doc.toJson());
    file.close();
  }
}

void MainController::__loadState() {
  const QString cacheJsonPath =
      State::instance().cacheDirectory() + "/xcursor-morph.cache.json";
  QFile file(cacheJsonPath);
  if (!file.exists()) {
    return;
  }
  if (!file.open(QIODevice::ReadOnly)) {
    return;
  }
  QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
  file.close();
  const QJsonObject root = doc.object();
  const QJsonObject cache = root["cache"].toObject();
  QMap<QString, QString> staticCache;
  QMap<QString, QString> animatedCache;
  for (const auto& key : cache.keys()) {
    const QString value = cache[key].toString();
    if (key.endsWith(".cur")) {
      staticCache[key] = value;
    } else if (key.endsWith(".ani")) {
      animatedCache[key] = value;
    }
  }
  StaticCursor::setCache(staticCache);
  AnimatedCursor::setCache(animatedCache);
  const QString currentState = root["current_state"].toString();
  if (currentState == "scan") {
    State::instance().setPhase(StatePhases::Scan);
  } else if (currentState == "extract") {
    State::instance().setPhase(StatePhases::Extract);
  }
  qDebug() << "Loaded cache";
}