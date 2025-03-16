#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QLineEdit>
#include <QMainWindow>
#include <QStackedWidget>
#include <views/components/header-component.hpp>
#include <views/screens/main-content-screen.hpp>
#include <views/screens/select-folder-screen.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QStackedWidget* ContentStack() const;
  SelectFolderScreen* SelectFolder() const;
  MainContentScreen* MainContent() const;
  HeaderComponent* Header() const;
  QWidget* Central() const;

 private:
  Ui::MainWindow* ui;
  bool __isMooving = false;
  QPoint __lastPosition;

 private slots:
  void minimizeWindow();
  void maximizeRestoreWindow();
  void closeWindow();
};

#endif  // MAIN_WINDOW_HPP
