#ifndef SCAN_STAGE_SCREEN_HPP
#define SCAN_STAGE_SCREEN_HPP

#include <QWidget>

namespace Ui {
class ScanStageScreen;
}

class ScanStageScreen : public QWidget {
  Q_OBJECT

 public:
  explicit ScanStageScreen(QWidget* parent = nullptr);
  ~ScanStageScreen();

 private:
  Ui::ScanStageScreen* ui;
};

#endif  // SCAN_STAGE_SCREEN_HPP
