#include "select-folder-screen.hpp"
#include <views/utils/colors.hpp>
#include "ui_select-folder-screen.h"

#include <QGraphicsDropShadowEffect>
#include <views/utils/colors.hpp>

SelectFolderScreen::SelectFolderScreen(QWidget* parent)
    : QWidget(parent), ui(new Ui::SelectFolderScreen) {
  ui->setupUi(this);
  auto pallete = ui->FolderInput->palette();
  pallete.setColor(QPalette::PlaceholderText, Colors::placeholderText);
  ui->FolderInput->setPalette(pallete);
  ui->AcceptButton->setFocus();
  QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
  shadow->setBlurRadius(5);
  shadow->setOffset(0, 4);
  shadow->setColor(Colors::buttonColor);
  ui->AcceptButton->setGraphicsEffect(shadow);
  QGraphicsDropShadowEffect* shadow2 = new QGraphicsDropShadowEffect(this);
  shadow2->setBlurRadius(5);
  shadow2->setOffset(0, 4);
  shadow2->setColor(Colors::buttonColor);
  ui->SearchButton->setGraphicsEffect(shadow2);
}

SelectFolderScreen::~SelectFolderScreen() {
  delete ui;
}

QLineEdit* SelectFolderScreen::FolderInput() const {
  return ui->FolderInput;
}

QPushButton* SelectFolderScreen::AcceptButton() const {
  return ui->AcceptButton;
}

QPushButton* SelectFolderScreen::SearchButton() const {
  return ui->SearchButton;
}

QLabel* SelectFolderScreen::ErrorLabel() const {
  return ui->ErrorLabel;
}