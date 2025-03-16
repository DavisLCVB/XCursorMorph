#include "select-folder-controller.hpp"

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <models/state.hpp>

QString SelectFolderController::__folderInputErrorStyle =
    "QLineEdit#FolderInput{"
    "	background-color: rgb(49, 50, 68);"
    "	border-radius: 10px;"
    "	border:none;"
    "	color: #ffffff;"
    "	font-size: 12pt;"
    "	selection-background-color: rgb(94, 144, 224);"
    "	border: 1px solid #E78284;"
    "	padding: 0px 10px 0px 10px;"
    "}";

QString SelectFolderController::__folderInputStyle =
    "QLineEdit#FolderInput{"
    "	background-color: rgb(49, 50, 68);"
    "	border-radius: 10px;"
    "	border:none;"
    "	color: #ffffff;"
    "	font-size: 12pt;"
    "	selection-background-color: rgb(94, 144, 224);"
    " padding: 0px 10px 0px 10px;"
    "}";

SelectFolderController::SelectFolderController(SelectFolderScreen* sub,
                                               QObject* parent)
    : QObject(parent), __sub(sub) {
  connect(__sub->FolderInput(), &QLineEdit::textChanged, this,
          &SelectFolderController::onChangeFolderInput);
  connect(__sub->SearchButton(), &QPushButton::clicked, this,
          &SelectFolderController::onPressSearchButton);
  connect(__sub->AcceptButton(), &QPushButton::clicked, this,
          &SelectFolderController::onPressAcceptButton);
}

void SelectFolderController::onChangeFolderInput(const QString& text) {
  if (text.isEmpty()) {
    return;
  }
  QDir dir(text);
  if (!dir.exists()) {
    __sub->FolderInput()->setStyleSheet(__folderInputErrorStyle);
    __sub->ErrorLabel()->setText("Folder does not exist");
    return;
  }
  __sub->FolderInput()->setStyleSheet(__folderInputStyle);
  __sub->ErrorLabel()->setText("");
}

void SelectFolderController::onPressSearchButton() {
  QString folderPath = QFileDialog::getExistingDirectory(
      nullptr, "Select Folder", QDir::homePath());
  if (folderPath.isEmpty()) {
    __sub->ErrorLabel()->setText("Please select a folder");
    return;
  }
  __sub->FolderInput()->setText(folderPath);
  __folderPath = folderPath;
  __sub->ErrorLabel()->setText("");
}

void SelectFolderController::onPressAcceptButton() {
  QDir dir(__folderPath);
  if (!dir.exists() || __folderPath.isEmpty()) {
    __sub->FolderInput()->setStyleSheet(__folderInputErrorStyle);
    if (__folderPath.isEmpty()) {
      __sub->ErrorLabel()->setText("Please select a folder");
    } else {
      __sub->ErrorLabel()->setText("Folder does not exist");
    }
    return;
  }
  __sub->FolderInput()->setStyleSheet(__folderInputStyle);
  qInfo() << "Working on directory: " << __folderPath;
  State::instance().setWorkingDirectory(__folderPath);
  emit folderSelected();
}