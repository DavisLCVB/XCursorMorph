#include "main-content-screen.hpp"
#include "ui_main-content-screen.h"

MainContentScreen::MainContentScreen(QWidget* parent)
    : QWidget(parent), ui(new Ui::MainContentScreen) {
  ui->setupUi(this);
}

MainContentScreen::~MainContentScreen() {
  delete ui;
}
