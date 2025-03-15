#include "scan-stage-screen.hpp"
#include "ui_scan-stage-screen.h"

#include <QGraphicsDropShadowEffect>
#include <views/utils/colors.hpp>

ScanStageScreen::ScanStageScreen(QWidget* parent)
    : QWidget(parent), ui(new Ui::ScanStageScreen) {
  ui->setupUi(this);
  QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
  shadow->setBlurRadius(5);
  shadow->setOffset(0, 4);
  shadow->setColor(Colors::buttonColor);
  ui->ScanButton->setGraphicsEffect(shadow);
}

ScanStageScreen::~ScanStageScreen() {
  delete ui;
}
