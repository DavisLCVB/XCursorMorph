#ifndef MAIN_CONTROLLER_HPP
#define MAIN_CONTROLLER_HPP

#include <QMap>
#include <QObject>
#include <QString>
#include <controllers/base-controller.hpp>
#include <controllers/screens/select-folder-controller.hpp>
#include <views/main-window.hpp>

class MainController final : public QObject {
  Q_OBJECT
 public:
  explicit MainController(MainWindow* sub, QObject* parent = nullptr);

 private slots:
  void onFolderSelected();
  void onFinishScan();

 private:
  MainWindow* __sub;
  SelectFolderController* __selectFolderController;
  QMap<QString, IBaseController*> __stagesControllers;

  void __initStages();
  void __saveState();
  void __loadState();
};

#endif  // MAIN_CONTROLLER_HPP