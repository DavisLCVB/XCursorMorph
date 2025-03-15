#include "main-content-screen.hpp"
#include "ui_main-content-screen.h"

#include <views/components/stage-button.hpp>

MainContentScreen::MainContentScreen(QWidget* parent)
    : QWidget(parent), ui(new Ui::MainContentScreen) {
  ui->setupUi(this);
  ui->Stage1->setText("Scan Stage");
  ui->Stage1->setState(StageButtonState::Done);
  ui->Stage2->setText("Extract Stage");
  ui->Stage2->setState(StageButtonState::Current);
  ui->Stage3->setText("Edit Stage");
  ui->Stage4->setText("Build Stage");
  ui->Stage5->setText("Configure Stage");
  ui->Stage6->setText("Linking Stage");
  ui->Stage7->setText("Finish Stage");
}

MainContentScreen::~MainContentScreen() {
  delete ui;
}
