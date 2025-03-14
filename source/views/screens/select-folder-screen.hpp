#ifndef SELECT_FOLDER_SCREEN_HPP
#define SELECT_FOLDER_SCREEN_HPP

#include <QWidget>

namespace Ui {
class SelectFolderScreen;
}

class SelectFolderScreen : public QWidget {
  Q_OBJECT

 public:
  explicit SelectFolderScreen(QWidget* parent = nullptr);
  ~SelectFolderScreen();

 private:
  Ui::SelectFolderScreen* ui;
};

#endif  // SELECT_FOLDER_SCREEN_HPP
