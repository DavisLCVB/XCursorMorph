#ifndef MAIN_CONTENT_SCREEN_HPP
#define MAIN_CONTENT_SCREEN_HPP

#include <QListWidgetItem>
#include <QWidget>
#include <views/stages/scan-stage-screen.hpp>

namespace Ui {
class MainContentScreen;
}

class MainContentScreen : public QWidget {
  Q_OBJECT

 public:
  explicit MainContentScreen(QWidget* parent = nullptr);
  ~MainContentScreen();
  ScanStageScreen* Stage1Screen() const;

 private:
  Ui::MainContentScreen* ui;
  QVector<QListWidgetItem*> __stageButtons;
};

#endif  // MAIN_CONTENT_SCREEN_HPP
