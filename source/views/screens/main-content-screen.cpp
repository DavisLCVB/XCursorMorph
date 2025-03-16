#include "main-content-screen.hpp"
#include "ui_main-content-screen.h"

#include <views/components/stage-button.hpp>

MainContentScreen::MainContentScreen(QWidget* parent)
    : QWidget(parent), ui(new Ui::MainContentScreen) {
  ui->setupUi(this);
  ui->Stage1->setText("Scan");
  ui->Stage2->setText("Extract");
  ui->Stage3->setText("Edit");
  ui->Stage4->setText("Build");
  ui->Stage5->setText("Configure");
  ui->Stage6->setText("Linking");
  ui->Stage7->setText("Finish");
  ui->Stage1->setState(StageButtonState::Current);
}

MainContentScreen::~MainContentScreen() {
  delete ui;
}

ScanStageScreen* MainContentScreen::Stage1Screen() const {
  return ui->Stage1Screen;
}