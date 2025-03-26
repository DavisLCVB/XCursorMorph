#include "main-content-screen.hpp"
#include "ui_main-content-screen.h"

#include <QDebug>
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
  connect(ui->Stage1, &StageButton::pressed, [this]() {
    qDebug() << "Stage1 button pressed";
    ui->StagesStack->setCurrentIndex(0);
  });
  connect(ui->Stage2, &StageButton::pressed, [this]() {
    qDebug() << "Stage2 button pressed";
    ui->StagesStack->setCurrentIndex(1);
  });
  connect(ui->Stage3, &StageButton::pressed, [this]() {
    qDebug() << "Stage3 button pressed";
    ui->StagesStack->setCurrentIndex(2);
  });
  connect(ui->Stage4, &StageButton::pressed, [this]() {
    qDebug() << "Stage4 button pressed";
    ui->StagesStack->setCurrentIndex(3);
  });
  connect(ui->Stage5, &StageButton::pressed, [this]() {
    qDebug() << "Stage5 button pressed";
    ui->StagesStack->setCurrentIndex(4);
  });
  connect(ui->Stage6, &StageButton::pressed, [this]() {
    qDebug() << "Stage6 button pressed";
    ui->StagesStack->setCurrentIndex(5);
  });
  connect(ui->Stage7, &StageButton::pressed, [this]() {
    qDebug() << "Stage7 button pressed";
    ui->StagesStack->setCurrentIndex(6);
  });
}

MainContentScreen::~MainContentScreen() {
  delete ui;
}

ScanStageScreen* MainContentScreen::Stage1Screen() const {
  return ui->Stage1Screen;
}

ExtractStageScreen* MainContentScreen::Stage2Screen() const {
  return ui->Stage2Screen;
}

void MainContentScreen::setStageButtonState(int index, StageButtonState state) {
  __changeButtonState(index, state);
  StageButtonState prevStage;
  switch (state) {
    case StageButtonState::Current:
      prevStage = StageButtonState::Done;
      break;
    case StageButtonState::Undone:
      prevStage = StageButtonState::Current;
      break;
    default:
      prevStage = StageButtonState::Done;
      break;
  }
  for (int i = index - 1; i > 0; i--) {
    __changeButtonState(i, prevStage);
  }
}

void MainContentScreen::__changeButtonState(int index, StageButtonState state) {
  switch (index) {
    case 1:
      ui->Stage1->setState(state);
      break;
    case 2:
      ui->Stage2->setState(state);
      break;
    case 3:
      ui->Stage3->setState(state);
      break;
    case 4:
      ui->Stage4->setState(state);
      break;
    case 5:
      ui->Stage5->setState(state);
      break;
    case 6:
      ui->Stage6->setState(state);
      break;
    case 7:
      ui->Stage7->setState(state);
      break;
    default:
      break;
  }
}