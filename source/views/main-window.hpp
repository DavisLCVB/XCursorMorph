#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

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
