#include "main-controller.hpp"

#include <controllers/stages/scan-stage-controller.hpp>
#include <metadata/meta.hpp>

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
}

void MainController::__initStages() {
  __stagesControllers["Scan"] =
      new ScanStageController(__sub->MainContent()->Stage1Screen());
}