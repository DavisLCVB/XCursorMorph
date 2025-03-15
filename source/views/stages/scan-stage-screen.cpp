#include "scan-stage-screen.hpp"
#include "ui_scan-stage-screen.h"

ScanStageScreen::ScanStageScreen(QWidget* parent)
    : QWidget(parent), ui(new Ui::ScanStageScreen) {
  ui->setupUi(this);
}

ScanStageScreen::~ScanStageScreen() {
  delete ui;
}
