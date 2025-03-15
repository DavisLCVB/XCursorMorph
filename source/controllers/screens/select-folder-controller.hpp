#ifndef SELECT_FOLDER_CONTROLLER_HPP
#define SELECT_FOLDER_CONTROLLER_HPP

#include <QString>
#include <views/screens/select-folder-screen.hpp>

class SelectFolderController final : public QObject {
  Q_OBJECT
 public:
  explicit SelectFolderController(SelectFolderScreen* sub,
                                  QObject* parent = nullptr);
 private slots:
  void onChangeFolderInput(const QString& text);
  void onPressSearchButton();
  void onPressAcceptButton();

 private:
  SelectFolderScreen* __sub;
  static QString __folderInputErrorStyle;
  static QString __folderInputStyle;
  QString __folderPath;

 signals:
  void folderSelected();
};

#endif  // SELECT_FOLDER_CONTROLLER_HPP