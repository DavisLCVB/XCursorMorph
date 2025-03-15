#ifndef MAIN_CONTROLLER_HPP
#define MAIN_CONTROLLER_HPP

#include <QObject>
#include <controllers/screens/select-folder-controller.hpp>
#include <views/main-window.hpp>

class MainController final : public QObject {
  Q_OBJECT
 public:
  explicit MainController(MainWindow* sub, QObject* parent = nullptr);

 private slots:
  void onFolderSelected();

 private:
  MainWindow* __sub;
  SelectFolderController* __selectFolderController;
};

#endif  // MAIN_CONTROLLER_HPP