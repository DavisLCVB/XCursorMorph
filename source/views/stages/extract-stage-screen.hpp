#ifndef EXTRACT_STAGE_SCREEN_HPP
#define EXTRACT_STAGE_SCREEN_HPP

#include <QPushButton>
#include <QWidget>

namespace Ui {
class ExtractStageScreen;
}

class ExtractStageScreen : public QWidget {
  Q_OBJECT

 public:
  explicit ExtractStageScreen(QWidget* parent = nullptr);
  ~ExtractStageScreen();
  QPushButton* ExtractButton();
  void setResult(bool result);

 private:
  Ui::ExtractStageScreen* ui;
};

#endif  // EXTRACT_STAGE_SCREEN_HPP
