#include "select-folder-screen.hpp"
#include <views/utils/colors.hpp>
#include "ui_select-folder-screen.h"

SelectFolderScreen::SelectFolderScreen(QWidget* parent)
    : QWidget(parent), ui(new Ui::SelectFolderScreen) {
  ui->setupUi(this);
  auto pallete = ui->FolderInput->palette();
  pallete.setColor(QPalette::PlaceholderText, Colors::placeholderText);
  ui->FolderInput->setPalette(pallete);
  ui->AcceptButton->setFocus();
}

SelectFolderScreen::~SelectFolderScreen() {
  delete ui;
}
