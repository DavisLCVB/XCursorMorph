#ifndef MAIN_CONTENT_SCREEN_HPP
#define MAIN_CONTENT_SCREEN_HPP

#include <QWidget>

namespace Ui {
class MainContentScreen;
}

class MainContentScreen : public QWidget {
  Q_OBJECT

 public:
  explicit MainContentScreen(QWidget* parent = nullptr);
  ~MainContentScreen();

 private:
  Ui::MainContentScreen* ui;
};

#endif  // MAIN_CONTENT_SCREEN_HPP
