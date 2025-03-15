#ifndef SELECT_FOLDER_SCREEN_HPP
#define SELECT_FOLDER_SCREEN_HPP

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

namespace Ui {
class SelectFolderScreen;
}

class SelectFolderScreen : public QWidget {
  Q_OBJECT

 public:
  explicit SelectFolderScreen(QWidget* parent = nullptr);
  ~SelectFolderScreen();
  QLineEdit* FolderInput() const;
  QPushButton* AcceptButton() const;
  QPushButton* SearchButton() const;
  QLabel* ErrorLabel() const;

 private:
  Ui::SelectFolderScreen* ui;
};

#endif  // SELECT_FOLDER_SCREEN_HPP
