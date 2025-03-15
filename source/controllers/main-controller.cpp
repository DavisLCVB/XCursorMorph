#include "main-controller.hpp"

#include <metadata/meta.hpp>

MainController::MainController(MainWindow* sub, QObject* parent)
    : QObject(parent), __sub(sub) {
  __selectFolderController = new SelectFolderController(__sub->SelectFolder());
  connect(__selectFolderController, &SelectFolderController::folderSelected,
          this, &MainController::onFolderSelected);
  __sub->Header()->setTitle(Meta::name + "  -  v" + Meta::version);
}

void MainController::onFolderSelected() {
  __sub->ContentStack()->setCurrentIndex(1);
}